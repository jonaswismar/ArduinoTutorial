#include <Arduino.h>

#include <ESP8266WiFi.h>

#define WIFI_DELAY 500
#define MAX_CONNECT_TIME 30000

void printEncryptionType(int thisType)
{
  // read the encryption type and print out the name:
  switch (thisType)
  {
  case ENC_TYPE_WEP:
    Serial.println("WEP");
    break;
  case ENC_TYPE_TKIP:
    Serial.println("WPA");
    break;
  case ENC_TYPE_CCMP:
    Serial.println("WPA2");
    break;
  case ENC_TYPE_NONE:
    Serial.println("None");
    break;
  case ENC_TYPE_AUTO:
    Serial.println("Auto");
    break;
  }
}

void printWifiData()
{
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(ip);

  IPAddress subnet = WiFi.subnetMask();
  Serial.print("NetMask: ");
  Serial.println(subnet);

  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("Gateway: ");
  Serial.println(gateway);
}

void listNetworks()
{
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    Serial.println("Couldn't get a wifi connection");
    while (true)
      ;
  }

  Serial.print("number of available networks:");
  Serial.println(numSsid);

  for (int thisNet = 0; thisNet < numSsid; thisNet++)
  {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tMAC: ");
    Serial.print(WiFi.BSSIDstr(thisNet));
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
    if (WiFi.encryptionType(thisNet) == ENC_TYPE_NONE)
    {
      WiFi.begin(WiFi.SSID(thisNet));
      unsigned short try_cnt = 0;
      while (WiFi.status() != WL_CONNECTED && try_cnt < MAX_CONNECT_TIME / WIFI_DELAY)
      {
        delay(WIFI_DELAY);
        Serial.print(".");
        try_cnt++;
      }
      if (WiFi.status() == WL_CONNECTED)
      {
        printWifiData();
      }
      else
      {
        Serial.println("Connection FAILED");
      }
    }
  }
}

void printLocalMacAddress()
{
  byte mac[6];

  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    while (true)
      ;
  }
  printLocalMacAddress();
}

void loop()
{
  Serial.println("Scanning available networks...");
  listNetworks();
  delay(10000);
}