<?php
// $Id: vocabindex_admin_vi_form.tpl.php,v 1.1.2.8 2008/10/19 10:52:59 xano Exp $

/**
 * @file
 * Renders the form to administer index pages and blocks.
 *
 * Available variables:
 * $form The Drupal form to render.
 */
$type = $form['vocabindex_type']['#value'];
$vis = vocabindex_vi_load($type, 0, FALSE);
$rows = array();
foreach ($vis as $vi) {
  $id = 'vocabindex_' . $vi->vid . '_';

  // Common form fields.
  $name = drupal_render($form[$id . 'name']);
  $list_style = drupal_render($form[$id . 'view']);
  $node_count = drupal_render($form[$id . 'node_count']);
  array_unshift($rows, array($name, NULL, $list_style, $node_count));
  // The path/enable form field.
  if ($type == VOCABINDEX_VI_PAGE) {
    $rows[0][1] = drupal_render($form[$id . 'path']);
  }
  else {
    $rows[0][1] = drupal_render($form[$id . 'enabled']);
  }
}

// Set the table header.
$header = array(t('Vocabulary'), NULL, t('View'), t('Node counts'));
if ($type == VOCABINDEX_VI_PAGE) {
  $header[1] = t('Path');
}
else {
  $header[1] = t('Enabled');
}

echo theme('table', $header, $rows) . drupal_render($form);