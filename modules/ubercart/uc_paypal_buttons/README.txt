/**
 * uc_paypal_buttons
 * Adds PayPal Buy Now or Subscription buttons to Ubercart products.
 *
 * By Joe Turgeon [http://arithmetric.com]
 * Licensed under GPL version 2
 * Version 2009/06/16 (6.x-1.0)
 */

This module allows PayPal Buy Now or Subscription buttons to be included
with or to replace the 'Add to Cart' button on products. These PayPal
buttons redirect the customer immediately to PayPal for payment, bypassing
the standard Ubercart checkout process. Order information (including the
customer's address) are obtained from PayPal after the purchase is complete.


FEATURES:

-- Provides customers a single click method to choose a product and proceed
to checkout through PayPal. At the same time, the purchase is still tracked
and handled by Ubercart.

-- Allows using PayPal subscriptions (recurring payments) with Ubercart.
PayPal handles sending the recurring payments, and this module records the
payments to an Ubercart order and provides status updates.

-- Rules integration: This module triggers Rules events when a Buy Now item
is purchased, and when a Subscription item is registered, renewed, or expires.


CONFIGURATION:

This module requires that the core Ubercart modules and the Ubercart PayPal
module are installed and enabled. Also, you must configure the Ubercart PayPal
module with your store's PayPal account e-mail address.

To enable the PayPal Buy Now or Subscription button for a product,
edit the product node, navigate to the Features tab, and add and configure
the 'PayPal Buy Now' or 'PayPal Subscription' product feature. The product
feature includes settings for the button style, as well as for the product
or subscription parameters.


EMBEDDING PAYPAL BUTTONS:

You have a variety of options for embedding PayPal buttons on your site
(in addition to on the 'Add to Cart' form), and you can also create custom
links or buttons that act like clicking on a PayPal button.

These are two methods for invoking the Buy Now or Subscription payment process:

1. Make a link using the URL:

[Drupal base path]/uc_paypal_buttons/[product node id]/[quantity]/[attribute id]/[option id]

The product node id is required. The quantity is optional and defaults to 1.

For example, to purchase node 12, use this URL:

http://example.com/uc_paypal_buttons/12

To purchase three of node 15 with some given attributes, use:

http://example.com/uc_paypal_buttons/12/3/1/3

Multiple attribute-option pairs can be used, for example:

http://example.com/uc_paypal_buttons/12/3/1/3/2/3

2. Embed the Add to Cart form with PHP.

You can add the Ubercart Add to Cart form to any page by using the
drupal_get_form function:

drupal_get_form('uc_product_add_to_cart_form', $node);

For example, to print the HTML for this form for node 12, use:

print drupal_get_form('uc_product_add_to_cart_form', node_load(12));
