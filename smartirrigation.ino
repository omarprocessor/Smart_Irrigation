#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <DHT.h>

// Wi-Fi Access Point credentials
const char *ssid = "ESP8266_AP";
const char *password = "12345678";

// Create a web server on port 80
WiFiServer server(80);

// Define software serial for SIM800L module (D5 = RX, D6 = TX)
SoftwareSerial sim800l(D5, D6);

// Sensor Pins
#define DHTPIN D4  // DHT11 data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define LDRPIN A0     // LDR connected to analog pin A0
#define SOILPIN D3    // Soil moisture sensor connected to D3

void setup()
{
    // Start the ESP8266 as an Access Point
    WiFi.softAP(ssid, password);
    server.begin();  // Start the web server

    // Initialize SIM800L communication
    sim800l.begin(9600);

    // Initialize sensors
    dht.begin();
    pinMode(SOILPIN, INPUT);
}

void loop()
{
    // Read sensor values
    int brightness = analogRead(LDRPIN);        // LDR sensor (0-1023)
    float temperature = dht.readTemperature();  // DHT11 temperature (°C)
    float humidity = dht.readHumidity();        // DHT11 humidity (%)
    int soilMoisture = digitalRead(SOILPIN);    // Soil moisture (0 or 1)

    // Check for incoming web clients
    WiFiClient client = server.available();
    if (client)
    {
        String request = client.readStringUntil('\r'); // Read HTTP request
        client.flush();

        // Handle request for the average sensor data API endpoint
        if (request.indexOf("/average") != -1)
        {
            // Create a JSON response
            String json = "{";
            json += "\"avg_brightness\": " + String(brightness) + ",";
            json += "\"avg_temperature\": " + String(temperature) + ",";
            json += "\"avg_humidity\": " + String(humidity) + ",";
            json += "\"avg_soil_wetness\": " + String(soilMoisture);
            json += "}";

            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json");
            client.println("Connection: close");
            client.println();
            client.println(json);
        }
        else // Default web interface with sensor values
        {
            // HTML response with styled sensor values
            String html = "<html><head>";
            html += "<title>Smart Irrigation</title>";
            html += "<style>";
            html += "body{text-align:center;font-family:Arial;background-color:#f4f4f4;padding:20px;}";
            html += ".container{display:flex;justify-content:center;flex-wrap:wrap;gap:20px;}";
            html += ".box{width:200px;padding:20px;border-radius:10px;color:#fff;font-size:22px;font-weight:bold;display:flex;align-items:center;justify-content:center;gap:10px;}";
            html += "#brightness{background-color:#ffcc00;}";
            html += "#temperature{background-color:#ff5733;}";
            html += "#humidity{background-color:#3498db;}";
            html += "#soil{background-color:#2ecc71;}";
            html += "</style>";
            html += "</head><body>";
            html += "<h2>Smart Irrigation</h2>";
            html += "<div class='container'>";
            html += "<div class='box' id='brightness'>&#9728; Brightness: " + String(brightness) + "</div>";
            html += "<div class='box' id='temperature'>&#127777; Temperature: " + String(temperature) + "°C</div>";
            html += "<div class='box' id='humidity'>&#128167; Humidity: " + String(humidity) + "%</div>";
            html += "<div class='box' id='soil'>&#127793; Soil Moisture: " + String(soilMoisture == 0 ? "Wet" : "Dry") + "</div>";
            html += "</div>";
            html += "<p>Last Irrigation: 2 hours ago</p>";
            html += "<p>Last SMS Request: 30 minutes ago</p>";
            html += "</body></html>";

            // Send HTTP response headers
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(html);
        }
    }

    // Check if SIM800L has received an SMS message
    if (sim800l.available())
    {
        String message = sim800l.readString(); // Read incoming message
        if (message.indexOf("GET DATA") != -1) // If message contains "GET DATA"
        {
            // Sensor values to be sent via SMS
            String response = "Brightness: " + String(brightness) + "\n";
            response += "Temperature: " + String(temperature) + "C\n";
            response += "Humidity: " + String(humidity) + "%\n";
            response += "Soil Moisture: " + String(soilMoisture == 0 ? "Wet" : "Dry");

            // Send SMS via SIM800L
            sim800l.println("AT+CMGF=1"); // Set SMS mode
            delay(100);
            sim800l.println("AT+CMGS=\"+1234567890\""); // Replace with recipient number
            delay(100);
            sim800l.print(response); // Send sensor data
            sim800l.write(26); // End SMS (CTRL+Z)
        }
    }
}
