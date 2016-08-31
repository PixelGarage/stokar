/**
 * This file contains all Drupal behaviours of the Apia theme.
 *
 * Created by ralph on 05.01.14.
 */

(function ($) {

  /**
   * This behavior adds shadow to header on scroll.
   *
  Drupal.behaviors.addHeaderShadow = {
    attach: function (context) {
      $(window).on("scroll", function () {
        if ($(window).scrollTop() > 10) {
          $("header.navbar .container").css("box-shadow", "0 4px 3px -4px gray");
          $("header.navbar .container-fluid").css("box-shadow", "0 4px 3px -4px gray");
        }
        else {
          $("header.navbar .container").css("box-shadow", "none");
          $("header.navbar .container-fluid").css("box-shadow", "none");
        }
      });
    }
  };
   */

  /**
   * Allows full size clickable items.
   */
   Drupal.behaviors.fullSizeClickableItems = {
    attach: function () {
      var $clickableItems = $('.view-zitate .views-row');

      $clickableItems.once('click', function () {
        $(this).on('click', function () {
          window.location = $(this).find("a:first").attr("href");
          return false;
        });
      });
    }
  };


  /**
   * Allows to add different intervals for each slide in a carousel.
   * The implementation uses a timer inside the slid-event to start and pause the carousel
   * according to the slide interval.
  Drupal.behaviors.intervalOfSlides = {
    attach: function() {
      var $carousel = $('#views-bootstrap-carousel-1'),
          $leftControl = $carousel.find('.carousel-control.left'),
          $rightControl = $carousel.find('.carousel-control.right'),
          startInterval = parseInt($carousel.find('.item.active').attr('data-interval'));

      //
      // start carousel with small interval (1000ms), which will be the default slide interval
      var timeout = setTimeout(function() {
        $carousel.carousel({interval: 1000});
      }, startInterval-1000);

      //
      // Add event handling of carousel
      // find interval time of displayed slide and set it
      $carousel.off('slid.bs.carousel');
      $carousel.on('slid.bs.carousel', function () {
        clearTimeout(timeout);
        var duration = parseInt($(this).find('.item.active').attr('data-interval'));

        // pause carousel until duration minus default interval has passed,
        // then start carousel again with default interval
        $carousel.carousel('pause');
        timeout = setTimeout(function() { $carousel.carousel(); }, duration-1000);
      });

      //
      // clear timeout if user clicks left/right control
      $leftControl.off('click');
      $leftControl.on('click', function(){
        clearTimeout(timeout);
      });

      $rightControl.off('click');
      $rightControl.on('click', function(){
        clearTimeout(timeout);
      });
    }
  }
   */


})(jQuery);
