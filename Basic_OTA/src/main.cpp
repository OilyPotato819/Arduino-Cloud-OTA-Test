#include <ArduinoIoTCloud.h>

KVStore kvStore;
WiFiConnectionHandler ArduinoIoTPreferredConnection;
NetworkConfiguratorClass NetworkConfigurator(ArduinoIoTPreferredConnection);

void setup()
{
  NetworkConfigurator.setStorage(kvStore);
  ArduinoCloud.setConfigurator(NetworkConfigurator);
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
}

void loop()
{
  ArduinoCloud.update();
}