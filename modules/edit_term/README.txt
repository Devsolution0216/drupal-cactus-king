Overview:
--------
This is a very simple module to make it easier to edit (or simply see the tid) 
of terms from the 'view term' page.

By default this option is available to everyone with "administer taxonomy"
permissions.  

Installation and configuration:
------------------------------
Please refer to the INSTALL file for complete installation and 
configuration instructions.

When enabled, A new tab labelled 'Edit Term' will be seen on taxonomy/term/n 
pages which will link directly to an equivalent of the the 
admin/content/taxonomy/edit/term/n interface.

If path.module is enabled, an edit field for an alias[URL path settings] is
added to the normal term edit form.

Requires:
--------
 - enabled taxonomy.module
 - optional : support for path.module
 - optional : support for image_gallery.module

Credits:
-------
 - Written and maintained by Benjamin Melan�on of Agaric Design Collective
   http://agaricdesign.com/
 - Term Editor additions by Dan Morrison (dman) 
   http://coders.co.nz/