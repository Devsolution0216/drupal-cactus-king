$Id: README.txt,v 1.6.2.2 2009/12/24 20:35:08 davereid Exp $

Description
-----------

Poormanscron is a module which runs the Drupal cron operations without
needing the cron application.

The module inserts a small amount of JavaScript on each page of your site that
when a certain amount of time has passed since the last cron run, calls an AJAX
request to run the cron tasks. Your users should not notice any kind of delay
or disruption when viewing your site.

This is a Drupal 6 backport of the simple Poormanscron feature that was added
to Drupal 7 (http://drupal.org/node/331611).


Installation
------------

Read http://drupal.org/getting-started/install-contrib on how to download
and install Drupal modules. The typical location for the module's files is
sites/all/modules/poormanscron in the Drupal directory.

Once the module is enabled, you can configure the module at:
  Administer > Site configuration > Site information


Authors
-------

 * Moshe Weitzman <http://drupal.org/user/23> - original author
 * Uwe Hermann <http://drupal.org/user/12054> - current maintainer
 * Rob Loach <http://drupal.org/user/61114> - co-maintainer
 * Dave Reid <http://drupal.org/user/53892> - co-maintainer
