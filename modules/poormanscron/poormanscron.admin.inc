<?php
// $Id: poormanscron.admin.inc,v 1.1 2008/02/06 16:35:17 robloach Exp $

/**
 * @file
 * Provides the administration page for Poormanscron.
 */
  
/**
 * Administration page for Poormanscron.
 */
function poormanscron_admin_settings() {
  $form['time_intervals'] = array('#type' => 'fieldset', '#title' => t('Time intervals'));
  $form['time_intervals']['poormanscron_interval'] = array(
    '#type' => 'textfield', '#title' => t('Cron runs interval'),
    '#default_value' => variable_get('poormanscron_interval', 60),
    '#size' => 5, '#maxlength' => 10,
    '#description' => t('Minimum number of minutes between cron runs. Cron will actually execute during the first page request after the interval has elapsed.')
  );
  $form['time_intervals']['poormanscron_retry_interval'] = array(
    '#type' => 'textfield', '#title' => t('Retry interval'),
    '#default_value' => variable_get('poormanscron_retry_interval', 10),
    '#size' => 5, '#maxlength' => 10,
    '#description' => t('The number of minutes to wait after a cron run error before retrying.')
  );

  $form['logging'] = array('#type' => 'fieldset', '#title' => t('Logging'));
  $form['logging']['poormanscron_log_cron_runs'] = array(
    '#type' => 'select', '#title' => t('Log successful cron runs'),
    '#default_value' => variable_get('poormanscron_log_cron_runs', 1),
    '#options' => array('1' => t('Yes'), '0' => t('No')),
    '#description' => t('If you want to log successful cron runs to the Drupal watchdog, say Yes here. If those messages annoy you, disable them by selecting No.')
  );
  $form['logging']['poormanscron_log_progress'] = array(
    '#type' => 'select', '#title' => t('Log poormanscron progress'),
    '#default_value' => variable_get('poormanscron_log_progress', 0),
    '#options' => array('1' => t('Yes'), '0' => t('No')),
    '#description' => t('If you want to log the progress of a poormanscron run to the Drupal watchdog, say Yes here. If those messages annoy you, disable them by selecting No.')
  );
  return system_settings_form($form);
}
