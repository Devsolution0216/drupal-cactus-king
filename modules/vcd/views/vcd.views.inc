<?php
/**
* Implements hook_views_plugins().
*/
function vcd_views_plugins() {
  $path = drupal_get_path('module', 'vcd');
  $plugins = array(
    'row' => array(
      'vcd' => array(
        'title' => t('VCD Object'),
        'help' => t('Displays the object with a contextual build mode'),
        'handler' => 'views_plugin_row_vcd',
        'path' => $path . '/views', // not necessary for most 
        'parent' => 'ds',
        'theme' => 'vcd_row_object',
        'theme path' => $path .'/theme',
        'theme file' => 'theme.inc',
        'uses fields' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-row-fields',
      ),
    ),
  );

  return $plugins;
}
