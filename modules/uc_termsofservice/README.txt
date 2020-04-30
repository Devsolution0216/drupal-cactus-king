-- Ubercart Terms of Service --
This module allows the administrator of a Ubercart Shop to add a check of 
Terms of Service (ToS) in the Checkout pane or in the Cart pane.

-- Installation --
Just enable the module, cart module and checkout module of ubercart are 
required.
The configuration of this module is merged into the Ubercart pane settings.
You can configure the options for checkout in panes' checkout configuration
page (admin/store/settings/checkout/edit/panes) and for cart in panes' cart
configuration page (admin/store/settings/cart/edit/panes).

Options available for configuration:
- Whether the ToS is displayed or not in cart and/or checkout pages.
- The weight of the pane.
- The node you want for ToS page.
- In case of checkout, if the ToS is required or not. 
- Cart pane can't be required.
- If ModalFrame API is present, you can also select if the ToS is displayed in
a popup window and its size.
- You can configure conditional actions so the checkout pane is only displayed
when there is one product from a given class.

Multilanguage is supported through the Translation module. You can translate the
ToS node and the correct translation will be displayed depending of the language.

-- ToS in js popup --
You can enable the ModalFrame API (http://drupal.org/project/modalframe) module
in order to have the Terms of Service opened in a js popup window, you can 
accept the ToS from this window.
You can disable the popup option in the settings of the module.

-- Theming & ToS text --
You can theme both form and ToS text from two tpl files included with this 
module and a css file, just copy those tpl files in your theme and modify the 
text, structure or css.
By default, the node body will be displayed.

-- Conditional Actions --
You can configure conditional actions to display the Terms of Service in the
checkout only if a product from a given product class or content type is 
present. The admin url for this is 
admin/store/ca/uc_termsofservice_display_pane/edit/conditions
You can also add extra conditions and actions.

-- Know Issues --
The ToS can be placed as a cart pane, but then it won't be required. 

If you need a previous agreement checkbox, i.e. in the registration of the 
users, please take a look to the Legal (http://drupal.org/project/legal) or 
Terms of Service (http://drupal.org/project/terms_of_use) module.

Module supported by Neurotic (http://www.neurotic.es)
