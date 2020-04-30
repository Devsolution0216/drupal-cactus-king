<?php

/**
 * @file
 * This file contains the Conditional Actions hooks and functions necessary to make the
 * order related entity, conditions, events, and actions work.
 */


/******************************************************************************
 * Conditional Actions Hooks                                                  *
 ******************************************************************************/

/**
 * Implementation of hook_ca_predicate().
 */
function uc_payment_ca_predicate() {
  $predicates = array();

  // Set the order status to "Payment Received" when a payment is received
  // and the balance is less than or equal to 0.
  $predicates['uc_payment_received'] = array(
    '#title' => t('Update order status on full payment'),
    '#description' => t('Only happens when a payment is entered and the balance is <= $0.00.'),
    '#class' => 'payment',
    '#trigger' => 'uc_payment_entered',
    '#status' => 1,
    '#conditions' => array(
      '#operator' => 'AND',
      '#conditions' => array(
        array(
          '#name' => 'uc_payment_condition_order_balance',
          '#title' => t('If the balance is less than or equal to $0.00.'),
          '#argument_map' => array(
            'order' => 'order',
          ),
          '#settings' => array(
            'negate' => FALSE,
            'balance_comparison' => 'less_equal',
          ),
        ),
        array(
          '#name' => 'uc_order_status_condition',
          '#title' => t('If the order status is not already Payment Received.'),
          '#argument_map' => array(
            'order' => 'order',
          ),
          '#settings' => array(
            'negate' => TRUE,
            'order_status' => 'payment_received',
          ),
        ),
      ),
    ),
    '#actions' => array(
      array(
        '#name' => 'uc_order_update_status',
        '#title' => t('Update the order status to Payment Received.'),
        '#argument_map' => array(
          'order' => 'order',
        ),
        '#settings' => array(
          'order_status' => 'payment_received',
        ),
      ),
    ),
  );

  // Set the order status to "Completed" when checkout is complete, none
  // of the products are shippable, and the balance is less than or equal to 0.
  $predicates['uc_checkout_complete_paid'] = array(
    '#title' => t('Update order status upon checkout completion with full payment'),
    '#trigger' => 'uc_checkout_complete',
    '#class' => 'payment',
    '#status' => 1,
    '#weight' => 1,
    '#conditions' => array(
      '#operator' => 'AND',
      '#conditions' => array(
        array(
          '#name' => 'uc_payment_condition_order_balance',
          '#title' => t('If the balance is less than or equal to $0.00.'),
          '#argument_map' => array(
            'order' => 'order',
          ),
          '#settings' => array(
            'negate' => FALSE,
            'balance_comparison' => 'less_equal',
          ),
        ),
        array(
          '#name' => 'uc_order_condition_is_shippable',
          '#title' => t('If the order is not shippable.'),
          '#argument_map' => array(
            'order' => 'order',
          ),
          '#settings' => array(
            'negate' => TRUE,
          ),
        ),
      ),
    ),
    '#actions' => array(
      array(
        '#name' => 'uc_order_update_status',
        '#title' => t('Update the order status to Completed.'),
        '#argument_map' => array(
          'order' => 'order',
        ),
        '#settings' => array(
          'order_status' => 'completed',
        ),
      )
    ),
  );

  return $predicates;
}

/**
 * Implementation of hook_ca_trigger().
 */
function uc_payment_ca_trigger() {
  $triggers['uc_payment_entered'] = array(
    '#title' => t('A payment gets entered for an order'),
    '#category' => t('Payment'),
    '#arguments' => array(
      'order' => array(
        '#entity' => 'uc_order',
        '#title' => t('Order'),
      ),
      'account' => array(
        '#entity' => 'user',
        '#title' => t('User'),
      ),
    ),
  );

  return $triggers;
}

/**
 * Implementation of hook_ca_condition().
 */
function uc_payment_ca_condition() {
  $conditions['uc_payment_condition_order_balance'] = array(
    '#title' => t('Check the order balance'),
    '#category' => t('Payment'),
    '#callback' => 'uc_payment_condition_order_balance',
    '#arguments' => array('order' => array('#entity' => 'uc_order')),
  );
  $conditions['uc_order_condition_payment_method'] = array(
    '#title' => t('Check the payment method'),
    '#category' => t('Order'),
    '#callback' => 'uc_order_condition_payment_method',
    '#arguments' => array('order' => array('#entity' => 'uc_order')),
  );

  return $conditions;
}


/******************************************************************************
 * Condition Callbacks and Forms                                              *
 ******************************************************************************/

// Check the current order balance.
function uc_payment_condition_order_balance($order, $settings) {
  $balance = uc_payment_balance($order);

  switch ($settings['balance_comparison']) {
    case 'less':
      return $balance < 0;
    case 'less_equal':
      return $balance <= .01;
    case 'equal':
      return $balance < .01 && $balance > -.01;
    case 'greater':
      return $balance >= .01;
  }
}

function uc_payment_condition_order_balance_form($form_state, $settings = array()) {
  $context = array(
    'revision' => 'formatted',
    'type' => 'amount',
  );
  $zero = array('!zero' => uc_price(0, $context));
  $options = array(
    'less' => t('Balance is less than !zero.', $zero),
    'less_equal' => t('Balance is less than or equal to !zero.', $zero),
    'equal' => t('Balance is equal to !zero.', $zero),
    'greater' => t('Balance is greater than !zero.', $zero),
  );

  $form['balance_comparison'] = array(
    '#type' => 'radios',
    '#title' => t('Balance comparison type'),
    '#options' => $options,
    '#default_value' => isset($settings['balance_comparison']) ? $settings['balance_comparison'] : 'equal',
  );

  return $form;
}

// Check the order payment method.
function uc_order_condition_payment_method($order, $settings) {
  return $order->payment_method == $settings['payment_method'];
}

function uc_order_condition_payment_method_form($form_state, $settings = array()) {
  foreach (_payment_method_list() as $method) {
    $options[$method['id']] = $method['title'];
  }

  $form['payment_method'] = array(
    '#type' => 'radios',
    '#title' => t('Payment method'),
    '#options' => $options,
    '#default_value' => $settings['payment_method'],
  );

  return $form;
}
