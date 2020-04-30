<?php
/**
 * @file
 * Theming functions for vcd
 */

/**
 * Template preprocess function for theme_views_view_row_object().
 * We delegate the manipulation of the object to a function
 * which every module implementing the ds_api should define.
 */
function template_preprocess_vcd_row_object(&$vars) {
  $options = $vars['options'];

  if (($plugin = context_get_plugin('reaction', 'vcd_views_context_reaction')) && $options['contextual']) {
    // We need to call all contextual conditions here. Context module invokes them through
    // context_page_alter() which is after Views' preprocess functions have been called.
    // This is not necessarily bad because Context loads them in a static cached object.
    module_invoke_all('context_page_condition');
    foreach (context_active_contexts() as $key => $context) {
      // When multiple contexts are active, only the last active context will set the build mode
      if (in_array('context_' . $key, array_keys($options))) {
        $plugin->execute($options, $options['context_' . $key]);
      }
    }
  }

  $vars['options'] = $options;

  // load the original DS preprocess function. We don't want to copy code from DS
  module_load_include('inc', 'ds', 'theme/theme');
  template_preprocess_ds_row_object($vars);
}