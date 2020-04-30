<?php
// $Id: ds.tools.inc,v 1.1.2.25 2010/09/02 21:22:25 swentel Exp $

/**
 * @file
 * Tools for Display suite like export & import.
 */

/**
 * Import functionality.
 */
function ds_import($form_state) {
  $form = array();

  $form['import'] = array(
    '#title' => t('Import display settings'),
    '#description' => t('Paste data to import field settings. Do not include the function declaration from the export. Note: only display settings can be imported here. <strong>Warning: existing data will be overwritten!</strong>'),
    '#type' => 'textarea',
    '#cols' => 60,
    '#default_value' => '',
    '#required' => TRUE,
    '#rows' => 10,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
  );

  return $form;
}

/**
 * Import submit function.
 */
function ds_import_submit($form_id, &$form_state) {
  $error = FALSE;

  ob_start();
  eval($form_state['values']['import']);
  ob_end_clean();

  // Validate the data. $data variable comes from the eval() function above.
  if (!is_array($data)) {
    $error = TRUE;
    drupal_set_message(t('Data string is not an array.'), 'error');
  }

  // All ok, let's import.
  if ($error == FALSE) {
    ds_import_data($data, TRUE, TRUE);
  }
}

/**
 * Import data function.
 *
 * @param array $data A complete data array with settings.
 * @param boolean $dsm Whether to output drupal messages.
 * @param boolean $override Whether to override existing settings or not.
 * @param string $revert_module The module to revert.
 * @param string $revert_type The object type to revert.
 * @param string $revert_build_mode The build mode to revert.
 */
function ds_import_data($data, $dsm = TRUE, $override = TRUE, $revert_module = '', $revert_type = '', $revert_build_mode = '') {
  foreach ($data as $module => $value) {
    foreach ($value as $type => $settings) {
      if ($dsm) {
        drupal_set_message(t('Saved display settings for @module and @type', array('@module' => $module, '@type' => $type)));
      }
      $old_settings = variable_get($module .'_display_settings_'. $type, array());
      foreach ($settings as $build_mode => $setting) {
        // Override no matter what. This comes from the import settings screen.
        if ($override) {
          $settings[$build_mode]['status'] = DS_SETTINGS_UI;
        }
        // We are importing from hook_ds_default_settings(). We need to
        // a) check if we have old settings and keep them if they are overridden.
        // b) compare $revert_module, $revert_type and $revert_build_mode and revert if necessary.
        else {
          if (isset($old_settings[$build_mode]['status']) && $old_settings[$build_mode]['status'] == DS_SETTINGS_OVERRIDDEN) {
            if ($module == $revert_module && $type == $revert_type && $build_mode == $revert_build_mode) {
              $settings[$build_mode]['status'] = DS_SETTINGS_DEFAULT;
            }
            else {
              $settings[$build_mode] = $old_settings[$build_mode];
            }
          }
          else {
            $settings[$build_mode]['status'] = DS_SETTINGS_DEFAULT;
          }
        }
      }
      // Keep old settings which aren't in the imported ones.
      if (!empty($old_settings)) {
        foreach ($old_settings as $build_mode => $setting) {
          if (!isset($settings[$build_mode])) {
            $settings[$build_mode] = $old_settings[$build_mode];
          }
        }
      }
      variable_set($module .'_display_settings_'. $type, $settings);
    }
  }
}

/**
 * Export functionality.
 */
function ds_export(&$form_state) {
  $form = array();
  $options = array();
  $ds_variables = array();
  $step = isset($form_state['storage']['step']) ? $form_state['storage']['step'] + 1 : 1;

  switch ($step) {

    // Show selection form.
    case 1:
      foreach (module_implements('ds_api') as $module) {
        $api_info = ds_api_info($module);
        $module = $api_info['module'];

        // Content types.
        foreach ($api_info['types']() as $tkey => $type) {

          $global_exclude = variable_get($module .'_type_'. $tkey, FALSE);

          // Views displays is special case.
          if ($module == 'vd') {
            if ($global_exclude == TRUE) {
              continue;
            }
          }
          $options[$module .'-'. $type->type] = $type->name;
          if ($global_exclude == TRUE) {
            $ds_variables[] = $module .'_type_'. $tkey;
          }
        }

        // Plugins.
        $plugins = variable_get($module .'_plugin_settings', array());
        if (!empty($plugins)) {
          $ds_variables[] = $module .'_plugin_settings';
        }
        // Build modes
        $build_modes = variable_get($module .'_build_modes', array());
        if (!empty($build_modes)) {
          $ds_variables[] = $module .'_build_modes';
        }
        // Build modes exclude.
        $ds_variables[] = $module .'_buildmodes_exclude';
      }

      if (!empty($options)) {
        $form['#prefix'] = t('Select one or more types to export.');
        $form['types'] = array(
          '#title' => 'Types',
          '#type' => 'checkboxes',
          '#options' => $options,
          '#required' => TRUE,
        );
        $form['module'] = array(
          '#title' => t('Module'),
          '#type' => 'textfield',
          '#description' => t('Fill in a name for your module (optional)'),
        );
      }
      else {
        $form['info'] = array(
          '#type' => 'item',
          '#value' => t('No object types found to export.'),
        );
      }
      break;

    // Show export.
    case 2:
      $export = ds_export_build($form_state['values']['types']);

      if (!empty($export['exclude']['fields'])) {
        drupal_set_message(t('Following fields were not included in the export because they are default fields: %fields', array('%fields' => implode(', ', $export['exclude']['fields']))));
      }

      if (!empty($export['ds'])) {

        $module_name = (!empty($form_state['values']['module'])) ? $form_state['values']['module'] : 'YOURMODULENAME';
        $form['export_hooks'] = array(
          '#title' => t('Display suite hooks'),
          '#description' => t('These are the hooks you need to implement for default data. You are free to return all data in this hook, this is just a suggestion.'),
          '#type' => 'textarea',
          '#cols' => 60,
          '#rows' => 8,
          '#value' => "<?php\n"
        );
        $form['export_data'] = array(
          '#title' => t('Display suite export data'),
          '#description' => t('You can paste this data into @module_name/@module_name.ds_default.inc. If you only want to store this data to import later, omit the function declaration.', array('@module_name' => $module_name)),
          '#value' => "<?php\n/**\n * @file\n * Display suite default settings.\n */\n",
          '#type' => 'textarea',
          '#cols' => 60,
          '#rows' => 15,
        );

        // Display settings.
        if (isset($export['ds']['settings'])) {
          $export_value = ds_var_export($export['ds']['settings']);
          $form['export_hooks']['#value'] .= "\n/**\n * Implementation of hook_ds_default_settings().\n */\nfunction ". $module_name ."_ds_default_settings() {\n  include_once('". $module_name .".ds_default.inc');\n  return _". $module_name ."_ds_default_settings();\n}\n";
          $form['export_data']['#value'] .= "\nfunction _". $module_name ."_ds_default_settings() {\n  \$data = ". $export_value .";\n  return \$data;\n}\n";
        }
        // Fields.
        if (isset($export['ds']['fields'])) {
          if (!empty($export['ds']['fields'])) {
            $export_value = ds_var_export($export['ds']['fields']);
            $form['export_hooks']['#value'] .= "\n/**\n * Implementation of hook_ds_fields().\n */\nfunction ". $module_name ."_ds_fields() {\n  include_once('". $module_name .".ds_default.inc');\n  return _". $module_name ."_ds_fields();\n}\n";
            $form['export_data']['#value'] .= "\nfunction _". $module_name ."_ds_fields() {\n  \$data = ". $export_value .";\n  return \$data;\n}\n";
          }
        }
      }
      else {
        $form['info'] = array(
          '#type' => 'item',
          '#value' => t('No settings found to export.'),
        );
      }

      break;
  }

  if ($step == 1 && !empty($options)) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Export'),
    );
    if (!empty($ds_variables)) {
      $form['other'] = array(
        '#type' => 'item',
        '#value' => t('Other variables you might consider to have in code (likely your install file): %variables. You can look this up in your database or use <a href="http://drupal.org/project/variable_dump">http://drupal.org/project/variable_dump</a> to create variable exports.', array('%variables' => implode(', ', $ds_variables))),
      );
    }
  }

  $form['step'] = array(
    '#type' => 'value',
    '#value' => $step,
  );

  return $form;
}

/**
 * Build the export variable.
 */
function ds_export_build($values) {
  $return = array();
  foreach ($values as $otype => $value) {
    if ($otype === $value) {
      list($module, $type) = explode('-', $value);
      // Display settings.
      $settings = variable_get($module .'_display_settings_'. $type, array());
      if (!empty($settings)) {
        foreach ($settings as $build_mode => $setting) {
          $settings[$build_mode]['status'] = DS_SETTINGS_DEFAULT;
        }
        $return['ds']['settings'][$module][$type] = $settings;
      }
      // Fields.
      $fields = variable_get($module .'_fields', array());
      if (!empty($fields)) {
        // We don't export overridden fields, unset them if necessary.
        foreach ($fields as $key => $field) {
          if ($field['status'] == DS_FIELD_STATUS_OVERRIDDEN) {
            unset($fields[$key]);
            $return['exclude']['fields'][] = $field['title'];
          }
          elseif ($field['status'] == DS_FIELD_STATUS_CUSTOM) {
            $fields[$key]['status'] = DS_FIELD_STATUS_DEFAULT;
          }
        }
        if (!empty($fields))
        $return['ds']['fields'][$module] = $fields;
      }
    }
  }
  return $return;
}

/**
 * Export submit function.
 */
function ds_export_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $form_state['storage']['step'] = $form_state['values']['step'];
}

/**
 * Revert form.
 *
 * @param string $module The name of the module.
 * @param string $object_type The object type name.
 * @param string $build_mode The build mode.
 */
function ds_revert_form($form_state, $module = '', $type = '', $build_mode = '') {

  $display_settings = variable_get($module .'_display_settings_'. $type, array());

  if (isset($display_settings[$build_mode]) &&
    isset($display_settings[$build_mode]['status']) &&
    $display_settings[$build_mode]['status'] == DS_SETTINGS_OVERRIDDEN
    ) {

    $question = t('Are you sure you want to revert the display settings for %module, %type and %build_mode. This will bring back the default settings and any changes you have done will be lost.', array('%module' => $module, '%type' => $type, '%build_mode' => $build_mode));
    $path = 'admin/build/ds/layout';
    $form['#module'] = $module;
    $form['#object_type'] = $type;
    $form['#build_mode'] = $build_mode;
    $form['#path'] = $path;
    return confirm_form($form, $question, $path);
  }
  else {
    drupal_set_message(t('Variables not found.'));
    drupal_goto('admin/build/ds');
  }
}

/**
 * Revert form submit.
 */
function ds_revert_form_submit($form, &$form_state) {
  drupal_set_message(t('Display settings for %module, %type and %build_mode have been reverted.', array('%module' => $form['#module'], '%type' => $form['#object_type'], '%build_mode' => $form['#build_mode'])));
  ds_import_default_data($form['#module'], $form['#object_type'], $form['#build_mode']);
  $form_state['redirect'] = $form['#path'];
}

/**
 * Export stylesheet.
 */
function ds_export_stylesheet() {
  $selectors = array();
  $regions = ds_regions();
  $all_build_modes = ds_get_build_modes();

  // Build an array of selectors of all enabled objects and fields.
  foreach (module_implements('ds_api') as $module) {

    // Let's skip hds for now
    if ($module == 'hds' || $module == 'vd') {
      continue;
    }

    $api_info = ds_api_info($module);

    // Title.
    $selectors[] = "/* ". $api_info['title'] ." */\n";

    // Regions
    $selectors[] = "/* Regions */";
    $selectors[] = str_replace('@replace', $module, ds_export_style_sheet_regions());

    // Get all objects.
    $build_modes = $all_build_modes[$module];
    if (!empty($build_modes)) {
      foreach ($api_info['types']() as $tkey => $type) {

        $type_name = $type->type;
        $type_url_str = str_replace('_', '-', $type_name);
        $display_settings = variable_get($module .'_display_settings_'. $type_name, array());

        // Global exclude.
        if (variable_get($module .'_type_'. $type->type, FALSE)) {
          continue;
        }

        $type_selectors = array();
        $exclude_build_modes = variable_get($module .'_buildmodes_exclude', array());
        foreach ($build_modes as $key => $value) {

          // Check if build mode is excluded for this object type.
          $excluded = (isset($exclude_build_modes[$type_name][$key]) && $exclude_build_modes[$type_name][$key] == TRUE) ? TRUE : FALSE;
          if ($excluded) {
            continue;
          }

          // Get any configured fields.
          $field_settings = ds_default_value($display_settings, $key, 'fields');
          foreach ($field_settings as $field_key => $field) {
            if ($field['region'] != 'disabled') {

              $class = isset($field['properties']['css-class']) ? $field['properties']['css-class'] : 'field-'. strtr($field_key, '_', '-');
              if (isset($field_settings[$field]['css-class']) && !empty($field_settings[$field]['css-class'])) {
                $class .= ' '. $field_settings[$field]['css-class'];
              }
              if ($field['type'] == DS_FIELD_TYPE_GROUP) {
                $class .= ' field-group';
              }

              // This actually a bit hardcoded, pity.
              switch ($module) {
                case 'nd':
                  $prefix = '.buildmode-'. $key .' .node-type-'. $type_name;
                  break;
                case 'ud':
                  $prefix = '.buildmode-'. $key .' .profile';
                  break;
                case 'cd':
                  $prefix = '.buildmode-'. $key .' .comment';
                  break;
              }
              $type_selectors[] = $prefix ." .". $class ." {\n}";
            }
          }
        }

        // Add selectors when not empty.
        if (!empty($type_selectors)) {
          $selectors[] = "/* Fields of ". $type_name ." */\n";
          $selectors = array_merge($selectors, $type_selectors);
          $selectors[] = "";
        }
      }
    }
  }

  $skeleton = implode("\n", $selectors);

  $form = array();
  $form['info'] = array(
    '#type' => 'markup',
    '#value' => t('The textarea underneath generates a skeleton stylesheet for enabled objects and fields in your site. Views displays and Heartbeat displays are not supported yet.')
  );
  $form['skeleton'] = array(
    '#type' => 'textarea',
    '#rows' => 25,
    '#default_value' => $skeleton,
  );

  return $form;
}

/**
 * Skeleton for default regions.
 */
function ds_export_style_sheet_regions() {
  return '
.@replace-region-header {
}
.@replace-region-left {
}
.@replace-no-sidebars .@replace-region-middle {
}
.@replace-sidebar-left .@replace-region-middle {
}
.@replace-sidebar-right .@replace-region-middle {
}
.@replace-two-sidebars .@replace-region-middle {
}
.@replace-region-right {
}
.@replace-region-footer {
}
  ';
}

/**
 * Nice var exporter, based on Views.
 */
function ds_var_export($var, $prefix = '  ', $init = TRUE, $indent = '  ') {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $prefix .= '  ';
      $old = $indent;
      $indent .= '  ';
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "$indent'$key' => " . ds_var_export($value, $prefix, FALSE, $indent) . ",\n";
      }
      $indent = $old;
      $output .= "$indent)";
    }
  }
  elseif (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  elseif (is_string($var) && strpos($var, "\n") !== FALSE) {
    // Replace line breaks in strings with a token for replacement
    // at the very end. This protects multi-line strings from
    // unintentional indentation.
    $var = str_replace("\n", "***BREAK***", $var);
    $output = var_export($var, TRUE);
  }
  else {
    $output = var_export($var, TRUE);
  }


  if ($init) {
    $output = str_replace("***BREAK***", "\n", $output);
  }

  return $output;
}
