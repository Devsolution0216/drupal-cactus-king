<?php

// custom theme settings: dropdown menu, css image preload

function phptemplate_settings($saved_settings) {

  $defaults = array(
    'menutype' => 0,
    'cssPreload' =>0
  );


  $settings = array_merge($defaults, $saved_settings);

	  $form['menutype'] = array(
	    '#type' => 'select',
	    '#title' => t('Do you want to use static or drop down Primary Links ?'),
	    '#default_value' => $settings['menutype'],
	    '#options' => array(
		0 => 'static',
		1 => 'drop down',
		)
	  );
	  
	  $form['cssPreload'] = array(
	    '#type' => 'radios',
	    '#title' => t('Do you want to use image preload ?'),
	    '#default_value' => $settings['cssPreload'],
	    '#options' => array(
		0 => 'no',
		1 => 'yes',
		)
	  );
  

  return $form;
}


?>