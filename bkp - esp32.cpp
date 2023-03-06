/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is based on the Arduino WiFi Shield library, but has significant changes as newer WiFi functions are supported.
 *  E.g. the return value of `encryptionType()` different because more modern encryption is supported.
 */
#include "WiFi.h"
#include "ThingESP.h"

int bestSignal = -1000; // "Signal quality" evaluation parameter
int connection = 0; // Chosen network
//bool enviou = false;

ThingESP32 thing("todasporuma", "ESP32", "1234567890");
unsigned long previousMillis = 0;
const long INTERVAL = 10000;



/*void sendMessage(){
  
}*/

void initWiFi(const char* ssid) {
  const char* test = "Redmi Note 10S";
  WiFi.mode(WIFI_STA);
  WiFi.begin(test);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }

 //thing.SetWiFi(ssid, "");
   
  //connected = true;
}

/*String HandleResponse(String query)
{
  if(query == "teste") {
    return ":)";
  }
  else return ":("; 
}*/

void setup()
{
  Serial.begin(115200);
   
  // Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  //--------------------
  Serial.println("Scan start");

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
  initWifi(WiFi.SSID(connection).c_str());
  thing.initDevice();
  Serial.println("######################");    
    

}

void loop()
{  
  if (millis() - previousMillis >= INTERVAL)
   {
       previousMillis = millis();
      
       thing.sendMsg("+5511940626540", "hihi");
  }

  thing.Handle();

  // Delete the scan result to free memory for code below.
  //WiFi.scanDelete();

  // Wait a bit before scanning again.
  //delay(5000);
}

// ######################################################################

