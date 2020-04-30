<?php
if ( ($block->region == 'right' || $block->region == 'left')
      && ($nokia_mobile_device_class == NOKIAMOBILE_THEME_HIGHEND_GROUP
          || $nokia_mobile_device_class == NOKIAMOBILE_THEME_HIGHEND_TOUCH_GROUP) ) {
?>
<dl id="<?php echo "accordion-{$block->module}-{$block->delta}"; ?>" class="list-accordion">
  <dt><span></span><?php print $block->subject ?></dt>
  <dd>
  <div id="content"><?php print $block->content ?></div>
  </dd>
</dl>
<?php
} else {
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="clear-block block block-<?php print $block->module ?> expanded">

<?php if (!empty($block->subject)): ?>
  <h2><?php print $block->subject ?></h2>
<?php endif;?>

  <div class="content"><?php print $block->content; ?></div>
</div>
<?php
}
?>
