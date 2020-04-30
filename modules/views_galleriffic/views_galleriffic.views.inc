<?php

/**
 * @file
 *  Provide the Galleriffic plugin definition.
 */

function views_galleriffic_views_plugins() {
  return array(
    'module' => 'views_galleriffic',
    'style' => array(
      'views_galleriffic' => array(
        'title' => t('Galleriffic Gallery'),
        'theme' => 'views_galleriffic_view',
        'help' => t('Display a view like a Galleriffic gallery.'),
        'handler' => 'views_galleriffic_style_plugin',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'row' => array(
      'gallerifficfields' => array(
        'title' => t('Galleriffic Fields'),
        'help' => t('Choose the fields to display in the Galleriffic gallery.'),
        'handler' => 'views_galleriffic_plugin_row_gallerifficrows',
        'theme' => 'views_galleriffic_view_gallerifficrows',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
