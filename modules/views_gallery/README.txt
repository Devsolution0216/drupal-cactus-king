Views Gallery Module
--------------------

This module pulls together the techniques Jeff Eaton outlined in 
http://www.lullabot.com/articles/photo-galleries-views-attach to automatically
create a simple gallery where each gallery is a node with an embedded view of
images that were assigned to that gallery.

The module creates the content types, sets up the imagecache presets, creates
the default gallery view that is embedded into the gallery nodes by Views
Attach, and adds css to make it all look nice.

This technique also works well to create individual image galleries for Organic
Groups, since the gallery and image content types can be configured as group
nodes. Views Gallery OG, included in this package, provides a setup page to
make it easy to automatically create a gallery for every group and adds group
context to the forms wherever possible so the right groups and group galleries
are pre-selected when you create gallery images.

The following modules provide the nuts and bolts for this to work.
It is a long list of modules, but there is little or nothing you need to do
except make sure the latest versions of all these modules are available when
you install Views Gallery and everything will be installed and configured for
you. Plus, most of them are modules you will probably use elsewhere.

* CCK (http://drupal.org/project/cck)
* Views (http://drupal.org/project/views)
* Views Attach (http://drupal.org/project/views_attach)
* Nodereference URL (http://drupal.org/project/nodereference_url)
* Filefield (http://drupal.org/project/filefield)
* Imagefield (http://drupal.org/project/imagefield)
* ImageAPI (http://drupal.org/project/imageapi)
* Imagecache (http://drupal.org/project/imagecache)
* Token (http://drupal.org/project/token)

If the Custom Pagers (http://drupal.org/project/custom_pagers) module is enabled,
back/next links will be added to the image nodes. 

If the Lightbox2 (http://drupal.org/project/lightbox2) module is enabled, a
'View Slideshow' link will be added to the gallery view, which will bring up a
lightshow of the gallery images.

If the Views Slideshow module (http://drupal.org/project/views_slideshow,
version 6.2) is enabled, a Views Slideshow block is added to the default view.

This module has been sponsored by Buzzr (http://buzzr.com/).


Installation
------------

Chekc the module's requirements, download the 'views_gallery' module and enable
it. You should not have to do anything, it will create the content types and
views and an initial gallery node for you and configure everything else that
needs to be done.

The following content types will be created by the module:
* gallery
* gallery_image

The following views will be created by the module:
* gallery
* gallery_list

The following initial gallery node will be created by the module:
* gallery


Configuration
-------------

The module can be configured through Admin -> Setting -> Views Gallery
(./admin/settings/views_gallery). On this page you can choose a Views Gallery
Gallery Type and a Views Gallery Image Type.

Upgrading instructions
----------------------

This module implements the techniques show in Jeff's screencast but has
implemented numerous tweaks and adjustments to fix bugs or add new
features. If you have created content types and views from that
screencast they WILL NOT WORK in this module because of subsequent changes.
Delete them and start over, this module will create the right types
and views.

More documentation
------------------

To understand what you can accomplish with Node-based galleries with CCK and
Views, you can have a look at Jeff Eatons screencast at Lullabot:

http://www.lullabot.com/articles/photo-galleries-views-attach

This screencast has been partially transcribed as an (incomplete) Howto:

http://drupal.org/node/599672

The screencast and the Howto will give you a basic understand what's going
on under the hood if you install the 'views_gallery' module.


Troubleshooting
---------------

If the module behaves unexpectd, please check first the Drupal status report
at Admin -> Reports -> Status (./admin/reports/status).


Author and Copyright
--------------------

Author: Karen Stevenson <http://drupal.org/user/45874>

For further copyright information please see the included LICENSE.txt.
