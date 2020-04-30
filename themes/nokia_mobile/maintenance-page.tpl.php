<?php print $doctype."\n"; ?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" dir="<?php print $language->dir ?>">
<head>
	<?php print $head; ?>
	<title><?php print $head_title; ?></title>
	<?php print $styles; ?>
	<?php print $scripts; ?>
</head>
<body class="<?php print $bodyclasses; ?>">
	<div id="container">
		<div id="header-region"><?php print $header; ?></div>
		<div id="header" class="mobileregion">
			<?php
			if ($logo) {
				//TODO print '<img src="'. check_url($logo) .'" id="logo" />';
			}
			if ($site_name) {
				print '<h1><a href="' . check_url($front_page) . '" title="' . $site_slogan . '">' . $site_name . '</a></h1>';
			}
			?>
		</div>
		<div id="primary_links">
			&nbsp;
		</div>
		<div id="maincontent" class="mobileregion">
			<?php if($title) : ?>
			<div id="main">
				<h2><?php print $title; ?></h2>
			</div>
			<?php endif; ?>
			<?php print $help; ?>
			<?php print $messages; ?>
			<div id="content">
				<?php print $content; ?>
			</div>
		</div>
		<?php if ($left): ?>
		<div id="sidebar-left" class="mobileregion">
			<?php if ($search_box): ?><div class="block block-theme"><?php print $search_box; ?></div><?php endif; ?>
			<?php print $left ?>
		</div>
		<?php endif; ?>
		<?php if ($right): ?>
		<div id="sidebar-right" class="mobileregion">
			<?php if (!$left && $search_box): ?><div class="block block-theme"><?php print $search_box ?></div><?php endif; ?>
			<?php print $right; ?>
		</div>
		<?php endif; ?>
		<div id="footer" class="mobileregion">
			<?php print $footer_message . $footer; ?>
		</div>
		<?php endif; ?>
	</div>
</body>
</html>
