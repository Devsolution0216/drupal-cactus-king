<?php
// $Id: uc_views_handler_field_order_id.inc,v 1.1 2009/04/07 11:04:35 madsph Exp $
/**
 * @file
 * Contains the basic 'order' field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to the order adminstration page.
 */
class uc_views_handler_field_order_id extends views_handler_field {
  /**
   * Override init function to provide generic option to link to user.
   */
  function init(&$view, &$data) {
    parent::init($view, $data);
    if (!empty($this->options['link_to_order'])) {
      $this->additional_fields['order_id'] = 'order_id';
    }
  }
  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_order'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide link to order adminstration page
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_order'] = array(
      '#title' => t('Link this field to order administration'),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_order']),
    );
  }

  /**
   * Render whatever the data is as a link to the order.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_order']) &&
        user_access('view all orders') &&
        $values->{$this->aliases['order_id']} &&
        $data !== NULL &&
        $data !== '') {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "admin/store/orders/" . $values->{$this->aliases['order_id']};
    }
    return $data;
  }

  function render($values) {
    return $this->render_link(check_plain($values->{$this->field_alias}), $values);
  }
}
