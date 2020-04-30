// $Id: uc_termsofservice.js,v 1.1.2.1 2009/11/08 20:05:07 pcambra Exp $

(function ($) {
  
Drupal.behaviors.uc_termsofservice_modalframe = function() {
  $('.uc_termsofservice-child:not(.modalframe-tos-processed)').addClass('modalframe-tos-processed').click(function() {
    var element = this;
    
    function onSubmitCallbackToS(args, statusMessages){
     if (args && args.tos_selected.agreed) {
       if (args.tos_selected.agreed == 'agreed') {
        $(".form-checkboxes input[id*='tos-agree-popup-agreed']").attr('checked', true);
       }
       else {
        $(".form-checkboxes input[id*='tos-agree-popup-agreed']").attr('checked', false);
       }
     }
    }
    
    // Build modal frame options.
    var modalOptions = {
      url: $(element).attr('href'),
      autoResize: true,
      onSubmit: onSubmitCallbackToS
    };

    // Try to obtain the dialog size from the className of the element.
    var regExp = /^.*uc_termsofservice-size\[\s*([0-9]*\s*,\s*[0-9]*)\s*\].*$/;
    if (typeof element.className == 'string' && regExp.test(element.className)) {
      var size = element.className.replace(regExp, '$1').split(',');
      modalOptions.width = parseInt(size[0].replace(/ /g, ''));
      modalOptions.height = parseInt(size[1].replace(/ /g, ''));
    }

    // Open the modal frame dialog.
    Drupal.modalFrame.open(modalOptions);
    
    // Prevent default action of the link click event.
    return false;
  });
};

})(jQuery);