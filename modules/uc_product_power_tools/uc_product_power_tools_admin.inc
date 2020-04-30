<?php
// $Id: uc_product_power_tools_admin.inc,v 1.5 2009/10/08 20:19:46 tcindie Exp $

/**
 * @file 
 * Settings and config for uc_product_power_tools module.
 */
function uc_product_power_tools_admin_settings() {
  // Get a list of all product classes.
  $result = db_query('SELECT pcid, name from {uc_product_classes}');
  while ($classes = db_fetch_array($result)) {
    $productclasses[$classes['pcid']] = $classes['name'];
  }

  // Add entry for Default Products to end of the list:
  $productclasses['product'] = 'Default Ubercart Product Content Type';

  // Get a list of enabled classes.
  $result = db_query('SELECT pcid, enabled from {uc_power_tools}');
  while ($classes = db_fetch_array($result)) {
    $enabledclasses[$classes['pcid']] = $classes['enabled'];
  }

  $form = array();
  $form['content'] = array(
    '#value'       => t('<p>Product "Power Tools" give you a number of options for altering the product creation form.  This is useful when you have product classes that do not require all of the possible product fields.  Unneeded fields can be disabled and hidden, or preset and hidden.</p><p>Tweakable options:<ul><li>Auto Generate SKU</li><li>List Position</li><li>List Price &amp; Cost</li><li>Default Quantity &amp; Package Quantity</li><li>Shippable (can hide other shipping fields for non-shippable products)</li><li>Set default stock levels (If stock module is installed)</li></ul>'),
  );
  $form['classes'] = array(
    '#type'   => 'fieldset',
    '#title'  => 'Product Classes',
  );

  $header = array(
    t('Product Class'),
    t('"Power Tools" Status'),
    t('Actions'),
  );

  foreach ($productclasses as $pcid => $classname) {
    $enabled = $enabledclasses[$pcid];
    $radio1 = '<input type=radio name=radio['. $pcid .'] value=1';
    if ($enabled) {
      $radio1 .= ' checked="checked"';
    }
    $radio1 .= '> Enabled';
    $radio2 = '<input type=radio name=radio['. $pcid .'] value=0';
    if (!$enabled) {
      $radio2 .= ' checked="checked"';
    }
    $radio2 .= '> Disabled';
    $tablerow[] = array(
      l($classname, 'admin/store/products/power-tools/'. $pcid),
      $radio1 .'&nbsp;&nbsp;&nbsp;&nbsp;'. $radio2,
      l(t('Edit'), 'admin/store/products/power-tools/'. $pcid),
    );
  }

  $form['classes']['table'] = array(
    '#value' => theme('table', $header, $tablerow),
    );
  $form['classes']['submit'] = array(
    '#type'          => 'submit',
    '#value'         => t('Update'),
  );
  return $form;
}

function uc_product_power_tools_admin_settings_submit($form, &$form_state) {
  foreach ($form_state['clicked_button']['#post']['radio'] as $key => $value) {
    // If class is disabled, check to see if it's in the db, if not add it as disabled, otherwise update it's status to disabled.
    if ($value == 0) {
      $result = db_query("SELECT * FROM {uc_power_tools} WHERE pcid='%s'", $key);
      if (!db_fetch_array($result)) {
        db_query("INSERT INTO {uc_power_tools} (pcid, enabled) VALUES ('%s',0)", $key);
      }
      else {
        db_query("UPDATE {uc_power_tools} SET enabled=0 WHERE pcid='%s'", $key);
      }
    }
    // If class is enabled, insert into database if it's not already there.
    if ($value == 1) {
      $result = db_query("SELECT * FROM {uc_power_tools} WHERE pcid='%s'", $key);
      if (!db_fetch_array($result)) {
        db_query("INSERT INTO {uc_power_tools} (pcid, enabled) VALUES ('%s',1)", $key);
      }
      else {
        db_query("UPDATE {uc_power_tools} SET enabled=1 WHERE pcid='%s'", $key);
      }
    }
  }
  drupal_set_message('"Power Tools" Class Settings updated.');
}



function uc_product_power_tools_class_settings() {
  $tmp = explode("/", $_GET['q']);
  $prodclass = $tmp[4];
  $data = db_fetch_array(db_query("SELECT * FROM {uc_power_tools} WHERE pcid = '%s'", $prodclass));
  $class = ($prodclass != 'product') ? db_fetch_array(db_query("SELECT name from {uc_product_classes} WHERE pcid = '%s'", $prodclass)) : array('name' => 'Default Ubercart Product Content Type');
  $sign_flag = variable_get('uc_sign_after_amount', FALSE);
  $currency_sign = variable_get('uc_currency_sign', '$');

  $form = array();
  $form['product_class'] = array(
    '#type'   => 'hidden',
    '#value'  => $prodclass,
  );
  $form['power_tools'] = array(
    '#type'        => 'fieldset',
    '#title'       => $class['name'] .' "Power Tools" Settings',
    '#collapsible' => FALSE,
  );
  $form['power_tools']['autosku'] = array(
    '#type'        => 'fieldset',
    '#title'       => 'Auto SKU Generation',
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
  );
  $form['power_tools']['autosku']['asku'] = array(
    '#type' => 'radios',
    '#default_value' => isset($data['asku']) ? $data['asku'] : 0,
    '#options' => array(
      t('Show SKU field on product entry form'),
      t('Hide SKU field and Automatically Generate from replacement pattern below:'),
    )
  );

  if (module_exists('token')) {
    $description = t('This string will be used as SKU.');
    if (module_exists('token')) {
      $description .= ' '. t('Use the syntax [token] if you want to insert a replacement pattern.<br />Note: CCK Fields that are not assigned to products in this product class will return no value. If using the Auto Node Title module, [title] and [title-raw] will return "ant".');
    }
    $form['power_tools']['autosku']['asku_pattern'] = array(
      '#type' => 'textarea',
      '#title' => t('Pattern for the SKU'),
      '#description' => $description,
      '#default_value' => isset($data['asku-settings']) ? $data['asku-settings'] : '',
    );
  }

  if (module_exists('token')) {
    $form['power_tools']['autosku']['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
    );
    $form['power_tools']['autosku']['token_help']['help'] = array(
      '#value' => theme('token_help', 'node'),
    );
  }

  $form['power_tools']['pricing'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Prices',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['pricing']['lp'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'List Price',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['pricing']['lp']['lponoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['lp']) ? $data['lp'] : 0,
    '#options'       => array(
      t('Show List Price field on product entry form'),
      t('Hide List Price field & Use Sell Price Value entered on product form'),
      t('Hide List Price field & Use default value below:'),
    )
  );
  $form['power_tools']['pricing']['lp']['lp_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('List price'),
    '#required'      => FALSE,
    '#default_value' => isset($data['lp-settings']) ? $data['lp-settings'] : 0,
    '#weight' => 0,
    '#size' => 20,
    '#maxlength' => 35,
    '#field_prefix' => $sign_flag ? '' : $currency_sign,
    '#field_suffix' => $sign_flag ? $currency_sign : '',
  );
  $form['power_tools']['pricing']['cost'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Cost',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['pricing']['cost']['costonoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['cost']) ? $data['cost'] : 0,
    '#options'       => array(
      t('Show Cost field on product entry form'),
      t('Hide Cost field & Use default value below:'),
    )
  );
  $form['power_tools']['pricing']['cost']['cost_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('Cost'),
    '#required'      => FALSE,
    '#default_value' => isset($data['cost-settings']) ? $data['cost-settings'] : 0,
    '#weight' => 0,
    '#size' => 20,
    '#maxlength' => 35,
    '#field_prefix' => $sign_flag ? '' : $currency_sign,
    '#field_suffix' => $sign_flag ? $currency_sign : '',
  );
  $form['power_tools']['pricing']['sp'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Sell Price',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['pricing']['sp']['sponoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['sp']) ? $data['sp'] : 0,
    '#options'       => array(
      t('Show Sell Price field on product entry form'),
      t('Hide Sell Price field & Use default value below:'),
    )
  );
  $form['power_tools']['pricing']['sp']['sp_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('Sell price'),
    '#required'      => FALSE,
    '#default_value' => isset($data['sp-settings']) ? $data['sp-settings'] : 0,
    '#weight' => 0,
    '#size' => 20,
    '#maxlength' => 35,
    '#field_prefix' => $sign_flag ? '' : $currency_sign,
    '#field_suffix' => $sign_flag ? $currency_sign : '',
  );
  $form['power_tools']['qtys'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Quantities',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['qtys']['dq'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Default Quantity',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['qtys']['dq']['dqonoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['dq']) ? $data['dq'] : 0,
    '#options'       => array(
      t('Show Default Quantity field on product entry form'),
      t('Hide Default Quantity field & Use default value below:'),
    t('Show Default Quantity field & Use default value below:'),
    )
  );
  $form['power_tools']['qtys']['dq']['dq_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('Default Quantity'),
    '#description'   => t('Default quantity to add to cart'),
    '#required'      => FALSE,
    '#default_value' => isset($data['dq-settings']) ? $data['dq-settings'] : 1,
    '#weight' => 0,
    '#size' => 20,
  );
  $form['power_tools']['qtys']['pq'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Package Quantity',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['qtys']['pq']['pqonoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['pq']) ? $data['pq'] : 0,
    '#options'       => array(
      t('Show Default Package Quantity field on product entry form'),
      t('Hide Default Package Quantity field & Use default value below:'),
    t('Show Default Package Quantity field & Use default value below:'),
    )
  );
  $form['power_tools']['qtys']['pq']['pq_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('Package Quantity'),
    '#description'   => t('For a package containing only this product, how many are in it?'),
    '#required'      => FALSE,
    '#default_value' => isset($data['pq-settings']) ? $data['pq-settings'] : 1,
    '#weight' => 0,
    '#size' => 20,
  );
  $form['power_tools']['lpos'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'List Position',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['lpos']['lposonoff'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['lpos']) ? $data['lpos'] : 0,
    '#options'       => array(
      t('Show List Position field on product entry form'),
      t('Hide List Position field & Use default value below:'),
    )
  );
  $form['power_tools']['lpos']['lpos_settings'] = array(
    '#type'          => 'textfield',
    '#size'          => 32,
    '#title'         => t('List Position'),
    '#description'   => t('List Position weight of products of this class.'),
    '#required'      => FALSE,
    '#default_value' => isset($data['lpos-settings']) ? $data['lpos-settings'] : 0,
    '#weight' => 0,
    '#size' => 20,
  );
  $form['power_tools']['ship'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Shipping',
    '#collapsible'   => TRUE,
    '#collapsed'     => TRUE,
  );
  $form['power_tools']['ship']['ship_settings'] = array(
    '#type'          => 'radios',
    '#default_value' => isset($data['ship']) ? $data['ship'] : 0,
    '#options'       => array(
      t('Product is Shippable. Show checkbox & all shipping fields on product entry form'),
      t('Product is Shippable. Hide checkbox, but show other shipping fields on product entry form'),
      t('Product is NOT Shippable. Hide checkbox, but show other shipping fields on product entry form'),
      t('Product is NOT Shippable. Hide checkbox & all shipping fields on product entry form'),
    ),
    '#description'  => 'The last option will hide shipping fields, as well as weight and size fields.',
  );

  $form['power_tools']['ship']['weight'] = array(
    '#weight' => 15,
    '#theme' => 'uc_product_form_weight',
  );
  $form['power_tools']['ship']['weight']['weight'] = array('#type' => 'textfield',
    '#title' => t('Weight'),
    '#default_value' => isset($data['weight']) ? $data['weight'] : 0,
    '#size' => 10,
    '#maxlength' => 15,
  );
  $units = array(
    'lb' => t('Pounds'),
    'kg' => t('Kilograms'),
    'oz' => t('Ounces'),
    'g' => t('Grams'),
  );
  $form['power_tools']['ship']['weight']['weight_units'] = array('#type' => 'select',
    '#title' => t('Unit of measurement'),
    '#default_value' => isset($data['weight_units']) ? $data['weight_units'] : variable_get('uc_weight_unit', 'lb'),
    '#options' => $units,
  );
  $form['power_tools']['ship']['dimensions'] = array('#type' => 'fieldset',
    '#title' => t('Dimensions'),
    '#description' => t('Physical dimensions of the packaged product.'),
    '#weight' => 20,
    '#theme' => 'uc_product_dimensions_form',
  );
  $form['power_tools']['ship']['dimensions']['length_units'] = array('#type' => 'select',
    '#title' => t('Units of measurement'),
    '#options' => array(
      'in' => t('Inches'),
      'ft' => t('Feet'),
      'cm' => t('Centimeters'),
      'mm' => t('Millimeters'),
    ),
    '#default_value' => isset($data['length_units']) ? $data['length_units'] : variable_get('uc_length_unit', 'in'),
  );
  $form['power_tools']['ship']['dimensions']['length'] = array('#type' => 'textfield',
    '#title' => t('Length'),
    '#default_value' => isset($data['length']) ? $data['length'] : '',
    '#size' => 10,
  );
  $form['power_tools']['ship']['dimensions']['width'] = array('#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => isset($data['width']) ? $data['width'] : '',
    '#size' => 10,
  );
  $form['power_tools']['ship']['dimensions']['height'] = array('#type' => 'textfield',
    '#title' => t('Height'),
    '#default_value' => isset($data['height']) ? $data['height'] : '',
    '#size' => 10,
  );

  if (module_exists('uc_stock')) {
    $form['power_tools']['stock'] = array(
      '#type'          => 'fieldset',
      '#title'         => 'Stock',
      '#collapsible'   => TRUE,
      '#collapsed'     => TRUE,
    );
    $form['power_tools']['stock']['stockonoff'] = array(
      '#type'          => 'radios',
      '#default_value' => isset($data['stock']) ? $data['stock'] : 0,
      '#options'       => array(
        t('Do not set stock level'),
        t('Set stock level using default value below'),
      ),
      '#description'   => t('If setting a default stock level, stock will be set to active for products of this type.'),
    );
    $form['power_tools']['stock']['stock_settings'] = array(
      '#type'          => 'textfield',
      '#size'          => 32,
      '#title'         => t('Default Stock'),
      '#description'   => t('Default Stock level for products of this class.'),
      '#required'      => FALSE,
      '#default_value' => isset($data['stock-settings']) ? $data['stock-settings'] : 0,
      '#weight' => 0,
      '#size' => 20,
    );
    $form['power_tools']['stock']['stock_threshold'] = array(
      '#type'          => 'textfield',
      '#size'          => 32,
      '#title'         => t('Notification Threshold'),
      '#description'   => t('When stock drops below this level you will be notified.'),
      '#required'      => FALSE,
      '#default_value' => isset($data['stock-threshold']) ? $data['stock-threshold'] : 0,
      '#weight' => 0,
      '#size' => 20,
    );
  }
  $form['submit'] = array(
    '#type'     => 'submit',
    '#value'    => t('Submit'),
    '#weight'   => 10,
  );
  return $form;
}

function uc_product_power_tools_class_settings_submit($form, &$form_state) {
  $pcid           = $form_state['values']['product_class'];
  $enabled        = 1;
  $asku           = isset($form_state['values']['asku']) ? $form_state['values']['asku'] : ' ';
  $askusettings   = $form_state['values']['asku_pattern'];
  $lp             = $form_state['values']['lponoff'];
  $lpsettings     = $form_state['values']['lp_settings'];
  $sp             = $form_state['values']['sponoff'];
  $spsettings     = $form_state['values']['sp_settings'];
  $cost           = $form_state['values']['costonoff'];
  $costsettings   = $form_state['values']['cost_settings'];
  $dq             = $form_state['values']['dqonoff'];
  $dqsettings     = $form_state['values']['dq_settings'];
  $pq             = $form_state['values']['pqonoff'];
  $pqsettings     = $form_state['values']['pq_settings'];
  $ship           = $form_state['values']['ship_settings'];
  $lpos           = $form_state['values']['lposonoff'];
  $lpossettings   = $form_state['values']['lpos_settings'];
  $stock          = $form_state['values']['stockonoff'];
  $stocksettings  = $form_state['values']['stock_settings'];
  $stockthreshold = $form_state['values']['stock_threshold'];
  $weight         = $form_state['values']['weight'];
  $weight_units   = $form_state['values']['weight_units'];
  $length_units   = $form_state['values']['length_units'];
  $length         = $form_state['values']['length'];
  $width          = $form_state['values']['width'];
  $height         = $form_state['values']['height'];

  db_query("DELETE FROM {uc_power_tools} WHERE pcid = '%s'", $pcid);
  db_query("INSERT INTO {uc_power_tools} (pcid, enabled, asku, `asku-settings`, lp, `lp-settings`, cost, `cost-settings`, sp, `sp-settings`, dq, `dq-settings`, pq, `pq-settings`, ship, weight, `weight_units`, `length_units`, length, width, height, lpos, `lpos-settings`, stock, `stock-settings`, `stock-threshold`)
                                  VALUES ('%s', %d, %d, '%s', %d, %f, %d, %f, %d, %f, %d, %d, %d, %d, %d, %f, '%s', '%s', %f, %f, %f, %d, %d, %d, %d, %d)",
                                  $pcid, $enabled, $asku, $askusettings, $lp, $lpsettings, $cost, $costsettings, $sp, $spsettings, $dq, $dqsettings, $pq, $pqsettings, $ship, $weight, $weight_units, $length_units, $length, $width, $height, $lpos, $lpossettings, $stock, $stocksettings, $stockthreshold);

  drupal_set_message('"Power Tools" settings saved.');
  drupal_goto('admin/store/products/power-tools');
}
