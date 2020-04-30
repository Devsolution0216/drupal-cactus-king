Drupal nodewords.module (aka Meta tags) README.txt
==============================================================================

This module allows you to set some meta tags for each node.

Giving more attention to the important keywords and/or description on some of
your nodes allows you to get better search engine positioning (given that you
really only provide the keywords which exist in the node body itself, and do
not try to lie).

This version of the module only works with Drupal 6.x.

Features
------------------------------------------------------------------------------

Some features include:

* The current supported meta tags are ABSTRACT, COPYRIGHT, DESCRIPTION,
  GEOURL, KEYWORDS and ROBOTS.

* You can define a global set of KEYWORDS that will appear on each page of
  your site. Node specific keywords are added before these global
  keywords.

* You can tell "nodewords" to add all terms of some specified vocabularies
  to the KEYWORDS meta tag.

* You can define a global COPYRIGHT tag. You can optionally override this
  copyright on one or more node pages.

* You can define a global GEOURL tag. You can optionally override this
  GeoURL on one or more node pages.

* You can optionally insert the teaser as a DESCRIPTION tag, if you leave
  the DESCRIPTION tag empty.

* You can specify a default ROBOTS tag to use for all pages. You can override
  this on each page.

* On taxonomy pages, the term description is used as the DESCRIPTION
  tag. The term itself is added to the list of KEYWORDS. You can override
  the description to use if you wish.

* You can seperately specify the meta tags to show on the front page of
  your site. See also configuration below.

* The module added support for META tags for views pages (see views
  module) in version 5.x-1.3. For this feature you need views-5.x-1.6 or
  later. Similar support for panels pages (see panels module) has been
  added to version 5.x-1.4. For this feature you need panels-5.x-1.2 or
  later.

* You can select which of these tags you want to output on each page. You
  can also remove the edit box for these tags from the node edit page if
  you don't like using it.

* All text of the DESCRIPTION and KEYWORDS meta tags are added to the search
  system so they are searable too.

Installing nodewords (aka Meta tags) (first time installation)
------------------------------------------------------------------------------

1. Backup your database.

2. Copy the complete 'nodewords/' directory into the 'modules/' directory of
   your Drupal site.

3. Enable the "Meta tags" module from the module administration page
   (Administer >> Site configuration >> Modules).

   The needed tables will be automatically created. If this fails, you will
   need to create the tables manually. For example, the table definition for
   MySQL is:

     CREATE TABLE nodewords (
       type varchar(16) not null,
       id varchar(255) not null,
       name varchar(32) not null,
       content varchar(255) null,
       PRIMARY KEY (type, id, name)
     ) /*!40100 DEFAULT CHARACTER SET utf8 */;

   Do not forget to adjust the table name (nodewords) to work with your table
   prefix if you use table prefixing.

4. Configure the module (see "Configuration" below).

Upgrading nodewords (aka Meta tags) (on Drupal 4.7 or later)
------------------------------------------------------------------------------

1. Backup your database.

2. Remove the old 'nodewords.module' or old 'nodewords/' directory from the
   'modules/' directory of your Drupal site (possible after making a backup
   of it).

3. Copy the complete 'nodewords/' directory into the 'modules/' directory of
   your Drupal site.

4. Go to the modules administration page ("Administer >> Site configuration
   >> Modules") and select to run update.php to update the database.

   The data from the previous version will automatically be converted to
   the new format if needed.

5. Configure the module (see "Configuration" below) if needed.

Configuration
------------------------------------------------------------------------------

1. On the access control administration page ("Administer >> User management
   >> Access control") you need to assign:

   + the "administer meta tags" permission to the roles that are allowed to
     administer the meta tags (such as setting the default values and/or
     enabling the possibility to edit them),

   + the "edit meta tags" permission to the roles that are allowed to set and
     edit meta tags for the content.

   All users will be able to see the assigned meta tags.

2. On the meta tags settings page ("Administer >> Content management >> Meta
   tags") you can specify the global settings for the module. This includes:
    - setting a global copyright,
    - setting global keywords and/or specify auto-keywords vocabularies,
    - specifying the tags to show on the edit form and/or the html head.

   Users need the "administer meta tags" permission to do this.

3. The front page is an important page for each website. Therefor you can
   specifically set the meta tags to use on the front page meta tags
   settings page ("Administer >> Content management >> Meta tags >>
   Front page").

   Users need the "administer meta tags" permission to do this.

   Alternatively, you can opt not to set the meta tags for the front page
   on this page, but to use the meta tags of the view, panel or node the
   front page points to. To do this, you need to uncheck the "Use front
   page meta tags" option on the meta tags settings page.

   Note that, in contrast to previous versions of this module, the site
   mission and/or site slogan are no longer used as DESCRIPTION or ABSTRACT
   on the front page!

4. You can completely disable the possibility to edit meta tags for each
   individual content type by editing the content type workflow options
   ("Administer >> Content management >> Content types").

   Note that this will still output the globally set meta tags.

Displaying nodewords META tags in your theme
------------------------------------------------------------------------------

The nodewords module depends on your theme to output the meta tags in the
right place. By default, themes will output $head (phptemplate) or {head}
(xtemplate) in the <head> section - that's all that is needed.

More precisely, you'll want something like the following in the beginning of
your theming file:

* for phptemplate themes (in page.tpl.php):

  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
            "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
  <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
      <title><?php print $head_title; ?></title>
      <?php print $head; ?> <!-- <<-- this must be present! -->
    </head>
    <body <?php print $onload_attributes; ?>>
      <!-- etc etc etc -->
    </body>
  </html>

* for xtemplate themes (in xtemplate.tmpl):

  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
            "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
  <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
      <title>{head_title}</title>
      {head} <!-- <<-- this must be present! -->
    </head>
    <body {onload_attributes}>
      <!-- etc etc etc -->
    </body>
  </html>

* for PHP only themes (not using a theming engine like the ones above), you
  need to include the output of 'drupal_get_html_head()' in the <head>
  section of each page. See for example the chameleon theme in Drupal core
  which includes the call in 'function chameleon_page($content)'.

On the other hand, if you want to display the meta tags for a node or a page
in your theme on a different place than in the <head> section of your HTML
(the <meta ...> tags), then you'll need to load the tags manually.
The core function to do this is:

  $tags = nodewords_get();

This will return the tags defined for this page. If you want to be more
specific about the tags to load, you can use:

  $tags = nodewords_get('node', $node->nid);

for example in your node.tpl.php.

As an example, see node.tpl.php-example in this directory.

Using nodewords and tagadelic
------------------------------------------------------------------------------

The tagadelic module (http://drupal.org/project/tagadelic) allows one to
create a tagcloud of all terms used. The keywords you assign to nodes with
the nodewords module will not appear in these clouds as we don't use
taxonomy to assign the meta KEYWORDS to a node (because we want to keep
the order of the keywords entered).

If you want to use tagclouds and have the same terms in the KEYWORDS meta
tag, you can configure nodewords as follows:

1. Create a "Free tagging" vocabulary at "Administer >> Content management
   >> Categories". For example, call this vocabulary "Keywords".

2. On the meta tags settings page ("Administer >> Content management >>
   Meta tags"), select the "Keywords" vocabulary as one of the "Auto-keywords
   vocabularies". This will make sure that all terms you assign to nodes
   will appear in the KEYWORDS meta tag.

3. On the same page, deselect the checkbox "Keywords" in the "Tags to
   show on edit form" fieldset. This will remove the KEYWORDS meta tag
   input box on all node edit forms. The only way to assign KEYWORDS then
   is to enter them in the vocabulary "Keywords" input box (which will
   appear in the "Categories" box instead of the "Meta tags" one).

The result is that the KEYWORDS meta tag will only contain the keywords
assigned to nodes by entering them in the free-tagging input box of the
"Keywords" vocabulary. Nodewords will add them to the KEYWORDS meta tag
and you can use a tagcloud to show all keywords too.

Auto-generated meta DESCRIPTION for CCK content types
------------------------------------------------------------------------------

The nodewords module uses the teaser of a node as the auto-generated
DESCRIPTION for nodes if instructed to do so on the meta tags settings
page (Administer >> Content management >> Meta tags). Unfortunately, for
CCK (Content Construction Kit) content types, this teaser is not really
useful for use as meta DESCRIPTION.

It is recommended to use the contemplate (Content Template) module to
create a nicer looking node teaser that can also be used as auto-generated
DESCRIPTION.

Note that nodewords module does not use the node.tpl.php file (or any
node-*.tpl.php file) from your theme as teaser because in general this
includes the "Submitted by ..." text which should not be included in
the meta tag.

Bugs and shortcomings
------------------------------------------------------------------------------

* See the list of issues at http://drupal.org/project/issues/nodewords.

Credits / Contact
------------------------------------------------------------------------------

The original author of this module is Andras Barthazi. Mike Carter
(mike[at]buddasworld.co.uk) and Gabor Hojtsy (gobap[at]hp.net)
provided some feature enhancements.
Robrecht Jacques (robrecht.jacques[at]advalvas.be) is the current
active maintainer.

Best way to contact the authors is to submit a (support/feature/bug) issue at
the projects issue page at http://drupal.org/project/issues/nodewords.

$Id: README.txt,v 1.27.2.2 2008/01/22 09:31:37 robrechtj Exp $
