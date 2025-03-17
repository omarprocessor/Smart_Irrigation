#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

const char *ssid = "ESP8266_AP";
const char *password = "12345678";

WiFiServer server(80);
SoftwareSerial sim800l(D5, D6); // RX, TX

void setup()
{
    WiFi.softAP(ssid, password);
    server.begin();
    sim800l.begin(9600);
}

void loop()
{
    WiFiClient client = server.available();
    if (client)
    {
        String request = client.readStringUntil('\r');
        client.flush();

        if (request.indexOf("/average") != -1)
        {
            float avgBrightness = 512;
            float avgTemperature = 25;
            float avgHumidity = 60;
            float avgSoilWetness = 300;

            String json = "{";
            json += "\"avg_brightness\": " + String(avgBrightness) + ",";
            json += "\"avg_temperature\": " + String(avgTemperature) + ",";
            json += "\"avg_humidity\": " + String(avgHumidity) + ",";
            json += "\"avg_soil_wetness\": " + String(avgSoilWetness);
            json += "}";

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json");
            client.println("Connection: close");
            client.println();
            client.println(json);
        }
        else
        {
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
            html += "<div class='box' id='brightness'>&#9728; Brightness: 512</div>";
            html += "<div class='box' id='temperature'>&#127777; Temperature: 25°C</div>";
            html += "<div class='box' id='humidity'>&#128167; Humidity: 60%</div>";
            html += "<div class='box' id='soil'>&#127793; Soil Moisture: 300</div>";
            html += "</div>";
            html += "<p>Last Irrigation: 2 hours ago</p>";
            html += "<p>Last SMS Request: 30 minutes ago</p>";
            html += "</body></html>";

            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            client.println(html);
        }
    }

    if (sim800l.available())
    {
        String message = sim800l.readString();
        if (message.indexOf("GET DATA") != -1)
        {
            String response = "Brightness: 512\nTemperature: 25C\nHumidity: 60%\nSoil Moisture: 300";
            sim800l.println("AT+CMGF=1");
            delay(100);
            sim800l.println("AT+CMGS=\"+1234567890\"");
            delay(100);
            sim800l.print(response);
            sim800l.write(26);
        }
    }
}
