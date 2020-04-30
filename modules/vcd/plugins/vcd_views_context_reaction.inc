<?php
/**
 * @file
 * Context reaction plugin
 */

class vcd_views_context_reaction extends context_reaction {

  function options_form($context) {
    $form['debug'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );

    $form['description'] = array(
      '#type' => 'markup',
      '#prefix' => '<p>',
      '#value' => t('This reaction is not configurable. Set it to load the context into Views. When you use the VCD Object row style plugin, you\'ll be able to associate a build mode to a context that loads this reaction.'),
      '#suffix' => '</p>',
    );

    return $form;
  }

  function options_form_submit($values) {
    return array('debug' => 1);
  }
	
	/**
	 * Executes the reaction when all conditions are met
	 * Sets the build mode of the view
	 *
	 * @param array $options the options array of the subject view
	 * @param string $build_mode The build mode which overrules the default build_mode
	 */
  function execute(&$options, $build_mode) {
    $options['build_mode'] = $build_mode;
  }
}