<?php

/**
 * Implementation of hook_token_list().
 */
function content_taxonomy_token_list($type = 'all') {
  if ($type == 'field' || $type == 'all') {
    $tokens = array();

    $tokens['content_taxonomy']['term']  = t('Name of top taxonomy term');
    $tokens['content_taxonomy']['tid']   = t('ID of top taxonomy term');
    $tokens['content_taxonomy']['terms']  = t('Names of all taxonomy terms separated by commas');
    $tokens['content_taxonomy']['tids']   = t('IDs of all taxonomy terms separated by commas');
    $tokens['content_taxonomy']['vocab'] = t('Name of terms vocabulary');
    $tokens['content_taxonomy']['vid']   = t('ID of terms vocabulary');

    return $tokens;
  }
}

/**
 * Implementation of hook_token_values().
 */
function content_taxonomy_token_values($type, $object = NULL) {
  if ($type == 'field') {
    $items = $object;
    $terms = array();
    $tids = array();
    
    foreach ($items as $item) {
      $tid = $item['value'];
      if ($tid) {
        $term = taxonomy_get_term($tid);
        $tids[] = $tid;
        $terms[] = check_plain($term->name);
        $vid = $term->vid;
      }
    }
    if ($vid) {
      $vocabulary = taxonomy_vocabulary_load($vid);
    }

    $tokens['terms'] = implode(', ', $terms);
    $tokens['tids']  = implode(', ', $tids);
    $tokens['term']  = $terms[0];
    $tokens['tid']   = $tids[0];
    $tokens['vocab'] = isset($vocabulary) ? $vocabulary->name : '';
    $tokens['vid']   = $vid;

    return $tokens;
  }
}
