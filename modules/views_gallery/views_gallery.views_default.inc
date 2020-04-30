<?php

function views_gallery_views_default_views() {
$views = array();  

$view = new view;
$view->name = 'gallery';
$view->description = 'Photos belonging to a selected gallery';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('relationships', array(
  'field_gallery_nid' => array(
    'label' => 'Gallery',
    'required' => 1,
    'delta' => -1,
    'id' => 'field_gallery_nid',
    'table' => 'node_data_field_gallery',
    'field' => 'field_gallery_nid',
    'relationship' => 'none',
  ),
));
$handler->override_option('fields', array(
  'field_gallery_image_fid' => array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => module_exists('lightbox2') ? 'imagefield__lightshow2__thumb__original' : 'thumb_linked',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_gallery_image_fid',
    'table' => 'node_data_field_gallery_image',
    'field' => 'field_gallery_image_fid',
    'relationship' => 'none',
  ),
  'title' => array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'exclude' => 0,
    'id' => 'title',
    'table' => 'node',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'created' => array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'date_format' => 'time ago',
    'custom_date_format' => '2',
    'exclude' => 0,
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'created' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'field_gallery_nid' => array(
    'default_action' => 'not found',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'node',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'id' => 'field_gallery_nid',
    'table' => 'node_data_field_gallery',
    'field' => 'field_gallery_nid',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      views_gallery_gallery_type() => views_gallery_gallery_type(),
    ),
    'validate_argument_node_access' => 1,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(),
    'validate_argument_type' => 'tid',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_php' => '',
  ),
));
$handler->override_option('filters', array(
  'status_extra' => array(
    'operator' => '=',
    'value' => '',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status_extra',
    'table' => 'node',
    'field' => 'status_extra',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('empty', 'No photos have been added to this gallery.');
$handler->override_option('empty_format', '1');
$handler->override_option('use_ajax', TRUE);
$handler->override_option('items_per_page', 6);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'grid');
$handler->override_option('style_options', array(
  'grouping' => '',
  'columns' => '3',
  'alignment' => 'horizontal',
));
$handler = $view->new_display('node_content', 'Full gallery', 'node_content_1');
if (module_exists('lightbox2')) {
  $handler->override_option('header', '<a href="#" onclick="Lightbox.triggerLightbox(\'lightshow\', \'field_gallery_image\');">Start Slideshow</a>');
  $handler->override_option('header_format', '2');
}
$handler->override_option('types', array(
  'gallery' => 'gallery',
));
$handler->override_option('modes', array(
  '0' => 'full',
));
$handler->override_option('argument_mode', 'nid');
$handler->override_option('default_argument', 'nid');
$handler->override_option('show_title', 0);
$handler = $view->new_display('node_content', 'Gallery image', 'node_content_2');
$handler->override_option('fields', array(
  'field_gallery_image_fid' => array(
    'label' => '',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => module_exists('lightbox2') ? 'imagefield__lightbox2__short__original' : 'short_default',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_gallery_image_fid',
    'table' => 'node_data_field_gallery_image',
    'field' => 'field_gallery_image_fid',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('style_plugin', 'default');
$handler->override_option('style_options', array(
  'grouping' => '',
));
$handler->override_option('types', array(
  'gallery' => 'gallery',
));
$handler->override_option('modes', array(
  '0' => 'teaser',
));
$handler->override_option('argument_mode', 'nid');
$handler->override_option('default_argument', 'nid');

$handler->override_option('argument_mode', 'nid');
$handler->override_option('default_argument', 'nid');
$handler = $view->new_display('block', 'Gallery block', 'block_1');
$handler->override_option('fields', array(
  'nid' => array(
    'label' => 'Nid',
    'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'exclude' => 1,
    'id' => 'nid',
    'table' => 'node',
    'field' => 'nid',
    'override' => array(
      'button' => 'Use default',
    ),
    'relationship' => 'field_gallery_nid',
  ),
   'field_gallery_image_fid' => array(
   'label' => '',
   'alter' => array(
      'alter_text' => 1,
      'text' => '',
      'make_link' => 1,
      'path' => 'node/[nid]',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 0,
    'label_type' => 'none',
    'format' => 'short_default',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_gallery_image_fid',
    'table' => 'node_data_field_gallery_image',
    'field' => 'field_gallery_image_fid',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('arguments', array(
  'field_gallery_nid' => array(
    'default_action' => 'ignore',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => t('Latest image'),
    'breadcrumb' => '',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'node',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'id' => 'field_gallery_nid',
    'table' => 'node_data_field_gallery',
    'field' => 'field_gallery_nid',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => variable_get('views_gallery_nid', 0),
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      views_gallery_gallery_type() => views_gallery_gallery_type(),
    ),
    'validate_argument_node_access' => 1,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(),
    'validate_argument_type' => 'tid',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_php' => '',
    'override' => array(
      'button' => 'Use default',
    ),
    'validate_argument_node_flag_name' => '*relationship*',
    'validate_argument_node_flag_test' => 'flaggable',
    'validate_argument_node_flag_id_type' => 'id',
    'validate_argument_user_flag_name' => '*relationship*',
    'validate_argument_user_flag_test' => 'flaggable',
    'validate_argument_user_flag_id_type' => 'id',
    'validate_argument_is_member' => 0,
    'validate_argument_signup_status' => 'any',
    'validate_argument_signup_node_access' => 1,
  ),
));
$handler->override_option('style_plugin', 'grid');
$handler->override_option('style_options', array(
  'grouping' => '',
  'columns' => '1',
  'alignment' => 'horizontal',
));$handler->override_option('items_per_page', 1);
$handler->override_option('use_pager', '0');
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);

if (module_exists('views_slideshow_singleframe')) {
$handler = $view->new_display('block', 'Slideshow block', 'block_2');
$handler->override_option('items_per_page', 10);
$handler->override_option('use_pager', 0);
$handler->override_option('style_plugin', 'slideshow');
$handler->override_option('style_options', array(
  'grouping' => '',
  'type' => 'ul',
  'mode' => 'singleframe',
  'singleframe' => array(
    'timeout' => '1000',
    'delay' => '1',
    'speed' => '2000',
    'random' => '0',
    'pause' => '2',
    'controls' => '0',
    'pager' => '2',
    'pager_type' => 'Numbered',
    'pager_hover' => '1',
    'image_count' => '0',
    'effect' => 'fade',
    'sync' => '1',
    'advanced' => '',
    'ie' => array(
      'cleartype' => TRUE,
      'cleartypenobg' => FALSE,
    ),
  ),
  'thumbnailhover' => array(
    'hover_breakout' => 'teaser',
    'teasers_last' => 1,
    'timeout' => '1500',
    'delay' => '0',
    'speed' => '1500',
    'random' => '0',
    'pause' => '1',
    'pager_event' => 'mouseover',
    'controls' => '0',
    'image_count' => '0',
    'effect' => 'fade',
    'sync' => '',
    'advanced' => '',
    'ie' => array(
      'cleartype' => TRUE,
      'cleartypenobg' => FALSE,
    ),
  ),
));
$handler->override_option('fields', array(
   'field_gallery_image_fid' => array(
   'label' => '',
   'alter' => array(
      'alter_text' => 0,
      'text' => '',
      'make_link' => 0,
      'path' => '',
      'link_class' => '',
      'alt' => '',
      'prefix' => '',
      'suffix' => '',
      'help' => '',
      'trim' => 0,
      'max_length' => '',
      'word_boundary' => 1,
      'ellipsis' => 1,
      'strip_tags' => 0,
      'html' => 0,
    ),
    'link_to_node' => 1,
    'label_type' => 'none',
    'format' => 'reg_linked',
    'multiple' => array(
      'group' => TRUE,
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_reversed' => FALSE,
    ),
    'exclude' => 0,
    'id' => 'field_gallery_image_fid',
    'table' => 'node_data_field_gallery_image',
    'field' => 'field_gallery_image_fid',
    'relationship' => 'none',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
$handler->override_option('row_options', array(
  'inline' => array(),
  'separator' => '',
));
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);
$handler->override_option('arguments', array(
  'field_gallery_nid' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => '',
    'breadcrumb' => '',
    'default_argument_type' => 'fixed',
    'default_argument' => '',
    'validate_type' => 'node',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'id' => 'field_gallery_nid',
    'table' => 'node_data_field_gallery',
    'field' => 'field_gallery_nid',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
      '5' => 0,
      '3' => 0,
      '4' => 0,
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => variable_get('views_gallery_nid', 0),
    'default_argument_php' => '',
    'validate_argument_node_type' => array(
      views_gallery_gallery_type() => views_gallery_gallery_type(),
    ),
    'validate_argument_node_access' => 1,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_vocabulary' => array(
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
    'validate_argument_php' => '',
    'override' => array(
      'button' => 'Use default',
    ),
  ),
));
}

$views[$view->name] = $view;

$view = new view;
$view->name = 'galley_list';
$view->description = 'A teaser list of all galleries.';
$view->tag = '';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('sorts', array(
  'created' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
  'changed' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'changed',
    'table' => 'node',
    'field' => 'changed',
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'status' => array(
    'operator' => '=',
    'value' => '1',
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
  'type' => array(
    'operator' => 'in',
    'value' => array(
      views_gallery_gallery_type() => views_gallery_gallery_type(),
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('cache', array(
  'type' => 'none',
));
$handler->override_option('title', 'Galleries');
$handler->override_option('items_per_page', 0);
$handler->override_option('use_pager', '1');
$handler->override_option('style_plugin', 'grid');
$handler->override_option('style_options', array(
  'columns' => '3',
  'alignment' => 'horizontal',
));
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'relationship' => 'none',
  'build_mode' => 'teaser',
  'links' => 1,
  'comments' => 0,
));
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->override_option('path', 'gallery-list');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
  'name' => 'navigation',
));

$views[$view->name] = $view;
return $views;
}