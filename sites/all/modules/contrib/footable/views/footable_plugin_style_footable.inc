<?php

/**
 * @file
 * Contains the FooTable style plugin.
 */

/**
 * Style plugin to render a FooTable.
 *
 * @ingroup views_style_plugins
 */
class footable_plugin_style_footable extends views_plugin_style_table {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['footable'] = array(
      'default' => array(
        'expand_all' => FALSE,
        'expand_first' => FALSE,
        'show_header' => TRUE,
        'toggle_column' => 'first',
        'icon_expanded' => 'plus',
        'icon_collapsed' => 'minus',
        'bootstrap' => array(
          'striped' => FALSE,
          'bordered' => FALSE,
          'hover' => FALSE,
          'condensed' => FALSE,
        ),
        'component' => array(
          'paging' => array(
            'enabled' => FALSE,
            'count_format' => '{CP} of {TP}',
            'current' => 1,
            'limit' => 5,
            'position' => 'right',
            'size' => 10,
          ),
          'filtering' => array(
            'enabled' => FALSE,
            'delay' => 1200,
            'ignore_case' => TRUE,
            'min' => 3,
            'placeholder' => 'Search',
            'position' => 'right',
            'space' => 'AND',
          ),
          'sorting' => array(
            'enabled' => FALSE,
          ),
        ),
      ),
    );
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Check if fields have been added.  Table style plugin will set
    // error_markup if fields are not added.
    // @see views_plugin_style_table::options_form()
    if (isset($form['error_markup'])) {
      return;
    }

    // Override default plugin theme.
    $form['#theme'] = 'footable_style_plugin_table';

    $columns = $this->sanitize_columns($this->options['columns']);
    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      $form['info'][$field]['type'] = array(
        '#type' => 'select',
        '#options' => array(
          '' => t('Automatic'),
          'number' => t('Number'),
          'date' => t('Date'),
          'text' => t('Text'),
          'html' => t('HTML'),
        ),
        '#default_value' => !empty($this->options['info'][$field]['type']) ? $this->options['info'][$field]['type'] : '',
        '#dependency' => array('edit-style-options-columns-' . $safe => array($field)),
      );
    }

    $form['footable'] = array(
      '#type' => 'fieldset',
      '#title' => t('FooTable settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['footable']['expand_all'] = array(
      '#type' => 'select',
      '#title' => t('Expand all rows'),
      '#description' => t('Whether or not to expand all rows of the table.'),
      '#options' => array(
        FALSE => t('Disabled'),
        TRUE => t('Enabled'),
      ),
      '#default_value' => $this->options['footable']['expand_all'],
    );

    $form['footable']['expand_first'] = array(
      '#type' => 'select',
      '#title' => t('Expand first row'),
      '#description' => t('Whether or not to expand the first row of the table.'),
      '#options' => array(
        FALSE => t('Disabled'),
        TRUE => t('Enabled'),
      ),
      '#default_value' => $this->options['footable']['expand_first'],
      '#states' => array(
        'invisible' => array(
          ':input[name="style_options[footable][expand_all]"]' => array('value' => 1),
        ),
      ),
    );

    $form['footable']['show_header'] = array(
      '#type' => 'select',
      '#title' => t('Show header'),
      '#description' => t('Whether or not to display a header row in the table.'),
      '#options' => array(
        TRUE => t('Yes'),
        FALSE => t('No'),
      ),
      '#default_value' => $this->options['footable']['show_header'],
    );

    $form['footable']['toggle_column'] = array(
      '#type' => 'select',
      '#title' => t('Expandable column'),
      '#description' => t('Specify which column the toggle is appended to in a row.'),
      '#options' => array(
        'first' => t('First'),
        'last' => t('Last'),
      ),
      '#default_value' => $this->options['footable']['toggle_column'],
    );

    // Icons.
    $icons = footable_icons();
    $form['footable']['icon_collapsed'] = array(
      '#type' => 'select',
      '#title' => t('Collapsed icon style'),
      '#description' => t('The icon displayed when a row is collapsed.'),
      '#options' => $icons,
      '#default_value' => $this->options['footable']['icon_collapsed'],
    );

    $form['footable']['icon_expanded'] = array(
      '#type' => 'select',
      '#title' => t('Expanded icon style'),
      '#description' => t('The icon displayed when a row is expanded.'),
      '#options' => $icons,
      '#default_value' => $this->options['footable']['icon_expanded'],
    );

    // Bootstrap style configuration.
    if (variable_get('footable_plugin_type', 'standalone') == 'bootstrap') {
      $form['footable']['bootstrap'] = array(
        '#type' => 'fieldset',
        '#title' => t('Bootstrap'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['footable']['bootstrap']['striped'] = array(
        '#type' => 'checkbox',
        '#title' => t('Striped'),
        '#default_value' => $this->options['footable']['bootstrap']['striped'],
      );

      $form['footable']['bootstrap']['bordered'] = array(
        '#type' => 'checkbox',
        '#title' => t('Bordered'),
        '#default_value' => $this->options['footable']['bootstrap']['bordered'],
      );

      $form['footable']['bootstrap']['hover'] = array(
        '#type' => 'checkbox',
        '#title' => t('Hover'),
        '#default_value' => $this->options['footable']['bootstrap']['hover'],
      );

      $form['footable']['bootstrap']['condensed'] = array(
        '#type' => 'checkbox',
        '#title' => t('Condensed'),
        '#default_value' => $this->options['footable']['bootstrap']['condensed'],
      );
    }

    // Components.
    $form['footable']['component'] = array(
      '#type' => 'fieldset',
      '#title' => t('Components'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    // Filtering.
    $form['footable']['component']['filtering'] = array(
      '#type' => 'fieldset',
      '#title' => t('Filtering'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['footable']['component']['filtering']['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => $this->options['footable']['component']['filtering']['enabled'],
    );

    $form['footable']['component']['filtering']['delay'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay'),
      '#description' => t('The number of milliseconds before a search input filter is applied after it changes.'),
      '#default_value' => $this->options['footable']['component']['filtering']['delay'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['filtering']['ignore_case'] = array(
      '#type' => 'select',
      '#title' => t('Ignore case'),
      '#description' => t('Whether or not to ignore case when filtering.'),
      '#options' => array(
        TRUE => t('Yes'),
        FALSE => t('No'),
      ),
      '#default_value' => $this->options['footable']['component']['filtering']['ignore_case'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['filtering']['min'] = array(
      '#type' => 'textfield',
      '#title' => t('Minimum characters'),
      '#description' => t('The minimum number of characters in the search input before auto applying the filter.'),
      '#default_value' => $this->options['footable']['component']['filtering']['min'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['filtering']['placeholder'] = array(
      '#type' => 'textfield',
      '#title' => t('Placeholder'),
      '#description' => t('The placeholder text displayed within the search input.'),
      '#default_value' => $this->options['footable']['component']['filtering']['placeholder'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['filtering']['position'] = array(
      '#type' => 'select',
      '#title' => t('Position'),
      '#description' => t('The position of the search input within the filter row.'),
      '#options' => array(
        'right' => t('Right'),
        'left' => t('Left'),
        'center' => t('Center'),
      ),
      '#default_value' => $this->options['footable']['component']['filtering']['position'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['filtering']['space'] = array(
      '#type' => 'select',
      '#title' => t('Space'),
      '#description' => t('How to treat whitespace.'),
      '#options' => array(
        'AND' => 'AND',
        'OR' => 'OR',
      ),
      '#default_value' => $this->options['footable']['component']['filtering']['space'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][filtering][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    // Paging.
    $form['footable']['component']['paging'] = array(
      '#type' => 'fieldset',
      '#title' => t('Paging'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['footable']['component']['paging']['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => $this->options['footable']['component']['paging']['enabled'],
    );

    $form['footable']['component']['paging']['count_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Count format'),
      '#description' => t('The string used as a format to generate the count text.'),
      '#default_value' => $this->options['footable']['component']['paging']['count_format'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][paging][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['paging']['current'] = array(
      '#type' => 'textfield',
      '#title' => t('Current'),
      '#description' => t('The page number to display when first initialized.'),
      '#default_value' => $this->options['footable']['component']['paging']['current'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][paging][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['paging']['limit'] = array(
      '#type' => 'textfield',
      '#title' => t('Limit'),
      '#description' => t('The maximum number of page links to display in the pagination control.'),
      '#default_value' => $this->options['footable']['component']['paging']['limit'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][paging][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['paging']['position'] = array(
      '#type' => 'select',
      '#title' => t('Position'),
      '#description' => t('The position of the pagination control within the paging row.'),
      '#options' => array(
        'right' => t('Right'),
        'left' => t('Left'),
        'center' => t('Center'),
      ),
      '#default_value' => $this->options['footable']['component']['paging']['position'],
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][paging][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    $form['footable']['component']['paging']['size'] = array(
      '#type' => 'textfield',
      '#title' => t('Size'),
      '#description' => t('The number of rows per page.'),
      '#default_value' => $this->options['footable']['component']['paging']['size'],
      '#element_validate' => array('element_validate_integer_positive'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[footable][component][paging][enabled]"]' => array('checked' => TRUE),
        ),
      ),
    );

    // Sorting.
    $form['footable']['component']['sorting'] = array(
      '#type' => 'fieldset',
      '#title' => t('Sorting'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['footable']['component']['sorting']['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enabled'),
      '#default_value' => $this->options['footable']['component']['sorting']['enabled'],
    );

    // Breakpoints overwrite.
    $form['footable']['overwrite'] = array(
      '#type' => 'fieldset',
      '#title' => t('Overwrite breakpoints'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    foreach (footable_breakpoint_load_multiple() as $breakpoint) {
      $form['footable']['overwrite'][$breakpoint->machine_name] = array(
        '#type' => 'textfield',
        '#title' => check_plain($breakpoint->name),
        '#default_value' => isset($this->options['footable']['overwrite'][$breakpoint->machine_name]) ? $this->options['footable']['overwrite'][$breakpoint->machine_name] : NULL,
        '#element_validate' => array('element_validate_integer_positive'),
        '#field_suffix' => 'px',
        '#attributes' => array(
          'placeholder' => $breakpoint->breakpoint,
        ),
      );
    }

    // Breakpoints.
    $form['footable']['breakpoint'] = array(
      '#type' => 'fieldset',
      '#title' => t('Collapsed columns'),
      '#description' => t('Select the "breakpoints" where a particular column should be hidden.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $breakpoints = array();
    foreach (footable_breakpoint_load_all(TRUE) as $breakpoint) {
      $breakpoints[$breakpoint->machine_name] = check_plain($breakpoint->name);
    }

    foreach ($this->display->handler->get_field_labels() as $name => $label) {
      $form['footable']['breakpoint'][$name] = array(
        '#title' => check_plain($label),
        '#type' => 'checkboxes',
        '#options' => $breakpoints,
        '#default_value' => isset($this->options['footable']['breakpoint'][$name]) ? $this->options['footable']['breakpoint'][$name] : array(),
        '#multiple' => TRUE,
      );
    }
  }

}
