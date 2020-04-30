<?php

/**
 * @file
 * Views 2 hooks and callback registries.
 */

/**
 * Implementation of hook_views_data().
 */
function uc_product_views_data() {
  $data['uc_products']['table']['group'] = t('Product');

  $data['uc_products']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  $data['uc_products']['model'] = array(
    'title' => t('SKU'),
    'help' => t('The model number.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['uc_products']['list_price'] = array(
    'title' => t('List price'),
    'help' => t("The manufacturer's suggested price."),
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
      'float' => TRUE,
      'additional fields' => array(
        'nid' => array(
          'table' => 'node',
          'field' => 'nid',
        ),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );

  $data['uc_products']['cost'] = array(
    'title' => t('Cost'),
    'help' => t('The cost of the product to the store.'),
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
      'float' => TRUE,
      'additional fields' => array(
        'nid' => array(
          'table' => 'node',
          'field' => 'nid',
        ),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );

  $data['uc_products']['sell_price'] = array(
    'title' => t('Sell price'),
    'help' => t('The price for which the product is sold.'),
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
      'float' => TRUE,
      'additional fields' => array(
        'nid' => array(
          'table' => 'node',
          'field' => 'nid',
        ),
      ),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );

  $data['uc_products']['weight'] = array(
    'title' => t('Weight'),
    'help' => t('The physical weight.'),
    'field' => array(
      'additional fields' => array(
        'field' => 'weight_units',
      ),
      'handler' => 'uc_product_handler_field_weight',
      'click sortable' => TRUE,
      'float' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_float',
    ),
  );

  $data['uc_products']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['uc_products']['is_product'] = array(
    'title' => t('Is a product'),
    'help' => t('Check for the fields provided by the Ubercart product module.'),
    'group' => t('Node'),
    'filter' => array(
      'handler' => 'uc_product_handler_filter_product',
      'label' => t('Is a product'),
    ),
  );

  $data['uc_products']['addtocartlink'] = array(
    'title' => t('Add to cart form'),
    'help' => t("Form to put the product in the customer's cart."),
    'group' => t('Product'),
    'field' => array(
      'additional fields' => array(
        'nid' => array(
          'table' => 'node',
          'field' => 'nid',
        ),
        'type' => array(
          'table' => 'node',
          'field' => 'type',
        ),
      ),
      'handler' => 'uc_product_handler_field_addtocart',
    ),
  );

  $data['uc_products']['buyitnowbutton'] = array(
    'title' => t('Buy it now button'),
    'help' => t('A button to add a product to the cart without quantity or attribute fields.'),
    'group' => t('Product'),
    'field' => array(
      'table' => 'node',
      'additional fields' => array(
        'nid' => array(
          'table' => 'node',
          'field' => 'nid',
        ),
      ),
      'handler' => 'uc_product_handler_field_buyitnow',
    ),
  );

  return $data;
}


/**
 * Implementation of hook_views_handlers().
 */
function uc_product_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'uc_product') .'/views',
    ),
    'handlers' => array(
      'uc_product_handler_field_price' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'uc_product_handler_field_weight' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'uc_product_handler_filter_product' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
      'uc_product_handler_field_addtocart' => array(
        'parent' => 'views_handler_field',
      ),
      'uc_product_handler_field_buyitnow' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}


/**
 * Implementation of hook_views_tables_alter().
 *
 * Conditionally add editablefields support.
 */
function uc_product_views_tables_alter(&$tables) {
  if (module_exists('editablefields')) {
    if (is_array($tables['uc_products']['fields']['model']['option'])) {
      $tables['uc_products']['fields']['model']['option']['#options']['editable'] = t('Editable');
    }
    else {
      $tables['uc_products']['fields']['model']['option'] = array(
        '#type' => 'select',
        '#options' => array(
          'display' => t('Display'),
          'editable' => t('Editable'),
        ),
      );
    }
    $tables['uc_products']['fields']['model']['form_parents'] = 'base][model';
    if (is_array($tables['uc_products']['fields']['list_price']['option'])) {
      $tables['uc_products']['fields']['list_price']['option']['#options']['editable'] = t('Editable');
    }
    else {
      $tables['uc_products']['fields']['list_price']['option'] = array(
        '#type' => 'select',
        '#options' => array(
          'display' => t('Display'),
          'editable' => t('Editable'),
        ),
      );
    }
    $tables['uc_products']['fields']['list_price']['form_parents'] = 'base][prices][list_price';
    if (is_array($tables['uc_products']['fields']['cost']['option'])) {
      $tables['uc_products']['fields']['cost']['option']['#options']['editable'] = t('Editable');
    }
    else {
      $tables['uc_products']['fields']['cost']['option'] = array(
        '#type' => 'select',
        '#options' => array(
          'display' => t('Display'),
          'editable' => t('Editable'),
        ),
      );
    }
    $tables['uc_products']['fields']['cost']['form_parents'] = 'base][prices][cost';
    if (is_array($tables['uc_products']['fields']['sell_price']['option'])) {
      $tables['uc_products']['fields']['sell_price']['option']['#options']['editable'] = t('Editable');
    }
    else {
      $tables['uc_products']['fields']['sell_price']['option'] = array(
        '#type' => 'select',
        '#options' => array(
          'display' => t('Display'),
          'editable' => t('Editable'),
        ),
      );
    }
    $tables['uc_products']['fields']['sell_price']['form_parents'] = 'base][prices][sell_price';
    if (is_array($tables['uc_products']['fields']['weight']['option'])) {
      $tables['uc_products']['fields']['weight']['option']['#options']['editable'] = t('Editable');
    }
    else {
      $tables['uc_products']['fields']['weight']['option'] = array(
        '#type' => 'select',
        '#options' => array(
          'display' => t('Display'),
          'editable' => t('Editable'),
        ),
      );
    }
    $tables['uc_products']['fields']['weight']['form_parents'] = 'base][weight';
  }
}
