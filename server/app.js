var SerialPort = require("serialport");

var request = require('request');


var port = new SerialPort("COM3", {
    baudRate: 115200,
    parser: SerialPort.parsers.readline('\n')
});

port.on('data', function (data) {
    console.log(data)
    try {
        var obj = JSON.parse(data);
        if (obj) {
            request('http://davideandreazzini.co.uk:3999/data/'+obj.h+'/'+obj.t, function (error, response, body) {                
                if (!error && response.statusCode == 200) {
                    console.log(body) // Show the HTML for the Google homepage. 
                }
            })
        }
    } catch (e) {
        console.log(e)
    }


});