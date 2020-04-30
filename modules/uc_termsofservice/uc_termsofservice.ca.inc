<?php
// $Id: uc_termsofservice.ca.inc,v 1.1.2.1 2010/05/09 15:42:32 pcambra Exp $

/**
 * @file
 * This file contains the Conditional Actions hooks and functions necessary to
 * display the terms of service panes.
 */


/**
 * Ubercart Conditional Actions.
 */

/**
 * Implementation of hook_ca_predicate().
 */
function uc_termsofservice_ca_predicate() {

  $predicates['uc_termsofservice_display_pane'] = array(
    '#title' => t('Display pane depending on the product classes'),
    '#class' => 'uc_termsofservice',
    '#trigger' => 'uc_termsofservice_display_pane',
    '#status' => 1,
    '#conditions' => array(
      '#operator' => 'AND',
      '#conditions' => array(
        array(
          '#name' => 'uc_termsofservice_condition_product_class',
          '#title' => t('Check if there are products of the selected product classes.'),
          '#argument_map' => array(
            'cart' => 'cart',
          ),
          '#settings' => array(
            'negate' => FALSE,
            'class' => array('product'),
          ),
        ),
      ),
    ),
    '#actions' => array(),
  );

  return $predicates;
}

/**
 * Implementation of hook_ca_trigger().
 */
function uc_termsofservice_ca_trigger() {

  $triggers['uc_termsofservice_display_pane'] = array(
    '#title' => t('Display checkout or cart panes'),
    '#category' => t('Checkout'),
    '#arguments' => array(
      'cart' => array('#entity' => 'cart', '#title' => t('Cart')),
    ),
  );

  return $triggers;
}

/**
 * Implementation of hook_ca_condition().
 */
function uc_termsofservice_ca_condition() {
  $conditions['uc_termsofservice_condition_product_class'] = array(
    '#title' => t('Order has a product of a particular class'),
    '#category' => t('Order: Product'),
    '#callback' => 'uc_termsofservice_condition_product_class',
    '#arguments' => array(
      'cart' => array('#entity' => 'cart', '#title' => t('Cart')),
    ),
  );

  return $conditions;
}

/**
 * Condition Callbacks and Forms.
 */

/**
 * Check that an order has a product of the selected class.
 *
 * @see uc_termsofservice_condition_product_class_form()
 */
function uc_termsofservice_condition_product_class($cart, $settings) {
  foreach ($cart as $cart_item) {
    if ($cart_item->nid) {
      $type = db_result(db_query("SELECT type FROM {node} WHERE nid = %d", $cart_item->nid));
      if (in_array($type, array_values($settings['class']), TRUE)) {
        return TRUE;
      }
    }
  }

  return FALSE;
}

/**
 * @see uc_termsofservice_condition_product_class()
 */
function uc_termsofservice_condition_product_class_form($form_state, $settings = array()) {
  $form['class'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Product class'),
    '#options' => uc_product_type_names(),
    '#default_value' => $settings['class'],
    '#multiple' => TRUE,
  );
  return $form;
}