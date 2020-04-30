<?php
// $Id: uc_views.views.inc,v 1.9 2009/04/07 11:04:35 madsph Exp $
/**
 * @file
 * Views 2 hooks and callback registries.
 */

define('UC_PAYER_PREFIX', "Payer's");
define('UC_RECIPIENT_PREFIX', "Recipient's");

/**
 * Implementation of hook_views_data().
 */
function uc_views_views_data() {
  //Make the uc_order_products table visible for Views module
  $order_products = drupal_get_schema('uc_order_products');
  $data['uc_order_products']['table']['group'] = t('Order product');
  $data['uc_order_products']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'nid',
  );

  $data['uc_order_products']['model'] = array(
    'title' => t('SKU'),
    'help' => $order_products['fields']['model']['description'],
    'field' => array(
      'handler' => 'views_handler_field',
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

  $data['uc_order_products']['qty'] = array(
    'title' => t('qty'),
    'help' => $order_products['fields']['qty']['description'],
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products']['price'] = array(
    'title' => t('Price'),
    'help' => $order_products['fields']['price']['description'],
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products']['cost'] = array(
    'title' => t('Cost'),
    'help' => $order_products['fields']['cost']['description'],
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['uc_order_products']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );


  //Make the uc_order_products_qty_vw view visible for Views module
  $data['uc_order_products_qty_vw']['table']['group'] = t('Order product');
  $data['uc_order_products_qty_vw']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'nid',
  );
  $data['uc_order_products_qty_vw']['order_count'] = array(
    'title' => t('order_count'),
    'help' => t('The number of orderlines with the product.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_qty_vw']['avg_qty'] = array(
    'title' => t('avg_qty'),
    'help' => t('The average amount ordered.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_qty_vw']['sum_qty'] = array(
    'title' => t('sum_qty'),
    'help' => t('The summed amount of all orders.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_qty_vw']['max_qty'] = array(
    'title' => t('max_qty'),
    'help' => t('The maximum amount ordered.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_qty_vw']['min_qty'] = array(
    'title' => t('min_qty'),
    'help' => t('The minimum amount ordered.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_qty_vw']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );


  //Make the uc_order_products_user_vw view visible for Views module
  $data['uc_order_products_user_vw']['table']['group'] = t('Order product');
  $data['uc_order_products_user_vw']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'nid',
  );
  $data['uc_order_products_user_vw']['table']['join']['users'] = array(
      'left_field' => 'uid',
      'field' => 'uid',
  );
  $data['uc_order_products_user_vw']['uid'] = array(
    'title' => t('user_id'),
    'help' => t('The id of the user.'),
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
     'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'uid',
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['order_count'] = array(
    'title' => t('user_order_count'),
    'help' => t('The number of orderlines with the product for the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['avg_qty'] = array(
    'title' => t('user_avg_qty'),
    'help' => t('The average amount ordered for the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['sum_qty'] = array(
    'title' => t('user_sum_qty'),
    'help' => t('The summed amount of all orders for the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['max_qty'] = array(
    'title' => t('user_max_qty'),
    'help' => t('The maximum amount ordered for the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['min_qty'] = array(
    'title' => t('user_min_qty'),
    'help' => t('The minimum amount ordered for the user.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_user_vw']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );


  //Make the uc_order_products_pair_vw view visible for Views module
  $data['uc_order_products_pair_vw']['table']['group'] = t('Order product');
  $data['uc_order_products_pair_vw']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'pair_nid',
  );
  $data['uc_order_products_pair_vw']['nid'] = array(
    'title' => t('pairs_product_nid'),
    'help' => t('The nid of the product for which we are seeking pairs.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
     'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_pair_vw']['pair_nid'] = array(
    'title' => t('pairs_product_pair_nid'),
    'help' => t('The nid of the pair product.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_pair_vw']['order_count'] = array(
    'title' => t('pairs_order_count'),
    'help' => t('The number of orders in which the product pair has occured along with the product with nid.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_pair_vw']['pair_sum_qty'] = array(
    'title' => t('pairs_sum_qty'),
    'help' => t('The summed qty purchased on orders which also include the product with nid.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_order_products_pair_vw']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  //Make the uc_orders table visible for Views module
  //Thank you river_t for original patch (order_id, order_status and uid)!
  $data['uc_orders']['table']['group'] = t('Ubercart order');

  // Base and use of schema for descriptions added by sammys
  $order_schema = drupal_get_schema('uc_orders');
  $data['uc_orders']['table']['base'] = array(
    'field' => 'order_id',
    'title' => t('Ubercart orders'),
    'help' => t('Orders placed in your Ubercart store.'),
    'weight' => -10,
  );
  $data['users']['table']['join'] = array(
    'uc_orders' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['uc_order_products']['table']['join'] = array(
    'uc_orders' => array(
      'left_field' => 'order_id',
      'field' => 'order_id',
    ),
  );
  $data['node']['table']['join'] = array(
    'uc_orders' => array(
      'left_table' => 'uc_order_products',
      'left_field' => 'order_id',
      'field' => 'order_id',
    ),
    'uc_order_products' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  $data['uc_orders']['table']['join'] = array(
    'node' => array(
      'left_table' => 'uc_order_products',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'uc_order_products' => array(
      'left_field' => 'order_id',
      'field' => 'order_id',
    ),
  );
  //sammys: optionally link to order and allow order_id as argument
  $data['uc_orders']['order_id'] = array(
    'title' => t('Order ID'),
    'help' => $order_schema['fields']['order_id']['description'],
    'field' => array(
      'handler' => 'uc_views_handler_field_order_id',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // sammys: Information for accepting an order id as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'order_id',
    ),
  );
  $data['uc_orders']['order_status'] = array(
    'title' => t('Order Status'),
    'help' => $order_schema['fields']['order_status']['description'],
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_order_status',
    ),
  );
  $data['uc_orders']['uid'] = array(
    'title' => t('Order User ID'),
    'help' => $order_schema['fields']['uid']['description'],
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
     'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'uid',
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Order User'),
    ),
  );
  //sammys: Changed field handler to display as a price
  $data['uc_orders']['order_total'] = array(
    'title' => t('Order total'),
    'help' => $order_schema['fields']['order_total']['description'],
    'field' => array(
      'handler' => 'uc_product_handler_field_price',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_orders']['payment_method'] = array(
    'title' => t('Order Payment Method'),
    'help' => $order_schema['fields']['payment_method']['description'],
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $data['uc_orders']['created'] = array(
    'title' => t('Order Creation Date'),
    'help' => $order_schema['fields']['created']['description'],
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['uc_orders']['modified'] = array(
    'title' => t('Order Modification Date'),
    'help' => $order_schema['fields']['modified']['description'],
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['uc_orders']['primary_email'] = array(
    'title' => t('Email address'),
    'help' => t($order_schema['fields']['primary_email']['description']),
    'field' => array(
      'handler' => 'views_handler_field_user_mail',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $string_fields = array(
    'first_name' => 'first name',
    'last_name' => 'last name',
    'phone' => 'phone number',
    'company' => 'company',
    'street1' => 'address line 1',
    'street2' => 'address line 2',
    'city' => 'city',
    'postal_code' => 'zip/postal code',
  );

  foreach (array('delivery', 'billing') as $prefix) {
    $args = array(
      '!titleprefix' => ($prefix == 'delivery' ? UC_RECIPIENT_PREFIX : UC_PAYER_PREFIX),
    );
    foreach ($string_fields as $field => $suffix) {
      $data['uc_orders'][$prefix.'_'.$field] = array(
        'title' => t('!titleprefix !titlesuffix', $args + array('!titlesuffix' => $suffix)),
        'help' => $order_schema['fields'][$prefix.'_'.$field]['description'],
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
      );
    }
  }

  /**
   * Countries: added by sammys
   */

  $country_schema = drupal_get_schema('uc_countries');

  $country_views = array(
    'billing_countries' => array(
      'field' => 'billing_country',
      'prefix' => UC_PAYER_PREFIX,
    ),
    'delivery_countries' => array(
      'field' => 'delivery_country',
      'prefix' => UC_RECIPIENT_PREFIX,
    ),
  );

  foreach ($country_views as $key => $value) {
    $data['uc_orders'][$value['field']] = array(
      'title' => t($value['prefix'].' country'),
      'help' => t('Relate orders to '.str_replace('_', ' ', $value['field'])),
      'filter' => array(
        'handler' => 'uc_views_handler_filter_country',
      ),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'uc_countries',
        'relationship table' => $key,
        'field' => 'country_id',
        'label' => t($value['prefix'].' country'),
      ),
    );

    $data[$key]['table']['group'] = t('Ubercart order');

    $data[$key]['table']['join'] = array(
      'uc_orders' => array(
        'table' => 'uc_countries',
        'left_field' => $value['field'],
        'field' => 'country_id',
      ),
    );
    $data[$key]['country_id'] = array(
      'title' => t($value['prefix'].' country id'),
      'help' => t($order_schema['fields'][$value['field']]['description']),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      // Information for accepting an order id as an argument
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'country_iso_code_2',
        'numeric' => TRUE,
        'validate type' => 'country_id',
      ),
      // Information for accepting an order id as a filter
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      // Information for sorting on an order id.
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
    $data[$key]['country_name'] = array(
      'title' => t($value['prefix'].' country name'),
      'help' => t(str_replace(' ID ', ' ', $order_schema['fields'][$value['field']]['description'])),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );
    $data[$key]['country_iso_code_2'] = array(
      'title' => t($value['prefix'].' country ISO code (2 characters)'),
      'help' => t($country_schema['fields']['country_iso_code_2']['description']),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );
    $data[$key]['country_iso_code_3'] = array(
      'title' => t($value['prefix'].' country ISO code (3 characters)'),
      'help' => t($country_schema['fields']['country_iso_code_3']['description']),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );
  }

  /**
   * Zones: added by sammys
   */
  $zone_schema = drupal_get_schema('uc_zones');

  $zone_views = array(
    'billing_zones' => array(
      'field' => 'billing_zone',
      'prefix' => UC_PAYER_PREFIX,
    ),
    'delivery_zones' => array(
      'field' => 'delivery_zone',
      'prefix' => UC_RECIPIENT_PREFIX,
    ),
  );

  foreach ($zone_views as $key => $value) {
    $data['uc_orders'][$value['field']] = array(
      'title' => t($value['prefix'].' zone'),
      'help' => t('Relate orders to '.str_replace('_', ' ', $value['field'])),
      'filter' => array(
        'handler' => 'uc_views_handler_filter_zone',
      ),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'uc_zones',
        'relationship table' => $key,
        'field' => 'zone_id',
        'label' => t($value['prefix'].' zone'),
      ),
    );

    $data[$key]['table']['group'] = t('Ubercart order');

    $data[$key]['table']['join'] = array(
      'uc_orders' => array(
        'table' => 'uc_zones',
        'left_field' => $value['field'],
        'field' => 'zone_id',
      ),
    );
    $data[$key]['zone_id'] = array(
      'title' => t($value['prefix'].' zone id'),
      'help' => t($order_schema['fields'][$value['field']]['description']),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      // Information for accepting an order id as an argument
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name field' => 'zone_code',
        'numeric' => TRUE,
        'validate type' => 'zone_id',
      ),
      // Information for accepting an order id as a filter
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      // Information for sorting on an order id.
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
    $data[$key]['zone_name'] = array(
      'title' => t($value['prefix'].' zone name'),
      'help' => t(ereg_replace(' (id|ID) ', ' ', $order_schema['fields'][$value['field']]['description'])),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );

    $data[$key]['zone_code'] = array(
      'title' => t($value['prefix'].' zone code'),
      'help' => t(str_replace('of the ', 'of the '.strtolower($value['prefix']).' ', $zone_schema['fields']['zone_code']['description'])),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
      ),
    );
  }


  //Make the uc_cart_products table visible for Views module
  $data['uc_cart_products']['table']['group'] = t('Cart product');
  $data['uc_cart_products']['table']['join']['node'] = array(
      'left_field' => 'nid',
      'field' => 'nid',
  );
  $data['uc_cart_products']['table']['join']['users'] = array(
      'left_field' => 'uid',
      'field' => 'cart_id',
  );
  $data['uc_cart_products']['nid'] = array(
    'title' => t('Cart product id'),
    'help' => t('The nid of the product for in a cart.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
     'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_cart_products']['cart_id'] = array(
    'title' => t('Cart id'),
    'help' => t('The id of the cart (either user or session id).'),
    'field' => array(
      'handler' => 'uc_views_handler_field_cart_user',
      'click sortable' => TRUE,
    ),
     'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // the field to display in the summary.
      'numeric' => TRUE,
      'validate type' => 'cart_id',
    ),
     'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_cart_products']['qty'] = array(
    'title' => t('qty'),
    'help' => t('The amount ordered.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['uc_cart_products']['changed'] = array(
    'title' => t('Cart Product Line Changed Date'),
    'help' => t('The date the cart line was changed'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
     'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['uc_cart_products']['ordering'] = array(
    'title' => t('List position'),
    'help' => t('The default sort criteria in the catalog.'),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function uc_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'uc_views') . '/views',
    ),
    'handlers' => array(
      // filters
      'uc_views_handler_field_order_id' => array( 'parent' => 'views_handler_field',),
      'uc_views_handler_field_cart_user' => array('parent' => 'views_handler_field',),
      'views_handler_filter_order_status' => array('parent' => 'views_handler_filter_in_operator',),
      'uc_views_handler_filter_country' => array('parent' => 'views_handler_filter_in_operator',),
      'uc_views_handler_filter_zone' => array('parent' => 'views_handler_filter_in_operator',),
    ),
  );
}

/**
 * Conditionally add editablefields support.
 */
function uc_views_views_tables_alter(&$tables) {
}

