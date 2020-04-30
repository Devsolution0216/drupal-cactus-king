<?php
/* $Id: nodewords.admin.inc,v 1.1.2.4 2009/02/07 08:09:09 robrechtj Exp $ */

/**
 * @file
 * Assign META tags to nodes, vocabularies, terms and pages.
 */

/**
 * Menu callback: settings form.
 */
function nodewords_admin_settings_form() {
  $settings = _nodewords_get_settings();
  $form = array(
    '#submit' => array('nodewords_admin_settings_submit'),
  );

  $form['nodewords'] = array(
    '#tree' => TRUE,
  );
  $form['nodewords']['global'] = array(
    '#tree' => TRUE,
  );

  $form['nodewords']['global']['copyright'] = array(
    '#type' => 'textfield',
    '#title' => t('Global copyright'),
    '#default_value' => $settings['global']['copyright'],
    '#size' => 60,
    '#maxlength' => $settings['max_size'],
    '#description' => t('Enter a short copyright statement (one line) that will be used on all pages unless specifically set.'),
  );

  $form['nodewords']['global']['geourl'] = array(
    '#type' => 'textfield',
    '#title' => t('Global GeoURL'),
    '#default_value' => $settings['global']['geourl'],
    '#size' => 60,
    '#maxlength' => $settings['max_size'],
    '#description' => t('Enter a GeoURL (latitude, longitude) that will be used on all pages unless specifically set.'),
  );

  $form['nodewords']['global']['keywords'] = array(
    '#type' => 'textfield',
    '#title' => t('Global keywords'),
    '#default_value' => $settings['global']['keywords'],
    '#size' => 60,
    '#maxlength' => $settings['max_size'],
    '#description' => t('Enter a comma separated list of global keywords. These global keywords will be added after the page-specific keywords on all pages.'),
  );

  if (function_exists('taxonomy_get_vocabularies')) {
    $select = array();
    foreach (taxonomy_get_vocabularies() as $vocabulary) {
      $select[$vocabulary->vid] = check_plain($vocabulary->name);
    }
    if (count($select) > 0) {
      $form['nodewords']['keywords_vids'] = array(
        '#type' => 'select',
        '#title' => t('Auto-keywords vocabularies'),
        '#default_value' => $settings['keywords_vids'],
        '#options' => $select,
        '#description' => t('Select the vocabularies which contain terms you want to add to the keywords meta tag for nodes. The terms of these vocabularies are added before the global keywords but after the page-specific keywords.'),
        '#multiple' => TRUE,
      );
    }
  }

  $form['nodewords']['use_teaser'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the teaser of the page if the meta description is not set.'),
    '#default_value' => $settings['use_teaser'],
  );

  $form['nodewords']['global']['robots'] = array(
    '#type' => 'select',
    '#title' => t('Default robots meta tag'),
    '#options' => array(
      'index,follow' => 'ALL=INDEX,FOLLOW',
      'noindex,follow' => 'NOINDEX,FOLLOW',
      'index,nofollow' => 'INDEX,NOFOLLOW',
      'noindex,nofollow' => 'NONE=NOINDEX,NOFOLLOW',
    ),
    '#multiple' => FALSE,
    '#default_value' => $settings['global']['robots'],
    '#description' => t('The ROBOTS meta tag offers a simple mechanism to indicate to web robots and crawlers wether the page should be indexed (INDEX or NOINDEX) and whether links on the page should be followed (FOLLOW or NOFOLLOW). Here you can enter the default robots meta tag to use for all pages. If unsure, select "ALL=INDEX,FOLLOW".'),
  );

  $form['nodewords']['max_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Text length'),
    '#default_value' => $settings['max_size'],
    '#size' => 6,
    '#maxlength' => 6,
    '#description' => t('The maximum number of characters the content of a meta tag can contain.'),
  );

  $form['nodewords']['db_max_size'] = array(
    '#type' => 'value',
    '#value' => isset($settings['db_max_size']) ? $settings['db_max_size'] : 255,
  );

  $form['nodewords']['edit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tags to show on edit form'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Select the meta tags you want to be able to edit on the edit page of nodes, terms and vocabularies.'),
  );
  $form['nodewords']['head'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tags to output in html head'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Select the meta tags you want to appear in the HEAD section of the HTML pages.'),
  );

  foreach (_nodewords_get_possible_tags() as $name) {
    foreach (array('edit', 'head') as $where) {
      $form['nodewords'][$where][$name] = array(
        '#type' => 'checkbox',
        '#title' => ucfirst($name), //TODO: is this UTF8 safe?
        '#default_value' => $settings[$where][$name],
      );
    }
  }

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced options'),
  );

  $form['advanced']['nodewords-repeat'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat meta tags for lists'),
    '#default_value' => variable_get('nodewords-repeat', 0),
    '#description' => t('Some search engines punish sites that use the same meta tags on different pages. Uncheck this option if you want to suppress the repetition of the same meta tags on pages that use the pager - if unchecked, Drupal will only display the meta tags for the first page and not for subsequent pages. If unsure, select this option.'),
  );

  $form['advanced']['nodewords-use_front'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use front page meta tags'),
    '#default_value' => variable_get('nodewords-use_front', 1),
    '#description' => t('Check this option if you want to use the <a href="!front-page-url" title="Meta tags for front page">meta tags for the front page</a> even if the <a href="!site-settings-url" title="Site information">default front page</a> specified is a view, panel or node - in this case, the meta tags specified for the view, panel or node will be ignored. If you want to use the meta tags of the view, panel or node instead, uncheck this option. If unsure, select this option and specify the meta tags you want on the <a href="!front-page-url" title="Meta tags for front page">meta tags for the front page</a>.', array('!front-page-url' => url('admin/content/nodewords/frontpage'), '!site-settings-url' => url('admin/settings/site-information'))),
  );

  return system_settings_form($form);
}

/**
 * Custom submit handler for settings form
 **/
function nodewords_admin_settings_submit($form, &$form_state) {
  $info = variable_get('nodewords', array());

  $new_max = $form_state['values']['nodewords']['max_size'];
  $old_max = isset($info['db_max_size']) ? $info['db_max_size'] : 255;

  if ($new_max > $old_max) {
    $ret = array();
    
    db_change_field($ret, 'nodewords', 'content', 'content',
                    array(
                      'type' => 'varchar',
                      'length' => $new_max,
                      'not null' => FALSE,
                      'default' => '',
                      'description' => t('Content of meta tag value.'),
                    )
    );

    $form_state['values']['nodewords']['db_max_size'] = $new_max;
  }
}

/**
 * Menu callback: front page settings form.
 */
function nodewords_admin_frontpage_form(&$form_state) {
  $tags = _nodewords_load('page', '');

  $form = array();
  $form['nodewords'] = _nodewords_form('page', $tags);

  unset($form['nodewords']['#title']);
  unset($form['nodewords']['#type']);
  if (empty($form['nodewords'])) {
    $form['nodewords'] = array('#value' => t('Currently no meta tags can be assigned to the front page because you have disabled all tags to show on the edit forms. <a href="!nodewords-settings-url" title="meta tags settings">Enable some meta tags to show on edit forms</a> first.', array('!nodewords-settings-url' => url('admin/content/nodewords'))));
  }
  elseif (!variable_get('nodewords-use_front', 1)) {
    $form['nodewords'] = array('#value' => t('You can not assign meta tags for the front page here because you have disabled them at the <a href="!nodewords-settings-url" title="Meta tags settings">meta tags settings page</a>. Instead, the meta tags for the view, panel or node you have set as front page will be used.', array('!nodewords-settings-url' => url('admin/content/nodewords'))));
  }
  else {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#weight' => 40,
    );
  }

  return $form;
}

function nodewords_admin_frontpage_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
    _nodewords_set('page', '', $form_state['values']['nodewords']);
    drupal_set_message(t('The meta tags for the front page have been saved.'));
    $form_state['redirect'] = 'admin/content/nodewords/frontpage';
  }
}
