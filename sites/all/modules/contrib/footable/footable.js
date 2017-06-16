/**
 * @file
 * Javascript file for the FooTable module.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.footable = {
    attach: function (context, settings) {
      if ($('.footable', context).footable) {
        $('.footable', context).each(function () {
          var id = $(this).attr('id');
          $(this).on({
            'expand.ft.row': function (e, ft, row) {
              row.$el.addClass('expanded');
            },
            'collapse.ft.row': function (e, ft, row) {
              row.$el.removeClass('expanded');
            }
          }).footable(settings.footable[id]).on();
        });
      }
    }
  };
}(jQuery));
