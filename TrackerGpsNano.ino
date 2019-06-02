#include <Arduino.h>
#include <SoftwareSerial.h>
#include "TinyGPS++.h"
#include <SPI.h>
#include <SD.h>

//constant GPS SERIAL
static const int RXPin =3, TXPin = 2;
static const uint32_t GPSBaud = 9600;

const int chipSelect = 5;
const int  DEBUG_MODE  = 0 ;
const int  DELAY_POS  = 5 ;//Min

// The serial connection to the GPS module
SoftwareSerial gpsSerial(TXPin, RXPin);

//GLOBAL
char fileName[32];
char lineText[100] ;

TinyGPSPlus gps;
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n";
   
//XML GPX FILE
int countPt = 0;
const char * trackPt =  "<trkpt lat=\"%s\" lon=\"%s\" ><time>%s</time></trkpt>"  ;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
    
   Serial.begin(115200);
   gpsSerial.begin(GPSBaud);
   
   pinMode(LED_BUILTIN, OUTPUT);
    
  // errorLed();
   
  //init SD CARD
  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD CARD init failed!"));
    errorLed();
    while (1);
  }
  Serial.println(F("init ok."));
  gpsSerial.print("$PUBX,40,GLL,0,0,0,0*5C\r\n");

}

void errorLed(){
  for (int i = 0 ; i < 20 ; i++) {
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(100);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(100); 
  }
}


void addLineToFile(){

  // open a new file and immediately close it:
  File myFile;
  myFile = SD.open(fileName, FILE_WRITE);
   Serial.print("open file: ");
    Serial.println(fileName);
  if (myFile) {
    myFile.println(lineText);
    myFile.close();
    Serial.println("save line: ");
    Serial.println(lineText);
   memset(lineText, 0, sizeof(lineText));
  }
  else{
     Serial.println(F("error opening sd!"));
  }

}


// the loop function runs over and over again forever
void loop() {

 while (gpsSerial.available() > 0 || DEBUG_MODE == 1){
   
  
   if ( DEBUG_MODE == 1 ){
      
       if (!gps.encode(*gpsStream++)){
          return;
         }
   }
   else{
       
      byte gpsData = gpsSerial.read();
      gps.encode(gpsData);
       
    }
    
     if (gps.location.isUpdated() ||  DEBUG_MODE == 1  ){
        TinyGPSDate d = gps.date ;
        TinyGPSTime t = gps.time ;
        if (gps.location.isValid() && d.isValid() && t.isValid()) {
       
        char lat[16];
        dtostrf(gps.location.lat(), 4, 6, lat);
        
        char lng[16];
        dtostrf(gps.location.lng(), 4, 6, lng);
        
       char timeUTC[50] = "";//2009-06-19T10:13:04Z<
       sprintf(timeUTC, "%02d-%02d-%02dT%02d:%02d:%02dZ",d.year(), d.month(), d.day(), t.hour(), t.minute(), t.second());
       
        sprintf(lineText, trackPt,  lat , lng, timeUTC);
        countPt ++;
        
           char dateChar[32];
         //date
         sprintf(dateChar, "%02d_%02d_%02d", d.month(), d.day(), d.year());
         Serial.println(dateChar);
         
         char timeChar[32];
         sprintf(timeChar, "%02d:%02d:%02d", t.hour(), t.minute(), t.second());
         Serial.println(timeChar);
         
         sprintf(fileName, "%02d%02d%02d.gpx", d.month(), d.day(), d.year());
          Serial.println(fileName);
         
         //add to gpx file
        if (fileName == NULL){//if first line create filename and file...
               Serial.println(F("fileName not init"));
              }
            else{
                 addLineToFile();
                  
                digitalWrite(LED_BUILTIN, LOW);
                delay(1000);  
                digitalWrite(LED_BUILTIN, HIGH);
                delay(1000);
                delay(DELAY_POS * 60UL * 1000UL);
       
            }
       
      }
       else
     {
       Serial.println(F("INVALID"));
        
      }
    }
  

  }
}
