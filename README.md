# Smart Irrigation System

## Overview
This project integrates an ESP8266 Wi-Fi module with a SIM800L GSM module to provide real-time monitoring for smart irrigation. The ESP8266 acts as a web server displaying sensor data, while the SIM800L module enables users to request data via SMS.

## Features
- **Web Interface**: Users can view environmental data such as brightness, temperature, humidity, and soil wetness via a simple and responsive web page.
- **SMS Data Retrieval**: Users can send an SMS with the text "GET DATA" to receive the latest sensor readings via SMS.
- **Access Point Mode**: The ESP8266 operates as a Wi-Fi access point, eliminating the need for an external network.
- **Smart Irrigation Control**: Uses sensor data to optimize watering schedules for improved efficiency.

## Hardware Requirements
- ESP8266 (NodeMCU or similar)
- SIM800L GSM Module
- Sensors (LDR for brightness, DHT11 for temperature and humidity, soil moisture sensor)
- Power supply (5V for ESP8266, 4.2V for SIM800L)

## Installation
1. Flash the provided firmware onto the ESP8266 using Arduino IDE.
2. Connect the SIM800L module to the ESP8266.
3. Power up the system and access the web interface via the ESP8266 AP.
4. Send "GET DATA" via SMS to receive sensor readings.

## Usage
- Connect to the ESP8266 AP and open the web interface.
- Send an SMS with "GET DATA" to retrieve sensor readings via SMS.
- View live sensor data directly from the web interface.
- Use sensor readings to manage irrigation schedules efficiently.

## API Endpoints
- `/` - Displays sensor data on the web interface.
- `/average` - Returns JSON-formatted average sensor readings.

## Future Improvements
- Implement real-time graphing for sensor values.
- Add more SMS commands for system control.
- Improve power efficiency for remote deployments.
- Integrate automated irrigation control based on sensor data.
