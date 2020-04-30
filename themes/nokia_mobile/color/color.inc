<?php
// $Id: color.inc,v 1.1 2010/01/05 19:40:09 atrasatti Exp $

$info = array(

  // Pre-defined color schemes
  'schemes' => array(
    '#0072b9,#0000ee,#298bc8,#298bc8,#494949' => t('Blue Lagoon (Default)'),
    '#464849,#2f4fa2,#707070,#707070,#494949' => t('Ash'),
    '#55c0e2,#000000,#007e94,#007e94,#696969' => t('Aquamarine'),
    '#d5b048,#6c420e,#971702,#971702,#494949' => t('Belgian Chocolate'),
    '#537aa2,#336699,#6a9eb1,#6a9eb1,#000000' => t('Bluemarine'),
    '#f5e407,#917803,#e6fb2d,#e6fb2d,#494949' => t('Citrus Blast'),
    '#261eb8,#434f8c,#0056e0,#0056e0,#000000' => t('Cold Day'),
    '#099c24,#0c7a00,#7be000,#7be000,#494949' => t('Greenbeam'),
    '#a9290a,#a9290a,#fc6d1d,#fc6d1d,#494949' => t('Mediterrano'),
    '#8f9eb3,#3f728d,#afb3c2,#afb3c2,#707070' => t('Mercury'),
    '#5b5fa9,#5b5faa,#355797,#355797,#494949' => t('Nocturnal'),
    '#7db323,#6a9915,#b5d52a,#b5d52a,#191a19' => t('Olivia'),
    '#ff4d8d,#1b1a13,#f391c6,#f391c6,#898080' => t('Pink Plastic'),
    '#bc3d2f,#c70000,#f21107,#f21107,#515d52' => t('Shiny Tomato'),
    '#34775a,#1b5f42,#52bf90,#52bf90,#2d2d2d' => t('Teal Top'),
  ),

  // Images to copy over
  'copy' => array(
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'style.css',
  ),

  // Coordinates of gradient (x, y, width, height)
  'gradient' => array(0, 0, 360, 27),

  // Color areas to fill (x, y, width, height)
  'fill' => array(
    'base' => array(0, 0, 360, 250)
  ),

  // Coordinates of all the theme slices (x, y, width, height)
  // with their filename as used in the stylesheet.
  'slices' => array(
  ),

  // Reference color used for blending. Matches the base.png's colors.
  'blend_target' => '#ffffff',

  // Preview files
  'preview_image' => 'color/preview.png',
  'preview_css' => 'color/preview.css',

  // Base file for image generation
  'base_image' => 'color/base.png'
);
