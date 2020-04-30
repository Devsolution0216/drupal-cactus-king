$Id: README.txt,v 1.1.2.1 2010/10/09 10:36:24 asak Exp $

Description
===========
Ubercart Product Actions provides a set of Drupal Action for usage by Ubercart
shop administrators for conducting site-wide changes to product data, using
custom codes or the excellent Views Bulk Operations (VBO) module.

It does so by provding a few new actions:

- Modify product Weight
- Modify product Sell Price
- Modify product List Price
- Modify product Cost Price

These actions can be used to manipulate the prices of multiple products, using
two methods:

1. Absolute - alter the price using an absolute value. 
   (for example: decrease the price of all products by $5.)
2. Percentage - alter the price using a percentage.
   (for example: increase the cost of selected products by 10%.)
	 
Usage
=====
The module does nothing on it's own. Here's how to quickly get it up and running:
 1) Download and install the Views and VBO modules:
    http://drupal.org/project/views
	http://drupal.org/project/vbo
 2) Create a new view, using a "Page" display and "VBO" as the display style.
 3) Filter the view to display products only, and expose some filters so that
    you can filter the list of products as you wish.
 4) In the VBO settings of that view, check the boxes next to the new "Modify
    product Sell Price" and "Modify product Weight" actions.
 5) Save the view, and visit the page.
 6) Filter the list (or simply select some products) and select the desired
    action from the Bulk Operations select box, and click Execute.
 7) On this screen enter your desired change, and click "Next".
 8) Make sure you got the right products, and click "Confirm".
 
 You're done! ;)

 
If you've got any problems/questions/ideas - please visit the Issue Queue and let us know:
http://drupal.org/project/issues/search/uc_product_actions
 
Author
======
Asaph (asak) - asaph at cpo.co.il