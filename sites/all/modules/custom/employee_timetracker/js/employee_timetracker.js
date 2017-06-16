jQuery(function() {
	
/*------------------------------------------------ Print Table ------------------------------------------------*/
	
	var l = window.location;
    var base_url = l.protocol + "//" + l.host + "/" + l.pathname.split('/')[1];

	jQuery(".emp-print-button a").on('click', function() {
					
		jQuery(this).parent().parent().find('.emp-timesheet-table').print({

			globalStyles : true,
			mediaPrint : true,
			stylesheet : base_url+'/sites/all/modules/employee_timetracker/css/employee_timetracker.css',
			iframe : false,
			noPrintSelector : ".emp-print-button, .emp-action",
			deferred: jQuery.Deferred().done(function() { console.log('Printing done', arguments); })
		});
	});

/*------------------------------------------------------------------------------------------------------------*/
	
});
