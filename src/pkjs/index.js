function getStopTimes(stopId){
    if(!stopId){
      //Forcing it to the airport stop for testing
      stopId = '40110';
    }
    var url = 'http://myrfta.com/bustime/eta/getStopPredictionsETA.jsp?route=all&stop=' + stopId;    
    var req = new XMLHttpRequest();
  
    req.open('GET', url, true);
    req.onload = function(e) {
        if (req.readyState == 4) {
            if (req.status == 200) {
//               console.log(req.responseText);
              //Parse the XML response
              console.log(req.responseXML);
	            parseBusInfo(req.responseXML);
            }
            else {
                console.log("Error getting bus times for stop: " + stopId);
            }
        }
    };
    req.send(null);
}

function parseBusInfo(xmlObj){
	var jsonObj = xmlToJson(xmlObj);
	var active, route, eta;
	
  //Loop through all of the upcoming busses
	for(var index = 0; index < jsonObj.stop.pre.length; index++){
		active = jsonObj.stop.pre[index];
		route = active.rn.text;
		eta = active.pt.text + ' ' + active.pu.text;
		console.log(route + ': ' + eta);
	}
}

// Changes XML to JSON
function xmlToJson(xml) {
  console.log("THE XML:");
  console.log(xml);
	// Create the return object
	var obj = {};
	if (xml.nodeType == 1) { // element
		// do attributes
		if (xml.attributes.length > 0) {
		obj["@attributes"] = {};
			for (var j = 0; j < xml.attributes.length; j++) {
				var attribute = xml.attributes.item(j);
				obj["@attributes"][attribute.nodeName] = attribute.nodeValue;
			}
		}
	} else if (xml.nodeType == 3) { // text
		obj = xml.nodeValue;
	}

	// do children
	if (xml.hasChildNodes()) {
		for(var i = 0; i < xml.childNodes.length; i++) {
			var item = xml.childNodes.item(i);
			
			//Getting rid of the pesky hashtag (seb 11/19/2017)
			var nodeName = item.nodeName.replace('#', '');

			if (typeof(obj[nodeName]) == "undefined") {
				obj[nodeName] = xmlToJson(item);
			} else {
				if (typeof(obj[nodeName].push) == "undefined") {
					var old = obj[nodeName];
					obj[nodeName] = [];
					obj[nodeName].push(old);
				}
				obj[nodeName].push(xmlToJson(item));
			}
		}
	}
	return obj;
}


Pebble.addEventListener("ready", function(e){
  console.log("Ready for interaction");
  getStopTimes();
});

Pebble.addEventListener("showConfiguration", function(e){
  Pebble.openURL("https://austinsparkleague.github.io/webpage_example/");
});

Pebble.addEventListener("webviewclosed", function(e){
  if(e.response){
    console.log("Got a message: " + e.response);
    Pebble.sendAppMessage(JSON.parse(e.response));
  }
});




Pebble.addEventListener("appmessage", function(e){
  console.log("Got getWeather with text: " + JSON.stringify(e.payload.getWeather));
  
  getWeatherFromLocation(e.payload.getWeather);
  
//   var object = {
//     testkey: 0
//   };
  
//   Pebble.sendAppMessage(object);

});