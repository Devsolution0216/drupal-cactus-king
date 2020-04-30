<?php
/**
 * @file
 * Contains the VCD Object row style plugin.
 */

/**
 * The VCD row plugin. It extends the DS Object row plugin
 *
 * This plugin adds one extra fields to the DS Object row plugin and allows for
 * contextual based build mode switching.
 *
 * @ingroup views_row_plugins
 */
class views_plugin_row_vcd extends views_plugin_ds_object_view {
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function options_form(&$form, &$form_state) {
    // @todo We load the original DS options but these are not fully functional (yet)
    parent::options_form(&$form, &$form_state);

    // Load all available build modes for this view
    $views_base_table = $this->view->base_table;
    $build_mode_options = array();
    $build_modes = ds_get_build_modes();
    foreach ($build_modes as $module => $modes) {
      $function = $module .'_ds_api';
      $api_info = $function();
      // $api_info['views_base'] can either be a string or an array.
      if ((is_array($api_info['views_base']) && in_array($views_base_table, $api_info['views_base'])) || (is_string($api_info['views_base']) && $api_info['views_base'] == $views_base_table)) {
        foreach ($modes as $key => $title) {
          $build_mode_options[$key] = $title['title'];
        }
      }
    }

    // Set an extra fieldset
    $form['context_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contextual build modes'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    // Set an extra fieldset
    $form['context_fieldset']['contextual'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable context switching.'),
      '#description' => t('Enabling contextual switching only overrides the Default Build Mode for this view.'),
      '#default_value' => ($this->options['contextual']) ? $this->options['contextual'] : FALSE,
    );
    
    // List all enabled contexts that load the vcd_views_context_reaction plugin
    $contexts = context_enabled_contexts();
    $contexts_values = array();
    foreach ($contexts as $name => $context) {
      $reactions = array_keys($context->reactions);
      if (in_array('vcd_views_context_reaction', $reactions)) {
        $conditions = array_keys($context->conditions);
        $form['context_fieldset']['context_' . $name] = array(
          '#type' => 'select',
          '#title' => t('Set buildmode for context %s', array('%s' => $name)),
          '#options' => $build_mode_options,
          '#description' => t('Condtions: %s, Reactions: %e', array('%s' => implode(', ', $conditions), '%e' => implode(' ,', $reactions))),
          '#default_value' => $this->options['context_fieldset']['context_' . $name],
        );
      }
    }
	}

  /**
   * Reset all fieldsets except for changing.
   */
	function options_submit($form, &$form_state) {
    parent::options_submit($form, $form_state);
    foreach ($form_state['values']['row_options']['context_fieldset'] as $context => $buildmode) {
      $form_state['values']['row_options'][$context] = $buildmode;
    }
  }
}
