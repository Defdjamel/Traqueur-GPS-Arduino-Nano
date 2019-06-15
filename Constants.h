//Hardware
static const int GPSRXPin = 4 , GPSTXPin = 5;
static const uint32_t GPSBaud = 9600;

// The serial connection to the GPS module
SoftwareSerial gpsSerial(GPSTXPin ,GPSRXPin);

const int chipSelect = 6;//SD card select pin
const int gpsPin = 8;

const int  DEBUG_MODE  = 0 ;

const unsigned long   DELAY_MAX_GPS_SEC  = 60 ;
volatile int SLEEPING_TIME_MIN = 10;


   
//XML GPX FILE
int countPt = 0;
const char * trackPt =  "<trkpt lat=\"%s\" lon=\"%s\" ><time>%s</time></trkpt>"  ;
const char headerGpsFile[] PROGMEM = {"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?><trk><trkseg>"};
const char footerGpsFile[] PROGMEM  = {"</trkseg></trk></gpx>"};

//gpsStream for debug
const char *gpsStream =
  "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n";
