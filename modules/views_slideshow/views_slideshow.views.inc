<?php
// $I$

/**
 *  @file
 *  views_slideshow.views.inc
 *  Defines slideshow view style plugins.
 */

/**
 * Slideshow View style plugins. Implementation of hook_views_plugins()
 */
function views_slideshow_views_plugins() {
  return array(
    'style' => array(
      'slideshow' => array(
        'title' => t('Slideshow'),
        'help' => t('Display the results as a slideshow.'),
        'handler' => 'views_slideshow_plugin_style_slideshow',
        'theme' => 'views_slideshow',
        'uses options' => TRUE,
        'uses row plugin' => TRUE,
        'type' => 'normal',
        'parent' => 'list',
      ),
    ),
  );
}

