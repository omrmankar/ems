<?php
function employee_timetracker_edit_confirm_form() {
   
    $userid = arg(2);
    $query = db_select('employee_timetsheet', 'et');
	$query->fields('et', array('id','office_in_time','office_out_time','half_day','work_update')); 
	$query->condition('et.id', $userid , '=');
	$result = $query->execute();
	$row = $result->fetchAll();
            foreach ($row as $result) 
             {
                        $work_update=$result->work_update;
				        $office_in=$result->office_in_time;
			        	$office_out=$result->office_out_time;
		        		$halfd=$result->half_day;
              }
    $form = array();
      
   if($halfd == 'Half day')
    {
     $checked = "checked";
    }
   else
    {
      $checked = "";
    }
	
	$form['id'] = array(
          '#type' => 'value',
          '#value' =>$userid,
          '#default_value' => $userid,
      );
  

	$form['work_update'] = array(
            '#type' => 'textarea', 
            '#title' => 'Work Update',
	        '#description'=>t('Please edit Your update with project details'),
            '#default_value' => $work_update,
            '#required' => TRUE,
     );

	$form['office_in_time']=array(
		'#type'=>'textfield',
		'#title'=>t('Office In Time'),
		'#description'=>t('Please edit your office-in time'),
		'#required' => TRUE,
        '#default_value' =>  $office_in,
		
	);
	$form['office_out_time']=array(
		'#type'=>'textfield',
		'#title'=>t('Office Out Time'),
		'#description'=>t('Please edit your office-out time'),
		'#required' => TRUE,
	    '#default_value' => $office_out,
	);

	$form['half_day']=array(
		'#type'=>'checkbox',
		'#title'=>t('Half Day'),
		'#description'=>t('Consider it as half day'),
		'#required' => FALSE,
		'#default_value' => $halfd,
		'#attributes' => array('class' => array('emp-half-day'),
							   $checked => $checked,
							  )
    );
   
   $form['submit']=array(
    '#type'=>'submit',
    '#value'=>t('Update'),
    '#redirect' => 'employee/timesheet'
  );
   return $form;
}

function employee_timetracker_edit_confirm_form_submit($form,&$form_state){
	
          $work=$form_state['values']['work_update'];    
          $office_in_time=$form_state['values']['office_in_time'];
          $office_out_time=$form_state['values']['office_out_time'];
          $half_day=$form_state['values']['half_day'];
          $id=$form_state['values']['id'];      
       
		   $query=db_merge('employee_timetsheet')
					->key(array(
					'id' => $id,
					  ))
					->updateFields(array(
						'work_update' => $work,
						'office_in_time' => $office_in_time,
						'office_out_time'=>$office_out_time,
						'half_day'=>$half_day,
					  ))
					->execute();

      if($query){
		drupal_set_message('Update Row '.$id. ' Successfully.');
		drupal_goto('employee/timesheet');
               }	
	  else 
		{	
		  drupal_set_message(t('Error while inserting data into database'), 'error');
	    }
   
}

?>
