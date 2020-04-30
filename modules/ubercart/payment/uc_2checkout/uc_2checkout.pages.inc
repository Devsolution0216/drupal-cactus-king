<?php

/**
 * @file
 * 2checkout menu items.
 *
 */

function uc_2checkout_complete($cart_id = 0) {
  watchdog('2Checkout', 'Receiving new order notification for order !order_id.', array('!order_id' => check_plain($_POST['merchant_order_id'])));

  $order = uc_order_load($_POST['merchant_order_id']);

  if ($order === FALSE || uc_order_status_data($order->order_status, 'state') != 'in_checkout') {
    return t('An error has occurred during payment.  Please contact us to ensure your order has submitted.');
  }

  $key = $_POST['key'];
  $valid = md5(variable_get('uc_2checkout_secret_word', 'tango') . $_POST['sid'] . $_POST['merchant_order_id'] . $_POST['total']);
  if (strtolower($key) != strtolower($valid)) {
    uc_order_comment_save($order->order_id, 0, t('Attempted unverified 2Checkout completion for this order.'), 'admin');
    return MENU_ACCESS_DENIED;
  }

  if ($_POST['demo'] == 'Y' xor variable_get('uc_2checkout_demo', TRUE)) {
    watchdog('uc_2checkout', 'The 2checkout payment for order <a href="!order_url">@order_id</a> demo flag was set to %flag, but the module is set to %mode mode.',
      array('!order_url' => url('admin/store/orders/'. $order->order_id), '@order_id' => $order->order_id, '%flag' => $_POST['demo'] == 'Y' ? 'Y' : 'N', '%mode' => variable_get('uc_2checkout_demo', TRUE) ? 'Y' : 'N'), WATCHDOG_ERROR);
    if (!variable_get('uc_2checkout_demo', TRUE)) {
      return MENU_ACCESS_DENIED;
    }
  }

  $order->billing_street1 = $_POST['street_address'];
  $order->billing_street2 = $_POST['street_address2'];
  $order->city = $_POST['city'];
  $order->billing_postal_code = $_POST['zip'];
  $order->billing_phone = $_POST['phone'];

  $zone_id = db_result(db_query("SELECT zone_id FROM {uc_zones} WHERE zone_code LIKE '%s'", $_POST['state']));
  if (!empty($zone_id)) {
    $order->billing_zone = $zone_id;
  }

  $country_id = db_result(db_query("SELECT country_id FROM {uc_countries} WHERE country_name LIKE '%s'", $_POST['country']));
  if (!empty($country_id)) {
    $order->billing_country = $country_id;
  }

  if (strtolower($_POST['email']) !== strtolower($order->primary_email)) {
    uc_order_comment_save($order->order_id, 0, t('Customer used a different e-mail address during payment: !email', array('!email' => check_plain($_POST['email']))), 'admin');
  }

  if ($_POST['credit_card_processed'] == 'Y' && is_numeric($_POST['total'])) {
    $comment = t('Paid by !type, 2Checkout.com order #!order.', array('!type' => $_POST['pay_method'] == 'CC' ? t('credit card') : t('echeck'), '!order' => check_plain($_POST['order_number'])));
    uc_payment_enter($order->order_id, '2checkout', $_POST['total'], 0, NULL, $comment);
  }
  else {
    drupal_set_message(t('Your order will be processed as soon as your payment clears at 2Checkout.com.'));
    uc_order_comment_save($order->order_id, 0, t('!type payment is pending approval at 2Checkout.com.', array('!type' => $_POST['pay_method'] == 'CC' ? t('Credit card') : t('eCheck'))), 'admin');
  }

  // Empty that cart...
  uc_cart_empty($cart_id);

  // Save changes to order without it's completion.
  uc_order_save($order);

  // Add a comment to let sales team know this came in through the site.
  uc_order_comment_save($order->order_id, 0, t('Order created through website.'), 'admin');

  $output = uc_cart_complete_sale($order, variable_get('uc_new_customer_login', FALSE));

  $page = variable_get('uc_cart_checkout_complete_page', '');

  if (!empty($page)) {
    drupal_goto($page);
  }

  return $output;
}
