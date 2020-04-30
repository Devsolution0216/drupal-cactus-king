<?php
// $Id: nodewords_bypath.forms.inc,v 1.1.2.3.2.3 2009/03/22 03:30:07 univate Exp $

/**
 * @file The form logic for the meta tag by path module.
 */


/**
 * Build the settings form for the module.
 *
 * @return array The form.
 */
function nodewords_bypath_admin_overview() {
  $form  = array();
  $rules = _nodewords_bypath_load_all();

  if (empty($rules)) {
    $form['emptytext']['#value'] = t('No rules found. <a href="@newrule">Create a new rule to get started.</a>', array('@newrule' => url('admin/content/nodewords/path/new')));
  }
  else {
    foreach ($rules as $rule) {
      $form[$rule->id]['id'] = array(
        '#type'  => 'value',
        '#value' => $rule->id,
      );
      
      $form[$rule->id]['name']   = array('#value' => $rule->name);
      $form[$rule->id]['weight'] = array('#value' => $rule->weight);
      $form[$rule->id]['edit']   = array('#value' => l(t('Edit'), 'admin/content/nodewords/path/'. $rule->id .'/edit'));
      $form[$rule->id]['delete'] = array('#value' => l(t('Delete'), 'admin/content/nodewords/path/'. $rule->id .'/delete'));
    }
  }
  
  return $form;
}


/**
 * Generate the form for creating a new custom title rule or editing an
 * existing one.
 *
 * @param $rule An existing rule to edit. If specified, this rule will be used
 *   to populate the form fields.
 *
 * @return array The form.
 */
function nodewords_bypath_form(&$form_state, $rule = NULL) {
  $form = array();

  if (!$rule) {
    $rule = new stdClass;
  }

  //------------------------------------------------------------------------
  // Basic Info
  $form['meta_rule'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Meta Tag Rule'),
    '#collapsible' => TRUE,
    '#weight'      => -10,
  );
  
  $form['meta_rule']['rule_id'] = array(
    '#type'  => 'value',
    '#value' => $rule->id,
  );
  
  $form['meta_rule']['name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Name'),
    '#default_value' =>  $rule->name,
    '#description'   => t('A short name to help you identify this rule when it\'s shown in the list view.'),
  );
  
  $form['meta_rule']['weight'] = array(
    '#type'        => 'select',
    '#title'       => t('Weight'),
    '#default_value' => ($rule) ? $rule->weight : 0,
    '#options'     => drupal_map_assoc(range(-10, 10)),
    '#description' => t('This determines the order that rules are evaluated. Rules with lower weight values are evaluated before rules with higher weights. Evaluation stops at the first rule that matches the path.'),
  );

  $options = array(
    1 => t('Apply rule only to the listed pages.'),
    2 => t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).'),
  );

  $form['meta_rule']['type'] = array(
    '#type'        => 'radios',
    '#title'       => t('Rule Application'),
    '#default_value' => ($rule) ? $rule->type : 1,
    '#options'     => $options,
    '#description' => t('Determines the method used apply the meta tag rule.'),
  );

  //------------------------------------------------------------------------
  // Path information.
  $subs = array(
    '%blog'          => 'blog', 
    '%blog-wildcard' => 'blog/*', 
    '%front'         => '<front>',
    '%php'           => '<?php ?>'
  );
  
  $description = t('Enter one page per line as Drupal paths. The "*" character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page. If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', $subs);
  
  $form['meta_rule']['paths'] = array(
      '#type'          => 'textarea',
      '#title'         => t('Path(s)'),
      '#default_value' => ($rule) ? $rule->path_expr : '',
      '#description'   => $description,
  );

  //------------------------------------------------------------------------
  // The tags themsevles
  $subs = array('%none' => NODEWORDS_NONE, '%robots' => 'robots', '%keywords' => 'keywords');
  $description = t('The values in these fields will be assigned to the corresponding tags when a visitor loads a URI matching the path above. Leave a field blank to use the global default for that tag, or enter %none to prevent the tag from being output. Note that the %node value will not force the %robots or %keywords tags.', $subs);
  $form['meta_tags'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Meta Tags'),
    '#description' => $description,
    '#collapsible' => TRUE,
    '#weight'      => -5,
  );    

  $settings = _nodewords_get_settings();
  
  foreach (_nodewords_get_possible_tags() as $tag) {
    $function = 'nodewords_'. $tag .'_form';
    if ($settings['edit'][$tag] && function_exists($function)) {
      $default = ($rule) ? $rule->tags[$tag] : '';
      $element = $function('page', $default, $settings);
      if ($element) {
        $form['meta_tags']['meta_tag_'. $tag] = $element;
      }
    }
  }

  //------------------------------------------------------------------------
  $form['submit'] = array(
    '#type'  => 'submit', 
    '#value' => ($rule) ? t('Update Rule') : t('Save Rule'),
  );
  
  $form['cancel'] = array(
    '#type'  => 'submit',
    '#value' => t('Cancel'),
  );
  
  return $form;
}


/**
 * Save the data from the pattern editing/creation form.
 *
 * @param $form_id mixed The ID of the form.
 * @param $form_values array The form values. 
 */
function nodewords_bypath_form_submit($form, &$form_state) {
  // -------------------------------------------------------------------------
  // Bail out on cancel.
  if ($form_state['values']['op'] == t('Cancel')) {
    $form_state['redirect'] = 'admin/content/nodewords/path';
    return;
  }
  
  // -------------------------------------------------------------------------
  // Build the rule object and save it.
  $rule            = new stdClass;
  $rule->id        = $form_state['values']['rule_id'];
  $rule->name      = trim($form_state['values']['name']);
  $rule->path_expr = trim($form_state['values']['paths']);
  $rule->weight    = intval($form_state['values']['weight']);
  $rule->type      = intval($form_state['values']['type']);
  $rule->tags      = array();
  
  $viewable_tags = _nodewords_get_viewable_tags();
  foreach ($viewable_tags as $tag_name) {
    if (array_key_exists('meta_tag_'. $tag_name, $form_state['values'])) {
      $rule->tags[$tag_name] = trim($form_state['values']['meta_tag_'. $tag_name]);
    }
  }
  
  nodewords_bypath_rule_save($rule);
  if ($rule->id > -1) {
    drupal_set_message(t('Updated meta tag rule %name', array('%name' => $rule->name)));
  }
  else {
    drupal_set_message(t('', array('%name' => $rule->name)));
  }
  
  $form_state['redirect'] = 'admin/content/nodewords/path';
  return; 
}


/**
 * Generate the confirmation form for deleting a title.
 *
 * @param $rule The rule to delete.
 *
 * @return array The form.
 */
function nodewords_bypath_delete_form(&$form_state, $rule) {
  $form = array();
  
  $form['pattern_id'] = array(
    '#type'  => 'value',
    '#value' => $rule->id,
  );
  
  $form['pattern_name'] = array(
    '#type'  => 'value',
    '#value' => $rule->name,
  );
  
  $question = t('You are about to remove the meta tag rule "%name".',
                array('%name' => $rule->name));
  $desc     = t('This action cannot be undone.');
                
  return confirm_form($form, $question, 'admin/content/nodewords/path', $desc, t('Delete'), t('Cancel'));
}


/**
 * Handle the delete form submission.
 *
 * @param $form_id mixed The form's ID.
 * @param $form_values array The form values.
 *
 * @return string The path to send the browser to after the form is
 *         submitted.
 */
function nodewords_bypath_delete_form_submit($form, &$form_state) {
  $id = $form_state['values']['pattern_id'];
  
  db_query('DELETE FROM {nodewords_bypath_rules} WHERE id = %d', $id);
  db_query('DELETE FROM {nodewords_bypath_tags} WHERE rule_id = %d', $id);
  
  drupal_set_message(t('Meta tag path rule "%name" has been deleted.', array('%name' => $form_state['values']['pattern_name'])));
  
  $form_state['redirect'] = 'admin/content/nodewords/path';
  return; 
}


/**
 * Generate the token reference.
 *
 * @return array The form.
 */
function nodewords_bypath_tokenref_form() {
  $form = array();
  
  $tokens = token_get_list();
  
  // -------------------------------------------------------------------------
  // The global tokens section
  $form['global_tokens'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Global Tokens'),
    '#collapsible' => TRUE,
    '#weight'      => -5,
    '#description' => t('Global tokens are available site wide. They may be used for meta tag rules that affect any page.'),
  );
  
  foreach ($tokens['global'] as $token => $description) {
    $form['global_tokens'][$token]['left'] = array(
      '#type'  => 'item',
      '#value' => '['. $token .']',
    );
    
    $form['global_tokens'][$token]['right'] = array(
      '#type'  => 'item',
      '#value' => $description,
    );
  }
  
  // -------------------------------------------------------------------------
  // The node tokens section
  $form['node_tokens'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Node Tokens'),
    '#collapsible' => TRUE,
    '#weight'      => -3,
    '#description' => t('Node tokens are available for page-level node presentation.'),
  );
  
  foreach ($tokens['node'] as $token => $description) {
    $form['node_tokens'][$token]['left'] = array(
      '#type'  => 'item',
      '#value' => '['. $token .']',
    );
    
    $form['node_tokens'][$token]['right'] = array(
      '#type'  => 'item',
      '#value' => $description,
    );
  }

  // -------------------------------------------------------------------------
  // Other tokens section
  $form['other_tokens'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Other Tokens'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#weight'      => 0,
    '#description' => t('All other tokens.'),
  );

  foreach ($tokens as $token_type => $token_list) {
    if ($token_type == 'node' || $token_type == 'global') continue;

    foreach ($token_list as $token => $description) {
      $form['other_tokens'][$token]['left'] = array(
        '#type'  => 'item',
        '#value' => '['. $token .']',
      );

      $form['other_tokens'][$token]['right'] = array(
        '#type'  => 'item',
        '#value' => $description,
      );
    }
  }
  
  return $form;
}

/**
 * Theme the token reference form.
 *
 * @param $form array The token reference form.
 *
 * @return string The themed form.
 */
function theme_nodewords_bypath_tokenref_form($form) {
  // -------------------------------------------------------------------------
  // The global tokens.
  $rows = array();
  foreach ($form['global_tokens'] as $name => $element) {
    if (isset($element['left']) && is_array($element['left'])) {
      $rows[] = array(
        array(
          'data'  => drupal_render($element['left']), 
        ),
        array(
          'data' => drupal_render($element['right']),
        ),
      );
      
      unset($form['global_tokens'][$name]);
    }
  }

  $form['global_tokens']['tokens'] = array(
    '#value' => theme('table', array(), $rows),
  );
  
  // -------------------------------------------------------------------------
  // The node tokens.
  $rows = array();
  foreach ($form['node_tokens'] as $name => $element) {
    if (isset($element['left']) && is_array($element['left'])) {
      $rows[] = array(
        array(
          'data' => drupal_render($element['left']), 
        ),
        array(
          'data' => drupal_render($element['right']),
        ),
      );
      
      unset($form['node_tokens'][$name]);
    }
  }

  $form['node_tokens']['tokens'] = array(
    '#value' => theme('table', array(), $rows),
  );
  
  // -------------------------------------------------------------------------
  // The other tokens.
  $rows = array();
  foreach ($form['other_tokens'] as $name => $element) {
    if (isset($element['left']) && is_array($element['left'])) {
      $rows[] = array(
        array(
          'data' => drupal_render($element['left']), 
        ),
        array(
          'data' => drupal_render($element['right']),
        ),
      );
      
      unset($form['other_tokens'][$name]);
    }
  }

  $form['other_tokens']['tokens'] = array(
    '#value' => theme('table', array(), $rows),
  );


  return drupal_render($form);
}


/**
 * Theme the table in the admin overview form.
 *
 * @param $form array The form elements to theme.
 *
 * @return string The rendered form elements.
 */
function theme_nodewords_bypath_admin_overview($form) {
  $output = '';
  if (!$form['emptytext']) {
    $rows = array();
    foreach ($form as $name => $element) {
      if (isset($element['name']) && is_array($element['name'])) {
        $rows[] = array(
          drupal_render($element['name']),
          drupal_render($element['weight']),
          drupal_render($element['edit']),
          drupal_render($element['delete'])
        );
        unset($form[$name]);
      }
    }
    $header = array(t('Name'), t('Weight'), t('Edit'), t('Delete'));
    $output = theme('table', $header, $rows);
  }
  $output .= drupal_render($form);

  return $output;
}

