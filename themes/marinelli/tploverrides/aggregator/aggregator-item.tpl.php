<?php
// $Id: aggregator-item.tpl.php,v 1.1 2008/03/11 19:25:59 lioz Exp $

//Marinelli template for feed aggregator
?>


<div class="feedcontainer">
<div class="feedimage">


</div>

<div class="feedcontent">

  <h2>
    <a href="<?php print $feed_url; ?>"><?php print $feed_title; ?></a>
  </h2>

  <?php if ($source_url) : ?>
    <p class="feedinfo"><span class="sorgente"><a href="<?php print $source_url; ?>" class="feed-item-source"><?php print $source_title; ?></a></span> -
  <?php endif; ?>
<?php print $source_date; ?></p>


<?php if ($content) : ?>
    <p><?php print $content; ?></p>
<?php endif; ?>


<?php if ($categories) : ?>
   <p> <?php print t('Categories'); ?>: <?php print implode(', ', $categories); ?></p>
<?php endif ;?>

</div>

</div>