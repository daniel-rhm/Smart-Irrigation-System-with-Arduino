# Smart-Irrigation-System-with-Arduino
An intelligent automatic plant watering system built with Arduino Uno. The system monitors soil moisture and waters the plant only when needed, with clear stage-by-stage feedback on an LCD display and status LEDs.

# Smart Irrigation System with Arduino

An intelligent automatic plant watering system built with Arduino Uno. The system monitors soil moisture and waters the plant only when needed, with clear stage-by-stage feedback on an LCD display and status LEDs.

## Demo Video

https://www.youtube.com/watch?v=HNAig2dBwsg

## Features

- Capacitive soil moisture sensor for accurate measurement
- Automatic watering with relay-controlled water pump
- 4-stage operation with clear feedback:
  - **Stage 1**: Soil is dry (30-second delay before action)
  - **Stage 2**: Preparing to water (10-second warning)
  - **Stage 3**: Watering in progress (yellow LED blinking)
  - **Stage 4**: Ideal soil condition (green LED)
- 16x2 LCD with I2C interface for real-time status display
- Visual feedback using red, yellow, and green LEDs
- Hysteresis to prevent rapid on/off cycling
- **Custom minimal power supply**: Powered directly from a standard phone charger and USB cable (no external adapter needed)

## Components Used

- Arduino Uno
- Capacitive Soil Moisture Sensor (v1.2 or similar)
- 16x2 LCD with I2C backpack (address 0x27)
- 5V single-channel relay module
- Small 5V DC water pump
- LEDs (Red, Yellow, Green) with 220Ω resistors
- Breadboard and jumper wires
- Power supply: Standard phone charger + USB cable (custom minimal design)

## Pin Connections

| Component                | Arduino Pin |
|--------------------------|-------------|
| LCD I2C SDA              | A4          |
| LCD I2C SCL              | A5          |
| Soil Moisture Sensor     | A2          |
| Relay Module             | 5           |
| Red LED                  | 2           |
| Yellow LED               | 3           |
| Green LED                | 4           |

## Circuit Photos & Components Photos

![1767455563470](https://github.com/user-attachments/assets/8f0faaa6-d2c5-425e-822e-d29fa299d883)
![1767455563478](https://github.com/user-attachments/assets/c4ab4da3-622b-4d5f-b686-9a787a004da3)
![1767455563464](https://github.com/user-attachments/assets/6dafc2cd-9bc2-488c-8bb4-af34257a2f3c)
![1767455563447](https://github.com/user-attachments/assets/0c103e9e-2918-49f9-a97d-69fd06854c51)
![1767455563432](https://github.com/user-attachments/assets/2d0ff708-9916-400b-97db-935195d70ddc)
![1767455563427](https://github.com/user-attachments/assets/3ad2d808-a459-4078-83f7-d35657887c58)
![1767455563421](https://github.com/user-attachments/assets/611189d1-7c34-466b-b4eb-02dda169f1be)


## Calibration

- Dry soil raw value: ~462 (0%)
- Wet soil raw value: ~160 (100%)
- Dry threshold: <30%
- Good threshold: >60%


## Future Improvements

- Add ESP32/ESP8266 for WiFi connectivity and remote monitoring
- Web dashboard or mobile app control (Blynk/ThingSpeak)
- Temperature and ambient humidity sensor integration
- Scheduled watering mode
- Data logging to SD card or cloud

## Author

Danail Rahmani  
Arduino & Embedded Systems Enthusiast

Feel free to fork, modify, and improve the project! 🌱💧
