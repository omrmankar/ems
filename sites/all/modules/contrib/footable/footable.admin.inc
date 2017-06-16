<?php

/**
 * @file
 * FooTable administration forms.
 */

/**
 * FooTable settings configuration form.
 */
function footable_form_admin_settings($form, &$form_state) {
  $form['config'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['config']['plugin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugin'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['config']['plugin']['footable_plugin_type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#options' => array(
      'standalone' => t('Standalone'),
      'bootstrap' => t('Bootstrap'),
    ),
    '#default_value' => variable_get('footable_plugin_type', 'standalone'),
  );

  $form['config']['plugin']['footable_plugin_compression'] = array(
    '#type' => 'radios',
    '#title' => t('Compression level'),
    '#options' => array(
      'minified' => t('Production (minified)'),
      'source' => t('Development (uncompressed)'),
    ),
    '#default_value' => variable_get('footable_plugin_compression', 'minified'),
  );

  $form['config']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['config']['advanced']['footable_breakpoint_load_default'] = array(
    '#type' => 'checkbox',
    '#title' => t("Load the module's default breakpoints"),
    '#description' => t("Control whether the module's default breakpoints are used. This will not affect breakpoints exported via Features."),
    '#default_value' => variable_get('footable_breakpoint_load_default', TRUE),
  );

  return system_settings_form($form);
}
