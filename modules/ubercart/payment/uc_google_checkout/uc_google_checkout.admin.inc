<?php

/**
 * @file
 * Google Checkout administration menu items.
 */

/**
 * Form builder for administrative settings form.
 *
 * @ingroup forms
 */
function uc_google_checkout_settings() {
  $form = array();

  $form['authentication'] = array(
    '#type' => 'fieldset',
    '#title' => t('Authentication'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['authentication']['uc_google_checkout_merchant_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Merchant ID'),
    '#default_value' => variable_get('uc_google_checkout_merchant_id', ''),
  );
  $form['authentication']['uc_google_checkout_merchant_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Merchant key'),
    '#default_value' => variable_get('uc_google_checkout_merchant_key', ''),
    '#description' => t('Used to sign cart information. Keep it secret, keep it safe.'),
  );

  $form['authentication']['sandbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Test Environment settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['authentication']['sandbox']['uc_google_checkout_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Test Mode'),
    '#default_value' => variable_get('uc_google_checkout_mode', 'checkout'),
    '#options' => array('sandbox' => t('On'), 'checkout' => t('Off')),
  );
  $form['authentication']['sandbox']['uc_google_checkout_test_merchant_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Test Merchant ID'),
    '#description' => t('Only needed for test mode. Click <a href="http://code.google.com/apis/checkout/developer/index.html#integration_overview" target="_blank">here</a> for more info.'),
    '#default_value' => variable_get('uc_google_checkout_test_merchant_id', ''),
    '#required' => FALSE,
  );
  $form['authentication']['sandbox']['uc_google_checkout_test_merchant_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Test Merchant Key'),
    '#default_value' => variable_get('uc_google_checkout_test_merchant_key', ''),
    '#required' => FALSE,
  );

  $form['messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Customer messages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['messages']['uc_google_checkout_order_cancel_reason'] = array(
    '#type' => 'textarea',
    '#title' => t('Reason for canceling order'),
    '#description' => t('This message will be sent with the cancelation notice through Google Checkout. Any comment given when the order is canceled will be sent as a separate message. This message uses <a href="!url">global and order tokens</a>.', array('!url' => 'admin/store/help/tokens')),
    '#default_value' => variable_get('uc_google_checkout_order_cancel_reason', t('Order canceled. See order comments at [order-url] for more information.')),
  );

  $form['button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Button settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['button']['uc_google_checkout_button_color'] = array(
    '#type' => 'radios',
    '#title' => t('Button background color'),
    '#default_value' => variable_get('uc_google_checkout_button_color', 'trans'),
    '#options' => array('trans' => t('Transparent'), 'white' => t('White')),
  );
  $form['button']['uc_google_checkout_button_size'] = array(
    '#type' => 'select',
    '#title' => t('Button size'),
    '#options' => array('large' => t('Large'), 'medium' => t('Medium'), 'small' => t('Small')),
    '#default_value' => variable_get('uc_google_checkout_button_size', 'large'),
  );
  $form['button']['uc_google_checkout_button_align'] = array(
    '#type' => 'radios',
    '#title' => t('Button alignment'),
    '#default_value' => variable_get('uc_google_checkout_button_align', 'right'),
    '#options' => array('right' => t('Right'), 'left' => t('Left')),
  );

  /* $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Merchant options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  ); */

  return system_settings_form($form);
}

/**
 * Form builder for shipping settings form.
 *
 * @ingroup forms
 */
function uc_google_checkout_shipping_settings() {
  $form = array();

  $form['help'] = array(
    '#value' => t("For merchant-calculated shipping, Google Checkout requires a fallback price in case it can't get a calculated shipping rate in time. When the cart request is sent to Google Checkout, Ubercart pre-calculates the shipping rates using this default address. Choose a location that will cause an average shipping cost to be returned."),
  );

  $form['uc_google_checkout_delivery_city'] = uc_textfield(uc_get_field_name('city'), variable_get('uc_google_checkout_delivery_city', ''), TRUE);
  if (isset($_POST['country'])) {
    $country = $_POST['country'];
  }
  else {
    $country = variable_get('uc_google_checkout_delivery_country', 0);
  }
  $form['uc_google_checkout_delivery_country'] = uc_country_select(uc_get_field_name('country'), variable_get('uc_google_checkout_delivery_country', 0));
  $form['uc_google_checkout_delivery_zone'] = uc_zone_select(uc_get_field_name('zone'), variable_get('uc_google_checkout_delivery_zone', 0), NULL, $country);
  $form['uc_google_checkout_delivery_postal_code'] = uc_textfield(uc_get_field_name('postal_code'), variable_get('uc_google_checkout_delivery_postal_code', ''), TRUE, NULL, 10, 10);

  return system_settings_form($form);
}

/**
 * Form builder for tax settings form.
 *
 * @see uc_google_checkout_taxes_settings_submit()
 * @see theme_uc_google_checkout_taxes_settings()
 * @ingroup forms
 */
function uc_google_checkout_taxes_settings() {
  $form = array(
    '#tree' => TRUE,
  );

  $result = db_query("SELECT zone, rate, tax_shipping FROM {uc_gc_taxes} ORDER BY zone");
  while ($tax = db_fetch_object($result)) {
    $form['taxes'][$tax->zone]['delete'] = array(
      '#type' => 'checkbox',
      '#default_value' => FALSE,
    );
    $form['taxes'][$tax->zone]['zone'] = array(
      '#type' => 'value',
      '#value' => $tax->zone,
    );
    $form['taxes'][$tax->zone]['rate'] = array(
      '#type' => 'textfield',
      '#default_value' => $tax->rate,
      '#size' => 8
    );
    $form['taxes'][$tax->zone]['tax_shipping'] = array(
      '#type' => 'checkbox',
      '#default_value' => $tax->tax_shipping,
    );
  }

  $form['taxes']['new']['delete'] = array(
    '#type' => 'checkbox',
    '#disabled' => TRUE,
  );
  $form['taxes']['new']['zone'] = uc_zone_select('');
  $form['taxes']['new']['rate'] = array(
    '#type' => 'textfield',
    '#default_value' => '',
    '#size' => 8
  );
  $form['taxes']['new']['tax_shipping'] = array(
    '#type' => 'checkbox',
    '#default_value' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save taxes'),
  );

  return $form;
}

/**
 * Themes tax settings form.
 *
 * @see uc_google_checkout_taxes_settings()
 * @ingroup themeable
 */
function theme_uc_google_checkout_taxes_settings($form) {
  $header = array(t('Delete'), uc_get_field_name('zone'), t('Rate'), t('Tax shipping?'));

  $rows = array();
  foreach (element_children($form['taxes']) as $zone) {
    $row = array();
    $row[] = drupal_render($form['taxes'][$zone]['delete']);
    if ($zone == 'new') {
      $row[] = drupal_render($form['taxes'][$zone]['zone']);
    }
    else {
      $row[] = $form['taxes'][$zone]['zone']['#value'];
    }
    //$form['taxes'][$zone]['zone']['#printed'] = TRUE;
    $row[] = drupal_render($form['taxes'][$zone]['rate']);
    $row[] = drupal_render($form['taxes'][$zone]['tax_shipping']);
    $rows[] = $row;
  }

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);

  return $output;
}

/**
 * Form submission handler for tax settings form.
 *
 * @see uc_google_checkout_taxes_settings()
 */
function uc_google_checkout_taxes_settings_submit($form, &$form_state) {
  foreach ($form_state['values']['taxes'] as $zone => $tax_values) {
    if ($zone == 'new' && $tax_values['zone'] && $tax_values['rate']) {
      db_query("DELETE FROM {uc_gc_taxes} WHERE zone = '%s'", $tax_values['zone']);
      db_query("INSERT INTO {uc_gc_taxes} (zone, rate, tax_shipping) VALUES ('%s', %f, %d)", uc_get_zone_code($tax_values['zone']), $tax_values['rate'], $tax_values['tax_shipping']);
    }
    elseif ($tax_values['delete']) {
      db_query("DELETE FROM {uc_gc_taxes} WHERE zone = '%s'", $tax_values['zone']);
    }
    else {
      db_query("UPDATE {uc_gc_taxes} SET rate = %f, tax_shipping = %d WHERE zone = '%s'", $tax_values['rate'], $tax_values['tax_shipping'], $tax_values['zone']);
    }
  }
}

/**
 * Menu callback function that presents payment terminal form to adminstrator.
 */
function uc_google_checkout_terminal($order) {
  $order_id = $order->order_id;

  if ($order === FALSE) {
    drupal_set_message(t('Order @order_id does not exist.', array('@order_id' => $order_id)));
    drupal_goto('admin/store/orders');
  }

  $output = l(t('Return to order view screen.'), 'admin/store/orders/'. $order_id);

  $gc_balance = $order->gc_total;
  $payments = uc_payment_load_payments($order_id);
  if (is_array($payments)) {
    foreach ($payments as $payment) {
      if ($payment->method == 'Google Checkout') {
        $gc_balance -= $payment->amount;
      }
    }
  }
  $balance = uc_payment_balance($order);
  $context = array(
    'revision' => 'themed-original',
    'type' => 'order_total',
    'subject' => array(
      'order' => $order,
    ),
  );
  $output .= '<p>'. t('Use this terminal to process credit card payments:') .'</p>'
            .'<table style="width: auto;"><tbody style="border-top: 0px;"><tr>'
            .'<td><strong>'. t('Order total:') .'</strong> </td><td>'
           . uc_price($order->order_total, $context) .'</td></tr><tr><td>'
            .'<strong>'. t('Balance:') .'</strong> </td><td>'
           . uc_price($balance, $context) .'</td></tr><tr><td><strong>'
           . t('Google Checkout total:') .'</strong></td><td>'
           . uc_price($order->gc_total, $context) .'</td></tr><tr><td><strong>'
           . t('Google Checkout balance:') .'</strong></td<td>'
           . uc_price($gc_balance, $context) .'</td></tr></tbody></table>';

  if (in_array($order->financial_state, array('REVIEWING', 'CHARGEABLE', 'CHARGED'))) {
    $output .= drupal_get_form('uc_google_checkout_terminal_form', $order, $gc_balance);
  }

  return $output;
}

/**
 * Form builder for virtual terminal form.
 *
 * @see uc_google_checkout_terminal_form_validate()
 * @see uc_google_checkout_terminal_form_submit()
 * @ingroup forms
 */
function uc_google_checkout_terminal_form($form_state, $order, $amount = 0) {
  $form = array();

  if ($order->financial_state == 'CHARGED') {
    $form['action'] = array(
      '#type' => 'select',
      '#title' => t('Action'),
      '#default_value' => 'charge',
      '#options' => array(
        'charge' => t('Charge'),
        'refund' => t('Refund'),
      ),
    );
    $form['reason'] = array(
      '#type' => 'textfield',
      '#title' => t('Reason for refund'),
      '#weight' => 1,
    );
    $form['comment'] = array(
      '#type' => 'textarea',
      '#title' => t('Refund Comment'),
      '#weight' => 2,
    );
  }
  else {
    $form['action'] = array(
      '#type' => 'value',
      '#value' => 'charge',
    );
  }

  $context = array(
    'revision' => 'formatted-original',
    'type' => 'amount',
  );
  $options = array(
    'sign' => FALSE,
    'thou' => FALSE,
    'dec' => '.',
  );

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount'),
    '#default_value' => uc_price($amount, $context, $options),
    '#size' => 10,
    '#weight' => 0,
    '#field_prefix' => variable_get('uc_sign_after_amount', FALSE) ? '' : variable_get('uc_currency_sign', '$'),
    '#field_suffix' => variable_get('uc_sign_after_amount', FALSE) ? variable_get('uc_currency_sign', '$') : '',
  );
  $form['gc_balance'] = array(
    '#type' => 'value',
    '#value' => $amount,
  );
  $form['gc_total'] = array(
    '#type' => 'value',
    '#value' => $order->gc_total,
  );
  $form['order_id'] = array(
    '#type' => 'hidden',
    '#value' => $order->order_id,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Form validation for virtual terminal form.
 *
 * @see uc_google_checkout_terminal_form()
 * @see uc_google_checkout_terminal_form_submit()
 */
function uc_google_checkout_terminal_form_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['amount']) || $form_state['values']['amount'] == 0) {
    form_set_error('amount', t('You must enter a number for the amount.'));
  }
  if ($form_state['values']['action'] == 'charge' && $form_state['values']['amount'] > $form_state['values']['gc_balance']) {
    form_set_error('amount', t('Google does not allow charges greater than the balance.'));
  }
  if ($form_state['values']['action'] == 'refund' && $form_state['values']['amount'] > $form_state['values']['gc_total'] - $form_state['values']['gc_balance']) {
    form_set_error('amount', t('Google does not allow refunds greater than the amount already charged.'));
  }
  if ($form_state['values']['action'] == 'refund' && empty($form_state['values']['reason'])) {
    form_set_error('reason', t('A reason for refunding the customer is required.'));
  }

  $order = uc_order_load($form_state['values']['order_id']);
  if ($order === FALSE) {
    form_set_error('', t('Invalid order ID.  Unable to process payment.'));
  }
}

/**
 * Form submission handler for virtual terminal form.
 *
 * @see uc_google_checkout_terminal_form()
 * @see uc_google_checkout_terminal_form_validate()
 */
function uc_google_checkout_terminal_form_submit($form, &$form_state) {
  if ($form_state['values']['action'] == 'charge') {
    $form_state['redirect'] = uc_google_checkout_charge($form_state['values']['order_id'], $form_state['values']['amount']);
  }
  elseif ($form_state['values']['action'] == 'refund') {
    $form_state['redirect'] = uc_google_checkout_refund($form_state['values']['order_id'], $form_state['values']['amount'], $form_state['values']['reason'], $form_state['values']['comment']);
  }
}
