
/* --------------------------------------------- 

* Filename:     custom.js
* Version:      1.0.0 (2014-10-14)
* Website:      http://www.zymphonies.com
                http://www.freebiezz.com
* Description:  System Js
* Author:       Zymphonies Dev Team
                info@zymphonies.com

-----------------------------------------------*/

jQuery(document).ready(function($) {
  $('.nav-toggle').click(function() {
    $('#main-menu div ul:first-child').slideToggle(250);
    return false;
  });
  if( ($(window).width() > 640) || ($(document).width() > 640) ) {
      $('#main-menu li').mouseenter(function() {
        $(this).children('ul').css('display', 'none').stop(true, true).slideToggle(250).css('display', 'block').children('ul').css('display', 'none');
      });
      $('#main-menu li').mouseleave(function() {
        $(this).children('ul').stop(true, true).fadeOut(250).css('display', 'block');
      })
        } else {
    $('#main-menu li').each(function() {
      if($(this).children('ul').length)
        $(this).append('<span class="drop-down-toggle"><span class="drop-down-arrow"></span></span>');
    });
    $('.drop-down-toggle').click(function() {
      $(this).parent().children('ul').slideToggle(250);
    });
  }

 jQuery(".action-links-field-collection-add > li > a").addClass("colorbox-load add-btn init-colorbox-load-processed cboxElement");
 jQuery(".field-collection-view-links > li > a").addClass("colorbox-load  edit-delete init-colorbox-load-processed cboxElement");


jQuery("#field-collection-item-form").prepend( '<div class="custom-error-mob">Mobile field is required.<a href="#" data-dismiss="alert" class="close">×</a></div><div class="custom-error-fm-cnt">Family contact field is required.<a href="#" data-dismiss="alert" class="close">×</a></div>' );
jQuery("#field-collection-item-form .custom-error-mob").hide();
jQuery("#field-collection-item-form .custom-error-fm-cnt").hide();
jQuery('#field-collection-item-form #edit-submit').click(function () {
var aaa = document.getElementById("edit-field-mobile-no-und-0-value").value;
if(jQuery.isNumeric(aaa))
  {
    
  }
  else{
    jQuery("#field-collection-item-form .custom-error-mob").show();
    jQuery(window).scrollTop(0);
    return false;
  }

});
});



























