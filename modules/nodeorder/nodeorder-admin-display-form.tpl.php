<?php
// $Id: nodeorder-admin-display-form.tpl.php,v 1.1.2.3 2009/01/17 15:43:33 pvanderspek Exp $

/**
 * @file nodeorder-admin-display-form.tpl.php
 * Default theme implementation to order nodes.
 *
 * Available variables:
 * - $node_listing: An array of nodes.
 * - $form_submit: Form submit button.
 *
 *
 * Each $data in $node_listing[$i] contains:
 * - $data->node_title: Node title.
 * - $data->weight: Drop-down menu for setting weights.
 * - $data->tid
 * - $data->nid
 *
 * @see template_preprocess_nodeorder_admin_display_form()
 * @see theme_nodeorder_admin_display()
 */
?>
<?php
  // Add table javascript.
  drupal_add_js('misc/tableheader.js');
  drupal_add_js(drupal_get_path('module', 'nodeorder') .'/nodeorder.js');
  drupal_add_tabledrag('ordernodes', 'order', 'sibling', 'nodeorder-weight');
?>
<table id="ordernodes" class="sticky-enabled">
  <thead>
    <tr>
      <th colspan=2><?php print t('Node title'); ?></th>
    </tr>
  </thead>
  <tbody>
    <?php $row = 0; ?>
    <?php if (isset($node_listing) && sizeof($node_listing) > 0): ?> 
      <?php foreach ($node_listing as $key => $data): ?>
        <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?><?php print $data->row_class ? ' '. $data->row_class : ''; ?>">
          <td class="node"><?php print $data->node_title; ?></td>
		  <td><?php print $data->weight; ?></td>
        </tr>
        <?php $row++; ?>
      <?php endforeach; ?>
    <?php else: ?>
      <tr>
        <td><em><?php print t('No nodes available.'); ?></em></td>
      </tr>
    <?php endif; ?>
  </tbody>
</table>

<?php print $form_submit; ?>