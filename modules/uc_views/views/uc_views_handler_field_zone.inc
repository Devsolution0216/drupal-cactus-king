<?php
// $Id: uc_views_handler_field_zone.inc,v 1.1 2009/03/24 09:43:50 madsph Exp $

/**
 * @file
 * Views handler: Return zone name for zone id
 */

/**
 * Return a zone name for zone id
 */
class uc_views_handler_field_zone extends views_handler_field {
  function render($values) {
    return uc_zone_get_by_id($values->{$this->field_alias});
  }
}
