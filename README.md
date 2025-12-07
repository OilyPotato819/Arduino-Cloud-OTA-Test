# Arduino-Cloud-OTA-Test

Minimal test project to build firmware with PlatformIO and push OTA updates to the Arduino UNO R4 WiFi via Arduino Cloud CLI.

## Prerequisites

- [arduino-cli](https://github.com/arduino/arduino-cli/releases)
- [arduino-cloud-cli](https://github.com/arduino/arduino-cloud-cli/releases)

> **Note:** Append the flag -h to any `arduino-cli` or `arduino-cloud-cli` command for more information.

## Authentication

Authenticate with Arduino Cloud by generating a clientId and clientSecret from [Arduino Cloud API Keys](https://app.arduino.cc/api-keys), then enter them into the command line when prompted after running this command:

```
arduino-cloud-cli credentials init --dest-dir <credentialsPath>
```

Credentials are searched for in the following order: the current working directory, parent directories, and the default arduino15 directory.

## Create Device

Begin by updating the local cache of available platforms and libraries:

```
arduino-cli core update-index
```

You will now have to plug the board into your computer so that you can provision it. Find the port and platform core of your board by running:

```
arduino-cli board list
```

Install the listed core if it has not already been installed with:

```
arduino-cli core install <coreName>
```

And finally, use this command with the port name from earlier to add the device to the cloud:

```
arduino-cloud-cli device create --name <deviceName> --port <portName> --connection wifi
```

The board type is normally automatically detected from the port, but if the FQBN appears incorrectly in the board list you can manually specify it using the --fqbn flag. The list of supported FQBN can be retrieved with the `device list-fqbn` command.

You will need to enter in the Wi-Fi network SSID and password. When this process completes it should display the device ID along with some other info. Save the device ID for later.

## Create Thing

Once the device has been provisioned you can disconnect it from your computer and power it externally.

In order to create a thing on the command line you need a template in either JSON or YAML format. A [minimal thing](minimal_thing.yaml) template is provided in this repository, but if you need additional configuration you can create a thing on the Arduino Cloud website. After that, if you want a template for use on the command line you can generate one using the `thing extract` command.

Create a thing on the Arduino Cloud:

```
arduino-cloud-cli thing create --name <thingName> --template <templatePath>
```

Similarly to the `device create` command, some info will be printed to the console once the thing has been uploaded to the cloud. Using the thing ID and the device ID from earlier, you can now bind the thing to the device.

```
arduino-cloud-cli thing bind --id <thingID> --device-id <deviceID>
```

To check whether everything has been done correctly so far, you can use these two commands:

```
arduino-cloud-cli device list
arduino-cloud-cli thing list
```

The thing's device field should match the correct device ID, and the status of the device should be ONLINE, indicating that it is connected to the cloud.

> **Note:** You can also do all of this on the [Arduino Cloud](https://app.arduino.cc/) website by just setting up the device and attaching a thing the usual way.

## OTA Update

For a device to accept OTA updates you must include some additional code in your sketches. This code is provided in the [main](Basic_OTA/src/main.cpp) source file of the Basic_OTA PlatformIO project, and it uses the ArduinoIoTCloud library to manage connectivity and OTA updates. When you provision the device, the Wi-Fi credentials you enter are saved to the device’s persistent storage. The sketch initializes the cloud connection, configures storage, and maintains the connection through `ArduinoCloud.update()`, enabling automatic reconnection and OTA functionality.

> **Warning:** Uploading a sketch without any network-configuration or cloud-update code will prevent any subsequent OTA attempts from going through. You will have to serially upload a new sketch with the required code to reconnect the device to the cloud.

To perform an OTA update with a sketch you just need to build the PlatformIO project, ensuring it is set up with the correct board configuration. This will generate a binary file at `.pio/build/<boardName>/firmware.bin`. The Christmas_Tree folder contains an example PlatformIO project for the LED matrix on the UNO R4 WiFi and can be used to test OTA updates. Finally, this command will wirelessly upload the binary file to the device:

```
arduino-cloud-cli ota upload --device-id <deviceId> --file <binaryPath>
```

## Recommendations

This workflow scales well because it is fully command-line driven and can be automated. The `arduino-cloud-cli` tool also has a `thing clone` command to easily create many copies of an already existing thing, as well as an `ota mass-upload` command to deploy firmware to a list of devices simultaneously.

Because the Uva Core uses the same Renesas MCU + ESP32 architecture as the UNO R4 WiFi, it should be able to run the same ArduinoIoTCloud OTA agent and be provisioned through the Arduino Cloud CLI. With an appropriate board definition, PlatformIO-built binaries can be OTA-uploaded using the same CLI commands, making this workflow directly reusable for the Uva Core.

## References

- https://github.com/arduino/arduino-cli/
- https://github.com/arduino/arduino-cloud-cli/
- https://github.com/arduino-libraries/ArduinoIoTCloud/
- https://arduino.github.io/arduino-cli/1.3/getting-started/
- https://docs.arduino.cc/arduino-cloud/arduino-cloud-cli/getting-started/
- https://docs.arduino.cc/arduino-cloud/features/ota-getting-started/
- https://docs.arduino.cc/arduino-cloud/hardware/device-provisioning/
