
//   https://www.youtube.com/watch?v=x5A5S0hoyJ0

#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>


const char* ssid =     "SDFWAwifi";
const char* password = "dovetail";
const char* mqtt_server = "192.168.86.40";
long int lastMsg;
char* BGstatus;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  delay(100);
  Serial.begin(115200);


  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    MQTTconnect();
  }

  StaticJsonDocument<80> doc;
  char output[80];

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    /*
      float temp = bme.readTemperature();
      float pressure = bme.readPressure()/100.0;
      float humidity = bme.readHumidity();
      float gas = bme.readGas()/1000.0;
      doc["t"] = temp;
      doc["p"] = pressure;
      doc["h"] = humidity;
      doc["g"] = gas;

      serializeJson(doc, output);
      Serial.println(output);

    */

    BGstatus = "true";
    client.publish ("/BlastGates/M00", BGstatus);
    BGstatus = "off";
    client.publish ("/BlastGates/M01", BGstatus);
    Serial.println ( BGstatus);
    delay (10000);
    
    BGstatus = "false";
    client.publish ("/BlastGates/M00", BGstatus);
    BGstatus = "on";
    client.publish ("/BlastGates/M01", BGstatus);
    Serial.println ( BGstatus);
    delay (10000);

  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}


void MQTTconnect () {
  while (!client.connected()) {
    client.connect("Blast Gates", "blastgates", "LetBGin1952!");

    delay(5000);
    if (client.connected())
    {
      Serial.println ("MQTT Connected!");
    }
    if (!client.connected()) {
      Serial.println ("MQTT  NOT  Connected!");
    }
  }
}
