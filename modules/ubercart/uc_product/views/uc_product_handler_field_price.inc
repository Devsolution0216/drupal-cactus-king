<?php

/**
 * @file
 * Views handler: Product price field.
 */

/**
 * Return a formatted price value to display in the View.
 */
class uc_product_handler_field_price extends views_handler_field_numeric {
  function option_definition() {
    $options = parent::option_definition();

    $options['format'] = array('default' => 'uc_price');
    $options['revision'] = array('default' => 'themed');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = $this->options;

    $form['format'] =  array(
      '#title' => t('Format'),
      '#type' => 'radios',
      '#options' => array(
        'uc_price' => t('Ubercart price'),
        'numeric' => t('Numeric'),
      ),
      '#default_value' => $options['format'],
      '#weight' => 1,
    );

    $form['revision'] = array(
      '#title' => t('Revision'),
      '#type' => 'select',
      '#options' => array(
        'original' => t('Original'),
        'altered' => t('Altered'),
        'formatted-original' => t('Formatted original'),
        'formatted' => t('Formatted'),
        'themed-original' => t('Themed original'),
        'themed' => t('Themed'),
      ),
      '#default_value' => $options['revision'],
      '#process' => array('views_process_dependency'),
      '#dependency' => array('radio:options[format]' => array('uc_price')),
      '#weight' => 1,
    );

    // Change weight and dependency of the previous field on the parent numeric ones
    $weight = 2;
    foreach (array('set_precision', 'precision', 'decimal', 'separator', 'prefix', 'suffix') as $field) {
      $form[$field]['#process'] = array('views_process_dependency');

      if (is_array($form[$field]['#dependency'])) {
        $form[$field]['#dependency'] += array('radio:options[format]' => array('numeric'));
        $form[$field]['#dependency_count'] = count($form[$field]['#dependency']);
      }
      else {
        $form[$field]['#dependency'] = array('radio:options[format]' => array('numeric'));
      }

      $form[$field]['#weight'] = ++$weight;
    }
  }

  function render($values) {
    if ($this->options['format'] == 'numeric') {
      return parent::render($values);
    }

    if ($this->options['format'] == 'uc_price') {
      $product = node_load($values->{$this->aliases['nid']});
      $context = array(
        'revision' => $this->options['revision'],
        'type' => 'product',
        'class' => array(
          'product',
          $this->field,
        ),
        'field' => $this->real_field,
        'subject' => array(
          'node' => $product,
        ),
      );
      $options = array('label' => FALSE);

      return uc_price($product->{$this->real_field}, $context, $options);
    }
  }
}
