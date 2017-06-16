<?php

/**
 * @file
 * API documentation for FooTable module.
 */

/**
 * Add, remove or edit FooTable breakpoints.
 *
 * @array $breakpoints
 *   A keyed array of breakpoints. Each key represents the name of a
 *   breakpoint.
 */
function hook_footable_breakpoint_load_all_alter(&$breakpoints) {
}

/**
 * Add, remove or edit FooTable breakpoints.
 *
 * @array $breakpoints
 *   A keyed array of breakpoints. Each key represents the name of a
 *   breakpoint.
 */
function hook_footable_breakpoint_load_alter(&$breakpoints) {
}

/**
 * Provides a default configuration for FooTable breakpoints.
 *
 * This hook allows modules to provide their own FooTable breakpoints.
 *
 * This hook should be placed in MODULENAME.footable_breakpoint.inc and it will
 * be auto-loaded. MODULENAME.footable_breakpoint.inc *must* be in the same
 * directory as the .module file which *must* also contain an implementation of
 * hook_ctools_plugin_api, preferably with the same code as found in
 * footable_ctools_plugin_api().
 *
 * The $config->disabled boolean attribute indicates whether the FooTable
 * breakpoint instance should be enabled (FALSE) or disabled (TRUE) by default.
 *
 * @return array
 *   An associative array containing the structures of FooTable breakpoints, as
 *   generated from the Export tab, keyed by the FooTable breakpoint machine
 *   name.
 *
 * @see footable_default_footable_breakpoint()
 * @see footable_ctools_plugin_api()
 */
function hook_default_footable_breakpoint() {
  $footable_breakpoints = array();

  $footable_breakpoint = new stdClass();
  $footable_breakpoint->disabled = FALSE;
  $footable_breakpoint->api_version = 1;
  $footable_breakpoint->name = 'Example breakpoint';
  $footable_breakpoint->machine_name = 'breakpoint1';
  $footable_breakpoint->breakpoint = 1000;
  $footable_breakpoint[$footable_breakpoint->machine_name] = $footable_breakpoint;

  return $footable_breakpoints;
}

/**
 * Add, remove or edit FooTable icons.
 *
 * @array $icons
 *   A keyed array of breakpoints. Each key represents the name of an
 *   icon.
 *
 * @see footable_icons()
 */
function hook_footable_icons_alter(&$icons) {
}
