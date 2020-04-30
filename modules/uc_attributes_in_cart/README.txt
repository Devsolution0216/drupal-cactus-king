$Id:

INSTALLATION

1 - Extract the module in the /modules directory of your choice (e.g. /sites/all/modules).
2 - Install the module (admin/build/modules).
3 - The module is installed and working.



USAGE

1 - If you have not defined any attribute, go to admin/store/attributes/add and add one.
2 - Add an attribute to a product by going to node/%/edit/attributes/add (replace % with a number).
3 - Add the permission to administer the behavior of the module to the roles you want (admin/user/permissions).
4 - Administer the behavior of the module at admin/store/settings/attributes/in-cart.



WHAT YOU CAN DO WITH THIS MODULE

1 - You can show attributes of Ubercart products on the cart view page (and change them there).
2 - You can decide wich attributes to show.
2 - You can decide whether or not to display the title of each attribute.
3 - You can decide to enclose attributes in fieldsets, in case you have a long list of options.
4 - You can decide to filter out attributes that are no longer in stock (requires the uc_stock module to be enabled).
    This functionality is taken from the uc_attribute_stock_filter module (see http://drupal.org/project/uc_attribute_stock_filter)
