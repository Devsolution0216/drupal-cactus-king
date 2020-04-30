OptimizeDB Module

Author:
Sergey Pavlenko

DESCRIPTION
-----------

One of the  known issues of the  Drupal sites is table cache_form overgrowth
(see issue https://drupal.org/node/1506196). This table stores filled forms in
cache_form table but it  doesn’t get cleared while running cron tasks, so size
of this table can be much more bigger than other tables in database, which can
cause lack of disc space on the hosting server

"OptimizeDB" module clears outdated records in cache_form table during cron task
run in safe mode. You could clean cache_form table from admin area too

"OptimizeDB" module is also able to optimize selected database tables and
display their sizes on demand. Automatic optimizing of tables during cron tasks
is not available because it may cause problems with the database and crash
tables. However, you can configure the notification about need of table
optimization.

If your server  often has problems with the database server, make a backup of
the database before optimization run. The danger of losing data using module for
 optimization is the same as while using PHPMyAdmin.

"OptimizeDB" module  provides such features:
1. Ability to clean cache_from an administrative page or do it by cron.
2. Ability to optimize all database’s tables and display its sizes.
3. Configuration of notification about necessity to perform maintenance tasks.
4. Perform, check and repair operation with tables.
5. Prevent crashing tables when performing all maintained actions.

If your server have often  problems with the database server, make a backup of
the database before optimization run. The danger of losing data using module for
 optimization the same as while using PHPMyAdmin.

Module OptimizeDB provide such features:
1. Ability to clean cache_from in administrative page or do it by cron.
2. Ability to optimize all database’s tables and display its sizes.
3. Configuration of notification about necessity to perform maintenance tasks.
4. Perform check and repair operation with tables.
5. Prevent crashing tables when perform all maintained actions.

Additional features:
1. Work with MySQL and PgSQL
2. Execute operations with Drush

Similar projects:

DB Maintenance - differences https://drupal.org/node/2013040
