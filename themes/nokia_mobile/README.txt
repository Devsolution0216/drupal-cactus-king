// $Id: README.txt,v 1.4 2010/01/28 16:18:08 atrasatti Exp $

=== INTRODUCTION ===
This a theme designed for a mobile experience. If you think of serving both
regular desktops and mobile devices you should always have at least another
theme available for your users.

This theme is based on the original work of teemule and his Mobile Plugin and
the design is based on the official Nokia templates that can be found here:
http://www.forum.nokia.com/Technology_Topics/Web_Technologies/Browsing/Web_Templates/

This theme and the integration with Mobile Plugin was done by Andrea Trasatti
and kindly sponsored by Forum Nokia.
This theme is meant to work great on ALL mobile devices.

== PRE-REQUISITES ==
The theme might work with Drupal 5 or limited changes might be required, but
it was tested only on Drupal 6.*. It is therefore recommended to use the most
recent Drupal 6 version available.
The use of the Mobile Plugin is recommended, but NOT a requirement. See below
for more details.

== MOBILE PLUGINS ==
There a few good plugins available for Drupal that will help you detect mobile
devices and adapting your content to devices that are less capable. The theme
was designed mainly for the excellent Mobile Plugin by teemule, but was also
tested with other plugins. If you plan to use Mobile Plugin, please read 
README-mobileplugin.txt included in this package or the online handbook at
http://drupal.org/node/684728

The theme was also tested successfully with the following plugins:
- Mobile Theme http://drupal.org/project/mobile_theme
- Mobile Tools http://drupal.org/project/mobile_tools

== INSTALLATION ==
Install the theme like any other theme in Drupal, unzip in sites/all/themes and
then activate it from Administer > Site Building > Themes.
Configure as the default theme if you are serving mobile only, or use one of the
many plugins to switch automatically. See below or http://drupal.org/node/698010
for more details.

== Configuring blocks ==
Since blocks take up a lot of space it is recommended that in the mobile
presentation you limit the number to a minimum. Also, it is probably wise to
place the blocks either at the end of the "content" area or in the "right
sidebar", that will actually appear below the content area.

In order to configure which blocks appear where, use the standard configuration
of Drupal, by going to "Site building > Blocks" and choose "nokia_mobile". The
view on a regular browser will not be great, but it works ;)


== Testing ==
If you wanted to test your new theme from your PC you can do so by installing a
Firefox plugin like "User-Agent Switcher" or the "User Agent" drop-down
available in Safari in the Development menu (has to be enabled manually).
Please note that the Mobile Plugin uses cookies, hence if you want to "switch"
to a different presentation you will have to clear your cookies.

== Further development ==
Nokia is making an effort to help the mobile web to grow and this theme is to
show how the templates they published can be used. If you are designer or just
like to play with HTML and your sites, i t is STRONGLY recommended that you take
a look at the original templates or use this theme as a starting point to
personalise and improve the experience of your users.

== SUPPORT ==
This is Open Source, if you see anything that you think is not right, please let
me know. You can open an issue on the theme homepage or you can try reaching me
on Twitter as @AndreaTrasatti
