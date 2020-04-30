<?php
/**
 * @file
 * template for views galleriffic row
 */
?>
<?php if ($fields['slide_field']->content): ?>
  <li>
    <a class="thumb" href="<?php print $fields['slide_field']->content; ?>" title="<?php print $fields['title_field']->stripped; ?>"><img src="<?php print $fields['thumbnail_field']->content; ?>" alt="<?php print $fields['title_field']->stripped; ?>" /></a>
    <div class="caption">
      <div class="image-title"><?php print $fields['title_field']->content; ?></div>
      <div class="image-desc"><?php print $fields['description_field']->content; ?></div>
    </div>
  </li>
<?php endif; ?>

