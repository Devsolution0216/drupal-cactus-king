<?php
// $Id: theme-settings.php,v 1.4 2010/03/11 18:48:02 atrasatti Exp $

/**
 * This file is part of nokia_mobile is a theme based on the Nokia templates
 * published on Forum Nokia and fully sponsored by Nokia.
 * The theme should be used with the Mobile Plugin -module.
 *
 * @author Andrea Trasatti <atrasatti@gmail.com>
 * @copyright Copyright Nokia
 * @license http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt GPL Version 2.0
 */

/**
 * Implementation of THEMEHOOK_settings() function.
 *
 * @param $saved_settings
 *   An array of saved settings for this theme.
 * @param $subtheme_defaults
 *   Allow a subtheme to override the default values.
 * @return
 *   A form array.
 */

function nokia_mobile_settings($saved_settings) {
  // Load color.inc to get the base color
  require_once "color/color.inc";
  if (!isset($saved_settings['nokia_mobile_native']) || !(module_exists('mobileplugin'))) {
    $saved_settings['nokia_mobile_native'] = 1;
  }
  if (!isset($saved_settings['theme_header_text_color'])) {
    $saved_settings['theme_header_text_color'] = $info['blend_target'];
  }
  if (!isset($saved_settings['theme_image_colors'])) {
    $saved_settings['theme_image_colors'] = 0;
  }
  $form['recognition']['nokia_mobile_native'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Detect devices based on Nokia rules (default).'),
    '#description'   => 'Select to use embedded device recognition, or de-select to use your custom rules, read theme doc on how to use them.',
    '#default_value' => $saved_settings['nokia_mobile_native'],
    '#disabled'      => !(module_exists('mobileplugin')),
  );
  
  // NOTE: If you change the list of colours here you should also update the function nokia_mobile_settings_css_filename() in template.php
  $form['colors']['theme_image_colors'] = array(
    '#type'          => 'radios',
    '#title'         => t('Pick a color for buttons. Choose something that matches your theme colors.'),
    '#description'   => 'The theme comes with 4 sets of buttons in different colors to match your preferences. You are welcome to create your own and replace these.',
    '#default_value' => $saved_settings['theme_image_colors'],
    '#options' => array(t('Green'), t('Blue'), t('Red'), t('Grey')),
  );
  
  $form['colors']['theme_header_text_color'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Define the color for the site name text (white is the default). Use HEX notation, i.e. white is #ffffff and black is #000000.'),
    '#description'   => 'Define the color of the text for your site name, i.e. the text at the very top of the page. White will be good for most cases, but pick a different one if it clashes with your "header top" tint.',
    '#default_value' => $saved_settings['theme_header_text_color'],
  );
  
	return $form;
}

