#include <DYE_Fingerprint.h>
#include <SoftwareSerial.h>

/*
 * I/O definitions
 */
//Fingerprint software serial interface
#define TOUCH_RX 2 //Green wire
#define TOUCH_TX 3 //White wire



/*
 * Constants
 */
#define DEBUG 1



/*
 * Globals
 */
SoftwareSerial mySerial(TOUCH_RX, TOUCH_TX);
DYE_Fingerprint finger = DYE_Fingerprint(&mySerial);




void setup() {
  Serial.begin(115200);
  while(!Serial);
  #ifdef DEBUG
  Serial.println("Finger node firmware test");
  #endif

  //Fingerprint sensor init
  finger.begin(57600);

  if (finger.verifyPassword()) {
    #ifdef DEBUG
    Serial.println("Found fingerprint sensor!");
    #endif
  } else {
    #ifdef DEBUG
    Serial.println("Did not find fingerprint sensor :(");
    #endif
    
    while (1) { delay(1); }
  }
  #ifdef DEBUG
  Serial.println("Waiting for valid finger...");
  #endif

}

void loop() {
  uint8_t p = finger.getImage();
  if(p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if(p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if(p != FINGERPRINT_OK){
    #ifdef DEBUG
      Serial.println("Fingerprint not found!");
    #endif
    return -1;
  }

  //If above conditions are met, a valid
  //fingerprint was found
  
  #ifdef DEBUG
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print( " with confidence of "); Serial.println(finger.confidence);
  #endif

  Serial.println("5 seconds sleep...");
  delay(5000);

}
