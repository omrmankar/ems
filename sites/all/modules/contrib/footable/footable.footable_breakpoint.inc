<?php

/**
 * @file
 * Provide default FooTable Breakpoints.
 */

/**
 * Implements hook_default_footable_breakpoint().
 */
function footable_default_footable_breakpoint() {
  $footable_breakpoints = array();

  // Optionally skip loading the defaults.
  if (!variable_get('footable_breakpoint_load_default', TRUE)) {
    return $footable_breakpoints;
  }

  $footable_breakpoint = new stdClass();
  $footable_breakpoint->disabled = FALSE;
  $footable_breakpoint->api_version = 1;
  $footable_breakpoint->name = 'Extra small devices';
  $footable_breakpoint->machine_name = 'xs';
  $footable_breakpoint->breakpoint = 480;
  $footable_breakpoints[$footable_breakpoint->machine_name] = $footable_breakpoint;

  $footable_breakpoint = new stdClass();
  $footable_breakpoint->disabled = FALSE;
  $footable_breakpoint->api_version = 1;
  $footable_breakpoint->name = 'Small devices';
  $footable_breakpoint->machine_name = 'sm';
  $footable_breakpoint->breakpoint = 768;
  $footable_breakpoints[$footable_breakpoint->machine_name] = $footable_breakpoint;

  $footable_breakpoint = new stdClass();
  $footable_breakpoint->disabled = FALSE;
  $footable_breakpoint->api_version = 1;
  $footable_breakpoint->name = 'Medium devices';
  $footable_breakpoint->machine_name = 'md';
  $footable_breakpoint->breakpoint = 992;
  $footable_breakpoints[$footable_breakpoint->machine_name] = $footable_breakpoint;

  $footable_breakpoint = new stdClass();
  $footable_breakpoint->disabled = FALSE;
  $footable_breakpoint->api_version = 1;
  $footable_breakpoint->name = 'Large devices';
  $footable_breakpoint->machine_name = 'lg';
  $footable_breakpoint->breakpoint = 1200;
  $footable_breakpoints[$footable_breakpoint->machine_name] = $footable_breakpoint;

  return $footable_breakpoints;
}
