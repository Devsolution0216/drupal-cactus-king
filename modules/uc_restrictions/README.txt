// $Id: README.txt,v 1.3 2009/01/27 23:43:42 islco Exp $

DESCRIPTION
-----------

This module will do its best to prevent the wrong sort of people from ordering the wrong sort of goods, or to ship them to the wrong kinds of places.
For example, some products cannot be ordered by minors, or some products cannot be shipped to certain states.
The module was originally developed for a site that sells wine.

The functionality may vary depending on the sub-modules enabled.  The gist of this module is that
it will throw a thickbox overlay in front of the paths/patterns you designate.  The thickbox displays a form that asks the user qualifying questions.
If the user's answers do not qualify him or her, the user is redirected to an informational page.
When the user reviews his or her order for checkout, validation functions or required acknowlegments are 
added to the order review action.

REQUIREMENTS
------------

* Drupal 6
* Ubercart (Store, Cart, Order, Product)
* Thickbox



INSTALLATION
------------

1. CREATE DIRECTORY

Create a new directory "uc_restrictions" in the sites/all/modules directory and
place the entire contents of this uc_restrictions folder in it.

You need to download the cookies plugin for jquery at:
http://jquery.com/dev/svn/trunk/plugins/cookie/
Place it in the jquery subdirectory of the module.

2. ENABLE THE MODULE

Enable the module on the Modules admin page:
Administer > Site building > Modules
Note that there is one main module that is the main API.
Enable the sub-modules as you need them.

3. CREATE RESTRICTION INFORMATION PAGES

These are the pages that will educate users that they may or may not be able to buy certain goods on your site.
You create them as normal drupal pages, and you will enter their path into the module settings so that the
module may redirect people to those pages when appropriate.
If you are using the uc_restrictions_delivery_zone sub-module, you may use the uc_restrictions_zones_chart_render()
function to place a map on your page that automatically highlights the  deliverable zones.

4. CONFIGURE THE MODULE

Configure from the Ubercart "Configuration" sub-menu:
Administer > Store administration › Configuration.

5. THEMING
The uc_restrictions_theme takes two variables, height and width, so developers who extend this module
may change the dimensions of the thickbox interceptor.

CREDITS
-------

Written by Robert Hinrichs at ISL Consulting, San Francisco.