
     
      Ubercart Option Images
      Provided by www.vision-media.ca
      Developed by Tj Holowaychuk <tj@vision-media.ca>      
     
      ------------------------------------------------------------------------------- 
      INSTALLATION
      ------------------------------------------------------------------------------- 
      
      Install the imagecache module located at http://drupal.org/project/imagecache 
      then enable this module (supports both 1.6 and 2.x). Settings become available 
      on the attribute settings page which is located at admin/store/settings/attributes
      
      To display an image when no option image is available, the module will call theme_uc_option_image_no_image()
      This defaults to grabbing and image called 'noimage.png' in your themes 'images' folder. By
      default this theme with implement the imagecache preset size chosen in order to
      adjust the noimage image similar to that of the option images.      
      
      Example: sites/all/themes/mytheme/images/noimage.png
      
      ------------------------------------------------------------------------------- 
      MARKUP REQUIREMENTS
      ------------------------------------------------------------------------------- 
       
      Due to the nature of JavaScript dependency upon markup, this module supports
      default node.tpl.php and form item markup in order to switch images properly.
       
      -------------------------------------------------------------------------------
      PERMISSIONS
      ------------------------------------------------------------------------------- 
      
      view option images
      administer option images
              
      -------------------------------------------------------------------------------
      KNOWN ISSUES
      ------------------------------------------------------------------------------- 
      
      When multiple nodes are displayed on the same page they will not switch 
      properly due to "call_user_func_array('array_merge_recursive', $data)" in
      drupal_add_js();
      
      This issue is being investegated, but for now this feature has been disabled.                              
          


