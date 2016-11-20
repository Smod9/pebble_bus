

function getStopTimes(stopId){
    if(!stopId){
      //Forcing it to the airport stop for testing
      stopId = 40110;
    }
    var url = 'http://myrfta.com/bustime/eta/getStopPredictionsETA.jsp?route=all&stop=' + stopId;    
    var req = new XMLHttpRequest();
  
    req.open('GET', url, true);
    req.onload = function(e) {
        if (req.readyState == 4) {
            if (req.status == 200) {
              //Parse the XML response
//               console.log(req);
	            parseBusInfo(req.responseText);
            }
            else {
                console.log("Error getting bus times for stop: " + stopId);
            }
        }
    };
    req.send(null);
}

function parseBusInfo(xmlObj){
	var upcomingBusesArry = xmlToJson(xmlObj);
	var active, route, eta;
	
	console.log("*************************");
	console.log("UPCOMING BUSSES:")
	var len = upcomingBusesArry.length;
	for(var index = 0; index < len; index++){
		active = upcomingBusesArry[index];
		route = active.rn;
		
		if(active.pt == "DELAYED"){
			eta = active.pt;
		}
		else{
			eta = active.pt + ' ' + active.pu;
		}
		console.log(route + ': ' + eta);
	}
}

/*
	* A custom function to parse xml text from this bus app to a json object
*/
// Changes XML to JSON
function xmlToJson(xmlString) {
	// Create the return object
	var responseArry = [];
	var buses;
	var tempArry = [];
	xmlString = xmlString.replace(/\r|\n|\t/g, "");
	
	//Split on pre, and remove this illegal thing they give me sometimes....
	buses = xmlString.replace('<![CDATA[&nbsp;]]>', '').split("<pre>");
	
	//Remove the first item in the array
	buses.shift();
	
	//Iterate over the buses to parse the info into json
	for(var bus = 0; bus < buses.length;  bus++){
		
		//Clear the tempArry
		tempArry = [];
		
		//remove the closing pre tag, and split on the less than sign
		buses[bus] = buses[bus].replace(/<\/pre>/g, '').split('<');
		// console.log(buses[bus]);
		//Loop through all of the individual properties for each upcoming bus
		var len = buses[bus].length;
		for(var prop = 0; prop < len;  prop++){
			//We ditch every odd item because of how we split
			if(prop%2 != 0){
				tempArry.push('"' + buses[bus][prop].replace(/>/g, '": "') + '"');
			}
		}
		var jsonStr = "\{" + tempArry.join() + "\}";
		// console.log(jsonStr);
		responseArry.push(JSON.parse(jsonStr));
	}
	
	//Return the whole array
	return responseArry;
}


function getRoutesList(){
    var url = 'http://myrfta.com/bustime/map/getStopsForRouteDirection.jsp?route=L&direction=DV';    
    var req = new XMLHttpRequest();
  
    req.open('GET', url, true);
    req.onload = function(e) {
        if (req.readyState == 4) {
            if (req.status == 200) {
				//Parse the XML response
				// console.log(req.responseText);
				parseRoutesList(req.responseText);
            }
            else {
                console.log("Error getting bus times for stop: " + stopId);
            }
        }
    };

    req.send(null);
}

function parseRoutesList(xmlObj){
	var routesArry = xmlToJsonRoutes(xmlObj);

	console.log("ROUNTES LIST:")
	var len = routesArry.length;
	for(var index = 0; index < len;  index++){
		console.log(JSON.stringify(routesArry[index]));
	}
	getStopTimes();	
}

/*
	* A custom function to parse xml text from this bus app to a json object
*/
// Changes XML to JSON
function xmlToJsonRoutes(xmlString) {
	// Create the return object
	var responseArry = [];
	var buses;
	var tempArry = [];
	var tempObj = {};
	
	//Remove any sort of new line or tab or...
	xmlString = xmlString.replace(/\r|\n|\t/g, "");
	
	//Split on stop, and remove this illegal thing they give me sometimes....
	buses = xmlString.replace('<![CDATA[&nbsp;]]\>', '--').split("<stop>");

	//Remove the first item in the array
	buses.shift();
	
	//Iterate over the buses to parse the info into json
	for(var bus = 0; bus < buses.length;  bus++){
		
		//Clear the tempArry
		tempArry = [];
		
		//remove the closing pre tag, and split on the less than sign
		buses[bus] = buses[bus].replace(/<\/stop>/g, '').split('<');
				
		//Loop through all of the individual properties for each upcoming bus
		var len = buses[bus].length;
		for(var prop = 0; prop < len;  prop++){
			//We ditch every odd item because of how we split
			if(prop%2 != 0){
				tempArry.push('"' + buses[bus][prop].replace(/>/g, '": "') + '"');
			}
		}
		
		//Use this to sanitize the object before grabbing it. Just take what you want
		tempObj = JSON.parse('{' + tempArry.join() + '}');
		responseArry.push({name:tempObj.name, id: tempObj.id});
	}
	
	//Return the whole array
	return responseArry;
}


/*PEBBLE EVENT LISTENERS*/

Pebble.addEventListener("ready", function(e){
  console.log("Ready for interaction");
  getRoutesList();
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