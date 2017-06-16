<?php

/**
 * @file
 * Provide FooTable breakpoint Ctools export ui integration.
 */

class footable_breakpoint extends ctools_export_ui {

  /**
   * {@inheritdoc}
   */
  function list_sort_options() {
    return array(
      'name' => t('Name'),
      'machine_name' => t('Machine name'),
      'breakpoint' => t('Breakpoint'),
      'type' => t('Type'),
      'storage' => t('Storage'),
    );
  }

  /**
   * {@inheritdoc}
   */
  function list_table_header() {
    return array(
      array('data' => t('Name'), 'class' => array('ctools-export-ui-name')),
      array('data' => t('Machine name'), 'class' => array('ctools-export-ui-machine-name')),
      array('data' => t('Breakpoint'), 'class' => array('ctools-export-ui-breakpoint')),
      array('data' => t('Storage'), 'class' => array('ctools-export-ui-storage')),
      array('data' => t('Operations'), 'class' => array('ctools-export-ui-operations')),
    );
  }

  /**
   * {@inheritdoc}
   */
  function list_build_row($item, &$form_state, $operations) {
    // Set up sorting.
    switch ($form_state['values']['order']) {
      case 'name':
        $sort = array($item->name);
        break;
      case 'machine_name':
        $sort = array($item->machine_name);
        break;
      case 'breakpoint':
        $sort = array($item->breakpoint);
        break;
      case 'storage':
        $sort = array($item->type);
        break;
      case 'disabled':
      default:
        $sort = array(empty($item->disabled));
        break;
    }
    $sort += array($item->breakpoint, $item->machine_name);
    $this->sorts[$item->machine_name] = implode('__', $sort);

    // Build row.
    $this->rows[$item->machine_name] = array(
      'data' => array(
        array('data' => check_plain($item->name), 'class' => array('ctools-export-ui-title')),
        array('data' => check_plain($item->machine_name), 'class' => array('ctools-export-ui-title')),
        array('data' => check_plain($item->breakpoint) . 'px', 'class' => array('ctools-export-ui-base')),
        array('data' => check_plain($item->type), 'class' => array('ctools-export-ui-storage')),
        array(
          'data' => theme('links__ctools_dropbutton', array(
            'links' => $operations,
            'attributes' => array(
              'class' => array('links', 'inline'),
            ),
          )),
          'class' => array('ctools-export-ui-operations'),
        ),
      ),
      'class' => array(!empty($item->disabled) ? 'ctools-export-ui-disabled' : 'ctools-export-ui-enabled'),
    );
  }

}
