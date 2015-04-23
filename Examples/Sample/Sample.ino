#include <SPI.h>
#include <MudbusWiFi.h>
#include <avr/pgmspace.h>
#include <WiFi.h>

MudbusWiFi Mb;
//Lamps
int Out2 = 2;
int Out3 = 3;
int Out4 = 4;

void setup()
{
 Serial.begin(9600);
  char ssid[] = "****";      //  your network SSID (name)
  char pass[] = "****";   // your network password
  int status = WL_IDLE_STATUS;     // the Wifi radio's stat
  pinMode(Out2, OUTPUT);               // assign Pin 2 as Output
  pinMode(Out3, OUTPUT);               // assign Pin 3 as Output
  pinMode(Out4, OUTPUT);               // assign Pin 4 as Output
 

// check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
  Serial.print("Connected to wifi. My address:");
  IPAddress myAddress = WiFi.localIP();
  Serial.println(myAddress);
}

void loop()
{
    Mb.Run(); // start MbTcp subroutine
    delay(1000);
    // Digital OUT 2 (as  Modbus Coil 1)
  if   (Mb.C[0] == HIGH) {
    digitalWrite(Out2, HIGH);
  }
  else {
    digitalWrite(Out2, LOW);
  }
  // Digital OUT 3 (as  Modbus Coil 2)
  if   (Mb.C[1] == HIGH) {
    digitalWrite(Out3, HIGH);
  }
  else {
    digitalWrite(Out3, LOW);
  }
  // Digital OUT 4 (as  Modbus Coil 3)
  if   (Mb.C[2] == HIGH) {
    digitalWrite(Out4, HIGH);
  }
  else {
    digitalWrite(Out4, LOW);
  }
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
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

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
