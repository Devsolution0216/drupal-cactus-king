// $Id$

var method_update;

$(document).ready(
  function () {
    $("input:radio[@name='panes[payment][payment_method]']").click(
      function () {
        update_method_line_item(this.value);
      }
    );
  }
);

/**
 * Update the payment method line item to reflect any payment specific subtotal adjustments
 */
function update_method_line_item(path) {
  var order = serializeOrder();

  if (!!order) {
    // Get the timestamp for the current update.
    var this_update = new Date();

    // Set the global timestamp for the update.
    method_update = this_update.getTime();

    // Make the post to get the details for the chosen payment method.
    $.post(Drupal.settings.basePath + 'cart/checkout/method_items/' + path, { order: order },
      function(adjustment) {
        if (this_update.getTime() == method_update) {
          var return_values = adjustment.split('|');
          if(return_values[0] && (return_values[0] >= .01 || return_values[0] <= -.01)) {
            set_line_item('payment_method', return_values[1], return_values[0], 1);
          }
          else {
            remove_line_item('payment_method');
            render_line_items();
          }
        }
      }
    );
  }
}
