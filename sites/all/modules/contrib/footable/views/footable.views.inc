<?php

/**
 * @file
 * FooTable views hooks.
 */

/**
 * Implements hook_views_plugins().
 */
function footable_views_plugins() {
  $path = drupal_get_path('module', 'footable');
  return array(
    'module' => 'footable',
    'style' => array(
      'footable' => array(
        'title' => t('FooTable'),
        'help' => t('Displays rows in a responsive table, using the jQuery plugin FooTable.'),
        'path' => $path . '/views',
        'theme path' => $path . '/views',
        'handler' => 'footable_plugin_style_footable',
        'parent' => 'table',
        'theme' => 'footable_view',
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
