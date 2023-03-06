#ifndef WhatsappMessage.h
#define WhatsappMessage.h

#include "WiFi.h"
#include "ThingESP.h"

int searchWifi() {
  int connection = -1;
  int bestSignal = -1000; // "Signal quality" evaluation parameter

  //------------
  // Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  // WiFi.scanNetworks will return the number of networks found.
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
        // Check if the sinal is open
        if(WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
            // Check which is the strongest signal
          if(WiFi.RSSI(i) < bestSignal) { connection = i; }  
        }
      }
  }
  return connection;
}

void connectWifi(const char* ssid) {
  publicESP32.SetWiFi(ssid, "");
  publicESP32.initDevice();  
}

void initWifi(const char* user, const char* project, const char* projectID) {
    ThingESP32 thing(user, project, projectID);

    int wifiID = searchWifi();
    connectWifi(WiFi.SSID(wifiID).c_str());
}

#endif