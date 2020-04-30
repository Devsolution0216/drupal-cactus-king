<?php
/**
 * @file
 *  Views Galleriffic theme wrapper.
 *
 * @ingroup views_templates
 */

?>
<div id="galleriffic" class="clear-block">
  <div id="gallery" class="content">
    <div id="controls" class="controls"></div>
    <div id="loading" class="loader"></div>
    <div id="slideshow" class="slideshow"></div>
    <div id="caption" class="embox"></div>
  </div>
  <div id="thumbs" class="navigation">
    <ul class="thumbs noscript">
      <?php foreach ($rows as $row): ?>
        <?php print $row?>
      <?php endforeach; ?>
    </ul>
  </div>
</div>

