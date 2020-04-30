<?php
// $Id: vocabindex.view.inc,v 1.1.2.2.2.79 2009/01/14 14:41:14 xano Exp $

/**
 * @file
 * All functions related to rendering Vocabulary Index pages or blocks.
 */

/**
 * Load the parent term/vocab of a tree
 *
 * @param $id
 *   Type: integer; The TID or the VID to generate the index page for.
 * @param $type
 *   Type: string; Either VOCABINDEX_TERM or VOCABINDEX_VOC.
 *
 * @return
 * Type: object; The parent
 */
function vocabindex_parent_load($id, $type) {
  switch ($type) {
    case VOCABINDEX_TERM:
      $parent = taxonomy_get_term($id);
      $parent->id = $id;
      break;
    case VOCABINDEX_VOC:
      $parent = taxonomy_vocabulary_load($id);
      $parent->id = $id;
  }

  return $parent;
}

/**
 * Cache a VI.
 *
 * @param $data
 *   Type: any; The data to cache.
 * @param $type
 *   Type: constant; VOCABINDEX_TERM or VOCABINDEX_VOC.
 * @param $id
 *   Type: integer; The VID or TID of the list to return.
 * @param $vi
 *   Type: object;
 */
function vocabindex_cache_set($data, $type, $id, $vi) {
  $lifetime = variable_get('vocabindex_cache_lifetime', 60);
  if ($lifetime > 0) {
    $expire = $lifetime * 60 + mktime();
    cache_set(_vocabindex_cid($type, $id, $vi), $data, 'cache', $expire);
  }
}

/**
 * Return a cached VI.
 *
 * @param $type
 *   Type: constant; VOCABINDEX_TERM or VOCABINDEX_VOC.
 * @param $id
 *   Type: integer; The VID or TID of the list to return.
 * @param $vi
 *   Type: object;
 *
 * @return
 *   Type: any; The cached data.
 */
function vocabindex_cache_get($type, $id, $vi) {
  $lifetime = variable_get('vocabindex_cache_lifetime', 60);
  if ($lifetime > 0) {
    return cache_get(_vocabindex_cid($type, $id, $vi), 'cache');
  }
  else {
    return 0;
  }
}

/**
 * Construct cache ID.
 *
 * @param $type
 *   Type: constant; VOCABINDEX_TERM or VOCABINDEX_VOC.
 * @param $id
 *   Type: integer; The VID or TID of the list.
 * @param $vi
 *   Type: object;
 */
function _vocabindex_cid($type, $id, $vi) {
  global $language;

  // Only alphabetical and browsable pages are pageable.
  if ($vi->type == VOCABINDEX_VI_PAGE && $vi->view == VOCABINDEX_VIEW_FLAT || $vi->view == VOCABINDEX_VIEW_ALPHABETICAL) {
    $page = isset($_GET['page']) ? $_GET['page'] : '0';
  }
  else {
    $page = 0;
  }
  $letter = $vi->view == VOCABINDEX_VIEW_ALPHABETICAL ? htmlentities(vocabindex_letter_get(), ENT_NOQUOTES, 'UTF-8') : NULL;

  return 'vocabindex_' . $type . '_' . $id . '_' . $vi->view . '_' . $language->language . '_' . $page . '_' . $letter;
}

/**
 * Converts a numerical view value to a string.
 *
 * Conversion needs to be done to provide a textual view representation for
 * easy use in CSS files.
 *
 * @param $view
 *   Type: integer; The numerical representation of the view.
 *   VOCABINDEX_VIEW_FLAT, VOCABINDEX_VIEW_ALPHABETICAL or
 *   VOCABINDEX_VIEW_TREE.
 *
 * @return
 *   Type: string; The textual representation of the given view.
 */
function vocabindex_convert_view($view) {
  $strings[VOCABINDEX_VIEW_FLAT] = 'flat';
  $strings[VOCABINDEX_VIEW_TREE] = 'tree';
  $strings[VOCABINDEX_VIEW_ALPHABETICAL] = 'alphabetical';

  return $strings[$view];
}

/**
 * Set the letter for which an alphabetical list is requested.
 *
 * @param $value
 *   Type: string; The letter in question.
 *
 * @return
 *   Type: any; The $value parameter is being returned if it's a string,
 *   otherwise FALSE is being returned.
 */
function vocabindex_letter_set($value = NULL) {
  static $letter = NULL;

  if (is_null($letter) && !is_null($value)) {
    $letter = $value;
  }

  return $letter;
}

/**
 * Get the letter for which an alphabetical index is requested.
 *
 * @param $tree
 *   Type: array; A taxonomy tree. Only necessary for the first call.
 *
 * @return
 *   Type: string; The letter in question.
 */
function vocabindex_letter_get($tree = array()) {
  static $letter = NULL;

  if (is_null($letter)) {
    $letter = vocabindex_letter_set();

    if ($letter == '') {
      $letters = vocabindex_letters_get($tree);
      $letter = array_shift($letters);
    }
  }

  return $letter;
}

/**
 * Get all first letters from the term names of a given tree.
 *
 * @param $tree
 *   Type: array; The taxonomy tree containing the terms.
 *
 * @return
 *   Type: array; The array has been sorted by value alphabetically.
 */
function vocabindex_letters_get($tree) {
  // Caching the letters won't be a problem as alphabetical VIs are only
  // available to pages.
  static $letters = array();

  if (empty($letters)) {
    $transliteration = variable_get('vocabindex_transliteration', FALSE);

    // Get all first letters from the term names.
    for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
      $term = $tree[$i];
      $letter = drupal_strtolower(drupal_substr($term->name, 0, 1));
      if ($transliteration == TRUE) {
        $letter = vocabindex_transliterate($letter);
      }
      $letters[] = $letter;
    }
    $letters = array_values(array_unique($letters));

    if ($transliteration == FALSE) {
      // Sort the letters.
      $letters_transliterated = array();
      for ($i = 0, $len_i = count($letters); $i < $len_i; $i++) {
        $letter = $letters[$i];
        // Group letters by their transliterated equivalent.
        $letters_transliterated[vocabindex_transliterate($letter)][] = $letter;
      }
      // Sort the groups.
      ksort($letters_transliterated);
      $letters = array();
      // Sort the letters from every single group and merge them with the main
      // array of letters.
      foreach ($letters_transliterated as $letter) {
        sort($letter);
        $letters = array_merge($letters, $letter);
      }
    }
  }

  return $letters;
}

/**
 * Display a Vocabulary Index page
 *
 * @param $id
 *   Type: integer; The TID or the VID to generate the index page for.
 * @param $type
 *   Type: constant; Either VOCABINDEX_VOC or VOCABINDEX_TERM.
 * @param $letter
 *   Type: string; The letter to display the terms for. Only needed for
 *   alphabetical VIs.
 *
 * @return string A fully rendered index page
 */
function vocabindex_view_page($id, $type, $letter = '') {
  vocabindex_letter_set($letter);
  $parent = vocabindex_parent_load($id, $type);
  $parent->description = check_plain($parent->description);
  $vi = vocabindex_vi_load(VOCABINDEX_VI_PAGE, $parent->vid);

  $output = vocabindex_vi_view($id, $type, $vi, $parent);

  return theme('vocabindex_page', $parent, $output['content'], isset($output['pager']) ? $output['pager'] : NULL, isset ($output['pager_alpha']) ? $output['pager_alpha'] : NULL);
}

/**
 * Display a Vocabulary Index block
 *
 * @param $id
 *   Type: integer; The VID to generate the Index Block for.
 *
 * @return
 *   Type: string; The block's content: a rendered index.
 */
function vocabindex_view_block($vid) {
  $vi = vocabindex_vi_load(VOCABINDEX_VI_BLOCK, $vid);
  $output = vocabindex_vi_view($vid, VOCABINDEX_VOC, $vi, $vi);

  return $output['content'];
}

/**
 * View an index.
 *
 * @param $id
 *   Type: integer; The TID or the VID to generate the index page for.
 * @param $type
 *   Type: string; Either 'term' or 'vocab'.
 * @param $vi
 *   Type: object; The VI the current index belongs to.
 * @param $parent
 *   Type: object; The object of the vocab or the term under which to generate
 *   the tree.
 *
 * @return
 *   Type: string; A fully rendered index.
 */
function vocabindex_vi_view($id, $type, $vi, $parent) {
  global $language;

  $path = drupal_get_path('module', 'vocabindex');
  drupal_add_css($path . '/vocabindex.css', 'module', 'screen', FALSE);
  // Only add the JavaScript file if this is a tree view.
  if ($vi->view == VOCABINDEX_VIEW_TREE) {
    drupal_add_js($path . '/vocabindex.js');
  }

  // Check for cached data.
  $cached_data = vocabindex_cache_get($type, $id, $vi);

  // There is no cached data, so render the output from scratch.
  if ($cached_data === 0) {
    // Check whether it's a term index or not. If so, set the term's TID as
    // $parent for taxonomy_get_tree(). Do not confuse with the $parent argument
    // of vocabindex_vi_view().
    $pid = $type == VOCABINDEX_TERM ? $parent->tid : 0;
    $tree = taxonomy_get_tree($parent->vid, $pid, -1, $vi->depth);

    // Display an error message if there are no terms.
    if (count($tree) == 0) {
      $output['content'] = t('There are currently no terms in this vocabulary.');
    }
    // We do have terms, so render them.
    else {
      // Calculate node counts.
      foreach ($tree as $term) {
        $term->node_count = $vi->node_count ? taxonomy_term_count_nodes($term->tid) : 0;
      }

      $children = vocabindex_get_children($tree);

      // Render the list-items.
      $view = vocabindex_convert_view($vi->view);
      $output = call_user_func('vocabindex_list_render_' . $view, $tree, $children, $vi);

      // Render the list.
      $output['content'] = theme('item_list', $output['list_items'], NULL, 'ul', array('class' => 'vocabindex ' . $view));
    }
    unset($output['list_items']);

    if ($vi->view == VOCABINDEX_VIEW_ALPHABETICAL) {
      $output['letter'] = vocabindex_letter_get($tree);
    }

    vocabindex_cache_set($output, $type, $id, $vi);
  }
  else {
    $output = $cached_data->data;
  }

  // Processes that cannot be cached.
  if ($vi->view == VOCABINDEX_VIEW_ALPHABETICAL && isset($output['letter'])) {
    drupal_set_title(check_plain($vi->name) . ' » ' . drupal_strtoupper($output['letter']));
  }

  return $output;
}

/**
 * Render a flat list.
 *
 * @param $tree
 *   Type: array; A taxonomy tree.
 * @param $children
 *   Type: array; The vocabindex_get_children() output for this particular tree.
 * @param $vi
 *   Type: object; The VI this list belongs to.
 *
 * @return
 *   Type: string; The fully rendered list.
 */
function vocabindex_list_render_flat($tree, $children, $vi) {
  // Filter out all children.
  $tree_buffer = array();
  for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
    if ($tree[$i]->depth == 0) {
      $tree_buffer[] = $tree[$i];
    }
  }
  $tree = $tree_buffer;

  // Page the tree.
  $pager = variable_get('vocabindex_pager', 25);
  if ($vi->type == VOCABINDEX_VI_PAGE && $pager > 0) {
    vocabindex_pager_query($tree);
  }

  $items = array();
  for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
    $term = $tree[$i];
    $zebra = ($i % 2 == 0 ? 'even' : 'odd');
    $items[] = array(
      'data' => vocabindex_term_link($term, $vi),
      'class' => $zebra . (isset($children[$term->tid]) ? ' parent' : NULL),
    );
  }

  return array('list_items' => $items, 'pager' => theme_pager());
}

/**
 * Render a tree
 *
 * @param $tree
 *   Type: array; A taxonomy tree.
 * @param $children
 *   Type: array; The vocabindex_get_children() output for this particular tree.
 * @param $vi
 *   Type: object; The VI this list belongs to.
 *
 * @return
 *   Type: string; The fully rendered list.
 */
function vocabindex_list_render_tree($tree, $children, $vi) {
  //Prepare the tree; use the TIDs as keys for easy access to the terms.
  $tree_buffer = array();
  for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
    $term = $tree[$i];
    $tree_buffer[$term->tid] = $term;
  }
  $tree = $tree_buffer;

  return array('list_items' => _vocabindex_list_render_tree($tree, $children, $vi));
}

/**
 * Helper function for vocabindex_list_render_tree()
 *
 * Walks through the tree and renders each term.
 *
 * @param $tree
 *   Type: array; The term tree. It is a taxonomy tree modified by
 *   _vocabindex_list_render_tree().
 * @param $children
 *   Type: array; The vocabindex_get_children() output for this particular tree.
 * @param $vi
 *   Type: object; The VI this list belongs to.
 * @param $pid
 *   Type: integer; The ID of the term to generate the children for. Internal
 *   use only.
 * @param $zebra_i
 *   Type: integer; Incrementor used for calculating the zebra value. Internal
 *   use only.
 *
 * @return
 *   Type: string; The fully rendered list.
 */
function _vocabindex_list_render_tree($tree, $children, $vi, $pid = 0, &$zebra_i = 0) {
  $items = array();

  for ($i = 0, $len_i = count($children[$pid]); $i < $len_i; $i++) {
    $zebra_i++;
    $zebra = ($zebra_i % 2 == 0 ? 'even' : 'odd');
    $term = $tree[$children[$pid][$i]];

    $term_children = NULL;
    $parent = NULL;
    if (array_key_exists($term->tid, $children)) {
      $term_children = _vocabindex_list_render_tree($tree, $children, $vi, $term->tid, $zebra_i);
    }

    // Render the current term.
    $items[] = array(
      'data' => vocabindex_term_link($term, $vi),
      'children' => $term_children,
      'class' => $zebra . (!is_null($term_children) ? ' parent expanded' : NULL),
    );
  }

  return $items;
}

/**
 * Render an alphabetical list.
 *
 * @param $tree
 *   Type: array; A taxonomy tree.
 * @param $children
 *   Type: array; The vocabindex_get_children() output for this particular tree.
 * @param $vi
 *   Type: object; The VI this list belongs to.
 */
function vocabindex_list_render_alphabetical($tree, $children, $vi) {
  $letter = vocabindex_letter_get($tree);

  $output['pager_alpha'] = vocabindex_pager(vocabindex_letters_get($tree), $vi->path);
  $tree_buffer = array();
  for ($i = 0, $len_i = count($tree); $i < $len_i; $i++) {
    $term = $tree[$i];
    // Reset depth to prevent terms with depth != 0 from not being displayed due
    // to the depth check in _vocabindex_list_render_flat().
    $term->depth = 0;
    $term_letter = drupal_strtolower(drupal_substr($term->name, 0, 1));
    if (variable_get('vocabindex_transliteration', FALSE) == TRUE) {
      $term_letter = vocabindex_transliterate($term_letter);
    }
    if ($letter == $term_letter) {
      $tree_buffer[] = $term;
    }
  }
  $tree = $tree_buffer;

  // Throw a 404 if there are no terms matching this letter.
  if (count($tree) == 0) {
    drupal_not_found();
    exit;
  }
  $output += vocabindex_list_render_flat($tree, array(), $vi);

  return $output;
}

/**
 * Render a pager for an alphabetical index.
 *
 * @param $letters
 *   Type: array; The available letters to create a pager for.
 *
 * @return
 *   Type: string; A fully rendered pager.
 */
function vocabindex_pager($letters, $path) {
  global $language;

  $letter_active = vocabindex_letter_get();
  $letters_rendered = array();
  for ($i = 0, $len_i = count($letters); $i < $len_i; $i++) {
    $letter = $letters[$i];
    $active = $letter == $letter_active ? 'active' : '';
    $path_letter = $i == 0 ? NULL : '/' . $letter;
    $letters_rendered[] = l(drupal_strtoupper($letter), $path . $path_letter, array('attributes' => array('class' => $active)));
  }

  if (defined('LANGUAGE_RTL') && $language->direction == LANGUAGE_RTL) {
    $letters_rendered = array_reverse($letters_rendered, TRUE);
  }

  $pager = implode(theme('vocabindex_pager_separator'), $letters_rendered);

  return theme('vocabindex_pager', $pager);
}

/**
 * Render a regular pager.
 *
 * Based on pager_query().
 *
 * @param $tree
 *   Type: array; The taxonomy tree to page.
 *
 * @return
 *   Type: string; A fully rendered pager.
 */
function vocabindex_pager_query(&$tree) {
  $limit = variable_get('vocabindex_pager', 25);
  if ($limit != 0) {
    global $pager_page_array, $pager_total, $pager_total_items;

    // Convert comma-separated $page to an array, used by other functions.
    $pager_page_array = isset($_GET['page']) ? explode(',', $_GET['page']) : array(0);

    $total_terms = count($tree);
    $buffer = array();
    foreach ($pager_page_array as $page) {
      $start = $page * $limit;
      // Throw a 404 if a non-existent range has been requested.
      if ($start < 0 || $start >= $total_terms) {
        drupal_not_found();
        exit;
      }
      $end = ($page + 1) * $limit;
      $end = min($end, $total_terms);
      while ($start < $end) {
        $buffer[] = $tree[$start];
        $start++;
      }
    }
    $tree = $buffer;

    // We calculate the total of pages as ceil(items / limit).
    $pager_total_items[] = $total_terms;
    $pager_total[] = ceil($total_terms / $limit);
    $pager_page_array[] = max(0, min((int)$pager_page_array[0], ((int)$pager_total[0]) - 1));
  }
}

/**
 * Return the current language's text direction.
 *
 * @return
 *   Type: string;
 */
function vocabindex_text_dir() {
  global $language;
  return defined('LANGUAGE_RTL') && $language->direction == LANGUAGE_RTL ? 'rtl' : 'ltr';
}

/**
 * Create a term link
 *
 * @param $term
 *   Type: object; A term object.
 * @param $vi
 *   Type: The VI object for the vocabulary $term belongs to.
 *
 * @return string
 */
function vocabindex_term_link($term, $vi) {
  $term->path = taxonomy_term_path($term);
  $term->name = check_plain($term->name);
  $term->description = check_plain($term->description);

  return theme('vocabindex_link', $term, $vi, vocabindex_text_dir());
}