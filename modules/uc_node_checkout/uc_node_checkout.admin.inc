<?php
// $Id: uc_node_checkout.admin.inc,v 1.1.2.4 2009/07/30 15:58:42 rszrama Exp $

/**
 * @file
 * Defines administration pages for the node checkout module.
 */

// Displays the node checkout settings table/form.
function uc_node_checkout_admin() {
  $nc_map = uc_node_checkout_product_map();
  $types = node_get_types('types');
  $rows = array();

  $header = array(t('Node type'), t('Product'), t('View'), t('Actions'));

  // Loop through all the node types on the site.
  foreach ($types as $type => $info) {
    // Look for a product node association.
    if ($nc_map[$type]['nid']) {
      $product = node_load($nc_map[$type]['nid']);
    }
    else {
      $product = FALSE;
    }

    // Look for a View association.
    $view = variable_get('uc_node_checkout_'. $type .'_view', '');

    // Add the node type's data to the table.
    $rows[] = array(
      $info->name,
      $product ? l($product->model, 'node/'. $product->nid) : t('n/a'),
      $nc_map[$type]['view'] ? check_plain($nc_map[$type]['view']) : t('n/a'),
      l(t('edit'), 'admin/store/settings/node-checkout/'. $type),
    );
  }

  return theme('table', $header, $rows);
}

// Displays the form to map a product to a node type.
function uc_node_checkout_type_form(&$form_state, $type) {
  $nc_map = uc_node_checkout_product_map();
  $form = array();

  $options = array(0 => t('<None>'));

  $result = db_query("SELECT n.nid, p.model, n.title FROM {uc_products} AS p INNER JOIN {node} AS n ON p.vid = n.vid ORDER BY p.model");
  while ($product = db_fetch_object($result)) {
    $options[$product->nid] = '('. $product->model .') '. $product->title;
  }

  $form['type'] = array(
    '#type' => 'value',
    '#value' => $type->type,
  );

  $form['product_nid'] = array(
    '#type' => 'textfield',
    '#title' => t('Product NID'),
    '#description' => t("When a %type node is created, one of the chosen product is added to the user's cart.<br />Start typing a SKU or title in this field to view autocomplete options.<br />Empty this field to disable node checkout for this node type.", array('%type' => $type->name)),
    '#default_value' => $nc_map[$type->type]['nid'],
    '#autocomplete_path' => 'uc_node_checkout/autocomplete',
  );

  if (module_exists('views')) {
    $views = array();

    // Generate an option list from all user defined and module defined views.
    foreach (views_get_all_views() as $view_key => $view_value) {
      // Only include node Views.
      if ($view_value->base_table == 'node') {
        foreach ($view_value->display as $display_key => $display_value) {
          $views[$view_key .'|'. $display_key] = check_plain($view_key .': '. $display_value->display_title);
        }
      }
    }

    $form['view'] = array(
      '#type' => 'select',
      '#title' => t('View'),
      '#description' => t('Optional. When a user creates a %type node, allow them to choose the associated product from this View.<br />If a View is specified, the Product NID setting will be ignored.', array('%type' => $type->name)),
      '#options' => array_merge(array('' => ' '), $views),
      '#default_value' => $nc_map[$type->type]['view'],
    );
  }

  $restrictions = variable_get('uc_node_checkout_'. $type->type .'_restrictions', array());

  $form['disable_preview'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the preview button for this node type for users without %access permission.', array('%access' => t('edit any @type content', array('@type' => $type->type)))),
    '#description' => t('This setting is recommended when using the general node checkout redirections.'),
    '#default_value' => in_array('preview', $restrictions),
  );

  // Integrate w/ content module from CCK to restrict field types from users
  // without access.
  if (module_exists('content')) {
    $cck_type = content_types($type->type);

    if (!empty($cck_type['fields'])) {
      $options = array();

      foreach ($cck_type['fields'] as $key => $value) {
        $options[$key] = check_plain($value['widget']['label']);
      }

      $form['restricted_fields'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Restricted node fields'),
        '#description' => t('Selected fields will only appear on the node form for users with %access permission.', array('%access' => t('edit @type content', array('@type' => $type->type)))),
        '#options' => $options,
        '#default_value' => $restrictions,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function uc_node_checkout_type_form_submit($form, &$form_state) {
  // Save the product node ID.
  if ($form_state['values']['product_nid'] || $form_state['values']['view']) {
    db_query("UPDATE {uc_node_checkout_types} SET product_nid = %d, node_view = '%s' WHERE node_type = '%s'", $form_state['values']['product_nid'], $form_state['values']['view'], $form_state['values']['type']);
    if (!db_affected_rows()) {
      db_query("INSERT INTO {uc_node_checkout_types} (node_type, product_nid, node_view) VALUES ('%s', %d, '%s')", $form_state['values']['type'], $form_state['values']['product_nid'], $form_state['values']['view']);
    }
  }
  else {
    db_query("DELETE FROM {uc_node_checkout_types} WHERE node_type = '%s'", $form_state['values']['type']);
  }

  // Save the restricted fields settings.
  $fields = array();

  foreach ((array) $form_state['values']['restricted_fields'] as $key => $value) {
    if ($value) {
      $fields[] = $key;
    }
  }

  if ($form_state['values']['disable_preview']) {
    $fields[] = 'preview';
  }

  variable_set('uc_node_checkout_'. $form_state['values']['type'] .'_restrictions', $fields);

  $form_state['redirect'] = 'admin/store/settings/node-checkout';
}

// Displays the settings form for node checkout behavior/display settings.
function uc_node_checkout_settings_form() {
  $form = array();

  $form['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behavior settings'),
  );
  $form['behavior']['uc_node_checkout_add_to_cart_node_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect customers to the node add form when they click add to cart buttons of node checkout associated products.'),
    '#description' => t('If this setting is turned off, make sure that the associated products are inaccessible to your customers.'),
    '#default_value' => variable_get('uc_node_checkout_add_to_cart_node_form', TRUE),
  );
  $form['behavior']['uc_node_checkout_node_access'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use UC Node Checkout to prevent anonymous node add access for node types it governs.'),
    '#description' => t('Enable anonymous creation of node checkout node types and anonymous users will be instructed to create an account.'),
    '#default_value' => variable_get('uc_node_checkout_node_access', TRUE),
  );
  $form['behavior']['uc_node_checkout_submit_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect customers to their cart after adding or editing a node checkout governed node.'),
    '#description' => t('Users who have "edit node_type content" permission are exempt from this redirect.'),
    '#default_value' => variable_get('uc_node_checkout_submit_redirect', TRUE),
  );
  $form['behavior']['uc_node_checkout_view_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect customers to their cart when they try to view a node governed by node checkout.'),
    '#description' => t('Users who have "edit node_type content" permission are exempt from this redirect.'),
    '#default_value' => variable_get('uc_node_checkout_view_redirect', TRUE),
  );
  $form['behavior']['uc_node_checkout_delete_orphans'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete products associated with nodes from shopping carts when the nodes are deleted.'),
    '#default_value' => variable_get('uc_node_checkout_delete_orphans', TRUE),
  );
  $form['behavior']['uc_node_checkout_delete_nodes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete nodes whose creators remove the associated product from their cart.'),
    '#default_value' => variable_get('uc_node_checkout_delete_nodes', TRUE),
  );

  if (module_exists('uc_stock')) {
    $form['stock'] = array(
      '#type' => 'fieldset',
      '#title' => t('Stock management'),
    );
    $form['stock']['uc_node_stock_prevent_checkout'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prevent checkout when a customer tries to purchase an out of stock node.'),
      '#default_value' => variable_get('uc_node_stock_prevent_checkout', TRUE),
    );
    $form['stock']['uc_node_stock_prevent_add'] = array(
      '#type' => 'checkbox',
      '#title' => t('Prevent node creation when a customer tries to create an out of stock node.'),
      '#default_value' => variable_get('uc_node_stock_prevent_add', FALSE),
    );
    $form['stock']['uc_node_stock_prevent_add_redirect'] = array(
      '#type' => 'textfield',
      '#title' => t('Out of stock redirect'),
      '#description' => t('Specify a redirect page if a customer is prevented from creating a node due to stock.'),
      '#default_value' => variable_get('uc_node_stock_prevent_add_redirect', 'cart'),
      '#size' => 32,
      '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    );
  }

  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display settings'),
  );
  $form['display']['uc_node_checkout_alter_node_submit_button'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alter the node form submit button to say "Add to cart" when a node is being created.'),
    '#default_value' => variable_get('uc_node_checkout_alter_node_submit_button', TRUE),
  );
  $form['display']['uc_node_checkout_cart_titles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Change cart item titles into edit links for their associated nodes.'),
    '#description' => t('Only works for the cart view form; you must implement a custom solution for the cart block.'),
    '#default_value' => variable_get('uc_node_checkout_cart_titles', TRUE),
  );
  $form['display']['uc_node_checkout_click_to_edit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a "click to edit" message or link on the cart view form for node checkout products.'),
    '#description' => t('Override theme_uc_cart_click_to_edit() in your theme to alter the display of this.'),
    '#default_value' => variable_get('uc_node_checkout_click_to_edit', TRUE),
  );
  $form['display']['uc_node_cart_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display the node cart teaser on the cart view form for node checkout products.'),
    '#description' => t('Override theme_uc_node_cart_teaser() in your theme to alter the display of this.'),
    '#default_value' => variable_get('uc_node_cart_teaser', TRUE),
  );
  $form['display']['order'] = array(
    '#type' => 'fieldset',
    '#title' => t('Order product display'),
    '#description' => t('These settings require the Attribute module to be enabled and will add an attribute line to the node checkout product on order view screens.'),
  );
  $form['display']['order']['uc_node_order_product_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display a node teaser as an attribute/option combination for nodes on orders.'),
    '#default_value' => variable_get('uc_node_order_product_display', TRUE),
    '#disabled' => !module_exists('uc_attribute'),
  );
  $form['display']['order']['uc_node_order_product_teaser_override'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add to the default node cart teaser using these settings.'),
    '#default_value' => variable_get('uc_node_order_product_teaser_override', FALSE),
  );
  $form['display']['order']['uc_node_order_product_attribute'] = array(
    '#type' => 'textfield',
    '#title' => t('Order product attribute'),
    '#description' => t('Specify the name of the attribute.'),
    '#default_value' => variable_get('uc_node_order_product_attribute', 'ID'),
  );
  $form['display']['order']['uc_node_order_product_option'] = array(
    '#type' => 'textfield',
    '#title' => t('Order product option'),
    '#description' => t('Specify a pattern for the option string; uses node tokens like [nid] and [title].'),
    '#default_value' => variable_get('uc_node_order_product_option', '[nid] - [title]'),
  );
  $form['display']['order']['tokens'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node tokens'),
    '#description' => t('Use these tokens in the attribute and option fields above.  They will be replaced with values from the node checkout nodes on the order pages. Do not use tokens ending in -raw for these settings!'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['display']['order']['tokens']['data'] = array(
    '#value' => '<div>'. theme('token_help', 'node') .'</div>',
  );

  return system_settings_form($form);
}

// Returns an autocomplete list for nodes on the node type settings form.
function uc_node_checkout_autocomplete($string = '') {
  $matches = array();

  if ($string) {
    $result = db_query_range("SELECT n.nid, n.title, p.model, p.unique_hash FROM {uc_products} AS p LEFT JOIN {node} AS n ON n.nid = p.nid WHERE p.unique_hash != '' AND (LOWER(n.title) LIKE '%s%%' OR LOWER(p.model) LIKE '%s%%')", strtolower($string), strtolower($string), 0, 10);
    while ($node = db_fetch_object($result)) {
      $matches[$node->nid] = t('@title [@sku]', array('@title' => $node->title, '@sku' => $node->model));
    }
  }

  print drupal_to_js($matches);
  exit();
}
