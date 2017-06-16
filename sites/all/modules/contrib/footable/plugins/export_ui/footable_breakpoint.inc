<?php

/**
 * @file
 * Provide Ctools exportables for the FooTable module.
 */

$plugin = array(
  'schema' => 'footable_breakpoint',
  'access' => 'administer footable',
  'menu' => array(
    'menu prefix' => 'admin/config/user-interface',
    'menu item' => 'footable',
    'menu title' => 'FooTable',
    'menu description' => 'Administer FooTable breakpoints.',
  ),
  'title singular' => t('FooTable breakpoint'),
  'title plural' => t('FooTable breakpoints'),
  'title singular proper' => t('FooTable breakpoint'),
  'title plural proper' => t('FooTable breakpoints'),
  'handler' => array(
    'class' => 'footable_breakpoint',
  ),
  'form' => array(
    'settings' => 'footable_breakpoint_ctools_export_ui_form',
  ),
);

/**
 * Define the preset add/edit form.
 */
function footable_breakpoint_ctools_export_ui_form(&$form, &$form_state) {
  $form['info']['name']['#required'] = TRUE;

  $form['breakpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Breakpoint'),
    '#required' => TRUE,
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => !empty($form_state['item']->breakpoint) ? $form_state['item']->breakpoint : '',
    '#field_suffix' => 'px',
  );
}
