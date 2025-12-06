# Arduino-Cloud-OTA-Test
Minimal test project to build firmware with PlatformIO and push OTA updates to the Arduino UNO R4 via Arduino Cloud CLI

- Install arduino-cli
- Install arduino-cloud-cli
- Add to PATH
- arduino-cli core install arduino:renesas\_uno
- arduino-cloud-cli credentials init
- plug in board
- arduino-cloud-cli device create --name OTA\_Test --fqbn arduino:renesas\_uno:unor4wifi --connection wifi
- arduino-cloud-cli thing create --template minimal\_thing.yaml
- arduino-cloud-cli thing bind --id <thingID> --device-id <deviceID>
- arduino-cloud-cli device list
- arduino-cloud-cli thing list
- Add ArduinoIoTCloud PlatformIO library to project
- arduino-cloud-cli ota upload --device-id d5cc710d-da7d-4b4b-88d3-28e01d147eef --file firmware.bin

References:
- https://github.com/arduino/arduino-cli
- https://github.com/arduino/arduino-cloud-cli
- https://github.com/arduino-libraries/ArduinoIoTCloud
- https://docs.arduino.cc/arduino-cloud/arduino-cloud-cli/getting-started/
- https://docs.arduino.cc/arduino-cloud/features/ota-getting-started/
