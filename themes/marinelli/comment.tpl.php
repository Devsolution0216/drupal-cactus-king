
<div class="comment <?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status; print ' '. $zebra; ?>">

 
    <?php if ($picture) {
    print $picture;
  } ?>

  
    <div class="commentTitle"><?php print $title; ?></div>
    <div class="submitted"><?php print $submitted; ?></div>
    <div class="content"><?php print $content; ?></div>
    <div class="firma">
    <?php print $signature ?>
    </div>
    <div class="links"><?php print $links; ?></div>
  </div>
