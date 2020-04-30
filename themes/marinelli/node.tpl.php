
 
    <?php if ($teaser): ?><?php print '<div style="border-top:1px solid #8989b2;border-bottom:1px solid #8989b2;padding:5px">';endif; ?>
 
  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
 	       <?php if ($picture) {
      print $picture;
    }?>
    

    <?php if ($page == 0) { ?><h2 class="nodeTitle"><a href="<?php print $node_url?>"><?php print $title?></a>
	<?php global $base_url;
	if ($sticky) { print '<img src="'.base_path(). drupal_get_path('theme','marinelli').'/img/sticky.gif" alt="'.t('sticky icon').'" class="sticky" />'; } ?>
	</h2><?php }; ?>
    
	
    
    <div class="content">
	
	
	<?php print $content?></div>
    
    
    <?php if (!$teaser): ?>
    <?php if ($links) { ?><div class="links"><?php print $links?></div><?php }; ?>
    <?php endif; ?>
    
 
    
    
    <?php if (!$teaser): ?>
    <?php if ($terms) { ?><div class="taxonomy"><span><?php print t('Tags') ?></span> <?php print $terms?></div><?php } ?>
    <?php endif; ?>

    
  </div>
<?php if ($teaser): ?><?php print '</div>';endif; ?>