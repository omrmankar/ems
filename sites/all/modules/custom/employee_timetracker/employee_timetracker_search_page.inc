<?php

function employee_timetracker_search_form() {
	global $user;
	
	$options = array();
	
	$query = db_select('users', 'u');
	$query->fields('u', array('uid','name'));  // select your required fields here
	$result = $query->execute();
	$row = $result->fetchAll();
	foreach($row as $res) {
		if($res->uid == 0){
			$res->name = "-- Select User --";
		}
		$options[$res->name] = $res->name;
	}
    //print '<pre>'; print_r($options); exit;
	$form = array();
	if (in_array('administrator', array_values($user->roles))){
		$form['emp_name']=array(
			'#title' => t('Employee Name'),
			'#type'=>'select',
			'#required' => False,
			'#options' => $options,
			'#default_value' => isset($_GET['emp_name']) ? $_GET['emp_name'] : "",
			'#attributes' => array('class' => array('emp_name_search')),
		);	
	}
	$form['emp_month']=array(
		'#title' => t('Month'),
		'#type'=>'select',
		'#required' => False,
		'#default_value' => isset($_GET['emp_month']) ? $_GET['emp_month'] : date("M"),
		'#attributes' => array('class' => array('emp-month-search')),
		'#options' => array(//'none' => t('-- Select Month --'),
							'Jan' => t('January'),
							'Feb' => t('February'),
							'Mar' => t('March'),
							'apr' => t('April'),
							'May' => t('May'),
							'Jun' => t('June'),
							'Jul' => t('July'),
							'Aug' => t('August'),
							'Sep' => t('September'),
							'Oct' => t('October'),
							'Nov' => t('November'),
							'Dec' => t('Decemder')),
	);	
	$form['emp_year']=array(
		'#title' => t('Year'),
		'#type'=>'select',
		'#required' => False,
		'#default_value' => isset($_GET['emp_year']) ? $_GET['emp_year'] : date("Y"),
		'#attributes' => array('class' => array('emp-year-search')),
		'#options' => array(//'none' => t('-- Select Year --'),
							'2017' => t('2017'),
							'2018' => t('2018'),
							'2019' => t('2019'),
							'2020' => t('2020'),
							'2021' => t('2021'),
							'2022' => t('2022'),
							'2023' => t('2023'),
							'2024' => t('2024'),
							'2025' => t('2025')),
	);
		
	$form['submit']=array(
		'#type'=>'submit',
		'#value'=>t('Search'),
		'#attributes' => array('class' => array('emp-submit-search'))
	);
	//~ $form['emp_print']=array(
			//~ '#type' => 'markup',
		    //~ '#prefix' => '<div class="emp-print-button">',
		    //~ '#suffix' => '<a id="print_button2" href="javascript:void(0);">Print</a></div>',
	//~ );
	return $form;
}

function employee_timetracker_search_form_submit($form, &$form_state) {
	global $user;
	if(isset($form_state['input']['emp_name'])){
		$emp_name = $form_state['input']['emp_name'];
	}
	$emp_month = $form_state['input']['emp_month'];
	$emp_year = $form_state['input']['emp_year'];
	if (in_array('administrator', array_values($user->roles))){
		$form_state['redirect'] = array(
			'employee/timesheet',
			array(
				'query' => array(
				'emp_name' => $emp_name,
				'emp_month' => $emp_month,
				'emp_year' => $emp_year),
			),
		);
	}
	else{
		$form_state['redirect'] = array(
			'employee/timesheet',
			array(
				'query' => array(
				'emp_month' => $emp_month,
				'emp_year' => $emp_year),
			),
		);
	}
}




/**
 * Implements translation_words_editor_table_page_display().
 */

function employee_timetracker_data_display() {
	$header = array(
		array('data' => t('Eid'),'field' => 'employee_id'),
		array('data' => t('Employee Name'), 'field' => 'employee_name'),
		array('data' => t('Update Date'), 'field' => ''),
		array('data' => t('Office In Time'), 'field' => 'office_in_time'),
		array('data' => t('Office Out Time'), 'field' => ' 	office_out_time'),
		array('data' => t('Duration'), 'field' => ''),
		array('data' => t('Status'), 'field' => 'half_day'),
		array('data' => t('Work Update'), 'field' => 'work_update'),
		array('data' => t('View'), 'class' => 'emp-action'),
		array('data' => t('Edit'), 'class' => 'emp-action'),
		array('data' => t('Delete'), 'class' => 'emp-action'),
	  );
		global $user;
		if (in_array('administrator', array_values($user->roles))){
			if(isset($_GET['emp_name']) && isset($_GET['emp_month']) && isset($_GET['emp_year'])){
				$empname = $_GET['emp_name'];
				$empmonth = $_GET['emp_month'];
				$empyear = $_GET['emp_year'];
				$query = db_select('employee_timetsheet', 'et');
				$query->fields('et', array('id', 'employee_id','employee_name','update_day','update_month','update_year','office_in_time','office_out_time','half_day','work_update'));  // select your required fields here
				//$query->condition('et.employee_id', $user->uid , '=')
				$query->condition('et.employee_name', $empname , '=');
				$query->condition('et.update_month', $empmonth , '=');
				$query->condition('et.update_year', $empyear , '=');
				$table_sort = $query->extend('TableSort') // Add table sort extender.
									->orderByHeader($header); // Add order by headers.
				$pager = $table_sort->extend('PagerDefault')
									->limit(50);  // here you can limit the number of data per page.
				$result = $pager->execute();
				$rows = array();
				foreach($result as $res) {
					//if($res->half_day == 1){ $status = 'Half Day'; } else { $status = 'Full Day'; } 
					$status = $res->half_day;
					$intm = strtotime($res->office_in_time);
					$outtm = strtotime($res-> office_out_time);
					$tmdif = ($outtm - $intm) / 60;
					$tmdifhour =  floor($tmdif / 60);
					$tmdifminute = ($tmdif % 60);
					$comptm = sprintf('%02d:%02d', $tmdifhour, $tmdifminute);
					$update_dates = $res->update_day.'-'.$res->update_month.'-'.$res->update_year;
					
					$workupdate = limit_text($res->work_update, 5);

				$rows[] = array(array('data' => $res->employee_id, 'data-th' => 'Employee Id'),
						array('data' => $res->employee_name, 'data-th' => 'Employee Name'),
						array('data' => $update_dates, 'data-th' => 'Update Date'),
						array('data' => $res->office_in_time, 'data-th' => 'Office Intime'),
						array('data' => $res->office_out_time, 'data-th' => 'Office Outtime'),
						array('data' => $comptm, 'data-th' => 'Duration'),
						array('data' => $status, 'data-th' => 'Status'),
						array('data' => $workupdate, 'data-th' => 'Work Update'),
						array('data' => l('View', 'employee/' . $res->id), 'data-th' => 'View', 'class' => 'emp-action'),
						array('data' => l('Edit', 'employee/edit/' .$id= $res->id), 'data-th' => 'Edit', 'class' => 'emp-action'),
						array('data' => l('Delete', 'employee/delete/' .$id=$res->id), 'data-th' => 'Delete', 'class' => 'emp-action'),);
				}
			}
			else{
				$query = db_select('employee_timetsheet', 'et');
				$query->fields('et', array('id', 'employee_id','employee_name','update_day','update_month','update_year','office_in_time','office_out_time','half_day','work_update'));  // select your required fields here
				//$query->condition('et.employee_id', $user->uid , '=');
				$table_sort = $query->extend('TableSort') // Add table sort extender.
									->orderByHeader($header); // Add order by headers.
				$pager = $table_sort->extend('PagerDefault')
									->limit(50);  // here you can limit the number of data per page.
				$result = $pager->execute();
				$rows = array();
				foreach($result as $res) {
					//if($res->half_day == 1){ $status = 'Half Day'; } else { $status = 'Full Day'; } 
					$status = $res->half_day;
					$intm = strtotime($res->office_in_time);
					$outtm = strtotime($res-> office_out_time);
					$tmdif = ($outtm - $intm) / 60;
					$tmdifhour =  floor($tmdif / 60);
					$tmdifminute = ($tmdif % 60);
					$comptm = sprintf('%02d:%02d', $tmdifhour, $tmdifminute);
					$update_dates = $res->update_day.'-'.$res->update_month.'-'.$res->update_year;
					$workupdate = limit_text($res->work_update, 5);
					
				$rows[] = array(array('data' => $res->employee_id, 'data-th' => 'Employee Id'),
						array('data' => $res->employee_name, 'data-th' => 'Employee Name'),
						array('data' => $update_dates, 'data-th' => 'Update Date'),
						array('data' => $res->office_in_time, 'data-th' => 'Office Intime'),
						array('data' => $res->office_out_time, 'data-th' => 'Office Outtime'),
						array('data' => $comptm, 'data-th' => 'Duration'),
						array('data' => $status, 'data-th' => 'Status'),
						array('data' => $workupdate, 'data-th' => 'Work Update'),
						array('data' => l('View', 'employee/' . $res->id), 'data-th' => 'View', 'class' => 'emp-action'),
						array('data' => l('Edit', 'employee/edit/' .$id= $res->id), 'data-th' => 'Edit', 'class' => 'emp-action'),
						array('data' => l('Delete', 'employee/delete/' . $id=$res->id), 'data-th' => 'Delete', 'class' => 'emp-action'),);
				}
			}
		}
		else{
			if(isset($_GET['emp_month']) && isset($_GET['emp_year'])){
				$empmonth = $_GET['emp_month'];
				$empyear = $_GET['emp_year'];
				$query = db_select('employee_timetsheet', 'et');
				$query->fields('et', array('id', 'employee_id','employee_name','update_day','update_month','update_year','office_in_time','office_out_time','half_day','work_update'));  // select your required fields here
				$query->condition('et.employee_id', $user->uid , '=');
				$query->condition('et.update_month', $empmonth , '=');
				$query->condition('et.update_year', $empyear , '=');
				$table_sort = $query->extend('TableSort') // Add table sort extender.
									->orderByHeader($header); // Add order by headers.
				$pager = $table_sort->extend('PagerDefault')
									->limit(50);  // here you can limit the number of data per page.
				$result = $pager->execute();
				$rows = array();
				foreach($result as $res) {
					//if($res->half_day == 1){ $status = 'Half Day'; } else { $status = 'Full Day'; } 
					$status = $res->half_day;
					$intm = strtotime($res->office_in_time);
					$outtm = strtotime($res-> office_out_time);
					$tmdif = ($outtm - $intm) / 60;
					$tmdifhour =  floor($tmdif / 60);
					$tmdifminute = ($tmdif % 60);
					$comptm = sprintf('%02d:%02d', $tmdifhour, $tmdifminute);
					$update_dates = $res->update_day.'-'.$res->update_month.'-'.$res->update_year;
					$workupdate = limit_text($res->work_update, 5);

				$rows[] = array(array('data' => $res->employee_id, 'data-th' => 'Employee Id'),
						array('data' => $res->employee_name, 'data-th' => 'Employee Name'),
						array('data' => $update_dates, 'data-th' => 'Update Date'),
						array('data' => $res->office_in_time, 'data-th' => 'Office Intime'),
						array('data' => $res->office_out_time, 'data-th' => 'Office Outtime'),
						array('data' => $comptm, 'data-th' => 'Duration'),
						array('data' => $status, 'data-th' => 'Status'),
						array('data' => $workupdate, 'data-th' => 'Work Update'),
						array('data' => l('View', 'employee/' . $res->id), 'data-th' => 'View', 'class' => 'emp-action'),);
				}
			}
			else{
				$query = db_select('employee_timetsheet', 'et');
				$query->fields('et', array('id', 'employee_id','employee_name','update_day','update_month','update_year','office_in_time','office_out_time','half_day','work_update'));  // select your required fields here
				$query->condition('et.employee_id', $user->uid , '=');
				$table_sort = $query->extend('TableSort') // Add table sort extender.
									->orderByHeader($header); // Add order by headers.
				$pager = $table_sort->extend('PagerDefault')
									->limit(50);  // here you can limit the number of data per page.
				$result = $pager->execute();
				$rows = array();
				foreach($result as $res) {
					//if($res->half_day == 1){ $status = 'Half Day'; } else { $status = 'Full Day'; } 
					$status = $res->half_day;
					$intm = strtotime($res->office_in_time);
					$outtm = strtotime($res-> office_out_time);
					$tmdif = ($outtm - $intm) / 60;
					$tmdifhour =  floor($tmdif / 60);
					$tmdifminute = ($tmdif % 60);
					$comptm = sprintf('%02d:%02d', $tmdifhour, $tmdifminute);
					$update_dates = $res->update_day.'-'.$res->update_month.'-'.$res->update_year;
					$workupdate = limit_text($res->work_update, 5);
					
				$rows[] = array(array('data' => $res->employee_id, 'data-th' => 'Employee Id'),
						array('data' => $res->employee_name, 'data-th' => 'Employee Name'),
						array('data' => $update_dates, 'data-th' => 'Update Date'),
						array('data' => $res->office_in_time, 'data-th' => 'Office Intime'),
						array('data' => $res->office_out_time, 'data-th' => 'Office Outtime'),
						array('data' => $comptm, 'data-th' => 'Duration'),
						array('data' => $status, 'data-th' => 'Status'),
						array('data' => $workupdate, 'data-th' => 'Work Update'),
						array('data' => l('View', 'employee/' . $res->id), 'data-th' => 'View', 'class' => 'emp-action'),);
				}
			}
		}
		$output = '';

	
	if (!empty($rows)) {
		$output =  '<div class="emp-print-button"><a id="print_button2" href="javascript:void(0);">Print</a></div>';
		$output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'emp-timesheet-table', 'class' => array('emp-timesheet-table'))));
		$output .= theme('pager');
	}
	else {
		$output = '<div class="emp-print-button"><a id="print_button2" href="javascript:void(0);">Print</a></div>';
		$output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'emp-timesheet-table', 'class' => array('emp-timesheet-table'))));
		$output .= theme('pager');
		$output .= t("<h3>No results found.</h3>");
	}
	return $output;
}

/**
 * Implements _employee_timetracker_data_editor().
 */
function _employee_timetracker_data_editor() {
  $page = employee_timetracker_data_display();
  $my_form = drupal_get_form('employee_timetracker_search_form');
  $my_form = drupal_render($my_form);
  $my_form .= $page;
  return '<div class="employee-timetracker-wrapper">'.$my_form.'</div>';
}

function limit_text($text, $limit) {
      if (str_word_count($text, 0) > $limit) {
          $words = str_word_count($text, 2);
          $pos = array_keys($words);
          $text = substr($text, 0, $pos[$limit]) . '...';
      }
      return $text;
}



?>
