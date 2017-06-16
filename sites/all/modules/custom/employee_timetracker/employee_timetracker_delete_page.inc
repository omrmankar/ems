<?php
    function employee_timetracker_delete_confirm_form(){
              

               $id=arg(2);
               # print_r($id);
               $form = array();
               $form['id'] = array(
                 '#type' => 'value',
                 '#default_value' => $id,
                 '#value' => $id,
               );
              
              return confirm_form(
                 $form,
                 t('Are you sure you want to delete this item?'),
                'employee/timesheet',
                 t('This action cannot be undone.'),
                 t('Delete'),
                 t('Cancel')
              );
        }

function employee_timetracker_delete_confirm_form_submit($form, &$form_state) {


        if (is_numeric($form_state['values']['id'])){
        
          db_delete('employee_timetsheet')->condition('id',$form_state['values']['id'])->execute();
      }
      
      drupal_set_message('You confirmed item ' . $form_state['values']['id'] . '.');
      
      $form_state['redirect'] = 'employee/timesheet';
  }


?>
