<?php
function employee_timetracker_details_page() {
	$userid = arg(1);
	$query = db_select('employee_timetsheet', 'et');
	$query->fields('et', array('id', 'employee_id','employee_name','update_day','update_month','update_year','office_in_time','office_out_time','half_day','work_update'));  // select your required fields here
	$query->condition('et.id', $userid , '=');
	$result = $query->execute();
	$row = $result->fetchAll();
	$output = '';
	foreach($row as $res) {
		//if($res->half_day == 1){ $status = 'Half Day'; } else { $status = 'Full Day'; } 
		$status = $res->half_day;
		$intm = strtotime($res->office_in_time);
		$outtm = strtotime($res-> office_out_time);
		$tmdif = ($outtm - $intm) / 60;
		$tmdifhour =  floor($tmdif / 60);
		$tmdifminute = ($tmdif % 60);
		$comptm = sprintf('%02d:%02d', $tmdifhour, $tmdifminute);
		$update_dates = $res->update_day.'-'.$res->update_month.'-'.$res->update_year;

		$output = '<div class="employee-timetracker-wrapper">
					   <div class="employee-update-details-page">
						   <div class="employee-update-top">
								<h1 class="employee-update-title">Update '.$update_dates.'</h1>
						   </div>
						   <div class="employee-update-left">
								<div class="employee-update-name">'.$res->employee_name.'</div>
								<div class="employee-update-intime"><label>Office Intime: </label>'.$res->office_in_time.'</div>
								<div class="employee-update-outtime"><label>Office Outtime: </label>'.$res->office_out_time.'</div>
								<div class="employee-update-duration"><label>Duration: </label>'.$comptm.'</div>
								<div class="employee-update-status"><label>Status: </label>'.$status.'</div>
						   </div>
						   <div class="employee-update-right">
								<div class="employee-update-description">'.t($res->work_update).'</div>
						   </div>
					   </div>
		           </div>';		
	}
	return $output;
}
?>
