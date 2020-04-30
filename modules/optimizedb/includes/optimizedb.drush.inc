<?php

/**
 * @file
 * Functions for optimizing the tables and cleaning table cache_form.
 */

/**
 * Implements hook_drush_command().
 */
function optimizedb_drush_command() {
  $items = array();

  $items['optimizedb-optimize'] = array(
    'description' => dt('Optimizing tables of the active database.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'callback' => 'drush_optimizedb_optimize',
  );

  $items['optimizedb-cleaning'] = array(
    'description' => dt('Cleaning the table cache_form.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'callback' => 'drush_optimizedb_cleaning',
  );

  return $items;
}

/**
 * Optimizing the tables.
 */
function drush_optimizedb_optimize() {
  drush_bootstrap(DRUSH_BOOTSTRAP_DRUPAL_FULL);
  $form_state = array();
  optimizedb_admin_optimize_table_submit(array(), $form_state);
}

/**
 * Cleaning table cache_form.
 */
function drush_optimizedb_cleaning() {
  drush_bootstrap(DRUSH_BOOTSTRAP_DRUPAL_FULL);

  _optimizedb_clear_table();
  drush_log(dt('The table "cache_form" is cleared.'), 'ok');
}
