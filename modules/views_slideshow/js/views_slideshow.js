// $Id: views_slideshow.js,v 1.2 2008/09/30 20:10:22 aaron Exp $

// store the timer and current div data
slideshow_data = new Array();

// this stores all our static data
function views_slideshow_data(num_divs, timer_delay, sort_order, fade, fade_speed, fade_value) {
//   this._divs = divs;
  this._num_divs = num_divs;
  this._timer_delay = timer_delay;
  this._sort_order = sort_order;
  this._fade = fade;
  this._fade_speed = fade_speed;
  this._fade_value = fade_value;
  this._current_div = 0;
  this._pause = false;
}

// set the timer on or off
function views_slideshow_timer(slideshow_main, slideshow_status) {
  // stop the current timer
  clearTimeout(slideshow_data[slideshow_main]._timer_id);

  // start a new timer, if slideshow_status is true, unless we're currently paused
  if (slideshow_status && !slideshow_data[slideshow_main]._pause) {
    // our timer will call views_slideshow_switch, which fades out the current slide
    slideshow_data[slideshow_main]._timer_id = setTimeout("views_slideshow_switch('" + slideshow_main + "', views_slideshow_next_div('" + slideshow_main + "'))", slideshow_data[slideshow_main]._timer_delay);
  }
}

function views_slideshow_pause(slideshow_main) {
  slideshow_data[slideshow_main]._pause = true;
  views_slideshow_timer(slideshow_main, false);
}

function views_slideshow_resume(slideshow_main) {
  slideshow_data[slideshow_main]._pause = false;
  views_slideshow_timer(slideshow_main, true);
}

// fade out to the new div indicated
function views_slideshow_switch(slideshow_main, new_div) {
  // get the id for the main element
  _main_div = "#views_slideshow_main_" + slideshow_main;

  // turn off our timer
  views_slideshow_timer(slideshow_main, false);

  // check to see if we fade or not
  if (slideshow_data[slideshow_main]._fade) {
    // fade out -- at the end, switch to the next slide in the slideshow
    $(_main_div).fadeTo(slideshow_data[slideshow_main]._fade_speed, slideshow_data[slideshow_main]._fade_value, function() { views_slideshow_set_div(slideshow_main, new_div); });
  }
  else {
    // if we don't have a fade, then just switch without fading
    views_slideshow_set_div(slideshow_main, new_div);
  }
}

// set the main div html to the new node
function views_slideshow_set_div(slideshow_main, new_div_number) {
  // this is the id of the main div to change
  _main_div = "#views_slideshow_main_" + slideshow_main;

  // if the new div is greater than length, wrap to the first.
  // if it's less than zero, wrap to the last
  if (new_div_number >= slideshow_data[slideshow_main]._num_divs) {
    new_div_number = 0;
  }
  else if (new_div_number < 0) {
    new_div_number = slideshow_data[slideshow_main]._num_divs - 1;
  }

//   _old_breakout = "#views_slideshow_div_breakout_teaser_" + slideshow_main + "_" + slideshow_data[slideshow_main]._current_div;
//   _new_breakout = "#views_slideshow_div_breakout_teaser_" + slideshow_main + "_" + new_div_number;
  _old_breakout = "#views_slideshow_div_" + slideshow_main + "_" + slideshow_data[slideshow_main]._current_div;
  _new_breakout = "#views_slideshow_div_" + slideshow_main + "_" + new_div_number;


  // get the div with the html we need
  _new_div = "#views_slideshow_div_" + slideshow_main + "_" + new_div_number;

  // set the html of the new div
  //   $(_main_div).html($(_new_div).html());
//   $(_old_breakout).removeClass('views_slideshow_active_teaser');
//   $(_new_breakout).addClass('views_slideshow_active_teaser');

  $(_old_breakout).hide();
  $(_new_breakout).show();

  _old_breakout = "#views_slideshow_div_breakout_teaser_" + slideshow_main + "_" + slideshow_data[slideshow_main]._current_div;
  _new_breakout = "#views_slideshow_div_breakout_teaser_" + slideshow_main + "_" + new_div_number;
  $(_old_breakout).removeClass('views_slideshow_active_teaser');
  $(_new_breakout).addClass('views_slideshow_active_teaser');

  // set the current_div number to the new node
  slideshow_data[slideshow_main]._current_div = new_div_number;

  // check to see if we fade or not
  if (slideshow_data[slideshow_main]._fade) {
    // fade in -- at the end, turn on our timer
    $(_main_div).fadeTo(slideshow_data[slideshow_main]._fade_speed, 1, function() { views_slideshow_timer(slideshow_main, true); });
  }
  else {
    // if we don't have a fade, then just turn on our timer without fading
    views_slideshow_timer(slideshow_main, true);
  }
}

// get the next node div in our sequence
function views_slideshow_next_div(slideshow_main) {
  if (slideshow_data[slideshow_main]._sort_order) {
    // select the next div, in forward or reverse order
    new_div_number = slideshow_data[slideshow_main]._current_div + slideshow_data[slideshow_main]._sort_order;
  }
  else {
    // select a random div, but make sure we don't repeat ourselves, unless there's only one div
    do {
      new_div_number = Math.floor(Math.random() * slideshow_data[slideshow_main]._num_divs);
    } while (slideshow_data[slideshow_main]._num_divs > 1 && (new_div_number == slideshow_data[slideshow_main]._num_divs - 1));
  }
  return new_div_number;
}

