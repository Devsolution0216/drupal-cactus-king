<?php
/**
 * @file
 *  Provide the views gallariffic plugin object with default options and form.
 */

/**
  * Implementation of views_plugin_style().
  */
class views_galleriffic_style_plugin extends views_plugin_style {

  function option_definition() {
    $options = parent::option_definition();
    unset($options['grouping']);
    $options['css'] = array('default' => 'true');
    $options['delay'] = array('default' => '3000');
    $options['preload'] = array('default' => '10');
    $options['transition'] = array('default' => '1000');
    $options['numbthumbs'] = array('default' => '10');
    $options['pager_top'] = array('default' => '');
    $options['pager_bottom'] = array('default' => 'true');
    $options['renderss'] = array('default' => 'true');
    $options['rendernav'] = array('default' => 'true');
    $options['playtext'] = array('default' => 'Play');
    $options['pausetext'] = array('default' => 'Pause');
    $options['prevlink'] = array('default' => 'Previous');
    $options['nextlink'] = array('default' => 'Next');
    $options['nextpage'] = array('default' => 'Next >');
    $options['prevpage'] = array('default' => '< Prev');
    $options['history'] = array('default' => 'true');
    $options['start'] = array('default' => '');
    $options['sync'] = array('default' => 'true');
    $options['keyboard'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['grouping']);
    $history = views_galleriffic_history();
    $form['history'] = array(
      '#type' => $history['type'],
      '#title' => t('History'),
      '#description' => $history['description'],
      '#default_value' => $this->options['history'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['css'] = array(
      '#type' => 'select',
      '#title' => t('Use default css'),
      '#description' => t('You can use the default css or not. The default can\'t anticipate the image sizes you use so will likely need to be updated for individual needs.'),
      '#default_value' => $this->options['css'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['delay'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay'),
      '#default_value' => $this->options['delay'],
      '#description' => t('The delay between each slide. In miliseconds.'),
    );
    $form['transition'] = array(
      '#type' => 'textfield',
      '#title' => t('Transition Duration'),
      '#default_value' => $this->options['transition'],
      '#description' => t('If using the default transitions, specifies the duration of the transitions.'),
    );
    $form['preload'] = array(
      '#type' => 'textfield',
      '#title' => t('Images to Preload'),
      '#default_value' => $this->options['preload'],
      '#description' => t('Set to -1 to preload all images.'),
    );
    $form['numbthumbs'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of Thumbnails'),
      '#default_value' => $this->options['numbthumbs'],
      '#description' => t('This is the number of thumbnails that will appear before a pager is used.'),
    );
    $form['pager_top'] = array(
      '#type' => 'select',
      '#title' => t('Enable Top Pager'),
      '#description' => t('Enable the pager at the top of the gallery. This will only work if the number of slides is higher than the number of thumbs.'),
      '#default_value' => $this->options['pager_top'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['pager_bottom'] = array(
      '#type' => 'select',
      '#title' => t('Enable Bottom Pager'),
      '#description' => t('Enable the pager at the bottom of the gallery.'),
      '#default_value' => $this->options['pager_bottom'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['renderss'] = array(
      '#type' => 'select',
      '#title' => t('Show Play and Pause Controls'),
      '#description' => t('Specifies whether the slideshow\'s Play and Pause links should be rendered.'),
      '#default_value' => $this->options['renderss'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['rendernav'] = array(
      '#type' => 'select',
      '#title' => t('Show Next and Pause Controls'),
      '#description' => t('Specifies whether the slideshow\'s Next and Previous links should be rendered.'),
      '#default_value' => $this->options['rendernav'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['playtext'] = array(
      '#type' => 'textfield',
      '#title' => t('Play Link Text'),
      '#default_value' => $this->options['playtext'],
      '#description' => t('Text to display for the PLAY link.'),
    );
    $form['pausetext'] = array(
      '#type' => 'textfield',
      '#title' => t('Pause Link Text'),
      '#default_value' => $this->options['pausetext'],
      '#description' => t('Text to display for the PAUSE link.'),
    );
    $form['prevlink'] = array(
      '#type' => 'textfield',
      '#title' => t('Previous Link Text'),
      '#default_value' => $this->options['prevlink'],
      '#description' => t('Text to display for the PREVIOUS link.'),
    );
    $form['nextlink'] = array(
      '#type' => 'textfield',
      '#title' => t('Next Link Text'),
      '#default_value' => $this->options['nextlink'],
      '#description' => t('Text to display for the NEXT link.'),
    );
    $form['nextpage'] = array(
      '#type' => 'textfield',
      '#title' => t('Next Page Link Text'),
      '#default_value' => $this->options['nextpage'],
      '#description' => t('Text to display for the next PAGE link.'),
    );
    $form['prevpage'] = array(
      '#type' => 'textfield',
      '#title' => t('Previous Page Link Text'),
      '#default_value' => $this->options['prevpage'],
      '#description' => t('Text to display for the next PREVIOUS link.'),
    );
    $form['start'] = array(
      '#type' => 'select',
      '#title' => t('Auto Start'),
      '#description' => t('Specifies whether the slideshow should be playing or paused when the page first loads.'),
      '#default_value' => $this->options['start'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['sync'] = array(
      '#type' => 'select',
      '#title' => t('Sync Transitions'),
      '#description' => t('Specifies whether the out and in transitions occur simultaneously or distinctly.'),
      '#default_value' => $this->options['sync'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
    $form['keyboard'] = array(
      '#type' => 'select',
      '#title' => t('Keyboard Transitions'),
      '#description' => t('Specifies whether you want to be able to scroll through images with your keyboard. CAUTION, may interfere with comments if turned on.'),
      '#default_value' => $this->options['keyboard'],
      '#options' => array('true' => t('Yes'), '' => t('No')),
    );
  }

  /**
   * Make sure the display and all associated handlers are valid.
   *
   * @return
   *   Empty array if the display is valid; an array of error strings if it is not.
   */
  function validate() {
    $row_handler = $this->row_plugin->definition['handler'];
    switch ($row_handler) {
      case 'views_galleriffic_plugin_row_gallerifficrows':
      $errors = array();
      $row_fields= $this->row_plugin->options;
      //check to make sure fields aren't empty
      foreach ($row_fields as $title => $result) {
        if (empty($result)) {
          $errors[] = t('Views Galleriffic requires you to assign a field for "@field". Currently the "@field" is empty. Click \'Row Style: Galleriffic Fields\' to set.', array('@field' => $title));
        }
      }
      //check to make sure that two of the same image fields are not selected
      $results = array();
      foreach ($row_fields as $title => $result) {
        if (in_array($result, $results)) {
          $errors[] = t('Views Galleriffic does not allow you to use the same field instance twice. You can use the same field twice, and are encouraged to for images. You just need to make two instances of the same field.  To do add the same field twice under \'Fields\'. Give each a different label. Then select each instance of that field once under \'Row style: Galleriffic Fields\'. See README.txt for details.');
        }
        $results[] = $result;
      }
      if (empty($errors)) {
        //check to make sure that the url handler is selected
        foreach ($row_fields as $title => $result) {
          if ($title == 'slide_field' || $title == 'thumbnail_field') {
            $format = $this->view->display[$this->row_plugin->display->id]->handler->handlers['field'][$result]->options['format'];
            if (!stripos($format, 'url')) {
              $errors[] = t('You must select "url" as the imagecache handler for the "@field" field.', array('@field' => $title));
            }
          }
        }
      }
      //check to make sure 'group multiple values' is not selected
      $fields = $this->view->display[$this->row_plugin->display->id]->handler->handlers['field'];
      foreach ($fields as $name => $data) {
        $group = $data->options['multiple'];
        //if an imagefield has only 1 allowed value group will return TRUE, thus the is_bool
        if ((!is_bool($group['group']) && $group['group'] == 1 && ($group['multiple_number'] > 1 || empty($group['multiple_number'])))) {
          $errors[] = t('Views Galleriffic supports \'Group Multiple Values\' ONLY if the \'Show _ Value(s)\' is set to 1. Please update the field the "@field" field.', array('@field' => $name));
        }
      }

      return $errors;
    }
  }
}
