<?php

/**
 * @file
 * Views handler: Filter on comparison of stock level to threshold.
 */

class uc_stock_views_handler_filter_below_threshold extends views_handler_filter_boolean_operator {
  function query() {
    $this->ensure_my_table();
    $this->query->add_field($this->table_alias, 'stock');
    $this->query->add_field($this->table_alias, 'threshold');

    $this->query->add_where($this->options['group'], "$this->table_alias.stock " . (empty($this->value) ? '>=' : '<') . " $this->table_alias.threshold");
  }
}
