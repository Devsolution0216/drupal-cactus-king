<?php
// $Id: ds.admin.inc,v 1.1.2.9 2010/10/01 12:43:16 swentel Exp $

/**
 * @file
 * General file for administrative functions.
 */

/**
 * General page.
 */
function ds_general_page() {
  $i = 0;
  $output = '';
  $items = array();

  // Child pages.
  $item = menu_get_item('admin/build/ds');
  if ($content = system_admin_menu_block($item)) {
    foreach ($content as $item) {
      $link = l($item['title'], $item['link_path']);
      if (!empty($item['description'])) {
        $link .= ' : '. $item['description'];
      }
      $items[$i] = $link;
      $i++;
    }
    $childs = theme('item_list', $items);
  }
  else {
    $childs = t('You do not have any administrative items.');
  }

  $output = t('Click on one of the following items to get started.');
  $output .= $childs;

  return $output;
}