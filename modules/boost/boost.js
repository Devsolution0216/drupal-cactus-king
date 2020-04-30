/**
 * Set the immutable flag on each ahah form element setting.
 */
Drupal.behaviors.fix_ahah_immutable_flag = function(context) {
  for (var base in Drupal.settings.ahah) {
    Drupal.settings.ahah[base].immutable = true;
  }
};
