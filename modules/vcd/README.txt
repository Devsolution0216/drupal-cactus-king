VIEWS CONTEXTUAL DISPLAYS

Summary:

This module allows Views to set build modes for objects depending on a context. When should
you use this module?

* If you need to create a view which depending of the user (permission, role,...) shows 
certain 'limited access' fields of a row object or not. This does away with the restrictive,
clunky CCK field permission system.
* If you need to show a view on diverse sections of your site and you don't want to create 
a gazillion display variants. This promotes reuse of views displays.

Requirements:

- Chaos Tools
- Context module
- Display Suite
- Views

How to use it:

1. Install/Enable the module
2. Go to admin > build > context and create a new context
3. Add conditions to your new context
4. Add the VCD Reaction plugin as a single reaction to your context.
5. Go to admin > build > views
6. Create a new view or edit an existing view
7. Choose 'VCD Object' as the active Row Style plugin and edit its' options
8. Expand the Contextual build modes tab
9. You'll see all the contexts which have the VCD Reaction plugin set
10. Now choose build modes for those contexts

When a context' conditions are met, this will trigger the reaction plugin to set the build 
mode with which the context was associated with as 'active' for that view. The objects in 
the rows will now be displayed with through that particular build mode. Layouts associated 
with build mode are managed through Display Suite leaving you free on how to configure
these.

Gotcha's

If multiple contexts are tripped for a view, then the last active contexts' build mode will
be used for that view, overriding all other active contexts.

It's intended as an extension on the DS Object row style plugin. The original DS options are 
not fully functional yet though.

Support

This module is originally conceived for Drupal 6 but will be ported to Drupal 7 too.

Maintainers

netsensei - http://drupal.org/user/350460

Thanks to

swentel - http://drupal.org/user/107403
stalski - http://drupal.org/user/322618
mzenner - http://drupal.org/user/35077