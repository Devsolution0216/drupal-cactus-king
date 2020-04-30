<?php
// $Id: nodeorder.admin.inc,v 1.1.2.8 2009/01/17 16:36:04 pvanderspek Exp $

/**
 * @file
 * Admin page callbacks for the nodeorder module.
 */
 
 /**
 * Menu callback for nodeorder/order.
 */
function nodeorder_admin_display($tid) {
  return drupal_get_form('nodeorder_admin_display_form', $tid);
}

/**
 * Generate main blocks administration form.
 */
function nodeorder_admin_display_form(&$form_state, $tid) {
  // Build form tree
  $form = array(
    '#tree' => TRUE
  );
  
  $term = taxonomy_get_term($tid);
  drupal_set_title(t('Order nodes for <em>%term_name</em>', array( '%term_name' => $term->name)));
  
  $order = 'n.sticky DESC, tn0.weight_in_tid';
  $result = nodeorder_select_nodes(array($tid), 'and', 0, FALSE, $order, 0);
  $nodes = array();
  $node_count = 1;
  $options = array();
  while ($node = db_fetch_object($result)) {
    if (!isset($node->nodeorder)) {
      $node->nodeorder = array();

      // Store an element called 'nodeorder' that contains
      // an associative array of tid to weight_in_tid...
      $weights = db_query('SELECT tid, weight_in_tid FROM {term_node} WHERE nid = %d', $node->nid);
      while ($term_node = db_fetch_object($weights)) {
        $node->nodeorder[$term_node->tid] = $term_node->weight_in_tid;
      }
    }
    
    $nodes[] = $node;
    $options[$node_count] = $node_count;
    $node_count++;
  }
  
  // Weights range from -delta to +delta, so delta should be at least half
  // of the amount of blocks present. This makes sure all blocks in the same
  // region get an unique weight.
  $weight_delta = round($node_count / 2);
  
  $list_tr_id = 'node-sort-list-'. $tid;
  foreach ($nodes as $node) {
    $key = $list_tr_id .'_'. $node->nid;
  
    $form[$key]['tid'] = array(
      '#type' => 'value',
      '#value' => $tid,
    );
    $form[$key]['nid'] = array(
      '#type' => 'value',
      '#value' => $node->nid,
    );
    $form[$key]['info'] =  array(
      '#value' => check_plain($node->title),
    );
    $form[$key]['weight'] = array(
      '#type' => 'select',
      '#default_value' => $node->nodeorder[$tid],
      '#options' => $options
    );
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save order'),
    '#disabled' => TRUE 
  );

  return $form;
}

/**
 * Process main blocks administration form submission.
 */
function nodeorder_admin_display_form_submit($form, &$form_state) {
  $sql = "UPDATE {term_node} SET weight_in_tid = %d WHERE tid = %d AND nid = %d";
  $tid = -1;

  foreach ($form_state['values'] as $node) {
    // Only take form elements that are blocks.
    if (is_array($node) && array_key_exists('tid', $node)) {
      db_query($sql, $node['weight'], $node['tid'], $node['nid']);
      
      $tid = $node['tid'];
    }
  }

  drupal_set_message(t('The node orders have been updated.'));
  cache_clear_all();

  $form_state['redirect'] = 'nodeorder/term/'. $tid;
  return;
}

/**
 * Process variables for nodeorder-admin-display.tpl.php.
 *
 * The $variables array contains the following arguments:
 * - $form
 *
 * @see nodeorder-admin-display.tpl.php
 * @see theme_nodeorder_admin_display()
 */
function template_preprocess_nodeorder_admin_display_form(&$variables) { 
  foreach (element_children($variables['form']) as $i) {
    $node = &$variables['form'][$i];
  
    // Only take form elements that are nodes.
    if (is_array($node) && array_key_exists('info', $node)) {
      $variables['form'][$i]['weight']['#attributes']['class'] = 'nodeorder-weight';
      $variables['node_listing'][$i]->row_class = isset($block['#attributes']['class']) ? $block['#attributes']['class'] : '';
      $variables['node_listing'][$i]->node_title =  drupal_render($node['info']);
      $variables['node_listing'][$i]->weight = drupal_render($node['weight']);
      $variables['node_listing'][$i]->tid =  drupal_render($node['tid']);
      $variables['node_listing'][$i]->nid =  drupal_render($node['nid']);
    }
  }

  $variables['form_submit'] = drupal_render($variables['form']);
}