$(document).ready(function () {
  var parents = $('.vocabindex.tree .parent');
  parents.removeClass('expanded').addClass('collapsed').find('ul').hide();
  parents.children('a').click(function () {
    $(this).parent().toggleClass('collapsed').toggleClass('expanded').find('ul').eq(0).slideToggle('fast');
    return false;
  }).focus(function () {
    $(this).blur();
  });
});