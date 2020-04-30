<?php
// $Id: views_slideshow.views_slideshow.inc,v 1.1.2.1 2009/03/30 20:46:42 aaron Exp $

/**
 *  @file
 *  The default options available with Views Slideshow.
 */

function views_slideshow_views_slideshow_modes() {
  $options = array(
    VIEWS_SLIDESHOW_MODE_SINGLE_FRAME => t('Single frame'),
    VIEWS_SLIDESHOW_MODE_THUMBNAIL_HOVER => t('Thumbnail hover'),
//    VIEWS_SLIDESHOW_MODE_JCAROUSEL => t('jCarousel'),
  );
  return $options;
}

function views_slideshow_views_slideshow_option_definition() {
  $options['mode'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_MODE);
  $options['hover'] = array('default' => (module_exists('hoverintent') ? 'hoverIntent' : 'hover'));
  $options['timer_delay'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_TIMER_DELAY);
  $options['sort'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_SORT_ORDER);
  $options['fade'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_FADE);
  $options['fade_speed'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_FADE_SPEED);
  $options['fade_value'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_FADE_VALUE);
  $options['hover_breakout'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_HOVER_BREAKOUT);
  $options['teasers_last'] = array('default' => VIEWS_SLIDESHOW_DEFAULT_TEASERS_LAST);
  return $options;
}

function views_slideshow_views_slideshow_options_form(&$form, &$form_state, &$view) {
  $options = array(
    VIEWS_SLIDESHOW_HOVER_BREAKOUT_TEASER => t('Teaser'),
    VIEWS_SLIDESHOW_HOVER_BREAKOUT_FULL => t('Full'),
  );
  $form['hover_breakout'] = array(
    '#type' => 'radios',
    '#title' => t('Hover breakout'),
    '#options' => $options,
    '#default_value' => $view->options['hover_breakout'],
    '#description' => t("Hover breakout determines how to display the breakout element of the %thumbnail mode, either as a teaser or full node. It is ignored in %single mode.", array('%thumbnail' => t('Thumbnail hover'), '%single' => t('Single frame'))),
  );
  $form['teasers_last'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display teasers last'),
    '#default_value' => $view->options['teasers_last'],
    '#description' => t('When the mode is thumbnail hover, this determines whether to print the teasers first or second.'),
  );
  $options = array('hover' => t('Hover'));
  if (module_exists('hoverintent')) {
    $options['hoverIntent'] = t('HoverIntent');
  }
  $form['hover'] = array(
    '#type' => 'radios',
    '#title' => t('Mouse hover'),
    '#options' => $options,
    '#default_value' => $view->options['hover'],
    '#description' => t('The !hoverintent, if installed, adds the %hoverintent option here. Selecting it causes a delay when the mouse hovers, to stop quick flybys from triggering the behavior. Selecting %hoverdefault chooses the default mouse behavior.', array('!hoverintent' => l(t('HoverIntent module'), 'http://drupal.org/project/hoverintent'), '%hoverintent' => t('HoverIntent'), '%hoverdefault' => t('Hover'))),
  );
  $form['timer_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay (in milliseconds)'),
    '#default_value' => $view->options['timer_delay'],
  );
  $options = array(
    VIEWS_SLIDESHOW_SORT_FORWARD => t('Forward'),
    VIEWS_SLIDESHOW_SORT_REVERSE => t('Reverse'),
    VIEWS_SLIDESHOW_SORT_RANDOM => t('Random'),
  );
  $form['sort'] = array(
    '#type' => 'radios',
    '#title' => t('Slideshow sort order'),
    '#description' => t('This option determines the sort order of the returned results within the slideshow. Note that it is not related to the View\'s sorting options, and will only affect resulting items.'),
    '#options' => $options,
    '#default_value' => $view->options['sort'],
  );
  $form['fade'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fade'),
    '#default_value' => $view->options['fade'],
    '#description' => t('If checked, then the slideshow will fade between frames. Otherwise, the Fade speed and value, below, will be ignored.'),
  );
  $options = array(
    VIEWS_SLIDESHOW_FADE_SPEED_SLOW => t('Slow'),
    VIEWS_SLIDESHOW_FADE_SPEED_NORMAL => t('Normal'),
    VIEWS_SLIDESHOW_FADE_SPEED_FAST => t('Fast'),
  );
  $form['fade_speed'] = array(
    '#type' => 'radios',
    '#title' => t('Fade speed'),
    '#options' => $options,
    '#default_value' => $view->options['fade_speed'],
  );
  $form['fade_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Fade value'),
    '#description' => t('The opacity to fade to, between 0 (fully transparent) and 1 (fully opaque).'),
    '#default_value' => $view->options['fade_value'],
  );
  $options = array(
    VIEWS_SLIDESHOW_HOVER_BREAKOUT_TEASER => t('Teaser'),
    VIEWS_SLIDESHOW_HOVER_BREAKOUT_FULL => t('Full'),
  );
}
