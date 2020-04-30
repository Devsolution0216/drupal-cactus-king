<?php
// $Id: geourl.inc,v 1.1.4.2 2008/01/22 09:14:20 robrechtj Exp $

/**
 * @file
 * Support file for GEOURL meta tag.
 */

function nodewords_geourl_prepare($type, $ids, $value, $settings) {
  if ((!isset($value) || $value == '') && !($type == 'node' && variable_get('location_'. $type, 0) && module_exists('location'))) {
    $value = $settings['global']['geourl'];
  }
  return $value;
}

function nodewords_geourl_form($type, $value, $settings) {
  return array(
    '#type' => 'textfield',
    '#title' => t('GeoURL'),
    '#default_value' => $value,
    '#size' => 60,
    '#maxlength' => $settings['max_size'],
    '#description' => t('Enter a GeoURL (latitude, longitude) for this page.'),
  );
}
