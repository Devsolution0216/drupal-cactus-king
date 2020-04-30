/*!
 * Nokia Mobile Theme Javascript for high-end browsers, based on the original
 * Nokia Mobile Web Templates v0.5
 *
 * For more details see:
 * http://www.forum.nokia.com/Technology_Topics/Web_Technologies/Browsing/Web_Templates/
 *
 * @copyright Copyright Nokia
 * @license http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt GPL Version 2.0
 */


/*
 * AccordionList(string:id, callback:function)
 * usage: myAccordianList = new AccordianList(id, callback);
 * - id 'foo' can also be an array such as ids['foo','bar']
 * - callback (optional) function is triggered when a <dt> within the list is clicked
 *   and passes a reference to itself to the defined callback function.
 */
 
function AccordionList(_id, _callback) {
	var id = new Array();
	var callback;
	(!_isArray(_id))?id.push(_id):id=_id;
	(typeof _callback=="function")?callback=_callback:callback=function(){};
	
	for (var x=0;x<id.length;x++) {
		var dl = document.getElementById(id[x]);
		var dt = dl.getElementsByTagName("dt");
		for (var j=0; j < dt.length; j++) {
			var state = dt[j].getAttribute("class");
			// no classes defined, add class attribute with value 'collapsed'
			if (state == null) {
				dt[j].setAttribute("class", "collapsed");
				state = dt[j].getAttribute("class");
			}
			var expanded = state.search(/expanded/)+1;
			
			// find corresponding dd element
			var dd = dt[j];
			do dd = dd.nextSibling;
				while (dd && dd.nodeType != 1);
			(expanded)? dd.style['display'] = "block" : dd.style['display'] = "none" ;
			
			dt[j].onclick = function() {
				var dd = this;
				var state = this.getAttribute("class");
				var expanded = state.search(/expanded/)+1;
				var toggle;
				(expanded) ? toggle = state.replace(/expanded/, "collapsed") : toggle = state.replace(/collapsed/, "expanded") ;
				this.setAttribute("class", toggle);
				
				do dd = dd.nextSibling;
					while (dd && dd.nodeType != 1);
				(dd.style['display'] == "none")? dd.style['display'] = "block" : dd.style['display'] = "none" ;
				callback(this);
			}
		}	
	}
}

/*
 * styleTweaker()
 * usage: myStyleTweaker = new styleTweaker();
 * id can also be an array such as ids['foo','bar'…]
 * 
 */
 
function StyleTweaker() {
	this.ua = navigator.userAgent;
	this.tweaks = new Object();
}

StyleTweaker.prototype.add = function(_string, _stylesheet) {
	this.tweaks[_string] = _stylesheet;
}

StyleTweaker.prototype.remove = function(_term) {
	for (var _string in this.tweaks) {
		var exists = false;
		(_string == _term)?exists=true:false;
		(this.tweaks[_string])?exists=true:false;
		(exists)?delete this.tweaks[_string]:false;
	}
}

StyleTweaker.prototype.tweak = function() {
	for (var _string in this.tweaks) {
		if (this.ua.match(_string)) {
			loadStylesheet(this.tweaks[_string]);
		}
	}
}

StyleTweaker.prototype.untweak = function() {
	for (var _string in this.tweaks) {
		if (this.ua.match(_string)) {
			removeStylesheet(this.tweaks[_string]);
		}
	}
}

/*
 * _isArray()
 * usage: _isArray(object);
 * 
 */
function _isArray(x){
	return ((typeof x == "object") && (x.constructor == Array));
}

/*
 * addEvent()
 * usage: addEvent(event, function);
 * note: only targets window events!
 * 
 */

function addEvent(_event, _function) {
	var _current_event = window[_event];
	if (typeof window[_event] != 'function') {
		window[_event] = _function;
	} else {
		window[_event] = function() {
			_current_event();
			_function();
		}
	}
}

/*
 * loadStylesheet(file)
 * usage: loadStylesheet(filename.css);
 * 
 */
 
function loadStylesheet(filename) {
	var head = document.getElementsByTagName('head')[0];
	var link = document.createElement("link");
	link.setAttribute("rel", "stylesheet");
	link.setAttribute("type", "text/css");
	link.setAttribute("href", filename);
	head.appendChild(link);
}

/*
 * removeStylesheet(file)
 * usage: removeStylesheet(filename.css);
 * 
 */
 
function removeStylesheet(filename) {
	var stylesheets=document.getElementsByTagName("link");
	for (var i=stylesheets.length; i>=0; i--) { 
		if (stylesheets[i] && stylesheets[i].getAttribute("href")!=null && stylesheets[i].getAttribute("href").indexOf(filename)!=-1) {
			stylesheets[i].parentNode.removeChild(stylesheets[i]); 
		}
	}
}