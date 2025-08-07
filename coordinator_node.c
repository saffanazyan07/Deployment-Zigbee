#define THINGER_SERIAL_DEBUG
#include <ThingerESP8266.h>
#include "arduino_secrets.h"

ThingerESP8266 thing("rikafiqq_", "sensor", "5Mu-r6A3k3nFvQST");
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];// temporary array for use by strtok() function
// variables to hold the parsed data
char messageFromPC[numChars] = {0};
int node = 0;
float nilaisensor = 0.0;
float nilai1 = 0.0;
float nilai2 = 0.0;
float nilai3 = 0.0;
boolean newData = false;
void setup() 
{
// open serial for monitoring
  Serial.begin(9600);
// set builtin led as output
// pinMode(LED_BUILTIN, OUTPUT);
// add WiFi credentials
  thing.add_wifi("remahan", "blackpearl");
// digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
//  thing["led"] << digitalPin(LED_BUILTIN);
// resource output example (i.e. reading a sensor value)
  thing["Nsensor1"] >> outputValue(nilai1);
  thing["Nsensor2"] >> outputValue(nilai2);
  thing["Nsensor3"] >> outputValue(nilai3);
// more details at http://docs.thinger.io/arduino/
}
void loop() 
{ 
  recvWithStartEndMarkers();
  if (newData == true) { 
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() replaces the commas with \0
      if (node==1)
        {
          nilai1=nilaisensor;
        }
        else if (node==2)
        {
          nilai2=nilaisensor;
        }
        else if (node==3)
        {
          nilai3=nilaisensor;
        }
      parseData();
      Serial.println("parsing data selesai");
//showParsedData();
      newData = false;
    }
thing.handle();
}
void recvWithStartEndMarkers() 
{
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0';// terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) 
{
            recvInProgress = true;
        }
    }
}
void parseData() 
{
      // split the data into its parts
    char * strtokIndx; // this is used by strtok() as an index
    strtokIndx = strtok(tempChars,",");// get the first part - the string
    strcpy(messageFromPC, strtokIndx);// copy it to messageFromPC
    strtokIndx = strtok(NULL, ",");// this continues where the previous call left off
    node = atoi(strtokIndx);// convert this part to an integer
    strtokIndx = strtok(NULL, ",");
    nilaisensor = atof(strtokIndx);// convert this part to a float
}
void showParsedData() 
{
    Serial.print("Message ");
    Serial.println(messageFromPC);
    Serial.print("Integer ");
    Serial.println(node);
    Serial.print("Float ");
    Serial.println(nilaisensor);
}
