#ifndef FINGERPRINT_H
#define FINGERPRINT_H



/*  
    ===============
    I/O Definitions
    =============== 
*/

//Fingerprint software serial interface
#define TOUCH_RX 2 //Green wire
#define TOUCH_TX 3 //White wire




/*
    ================
    MISC Definitions
    ================
*/

//Control P-Channel MOSFET to enable/disable
//fingerprint sensor
#define FINGER_SENSOR_ON  0
#define FINGER_SENSOR_OFF 1



/*
    ==========
    PROTOTYPES
    ==========
*/
uint8_t initFingerprint(void);


/*
    =======
    GLOBALS
    =======
*/



#endif