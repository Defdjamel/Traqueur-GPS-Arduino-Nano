/*
 * prototype class
 */
void modeWakeUp(bool state);

/*
 * include
 */
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#include "TinyGPS++.h"
#include "Constants.h"
#include "Sleep.h"

/*
 * global Var
 */
char fileName[32];
char lineText[100] ;
TinyGPSPlus gps;

void setup() {
  // initialize 
   Serial.begin(115200);
   gpsSerial.begin(GPSBaud);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(gpsPin, OUTPUT);
   setupWatchDogTimer();delay(100);

   initPowerSave();

    //init state hardware wake up ( only gps)
    modeWakeUp(true);
 
  //init SD CARD
  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD failed!"));
    errorLed();
    while (1);
  }
  Serial.println(F("init ok."));
  
  //write testFile to sd card
  testFile();

 
}

void initPowerSave(){
  ADCSRA = 0;  // disable ADC to save 0.1mA
  //disable pin interrupt
  detachInterrupt(digitalPinToInterrupt(0));
  detachInterrupt(digitalPinToInterrupt(1));
}

//LED MANAGEMENT
void errorLed(){
  for (int i = 0 ; i < 100 ; i++) {
      digitalWrite(LED_BUILTIN, HIGH); 
      delay(100);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(100); 
  }
}

/*
 * This method manage state of hardware in sleep or wake up 
 * GPS VCC is switch by NPN TRANSITOR with Base connected to gpsPin( see scheme)
 */
void modeWakeUp(bool state){
  switchGps(state);
}

void switchGps(bool state){
  if( state ){
    Serial.print(F("gps on"));
    digitalWrite(gpsPin, HIGH);
  }else{
     Serial.print(F("gps off"));
    digitalWrite(gpsPin, LOW);
  }
  
}

/*
 * This method write a test file.txt in the sd card to check everythinh is wire correctly
 */
void testFile(){
 if ( SD.exists("test.txt")) {
    Serial.println("already existe");
  } else {
    
  
  }
  // open a new file and immediately close it:
  File myFile;
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.close();
    Serial.println("save line: ");
    Serial.println("test sd OK");
  }
  else{
     Serial.println(F("E open sd!"));
  }

}

/*
 * This method add one waypoint line to current file  
 */
void addLineToFile(){
  bool firstOpen = false ; 
  // open a new file and immediately close it:
  if ( SD.exists(fileName)) {
    Serial.println("already existe");
  } else {
    firstOpen = true;
  
  }
  
  File myFile;
  myFile = SD.open(fileName, FILE_WRITE);
   Serial.print("open file: ");
    Serial.println(fileName);
if (!myFile) {
     Serial.println(F("E open sd!"));
     return;
}

    if (firstOpen){
      //add header
       char myChar;
       for (byte k = 0; k < strlen_P(headerGpsFile); k++) {
           myChar = pgm_read_byte_near(headerGpsFile + k);
           myFile.print(myChar);
       }
      //remove footer
    }
    //add line
   myFile.println(lineText);
   myFile.close();
   Serial.println(F("save line: "));
   Serial.println(lineText);
   memset(lineText, 0, sizeof(lineText));
}


// the loop function runs over and over again forever
void loop() {  
if (isWakeUp == 0 ){//cyle = 8sec
  
    enterSleepCpu();
    return;
}

if ( ( millis() / 1000 ) >  (startTimeGpsSec + DELAY_MAX_GPS_SEC ) ){//timeOutGps signal
   Serial.println(F("timeOutGps signal"));
  enterSleep();
  return;
}


 //try to get GPS signal  
 while (gpsSerial.available() > 0 || DEBUG_MODE == 1){
   
    //Get Data from Gps or Debug
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
         sprintf(timeChar, "%02d:%02d:%02d", t.hour() , t.minute(), t.second());
         Serial.println(timeChar);
         
         sprintf(fileName, "%02d%02d%02d.gpx", d.month(), d.day(), d.year());
          Serial.println(fileName);
         
         //add to gpx file
        if (fileName == NULL){//if first line create filename and file...
               Serial.println(F("fileName not init"));
              }
            else{
              //ADD GPS SIGNAL
                addLineToFile();
              //ENTER IN SLEEP MODE
               
               enterSleep();
               
               
            }
       
      }
       else
     {
       Serial.println(F("INVALID"));
        
      }
    }
  

  }
  
}
