
var UCOI = UCOI || {};

/**
 * Initialize.
 */
UCOI.init = function() {
  var size = Drupal.settings.UCOI.size;   
  this.images = Drupal.settings.UCOI.images; 
  this.effect = Drupal.settings.UCOI.effect;
  this.noimage = Drupal.settings.UCOI.noimage;
  this.attributes = Drupal.settings.UCOI.attributes;
  this.defaultSize = Drupal.settings.UCOI.default_size;
  
  // Selects                                      
  $('.add-to-cart select.form-select').change(function(){
    if (aid = UCOI.getAID(this)){
      UCOI.switchImage(aid, this, size);  
    }
  });
  
  // Radios                                      
  $('.add-to-cart .form-radios input').click(function(){
    if (aid = UCOI.getAID(this)){
      UCOI.switchImage(aid, this, size);  
    }
  });
};

/**
 * Switch an option image.
 */
UCOI.switchImage = function(aid, input, size) {
  var pid = $(input).parents('.node').attr('id');
  var nid = pid.replace('node-', '');             
  var oid = $(input).val(); 
  var image = $(input).parents('.content').children('img.uc-option-image');       
          
  // Make sure we have permission to switch this attribute
  if (this.attributes[aid] === 0){
    return;
  }
          
  try {          
    var images = this.images[nid][aid];
    
    if (images[oid].derivative){ 
      this.switchImageEffect(image, images[oid].derivative);
    } 
  }
  catch (e){   
    this.switchImageEffect(image, this.noimage); 
  }
};

/**
 * Switch the imagepath based on the selected effect.
 */
UCOI.switchImageEffect = function(image, imagepath) {
  switch(this.effect){
    case 'fade':
      $(image).fadeOut(200, function(){
        $(this).attr('src', imagepath).fadeIn(200);
      });
      break;
      
    default:
      $(image).attr('src', imagepath); 
  }
};

/**
 * Get attribute AID from an input.
 */
UCOI.getAID = function(input) {
  var name = $(input).attr('name');
  return name.match(/attributes\[([0-9]+)\]/)[1]; 
};

if (Drupal.jsEnabled) {
  $(function(){
    UCOI.init();
  });
}