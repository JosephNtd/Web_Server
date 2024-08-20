#include <WiFi.h>

#include <WebServer.h>

const char* ssid = "Two Girls One Router_2G";
const char* password = "T@hp!@#$";

const byte DNS_PORT = 53;
const int red = 12;   
const int green = 13; 
const int blue = 14;  

WebServer webServer(80);

String webpage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
            .slidecontainer {
            width: 100%;
            }

            .slider {
            -webkit-appearance: none;
            width: 15%;
            height: 25px;
            border-radius: 20px;
            background: #f10808;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
            }

            .slider:hover {
            opacity: 1;
            }

            .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            border-radius: 25px;
            width: 25px;
            height: 25px;
            background: #ffffff;
            cursor: pointer;
            }

            .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            background: #2304aa;
            cursor: pointer;
            }

            .slider_green {
            -webkit-appearance: none;
            width: 15%;
            height: 25px;
            border-radius: 20px;
            background: #00ff08;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
            }

            .slider_green:hover {
            opacity: 1;
            }

            .slider_green::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            border-radius: 25px;
            width: 25px;
            height: 25px;
            background: #ffffff;
            cursor: pointer;
            }

            .slider_green:-moz-range-thumb {
            width: 25px;
            height: 25px;
            background: #04AA6D;
            cursor: pointer;
            }
            .slider_blue {
            -webkit-appearance: none;
            width: 15%;
            height: 25px;
            border-radius: 20px;
            background: #3700ff;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
            }

            .slider_blue:hover {
            opacity: 1;
            }

            .slider_blue::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            border-radius: 25px;
            width: 25px;
            height: 25px;
            background: #ffffff;
            cursor: pointer;
            }

            .slider_green:-moz-range-thumb {
            width: 25px;
            height: 25px;
            background: #04AA6D;
            cursor: pointer;
            }
        </style>
</head>
<body>

    <h1>RGB Range Slider</h1>
    <p>Drag the slider to display the 3-Color value.</p>

    <div class="slidecontainer">
        <p><input type="range" min="0" max="255" value="125" class="slider" id="red">
            Value: <span id="x"></span></p>  
        <p><input type="range" min="0" max="255" value="125" class="slider_green" id="green">
            Value: <span id="y"></span></p>  
        <p><input type="range" min="0" max="255" value="125" class="slider_blue" id="blue">
            Value: <span id="z"></span></p> 
        <script>
            var slider1        = document.getElementById("red");
            var slider2        = document.getElementById("green");
            var slider3        = document.getElementById("blue");
            var output_red         = document.getElementById("x");
            var output_green       = document.getElementById("y");
            var output_blue       = document.getElementById("z");
            output_red.textContent    = slider1.value;
            output_green.textContent  = slider2.value;
            output_blue.textContent  = slider3.value;
            function Send_data(red, green, blue ){
                var params = [
                  'r=' + red,
                  'g=' + green,
                  'b=' + blue
                ].join('&');
                var req = new XMLHttpRequest();
                req.open('POST', '?' + params, true);
                req.send();
            }
            Send_data(slider1.value, slider2.value, slider3.value);
            slider1.oninput = function() {
                output_red.textContent  = this.value;
                Send_data(slider1.value, slider2.value, slider3.value);
            }
            slider2.oninput = function() {
                output_green.textContent  = this.value;
                Send_data(slider1.value, slider2.value, slider3.value);
            }
            slider3.oninput = function() {
                output_blue.textContent  = this.value;
                Send_data(slider1.value, slider2.value, slider3.value);
            }
        </script>
    </div>
</body>
</html>
)rawliteral";


void handleRoot() {
  String red_pin = webServer.arg(0); 
  String green_pin = webServer.arg(1);
  String blue_pin = webServer.arg(2);

  if((red_pin != "") && (green_pin != "") && (blue_pin != ""))
  { 
    analogWrite(red,   255 - red_pin.toInt());
    analogWrite(green, 255 - green_pin.toInt());
    analogWrite(blue,  255 - blue_pin.toInt());
  }
  Serial.print("Red: ");
  Serial.println(red_pin.toInt()); 
  Serial.print("Green: ");
  Serial.println(green_pin.toInt()); 
  Serial.print("Blue: ");
  Serial.println(blue_pin.toInt()); 
  Serial.println();

  webServer.send(200, "text/html", webpage);
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  delay(1000);
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());

  webServer.on("/", handleRoot);
  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
