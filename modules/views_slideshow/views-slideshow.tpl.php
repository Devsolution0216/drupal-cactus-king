<?php
// $Id: views-slideshow.tpl.php,v 1.1.2.2 2009/03/30 20:46:42 aaron Exp $
/**
 * @file views-slideshow.tpl.php
 * Default view template to display a slideshow.
 *
 * - $view: The view object.
 * - $options: Style options. See below.
 * - $rows: The output for the rows.
 * - $title: The title of this group of rows.  May be empty.
 *
 * - $options['type'] will either be ul or ol.
 * - $options['mode'] has the slideshow mode: VIEWS_SLIDESHOW_MODE_SINGLE_FRAME or VIEWS_SLIDESHOW_MODE_THUMBNAIL_HOVER
 * - $options['hover'] is 'hover' or 'hoverIntent'. Defines the mouse hover behavior, and depends on hoverIntent for the latter.
 * - $options['timer_delay'] is how many milliseconds before flipping to the next frame.
 * - $options['sort'] is VIEWS_SLIDESHOW_SORT_FORWARD, VIEWS_SLIDESHOW_SORT_REVERSE, or VIEWS_SLIDESHOW_SORT_RANDOM.
 * - $options['fade'] will either be TRUE or FALSE. If TRUE, then the slideshow will fade between frames.
 * - $options['fade_speed'] will be VIEWS_SLIDESHOW_FADE_SPEED_SLOW, VIEWS_SLIDESHOW_FADE_SPEED_NORMAL, or VIEWS_SLIDESHOW_FADE_SPEED_FAST.
 * - $options['fade_value'] determines the opacity to fade down to, defaulting at VIEWS_SLIDESHOW_DEFAULT_FADE_VALUE (0.25). Between 0 and 1.


 $sort, $fade, $fade_speed, $fade_value
 * @ingroup views_templates
 */

 print theme('views_slideshow_'. $options[mode], $view, $options, $rows, $title);
?>
