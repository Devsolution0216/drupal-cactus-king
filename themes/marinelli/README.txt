Look drupal theme documentation here before using the theme

  http://drupal.org/theme-guide


Installation:

  1. Download Marinelli from http://drupal.org/project/marinelli

  2. Unpack the downloaded file, take the entire marinelli folder and place it in your
     Drupal installation under the following locations:
     sites/all/themes
        
  3. Log in as an administrator on your Drupal site and go to Administer > Site
     building > Themes (admin/build/themes) and make marinelli the default theme.

Theme preferences

To customize the theme go to admin/build/themes/settings/marinelli and check the features you need

Subthemes

To use a subtheme simpy select it in admin/build/themes (be sure to keep marinelli theme active)

Dop-Down Menu

To use the drop down menu for primary links you have to:

  1. Create a menu tree for primary links (admin/build/menu-customize/primary-links)

  2. Set all menu items to "expanded"
        
  3. Activate it in the subtheme you are using: for example if you are using marinelli go to /admin/build/themes/settings/marinelli
     and select drop down for the select box at the bottom of the page

Marinelli drop down menu uses the jQuery HoverIntent plugin by Brian Cherne

(http://cherne.net/brian/resources/jquery.hoverIntent.html)

Css image preload

To use this feature just activate it in the theme settings page (recommanded if javascript is enabled)
css image preload plugin developed by Scott Jehl

(http://www.filamentgroup.com/lab/update_automatically_preload_images_from_css_with_jquery/)


