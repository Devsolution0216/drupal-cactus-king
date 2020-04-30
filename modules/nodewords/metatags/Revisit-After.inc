<?php
// $Id: Revisit-After.inc,v 1.1.4.2 2009/02/07 08:03:01 robrechtj Exp $

/**
 * @file
 * Support file for Revisit-After meta tag.
 */

function nodewords_revisit_after_prepare($type, $ids, $value, $settings) {
  if (!is_numeric($value) || $value == 0) {
    return '';
  }
}

function nodewords_revisit_after_form($type, $value, $settings) {
  return array(
    '#type' => 'textfield',
    '#title' => t('Revisit after'),
    '#suffix' => t(' days'),
    '#size' => 6,
    '#default_value' => $value,
    '#description' => t('The Revisit-After META tag defines how often a search engine or spider should come to your website for re-indexing. Often this tag is used for websites that change their content often and on a regular basis. This tag can also be beneficial in boosting your rankings if search engines display results based on the most recent submissions.'),
  );
}

