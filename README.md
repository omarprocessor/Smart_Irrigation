# Smart Irrigation System

## Introduction
The **Smart Irrigation System** integrates an ESP8266 Wi-Fi module with a SIM800L GSM module to provide real-time monitoring for efficient irrigation management. The ESP8266 functions as a web server displaying sensor data, while the SIM800L module enables users to retrieve sensor data via SMS.

### Deployed Project
[Live Project Link](#) *https://omarprocessor.tech/*

### Blog Article
[Final Project Blog](#) *(Replace with actual blog link)*

### Author(s)
- **Omar Abdirashid Mohumed(#)** *https://www.linkedin.com/in/omar_processor*

## Features
- **Web Interface**: Displays real-time environmental data, including brightness, temperature, humidity, and soil wetness.
- **SMS Data Retrieval**: Users can send "GET DATA" via SMS to receive current sensor readings.
- **Access Point Mode**: The ESP8266 operates as a Wi-Fi AP, eliminating dependency on external networks.
- **Smart Irrigation Control**: Uses sensor data to optimize watering schedules for efficiency.

## Hardware Requirements
- **ESP8266** (NodeMCU or similar)
- **SIM800L GSM Module**
- **Sensors**:
  - LDR (Light-dependent resistor) for brightness
  - DHT11 for temperature and humidity
  - Soil moisture sensor
- **Power Supply**:
  - 5V for ESP8266
  - 4.2V for SIM800L

## Installation
1. Flash the provided firmware onto the ESP8266 using **Arduino IDE**.
2. Connect the SIM800L module to the ESP8266.
3. Power up the system and access the web interface via the ESP8266 AP.
4. Send "GET DATA" via SMS to receive sensor readings.

## Usage
- **Web Interface**: Connect to the ESP8266 AP and access the web UI to view sensor data.
- **SMS Commands**: Send "GET DATA" via SMS to receive sensor readings.
- **Irrigation Management**: Use real-time sensor readings to optimize irrigation schedules.

## API Endpoints
- `/` - Displays sensor data on the web interface.
- `/average` - Returns JSON-formatted average sensor readings.

## Contributing
We welcome contributions to improve this project. To contribute:
1. Fork the repository.
2. Create a new branch.
3. Implement your changes.
4. Submit a pull request for review.

## Related Projects
- Traffic Light for Persons with disabilities(#) *https://github.com/bozize/PWD*
  


## Future Improvements
- Implement real-time graphing for sensor values.
- Add more SMS commands for system control.
- Improve power efficiency for remote deployments.
- Integrate automated irrigation control based on sensor data.

## License
This project is licensed under the **MIT License**. See [LICENSE](#) for details.

