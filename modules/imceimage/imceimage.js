/**
 * $Id: imceimage.js,v 1.1 2008/04/09 18:59:57 panis Exp $
 * imceimage javascript handler functions supporting the imceimage module
 */
var imceImage = {};

imceImage.initiate = function() {
}

imceImage.open = function (url, field) {
   imceImage.target = field;
   imceImage.pop = window.open(url, '', 'width=760,height=560,resizable=1');
   imceImage.pop['imceOnLoad'] = function (win) {
      win.imce.setSendTo(Drupal.t('Add image to @app', {'@app': Drupal.t('imceimage')}), imceImage.insert);
   }

   imceImage.pop.focus();
}

imceImage.insert = function (file, win) {
	win.close();
	
	fld = imceImage.target;
	var img = '#imceimagearea-' + fld;
	$(img).attr('src', file.url);
	$(img).attr('width', file.width);
	$(img).attr('height', file.height);

	/* form elements here. */
	$('#imceimagepath-' + fld).val(file.url);
	$('#imceimagewidth-' + fld).val(file.width);
	$('#imceimageheight-' + fld).val(file.height);
}


imceImage.remove = function(fld) {
	$('#imceimagepath-' + fld).val('');
	$('#imceimagewidth-' + fld).val(0);
	$('#imceimageheight-' + fld).val(0);
	$('#imceimagearea-' + fld).attr('src', 'blank.jpg');
}

