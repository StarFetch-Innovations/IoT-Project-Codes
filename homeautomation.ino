#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ---------- CONFIG ----------
const char* ap_ssid = "NodeMCU-AP";
const char* ap_pass = "12345678";

const int LED1_PIN = D4; // GPIO2 (active LOW)
const int LED2_PIN = D3; // GPIO0 (active LOW)

ESP8266WebServer server(80);
// ----------------------------

String htmlPage = R"rawliteral(
<!doctype html>
<html>
<head>
  <meta name="viewport" content="width=device-width,initial-scale=1">
  <title>NodeMCU - 2 LEDs</title>
  <style>
    body{font-family:Arial;text-align:center;padding:16px}
    button{font-size:18px;padding:10px 16px;margin:8px}
    .row{margin:12px}
    #status{margin-top:14px;font-weight:bold}
  </style>
</head>
<body>
  <h2>NodeMCU — Control 2 LEDs</h2>

  <div class="row">
    <h3>LED1 (D4)</h3>
    <button onclick="fetch('/led1/on')">LED1 ON</button>
    <button onclick="fetch('/led1/off')">LED1 OFF</button>
  </div>

  <div class="row">
    <h3>LED2 (D3)</h3>
    <button onclick="fetch('/led2/on')">LED2 ON</button>
    <button onclick="fetch('/led2/off')">LED2 OFF</button>
  </div>

  <div id="status">Loading status...</div>

<script>
function updateStatus(){
  fetch('/status').then(r => r.json()).then(j => {
    document.getElementById('status').innerText =
      'LED1: ' + (j.led1 ? 'ON' : 'OFF') + '  |  LED2: ' + (j.led2 ? 'ON' : 'OFF');
  }).catch(e => {
    document.getElementById('status').innerText = 'Cannot reach device';
  });
}
setInterval(updateStatus, 1000);
window.onload = updateStatus;
</script>
</body>
</html>
)rawliteral";

// ---------- HANDLERS ----------
void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

// Active LOW logic: LOW = ON, HIGH = OFF
void handleLed1On(){
  digitalWrite(LED1_PIN, LOW);
  server.send(200, "text/plain", "OK");
}
void handleLed1Off(){
  digitalWrite(LED1_PIN, HIGH);
  server.send(200, "text/plain", "OK");
}
void handleLed2On(){
  digitalWrite(LED2_PIN, LOW);
  server.send(200, "text/plain", "OK");
}
void handleLed2Off(){
  digitalWrite(LED2_PIN, HIGH);
  server.send(200, "text/plain", "OK");
}

void handleStatus(){
  bool s1 = (digitalRead(LED1_PIN) == LOW); // LOW means ON
  bool s2 = (digitalRead(LED2_PIN) == LOW);
  String json = "{\"led1\":" + String(s1 ? "true":"false") +
                ",\"led2\":" + String(s2 ? "true":"false") + "}";
  server.send(200, "application/json", json);
}
// ----------------------------

void setup(){
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Start with LEDs OFF (active LOW)
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);

  WiFi.softAP(ap_ssid, ap_pass);
  Serial.println();
  Serial.println("Started AP:");
  Serial.print("SSID: "); Serial.println(ap_ssid);
  Serial.print("IP: "); Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/led1/on", HTTP_GET, handleLed1On);
  server.on("/led1/off", HTTP_GET, handleLed1Off);
  server.on("/led2/on", HTTP_GET, handleLed2On);
  server.on("/led2/off", HTTP_GET, handleLed2Off);
  server.on("/status", HTTP_GET, handleStatus);

  server.begin();
}

void loop(){
  server.handleClient();
}