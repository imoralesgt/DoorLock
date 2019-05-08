#include <DYE_Fingerprint.h>
#include <SoftwareSerial.h>
#include "fingerprint.h" 

/*
 * I/O definitions
 */

//#define TOUCH_RX 2 //Green wire
//#define TOUCH_TX 3 //White wire



/*
 * Constants
 */
#define DEBUG 1



/*
 * Globals
 */
SoftwareSerial mySerial(TOUCH_RX, TOUCH_TX);
DYE_Fingerprint finger = DYE_Fingerprint(&mySerial);


/*
 * Prototypes
 */
//Moved prototypes to header file "fingerprint.h" 



uint8_t initFingerprint(void){
  if(finger.verifyPassword())
    return FINGERPRINT_OK;
  return -1;
}


void setup() {
  Serial.begin(115200);
  while(!Serial);
  #ifdef DEBUG
  Serial.println("Finger node firmware test");
  #endif

  //Fingerprint sensor init
  finger.begin(57600);

  if(initFingerprint() != FINGERPRINT_OK){
    #ifdef DEBUG
      Serial.println("Fingerprint sensor not found!");
    #endif
    return -1;
  }
  #ifdef DEBUG
    Serial.println("Found fingerprint sensor!");
    Serial.println("Waiting for valid finger...");
  #endif

}



//TODO Start optimizing code below this line ----------------- 

void loop() {
  uint8_t p = finger.getImage();  
  if(p != FINGERPRINT_OK) return -1;

  #ifdef DEBUG
    Serial.println(p);
    Serial.println("Image read");
  #endif

  p = finger.image2Tz();
  if(p != FINGERPRINT_OK) return -1;

  #ifdef DEBUG
    Serial.println("Image to fingerprint data");
  #endif

  p = finger.fingerFastSearch();
  if(p != FINGERPRINT_OK){
    #ifdef DEBUG
      Serial.println(p);
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
