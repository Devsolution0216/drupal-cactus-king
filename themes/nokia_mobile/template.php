<?php
// $Id: template.php,v 1.6 2010/05/19 11:50:15 atrasatti Exp $

/**
 * nokia_mobile is a theme based on the Nokia templates published on Forum Nokia and fully sponsored by Nokia
 * The theme should be used with the Mobile Plugin -module.
 *
 * @author Andrea Trasatti <atrasatti@gmail.com>
 * @copyright Copyright Nokia
 * @license http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt GPL Version 2.0
 */

define('NOKIAMOBILE_THEME_HIGHEND_GROUP', 'nokia high-end');  // Series60 running webKit, Maemo, other webKit-based browsers
define('NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP', 'nokia high-end with touch');  // Series60/5.0 and Maemo (and iPhone and others)
define('NOKIAMOBILE_THEME_MIDEND_GROUP', 'nokia mid-end');  // currently not implemented
define('NOKIAMOBILE_THEME_LOWEND_GROUP', 'nokia low-end');  // default

function phptemplate_preprocess_block(&$vars) {
  $vars['nokia_mobile_device_class'] = _nokia_mobile_device_detection();
}

/**
 * Preprocesses template variables.
 * @param vars variables for the template
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();
  if (module_exists('color')) {
		_color_page_alter($vars);
  }
/*
  echo "<pre>\n";
  print_r($vars);
  echo "</pre>\n";
  die();
*/
  
	// here there used to be a check for the existence of the mobileplugin. Moved down.
	// everything should be indented back of two spaces
	// Make sure we have set the proper Nokia group IF the theme settings say so
	if ((arg(0) != 'admin')) {
		_nokia_mobile_force_nokia_group();
	}
	// add my styles - move to a function?
	$css_path = _nokia_mobile_get_css_path();
	$js_path = _nokia_mobile_get_js_path();
	$style_path = path_to_theme() . '/css/'.$css_path.'reset.css';  // dynamic based on device group
	$new_styles_order[$style_path] = 1;
	$theme_styles = $vars['css']['all']['theme'];
	$new_styles_order = array_merge($new_styles_order, $theme_styles);
	// Apply the Nokia style last. NO COLORS should be applied here unless really want to force
	$style_path = path_to_theme() . '/css/'.$css_path.'baseStyles.css';  // dynamic based on device group
	$new_styles_order[$style_path] = 1;
	$theme_image_color_css_filename = nokia_mobile_settings_css_filename().'.css';
	$style_path = path_to_theme() . '/css/'.$css_path.$theme_image_color_css_filename;  // dynamic based on color picked by admin
	$new_styles_order[$style_path] = 1;
	$vars['css']['all']['theme'] = $new_styles_order;
	$vars['header_text_color'] = '#ffffff';
	// make sure we are using color
	if (module_exists('color')) {
		$header_text_color = theme_get_setting('theme_header_text_color');
		$vars['header_text_color'] = $header_text_color;
	}
	$vars['doctype'] = _nokia_mobile_get_doctype();
	/*
	$vars['left'] = str_replace('user-login', 'my-user-login', $vars['left']);
	$vars['left'] = str_replace('user_login', 'my_user_login', $vars['left']);
	*/
	// Add Javscript
	if (is_file(drupal_get_path('theme', 'nokia_mobile').'/scripts/'.$js_path.'nokia_mobile.js')) {
		drupal_add_js(drupal_get_path('theme', 'nokia_mobile').'/scripts/'.$js_path.'nokia_mobile.js', 'theme');  // dynamic based on device group
	}
	
	$vars['inline_scripts'] = '';
	// High-end device specifics
	if (_nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_GROUP
			 || _nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP ) {
		if (!empty($vars['tabs'])) {
			// trick to get the closing vertical bar
			$vars['tabs'] .= "<li><a/></li>\n";
		}
		global $user;
		if (is_object($user)) {
			$user_uid = $user->uid;
		} else {
			$user_uid = '';
		}
		$tweaks_path = '/'.path_to_theme() . '/css/'.$css_path.'tweaks/';  // dynamic based on device group
		// We use accordions only in left and right regions, check block.tpl.php to change this
		$block_regions[] = 'left';
		$block_regions[] = 'right';
		$accordions_list = '';
		foreach($block_regions as $region) {
			$block_list = block_list($region);
			foreach($block_list as $block) {
				$block_id = "accordion-{$block->module}-{$block->delta}";
				$accordions_list .= '\''.$block_id.'\', ';
			}
		}
		if ($accordions_list != '') {
			$accordions_list = substr($accordions_list, 0, -2);
		}
		$inline_script = $vars['inline_scripts'] = '
		function init() {
			var myAccordionList = new AccordionList(['. $accordions_list .']);
			var myStyleTweaks = new StyleTweaker();
			myStyleTweaks.add("Series60/5.0", "'.$tweaks_path.'S605th.css");
			myStyleTweaks.add("Series60/3.2", "'.$tweaks_path.'S603rdFP2.css");
			myStyleTweaks.add("AppleWebKit/420+", "'.$tweaks_path.'S406th.css");
			myStyleTweaks.add("N900", "'.$tweaks_path.'maemo.css");
			myStyleTweaks.add("Firefox/3.0a1 Tablet browser 0.3.7", "'.$tweaks_path.'maemo.css");
			myStyleTweaks.add("Opera Mini/4", "'.$tweaks_path.'operamini.css");
			myStyleTweaks.tweak();
		}
		addEvent("onload",init);
';

		drupal_add_js($inline_script, 'inline', 'header');
	}
	// Theme the breadcrumb
	/*
	if (!empty($vars['breadcrumb'])) {
		$vars['breadcrumb'] = phptemplate_breadcrumb(drupal_get_breadcrumb());
	}
	*/
    
	if (module_exists('mobileplugin')) {
    // clean CSS, JS and get scaled logo using mobileplugin's (private) functions
		$vars['styles'] = _mobileplugin_filter_css($vars['css']);
    $vars['scripts'] = _mobileplugin_filter_js();
    $vars['bodyclasses'] = 'mobile' . _mobileplugin_add_class();
    $scaled_logo = _mobileplugin_image_scaled($vars['logo'], 30, 30);
    if (!is_array($scaled_logo)) {
      $vars['logo'] = $scaled_logo;
    }
  } else {
    // clean CSS, JS
		$js = drupal_add_js();
    $vars['scripts'] = _nokia_mobile_filter_js($js);
    $css = $vars['css'];
		$css['handheld']['theme']['/this_is_a_test.css'] = 1;
		$vars['styles'] = _nokia_mobile_filter_css($css);
		// Scale logo?
	}
}

function nokia_mobile_preprocess_page(&$vars) {
  // Add preprocess customizations to be executed AFTER the default preprocess_page
}

/**
 * Override local tasks theming to split the secondary tasks.
 * @return rendered local tasks
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

/**
 * Wraps comments to a stylable element.
 * @param content the comment markup
 * @param node the node commented
 * @return full comment markup
 */
function phptemplate_comment_wrapper($content, $node) {
  if (!$content || $node->type == 'forum') {
    return '<div id="comments">' . $content . '</div>';
  }
  return '<div id="comments"><h2 class="comments">' . t('Comments') . '</h2>' . $content . '</div>';
}

/**
 * Themes comment submitted info.
 * @param comment the comment
 * @return submitted info
 */
function phptemplate_comment_submitted(&$comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}

/**
 * Themes node submitted info.
 * @param node the node
 * @return submitted info
 */
function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/**
 * Themes feed icon.
 * @param url a feed url
 * @param title a feed title
 * @return feed markup
 */
function phptemplate_feed_icon($url, $title) {
  if ($image = theme('image', 'misc/feed.png', t('Syndicate content'), $title)) {
    return '<div class="feed-div"><a href="'. check_url($url) .'" class="feed-icon">'. $image . ' ' . $title . '</a></div>';
  }
}

/**
 * Register original theme functions.
 * @return theme function array
 */
function nokia_mobile_theme() {
  return array(
    'toplinks' => array(
      'arguments' => array($links => array(), $attributes => array())
    ),
    'breadcrumb' => array(
      'arguments' => array('breadcrumb' => $breadcrumb)
    ),
  );
}

/**
 * Themes the top links.
 * @param links links data
 * @param attributes attributes to add for the element
 * @return top links markup
 */
function nokia_mobile_toplinks($links, $attributes = array('class' => 'links')) {
  $num_links = count($links);
  if ($num_links == 0) {
    return '';
  }
//  If you wanted the top links to be rounded buttons, you should add this class
//  $attributes['class'] .= ' nav-horizontal-rounded';  //Add nokia style name
// then change the div in an ul and all spans in lis
// Links color in the site settings should be changed to a dark color, for example "Nocturnal"
  $output = '<div'. drupal_attributes($attributes) .'>';
  $i = 1;
  foreach ($links as $key => $link) {

    // Add active or passive class to links.
    $active = (strpos($key, 'active') ? ' active' : ' passive');
    if (isset($link['attributes']) && isset($link['attributes']['class'])) {
      $link['attributes']['class'] .= ' ' . $key;
    }
    else {
      $link['attributes']['class'] = $key;
    }

    // Add first and last classes to links.
    $extra_class = '';
    if ($i == 1) {
      $extra_class .= 'first ';
    }
    if ($i == $num_links) {
      $extra_class .= 'last ';
    }
    $output .= '<span '. drupal_attributes(array('class' => $extra_class . $key . $active)) .'>';

    // Create a link or plain title.
    $html = isset($link['html']) && $link['html'];
    $link['query'] = isset($link['query']) ? $link['query'] : NULL;
    $link['fragment'] = isset($link['fragment']) ? $link['fragment'] : NULL;
    if (isset($link['href'])) {
      $output .= l($link['title'], $link['href'], $link['attributes'], $link['query'], $link['fragment'], FALSE, $html);
    } else if ($link['title']) {
      if (!$html) {
        $link['title'] = check_plain($link['title']);
      }
      $output .= '<span'. drupal_attributes($link['attributes']) .'>'. $link['title'] .'</span>';
    }
    $output .= "</span>\n";
    $i++;
  }
  $output .= '</div>';
  return $output;
}

/* Nokia_mobile theme-specific changes and additions */
/**
* Return a themed breadcrumb trail. 
*
* @param $breadcrumb
*   An array containing the breadcrumb links.
* @return
*   A string containing the breadcrumb output. 
*/
function nokia_mobile_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    $b = '<ul class="breadcrumb">';
    for($i=0;$i<count($breadcrumb);$i++) {
      $entry = $breadcrumb[$i];
      if ($i==0) {
        $b .= '<li class="first">';
      } else {
        $b .= '<li>';
      }
      $b .= $entry;
      if ($i+1 < count($breadcrumb)) {
        $b .= ' > ';
      }
      $b .= '</li>';
    }
    $b .= '</ul>';
    return $b;
  }
}

/*
 * Restyle all submit buttons
 */
function nokia_mobile_button($element) {
  // Make sure not to overwrite classes.
  if (isset($element['#attributes']['class'])) {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'] .' '. $element['#attributes']['class'];
  }
  else {
    $element['#attributes']['class'] = 'form-'. $element['#button_type'];
  }
  
  $element['#attributes']['class'] .= ' button-submit';

  $attributes = drupal_attributes($element['#attributes']);
  if(_nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_GROUP || _nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP ) {
    $output = '<button value="'. check_plain($element['#value']) .'" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ') .'id="'. $element['#id'] .'" ' . $attributes .'><span>'. check_plain($element['#value']) .'</span></button> '."\n";
  } else {
    $output = '<input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ') .'id="'. $element['#id'] .'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." />\n";
  }
  return $output;
//  return '<input type="submit" '. (empty($element['#name']) ? '' : 'name="'. $element['#name'] .'" ') .'id="'. $element['#id'] .'" value="'. check_plain($element['#value']) .'" '. drupal_attributes($element['#attributes']) ." />\n";
}

function phptemplate_menu_tree($tree) {
  return '<ul class="menu">'. $tree .'</ul>';
}

/*
 * Based on the User-Agent string, determine the class the device/browser falls in
 * @todo define a way to detect mid-end devices and implement
 */
function _nokia_mobile_device_detection($forced_user_agent = NULL) {
  global $nokia_mobile_device_class;
  if (is_null($forced_user_agent)) {
    $ua = $_SERVER['HTTP_USER_AGENT'];
  } else {
    $ua = $forced_user_agent;
  }
  
  // fallback for all devices
  $nokia_mobile_device_class = NOKIAMOBILE_THEME_LOWEND_GROUP;
  if (stristr($ua, 'Nokia')) {
    // Nokia low-end
    $nokia_mobile_device_class = NOKIAMOBILE_THEME_LOWEND_GROUP;
  }
  if ((stristr($ua, 'Series60') && stristr($ua, 'webKit')) || preg_match("/(" . _nokia_mobile_ua_contains() . ")/i", $ua) ) {
    // Nokia high-end
    $nokia_mobile_device_class = NOKIAMOBILE_THEME_HIGHEND_GROUP;
  }
  if (stristr($ua, 'Series60/5.0') || stristr($ua, 'Maemo') || preg_match("/(" . _nokia_mobile_touch_ua_contains() . ")/i", $ua) ) {
    // Nokia high-end with touch
    $nokia_mobile_device_class = NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP;
  }

  return $nokia_mobile_device_class;
}

function _nokia_mobile_setcookie_device_class($nokia_mobile_device_class, $touch = FALSE) {
  $nokia_detection = theme_get_setting('nokia_mobile_native');
  if ($nokia_detection) {
    // force our class into the cookie
    setcookie('mobileplugin_group', $nokia_mobile_device_class .','. ($touch ? '1' : '0'), 0, '/');
//    setcookie('mobileplugin_group', $nokia_mobile_device_class .','. ($touch ? '1' : '0'), 0, '/', $_SERVER['HTTP_HOST']);
    
		// make sure the global variable is updated
		global $mobileplugin_group;
    $mobileplugin_group = $nokia_mobile_device_class;
  }
}
/*
 * Based on the device class, return the path for CSS
 */
function _nokia_mobile_get_css_path($device_class = FALSE) {
  if ($device_class === FALSE) {
    $nokia_detection = theme_get_setting('nokia_mobile_native');
    if ($nokia_detection) {
      $device_class = _nokia_mobile_device_detection();
    } else {
      // Use the global variable set by mobileplugin_init()
      global $mobileplugin_group;
      $device_class = $mobileplugin_group;
    }
  }
  
  switch($device_class) {
    case NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP:
    case NOKIAMOBILE_THEME_HIGHEND_GROUP:
      return 'high/';
      break;
    case NOKIAMOBILE_THEME_MIDEND_GROUP:
    case NOKIAMOBILE_THEME_LOWEND_GROUP:
      return 'low/';
      break;
    default:
      return 'low/';
      break;
  }
}

/*
 * Based on the device class, return the path for JS
 */
function _nokia_mobile_get_js_path($device_class = FALSE) {
  if ($device_class === FALSE) {
    $nokia_detection = theme_get_setting('nokia_mobile_native');
    if ($nokia_detection) {
      $device_class = _nokia_mobile_device_detection();
    } else {
      // Use the global variable set by mobileplugin_init()
      global $mobileplugin_group;
      $device_class = $mobileplugin_group;
    }
  }
  
  switch($device_class) {
    case NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP:
    case NOKIAMOBILE_THEME_HIGHEND_GROUP:
      return 'high/';
      break;
    case NOKIAMOBILE_THEME_MIDEND_GROUP:
    case NOKIAMOBILE_THEME_LOWEND_GROUP:
      return 'low/';
      break;
    default:
      return 'low/';
      break;
  }
}

/*
 * Other high-end devices with touch that we want to provide with the best theme
 */
function _nokia_mobile_touch_ua_contains() {
  return implode("|", array(
    'ipod',
    'webos',
    'iphone',
  ));
}

/*
 * Other high-end devices that we want to provide with the best theme
 */
function _nokia_mobile_ua_contains() {
  return implode("|", array(
    'android',
  ));
}

function _nokia_mobile_get_doctype() {
  $doctype = '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.0//EN"
"http://www.wapforum.org/DTD/xhtml-mobile10.dtd">';
  if (_nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_GROUP
      || _nokia_mobile_device_detection() == NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP ) {
    $doctype = '<!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN"
"http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd">';
  }
  
  return $doctype;
}

function nokia_mobile_settings_css_filename() {
  $theme_image_color = theme_get_setting('theme_image_colors');
  switch($theme_image_color) {
    case 1:
      return 'blue';
      break;
    case 2:
      return 'red';
      break;
    case 3:
      return 'grey';
      break;
    case 0:
    default:
      return 'green';
      break;
  }
}

function _nokia_mobile_force_nokia_group($force_update = FALSE) {
  $nokia_detection = theme_get_setting('nokia_mobile_native');
  if (!$nokia_detection) {
    // nothing to do
    return;
  }
  $nokia_device_groups = array(
    NOKIAMOBILE_THEME_HIGHEND_GROUP,
    NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP,
    NOKIAMOBILE_THEME_MIDEND_GROUP,
    NOKIAMOBILE_THEME_LOWEND_GROUP,
  );
  if ($force_update) {
    $update = TRUE;
  } else if (!isset($_COOKIE['mobileplugin_group']) ) {
    $update = TRUE;
  } else if (isset($_COOKIE['mobileplugin_group']) ) {
    list($group, $touch) = explode(',', $_COOKIE['mobileplugin_group']);
    if (!in_array($group, $nokia_device_groups)) {
      $update = TRUE;
    } else {
      $update = FALSE;
    }
  } else {
    $update = FALSE;
  }

  if ($update) {
    $device_group = _nokia_mobile_device_detection();
    $has_touch = ($device_group==NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP) ? TRUE:FALSE;
    _nokia_mobile_setcookie_device_class($device_group, $has_touch);
  }
}

function _nokia_mobile_filter_css($css) {
	$new_css_list = array();
	foreach($css as $css_media => $css_type_array) {
		// leave any CSS specific for handhelds untouched
		if ($css_media == 'handheld') {
			$new_css_list[$css_media] = $css_type_array;
			continue;
		}
		foreach($css_type_array as $css_type=>$css_filename_array) {
			foreach($css_filename_array as $css_filename => $val) {
				// Preserve CSS set by nokia_mobile theme
				if (stristr($css_filename, 'nokia_mobile')) {
					$new_css_list[$css_media][$css_type][$css_filename] = 1;
				}
			}
		}
	}
	return drupal_get_css($new_css_list);
}

function _nokia_mobile_filter_js($js) {
	$new_js_list = array();
	foreach($js as $js_type => $js_filename_array) {
		if ($js_type == 'inline') {
			// leave untouched
			$new_js_list[$js_type] = $js[$js_type];
			continue;
		}
		foreach($js_filename_array as $js_filename => $vals) {
			// only allow JS that came from nokia_mobile theme
			if (stristr($js_filename, 'nokia_mobile')) {
				$new_js_list[$js_type][$js_filename] = $js[$js_type][$js_filename];
			}
		}
	}
	return drupal_get_js('header', $new_js_list);
}
