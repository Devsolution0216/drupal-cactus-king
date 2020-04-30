<?php

/**
 * @file
 * Views handler: "Add to cart" form as a field.
 */

/**
 * Display the "Add to cart" form like the product page.
 */
class uc_product_handler_field_addtocart extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function element_type() {
    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }
    return 'div';
  }

  function render($values) {
    if (uc_product_is_product($values->{$this->aliases['type']})) {
      $type = node_get_types('type', $values->{$this->aliases['type']});
      $module = $type->module;
      $product = node_load($values->{$this->aliases['nid']});
      if (function_exists('theme_'. $module .'_add_to_cart')) {
        return theme($module .'_add_to_cart', $product);
      }
      elseif (function_exists('theme_uc_product_add_to_cart')) {
        return theme('uc_product_add_to_cart', $product);
      }
    }
  }
}
