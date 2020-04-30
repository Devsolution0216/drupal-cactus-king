<?php
// $Id: views-slideshow-single-frame.tpl.php,v 1.1.2.1 2009/03/30 20:46:42 aaron Exp $

/**
 *  @file
 *  Views Slideshow: Single Frame
 */

  $base = drupal_get_path('module', 'views_slideshow');
  drupal_add_js($base . '/js/views_slideshow.js', 'module');
  drupal_add_css($base . '/css/views_slideshow.css', 'module');

  $js = theme('views_slideshow_div_js', $rows, $options, $id);
  drupal_add_js($js, 'inline');

  $teaser = ($options['hover_breakout'] == VIEWS_SLIDESHOW_HOVER_BREAKOUT_TEASER ? TRUE : FALSE);
  $output = '';
  $view_teasers = FALSE;

  // these are hidden elements, used to cycle through the main div
  $hidden_elements = theme('views_slideshow_no_display_section', $view, $rows, $id, $options['mode'], $teaser);
  $output .= theme('views_slideshow_main_section', $id, $hidden_elements);

  if ($view_teasers && $options['teasers_last']) {
    $output .= $view_teasers;
  }

  print $output;

?>
