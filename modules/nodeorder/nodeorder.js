// $Id: nodeorder.js,v 1.2.2.2 2009/01/08 19:19:27 pvanderspek Exp $

/**
 * Order nodes associated with a term.
 *
 * This behavior is dependent on the tableDrag behavior, since it uses the
 * objects initialized in that behavior to update the row.
 */
Drupal.behaviors.blockDrag = function(context) {
  var table = $('table#ordernodes');
  var tableDrag = Drupal.tableDrag.ordernodes; // Get the blocks tableDrag object.

  // Add a handler for when a row is swapped, enable the submit button.
  tableDrag.onDrop = function() {
    var submit = document.getElementById('edit-submit');
    submit.disabled = false;
  };
}