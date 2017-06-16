<?php
function employee_timetracker_checkin_form() {
	global $user;
	$employee_id = $user->uid;
	$update_date = date("d-M-Y");
	$count = db_select('employee_checkin')
			->condition('employee_id', $employee_id)
			->condition('update_date', $update_date)
			->countQuery()->execute()->fetchField();
	if ($count == 0) {
		$disabled = '';
	}
	else{
		$disabled = 'disabled';
	}
	$form = array();
	
	$form['emp_checkin']=array(
			'#type' => 'markup',
		    '#prefix' => '<div class="emp-checkin-title">',
		    '#suffix' => '<label>Please checkin you office intime</label></div>',
	);	
	$form['submit']=array(
		'#type'=>'submit',
		'#value'=>t('Checkin'),
		'#attributes' => array('class' => array('emp-submit-checkin'),
								$disabled => $disabled,
							   'id' => 'checkin_submit'
							)
	);
	return $form;
}

function employee_timetracker_checkin_form_submit($form, &$form_state) {
	
	global $user;
	$employee_id = $user->uid;
	$employee_name = $user->name;
	$update_date = date("d-M-Y");
	$office_checkin_time = date("H:i");
	
	$data = array(
		'employee_id' => $employee_id,
		'employee_name' => $employee_name,
		'update_date' => $update_date,
		'office_checkin_time' => $office_checkin_time,
	);	
	
	$count = db_select('employee_checkin')
			->condition('employee_id', $employee_id)
			->condition('update_date', $update_date)
			->countQuery()->execute()->fetchField();
	if ($count == 0) { 			
		$query = db_insert('employee_checkin')->fields($data);
			$submit_query = $query->execute();
			if($submit_query) {
				drupal_set_message('Employee successfully checkin', $type = 'status');
				drupal_goto('employee/timetracker');
			}	
			else{	
				drupal_set_message(t('Error while inserting data into database.'), 'error');
			}
	}
	else{
		drupal_set_message(t('You are already checkin your time.'), 'error');
	}
	
}

?>
