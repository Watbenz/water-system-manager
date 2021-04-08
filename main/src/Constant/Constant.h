#ifndef CONSTANT_H
#define CONSTANT_H

#define SSID_AP "watbenz_server1"
#define PASSWORD_AP "123456789"
// #define SSID "Wachirawit_2.4G"
// #define PASSWORD "3422273580"
#define SSID_WIFI "watbenz"
#define PASSWORD_WIFI "watbenzzzzzz"
#define RESPONSE_OK 200
#define TEXT "text/plain"

#define FIREBASE_HOST "https://water-manager-system-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "EhP4M1upgcc0kzEW0u4bJI7FvYwfFmFGGZlZ87VS"
#define FIREBASE_TIMEOUT (1000 * 60)

#define iSYNC_USERNAME "watbenz"
#define iSYNC_AUTH "6047312e62c47f64b13fb5ad"
#define iSYNC_KEY "6047319862c47f64b13fbe3e"

#define NUMBER_OF_DEVICE 2
#define GMT (3600 * 7)

#define WATER_SENSOR 34
#define ECHO 2
#define TRIG 0
#define DEVICE_OUT 4

static bool emergencyClose = false;
static bool device[NUMBER_OF_DEVICE + 1] = {0};
static int tankHeight = 25;
static int tankGap = 5;

#endif