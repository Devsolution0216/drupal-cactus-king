<?php
// $Id: views_slideshow.theme.inc,v 1.1.2.2 2009/03/21 00:36:39 aaron Exp $

/**
 *  This inline js sets up the timer for this slideshow.
 */
function theme_views_slideshow_div_js($rows, $options, $id) {
  $hover = 'hover';
  if ($options['hover'] == 'hoverIntent') {
    if (module_exists('jq')) {
      $hover = jq_add('hoverIntent') ? 'hoverIntent' : 'hover';
    }
    else if (module_exists('hoverintent')) {
      $hover = hoverintent_add() ? 'hoverIntent' : 'hover';
    }
  }

  $num_divs = sizeof($rows);
  $fade = $options['fade'] ? 'true' : 'false';

  $js = <<<JS
// Set the timer data for a view slideshow.
$(document).ready(function() {
  // These are the divs containing the elements to be displayed in the main div in rotation or mouseover.
  slideshow_data["$id"] = new views_slideshow_data($num_divs, {$options['timer_delay']}, {$options['sort']}, $fade, "{$options['fade_speed']}", {$options['fade_value']});

  // This turns on the timer.
  views_slideshow_timer("$id", true);

  // This sets up the mouseover & mouseout to pause on the main element.
  $("#views_slideshow_main_$id").$hover(
    function() {
      views_slideshow_pause("$id");
    },
    function() {
      views_slideshow_resume("$id");
    });
});
JS;
  return $js;
}

/**
 *  This displays the main element, where the current slide is shown.
 */
function theme_views_slideshow_main_section($id, $hidden_elements) {
  $output = "\n\n" . '<div id="views_slideshow_main_' . $id . '" class="views_slideshow_main">' . "\n  ";
  $output .= $hidden_elements;
  $output .= '</div><!--close views_slideshow_main_' . $id . "-->\n\n";
  return $output;
}

/**
 *  These are the slideshow elements themselves; not actually displayed, but used to give the html to the main element.
 */
function theme_views_slideshow_no_display_section($view, $rows, $id, $mode, $teaser = TRUE) {
  $output = '<div id="views_slideshow_teaser_section_' . $id . '" class="views_slideshow_teaser_section">' . "\n";
  if ($mode == VIEWS_SLIDESHOW_MODE_THUMBNAIL_HOVER) {
    foreach ($view->result as $count => $node) {
      $output .= theme('views_slideshow_no_display_teaser', node_view(node_load($node->nid), $teaser, FALSE, FALSE), $id, $count);
    }
  }
  else {
    // Add support for the jQuery Cycle plugin.
    // If we have the jQ module installed, use that to add the Cycle plugin if possible.
    // That allows for version control.
    if (module_exists('jq')) {
      $js = jq_add('cycle');
    }

    // Otherwise, we'll add the version included with this module.
    if (!$js) {
      drupal_add_js(drupal_get_path('module', 'views_slideshow') .'/js/jquery.cycle.all.min.js', 'module');
    }

    foreach ($rows as $count => $item) {
      $output .= theme('views_slideshow_no_display_teaser', $item, $id, $count);
    }
  }
  $output .= "</div><!--close views_slideshow_no_display-->\n\n";
  return $output;
}

/**
 *  The html that will be placed into the element in its turn during its frame.
 */
function theme_views_slideshow_no_display_teaser($item, $id, $count) {
  $hidden = $count ? 'class="views_slideshow_hidden"' : '';
  $output = '  <div id="views_slideshow_div_' . $id . '_' . $count . '" '. $hidden .'>' . "\n  ";
  $output .= $item . "\n";
  $output .= '  </div><!--close views_slideshow_div_' . $id . '_' . $count . '-->' . "\n\n";
  return $output;
}

/**
 *  These are teasers that may be pointed at with a mouse to change the element directly.
 */
function theme_views_slideshow_breakout_teasers($items, $id) {
  $output = '<div id="views_slideshow_breakout_teasers_' . $id . '" class="views_slideshow_breakout_teasers">' . "\n";
  $js = "$(document).ready(function() {\n";
  foreach ($items as $count => $item) {
    $output .= theme('views_slideshow_breakout_teaser', $item, $id, $count);
    $js .= theme('views_slideshow_breakout_teaser_js', $id, $count);
  }
  $js .= "})\n";
  drupal_add_js($js, 'inline');

  $output .= "</div><!--close views_slideshow_breakout_teasers-->\n\n";

  return $output;
}

/**
 *  The mouseover event code for each breakout teaser.
 */
function theme_views_slideshow_breakout_teaser_js($id, $count) {
  // Return the js to set the main div to this teaser's element.
  $hover = (module_invoke('jq', 'add', 'hoverIntent')) ? 'hoverIntent' : 'hover';

  $js = '
  $("#views_slideshow_div_breakout_teaser_' . $id . '_' . $count . '").' . $hover . '(
    function() {
      views_slideshow_switch("' . $id . '", ' . $count . ');
      views_slideshow_pause("' . $id . '");
    },
    function() {
      views_slideshow_resume("' . $id . '");
   });
';
  return $js;
}

/**
 *  An individual breakout teaser.
 */
function theme_views_slideshow_breakout_teaser($item, $id, $count) {
  $class = $count ? '' : ' views_slideshow_active_teaser';
  $output = '  <div id="views_slideshow_div_breakout_teaser_' . $id . '_' . $count . '" class="views_slideshow_div_breakout_teaser' . $class . '">' . "\n  ";
  $output .= $item . "\n";
  $output .= '  </div><!--close views_slideshow_div_breakout_teaser_' . $id . '_' . $count . '-->' . "\n\n";
  return $output;
}
