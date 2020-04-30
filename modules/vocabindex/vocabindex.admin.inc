<?php
// $Id: vocabindex.admin.inc,v 1.1.2.3.2.60 2008/12/19 20:03:38 xano Exp $

/**
 * @file
 * The Vocabulary Index administration section.
 */

/**
 * Admin general settings page.
 *
 * @ingroup forms
 * @see vocabindex_admin_submit()
 *
 * @return
 *   Type: array; A Drupal form.
 */
function vocabindex_admin() {
  $form['#submit'] = array('vocabindex_admin_submit');

  $form['vocabindex_transliteration'] = array(
    '#type' => 'checkbox',
    '#title' => t('Character transliteration'),
    '#description' => t('Group terms by the <a href="!wiki_latin_alphabet">modern Latin</a> equivalent of their first letter for alphabetical views. <a href="!transliteration_info">More information</a>.', array('!wiki_latin_alphabet' => 'http://en.wikipedia.org/wiki/Latin_alphabet/', '!transliteration_info' => url('admin/help/vocabindex', array('fragment' => 'transliteration')))),
    '#default_value' => variable_get('vocabindex_transliteration', FALSE),
  );

  $form['vocabindex_pager'] = array(
    '#type' => 'textfield',
    '#title' => t('Terms per page'),
    '#description' => t('The amount of terms to display per page for browsable and alphabetical views. Use 0 to disable paging.'),
    '#default_value' => variable_get('vocabindex_pager', 25),
    '#maxlength' => 3,
    '#size' => 3,
    '#element_validate' => array('vocabindex_integer_validate'),
  );

  $form['vocabindex_caching'] = array(
    '#type' => 'fieldset',
    '#title' => t('Caching'),
  );

  $form['vocabindex_caching']['vocabindex_cache_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache lifetime'),
    '#description' => t('Specified in minutes. Use 0 to disable caching or if you are using a taxonomy access control module.'),
    '#default_value' => variable_get('vocabindex_cache_lifetime', 60),
    '#maxlength' => 3,
    '#size' => 3,
    '#element_validate' => array('vocabindex_integer_validate'),
  );

  $form['vocabindex_caching']['vocabindex_cache_clear'] = array(
    '#type' => 'checkbox',
    '#title' => t('Clear cache'),
  );

  return system_settings_form($form);
}

/**
 * Form submission handler for vocabindex_admin().
 *
 * @ingroup forms
 * @see vocabindex_admin()
 */
function vocabindex_admin_submit($form, &$form_state) {
  $clear_cache = FALSE;
  // Check each case in which the cache should be cleared.
  $values = $form_state['values'];
  if ($values['vocabindex_cache_lifetime'] != variable_get('vocabindex_cache_lifetime', 60)) {
    $clear_cache = TRUE;
  }
  elseif ($values['vocabindex_transliteration'] != variable_get('vocabindex_transliteration', FALSE)) {
    $clear_cache = TRUE;
  }
  elseif ($values['vocabindex_cache_clear'] == TRUE) {
    $clear_cache = TRUE;
  }
  // Clear the cache if any of the previous checks returned TRUE.
  if ($clear_cache == TRUE) {
    cache_clear_all('vocabindex', 'cache', TRUE);
    drupal_set_message(t('The cache has been cleared.'));
  }
}

/**
 * Validate the cache lifetime element used on the admin settings page.
 *
 * @param $element
 *  Type: aray; The form element to validate.
 */
function vocabindex_integer_validate($element) {
  if (preg_match('/\D/', $element['#value']) == 1) {
    form_set_error($element['#name'], t('%element_title may only contain numbers.', array('%element_title' => $element['#title'])));
  }
}

/**
 * Validate a menu path.
 *
 * @param $element
 *   Type: array; The form element to validate.
 */
function vocabindex_path_validate($element) {
  $path = $element['#value'];
  $name = $element['#name'];

  // If the path is empty, return to prevent form errors from popping up.
  if (empty($path)) {
  return;
  }

  // Prepare the path for validation.
  $path = drupal_strtolower($path);
  $path = preg_replace('#^/|/$#', '', $path);

  // Check for illegal characters.
  if (strpos($path, '%') !== FALSE) {
    form_set_error($name, t('Paths may not contain a percentage sign.'));
  }

  // The name pattern for path fields is 'vocabindex_VID_path'.
  $vid = preg_replace('#.+?_(.+?)_.+?$#', '\\1', $name);
  $count_vocabindex = db_result(db_query("SELECT COUNT(vid) FROM {vocabindex} WHERE vid = %d AND path = '%s'", $vid, $path));
  if ($count_vocabindex == 0) {
    // Check for existing menu paths.
    $count_menu_links = db_result(db_query("SELECT COUNT(link_path) FROM {menu_links} WHERE '%s' LIKE link_path", $path));
    if ($count_menu_links > 0) {
      form_set_error($name, t('Path is already used by a menu link.'));
    }
    // Check for existing aliases.
    elseif (drupal_lookup_path('source', $path) == TRUE) {
      form_set_error($name, t('Path is already used as an alias.'));
    }
  }
}

/**
 * Admin index pages/blocks.
 *
 * Display the form to add new index pages or blocks or to alter existing ones.
 * If no vocabularies exist a message is being displayed instead of the form.
 *
 * @param $type
 *   Type: constant; Either VOCABINDEX_VI_PAGE or VOCABINDEX_VI_BLOCK.
 *
 * @return
 *   Type: string; Either a rendered form or an empty string.
 */
function vocabindex_admin_vi($type) {
  if (count(vocabindex_vi_load($type, 0, FALSE))) {
    return drupal_get_form('vocabindex_admin_vi_form', $type);
  }
  else {
    drupal_set_message(t('You haven\'t yet got any vocabularies to enable an index for; you may create them at <a href="!link">the Taxonomy page</a>.', array('!link' => url(_vocabindex_menu_paths('taxonomy')))), 'error');

    return '';
  }
}

/**
 * The Vocabulary Index administration form to administer VIs.
 *
 * @ingroup forms
 * @see vocabindex_admin_vi_form_submit()
 *
 * @param $form
 *   Type: array; Internal use only.
 * @param $type
 *   Type: constant; VOCABINDEX_VI_PAGE to display the Index Pages form or
 *   VOCABINDEX_VI_BLOCK to display the Index Blocks form.
 *
 * @return
 *   Type: array; A Drupal form.
 */
function vocabindex_admin_vi_form($form, $type) {
  $vis = vocabindex_vi_load($type, 0, FALSE);
  $form = array();
  foreach ($vis as $vi) {
    $id = 'vocabindex_' . $vi->vid . '_';

    $form[$id . 'name'] = array(
      '#value' => check_plain($vi->name),
    );

    if ($type == VOCABINDEX_VI_PAGE) {
      if ($vi->enabled) {
        $description = t('Currently located at !location.', array('!location' => l('/' . $vi->path, $vi->path)));
      }
      else {
        $description = t('There is no index page set for this vocabulary.');
      }

      $form[$id . 'path'] = array(
        '#type' => 'textfield',
        '#description' => $description,
        '#default_value' => check_plain($vi->path),
        '#maxlength' => '255',
        '#size' => 30,
        '#element_validate' => array('vocabindex_path_validate'),
      );
    }
    elseif ($type == VOCABINDEX_VI_BLOCK) {
      $form[$id . 'enabled'] = array(
        '#type' => 'checkbox',
        '#default_value' => $vi->enabled,
      );
    }

    $default_value = !is_null($vi->view) ? $vi->view : VOCABINDEX_VIEW_TREE;
    $options = array(VOCABINDEX_VIEW_TREE => t('Tree'));
    if ($vi->type == VOCABINDEX_VI_PAGE) {
      $options[VOCABINDEX_VIEW_FLAT] = t('Browsable');
      $options[VOCABINDEX_VIEW_ALPHABETICAL] = t('Alphabetical');
    }
    else {
      $options[VOCABINDEX_VIEW_FLAT] = t('Flat');
    }
    $form[$id . 'view'] = array(
      '#type' => 'select',
      '#default_value' => $default_value,
      '#options' => $options,
    );

    $form[$id . 'node_count'] = array(
      '#type' => 'checkbox',
      '#default_value' => $vi->node_count,
    );
  }

  $form['vocabindex_type'] = array(
    '#type' => 'value',
    '#value' => $type,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration')
  );

  return $form;
}

/**
 * Submission function for the form vocabindex_form_vi().
 *
 * @ingroup forms
 * @see vocabindex_admin_vi_form()
 */
function vocabindex_admin_vi_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $vis = vocabindex_vi_load($values['vocabindex_type'], 0, FALSE);
  foreach ($vis as $vi) {
    $id = 'vocabindex_' . $vi->vid . '_';

    $vi->path = array_key_exists($id . 'path', $values) ? preg_replace('#^/|/$#', '', drupal_strtolower($values[$id . 'path'])) : NULL;
    $vi->view = $values[$id . 'view'];
    $vi->node_count = $values[$id . 'node_count'];
    $vi->enabled = isset($values[$id . 'enabled']) && $values[$id . 'enabled'] == TRUE || !empty($values[$id . 'path']) ? TRUE : FALSE;

    vocabindex_vi_save($vi);
  }

  menu_rebuild();

  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Save a VI to the database.
 *
 * @ingroup vi_management
 *
 * @param $vi
 *   Type: object; The VI to save.
 */
function vocabindex_vi_save($vi) {
  db_query("UPDATE {vocabindex} SET path = '%s', view = %d, node_count = %d, enabled = %d WHERE vid = %d AND type = %d", $vi->path, $vi->view, $vi->node_count, $vi->enabled, $vi->vid, $vi->type);
  if ($vi->type == VOCABINDEX_VI_BLOCK && $vi->enabled == FALSE) {
    db_query("DELETE FROM {blocks} WHERE module = 'vocabindex' AND delta = %d", $vi->vid);
  }
}