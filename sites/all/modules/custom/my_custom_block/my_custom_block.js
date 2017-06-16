
jQuery(document).ready(function(){
jQuery('.menu-block').hover(
	function()
{
   jQuery('.menu-link').stop(true, true).slideDown('medium');
},
 function () {
    jQuery('.menu-link').stop(true,true).slideUp('medium');
  }
);

});


/*$(document).ready(function () {
    $(".hoverli").hover(
  function () {
     $('ul.file_menu').stop(true, true).slideDown('medium');
  }, 
  function () {
     $('ul.file_menu').stop(true,true).slideUp('medium');
  }
);

});jQuery('.menu-block').hover(function()
{
   jQuery('.menu-link').stop(true,true).slideUp('medium');
});*/