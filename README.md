# Wi-Protect - Wi-Fi Network Disruption Alert with Response + Location-Based Wi-Fi Access Control

![Meme](https://i.imgflip.com/2lxd4y.jpg)
*"When your ESP8266 spots an intruder trying to sneak onto the network."*

## Overview
This ESP8266-based project combines Wi-Fi network disruption detection with location-based access control. It monitors for deauthentication attacks (a form of Wi-Fi jamming), alerts users to disruptions, and restricts access based on device proximity to the ESP8266, providing an added layer of security.

---

## Disclaimer
This project is intended for educational and ethical use only. Unauthorized monitoring or disruption detection may be restricted in some regions. Use responsibly and with appropriate permissions. The authors are not responsible for any misuse or legal consequences.

---

## Features
- **Network Disruption Detection**: Monitors for jamming attempts by detecting deauthentication frames and provides alerts.
- **Location-Based Access Control**: Restricts network access based on signal strength (RSSI) to ensure only nearby devices have access.
- **LED Alerts**: Flashes an LED when a network disruption is detected.
- **Web Dashboard**: Real-time logs of detected disruptions and proximity-based access control status.

## Installation

### Requirements
- **ESP8266** (e.g., NodeMCU)
- **Arduino IDE** with ESP8266 library
- **LED** (optional, for visual alert)
- **Wi-Fi credentials** (SSID and password)

### Setup
1. **Install ESP8266 Board in Arduino IDE**:
   - Go to **File > Preferences**.
   - Add `http://arduino.esp8266.com/stable/package_esp8266com_index.json` under **Additional Board Manager URLs**.
   - Go to **Tools > Board > Board Manager**, search for **ESP8266**, and install.

2. **Wiring**:
   - Connect an LED to GPIO pin **D4** with a resistor (220 ohms recommended).
   - Connect the LED anode (longer leg) to **D4** and the cathode to **GND**.

3. **Upload the Code**:
   - Replace `primarySSID`, `primaryPassword` with your network details.
   - Select the **ESP8266 board** and **COM port** in **Tools**, then upload the code.

4. **Access the Web Interface**:
   - Connect a device to the ESP8266’s network.
   - Enter the ESP8266’s IP address (usually `192.168.4.1`) in a browser to access the web dashboard.

---

## How to Use
1. **Disruption Detection**:
   - The ESP8266 detects deauthentication frames and logs them.
   - An LED will flash if a network disruption is detected and reaches the threshold.

2. **Location-Based Access Control**:
   - The ESP8266 continuously measures signal strength (RSSI).
   - If a device is outside the defined proximity range, it will be disconnected from the network.

3. **Web Dashboard**:
   - Use the web interface to view the number of disruption packets detected and access control status based on proximity.

## Advantages
- Provides security against Wi-Fi disruptions by detecting jamming attempts.
- Adds a location-based access control, allowing only close-range devices.
- Real-time monitoring with web access for security insights.

## Disadvantages
- May falsely disconnect devices if they temporarily move out of proximity range.
- Detection limited to deauthentication frames, a specific jamming type.
- LED alert and disconnection response may not actively prevent attacks but provide awareness.

## License
This project is open-source and available under the MIT License.
