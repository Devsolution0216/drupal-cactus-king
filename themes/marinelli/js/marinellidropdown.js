
//Marinelli jQuery Drop Down Menu (uses hoverIntent jquery plugin (http://cherne.net/brian/resources/jquery.hoverIntent.html)

$(document).ready(function(){

// add some markup

$('#plinks li.expanded > a').addClass("primoespanso");
$('#plinks li.expanded ul li.expanded > a').addClass('espanso');
$('#plinks li.expanded > ul').addClass('primosottolivello');
$('#plinks li.expanded ul li a').removeClass('active');
$('#plinks li.expanded ul li.expanded > ul').removeClass('primosottolivello').addClass('sottolivello'); 


// show & hide functions

function mostra(){
	$(this).children('.primosottolivello, .sottolivello').show(); 
	}
	
function nascondi(){
	$(this).children('.primosottolivello, .sottolivello').hide();	
	}
	
// set some options	for the hover effect

var config = {    
     sensitivity: 5, // number = sensitivity threshold (must be 1 or higher)    
     interval: 100, // number = milliseconds for onMouseOver polling interval    
     over: mostra, // function = onMouseOver callback (REQUIRED)    
     timeout: 200, // number = milliseconds delay before onMouseOut    
     out: nascondi // function = onMouseOut callback (REQUIRED)    
};

	 
     $('#plinks li.expanded').hoverIntent(config);
});