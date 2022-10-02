/*
    Video: https://www.youtube.com/watch?v=oCMOYS71NIU
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleNotify.cpp
    Ported to Arduino ESP32 by Evandro Copercini

   Create a BLE server that, once we receive a connection, will send periodic notifications.
   The service advertises itself as: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
   Has a characteristic of: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E - used for receiving data with "WRITE" 
   Has a characteristic of: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E - used to send data with  "NOTIFY"

   The design of creating the BLE server is:
   1. Create a BLE Server
   2. Create a BLE Service
   3. Create a BLE Characteristic on the Service
   4. Create a BLE Descriptor on the characteristic
   5. Start the service.
   6. Start advertising.

   In this example rxValue is the data received (only accessible inside that function).
   And txValue is the data to be sent, in this example just a byte incremented every second. 


   BLE_uartPocuterv007 werkt
*/
#include <Pocuter.h>
Pocuter* pocuter;

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
std::string ReceivedMessageBLE;
char sptext[120];

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

class MyServerCallbacks: public BLEServerCallbacks 
{
 void onConnect(BLEServer* pServer)    { deviceConnected = true; };
 void onDisconnect(BLEServer* pServer) { deviceConnected = false;}
};

class MyCallbacks: public BLECharacteristicCallbacks 
{
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      ReceivedMessageBLE = rxValue + "\n";
      if (rxValue.length() > 0)
      {  for (int i = 0; i < rxValue.length(); i++)   printf("%c",rxValue[i]); }
      printf("\n");
      
//      if (rxValue.length() > 0) printf("%s",ReceivedMessageBLE); 
//       {
//        printf("Received Value: ");
//        for (int i = 0; i < rxValue.length(); i++)   printf("%c",rxValue[i]);          
//        printf("\n");
//       }
    }
    
};


void setup() 
 {

 pocuter = new Pocuter();
 pocuter->begin();
 UGUI* gui = pocuter->ugui; 
 
  uint16_t sizeX;
  uint16_t sizeY;
  pocuter->Display->getDisplaySize(sizeX, sizeY);
    
 const char* TITLE = "BLE EdSoftV010 ";

  gui->UG_FillFrame(0, 0, sizeX - 1, 9, C_MIDNIGHT_BLUE);
  gui->UG_FillFrame(0, 10, sizeX - 1, sizeY - 1, C_DARK_BLUE);
  gui->UG_FontSelect(&FONT_5X8);
  gui->UG_SetForecolor(C_WHITE);
  gui->UG_SetBackcolor(C_MIDNIGHT_BLUE);
  gui->UG_PutString(1, 1, TITLE);


  // Create the BLE Device
  BLEDevice::init("UART Service EdN");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
		CHARACTERISTIC_UUID_TX,  BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY	);
   pTxCharacteristic->addDescriptor(new BLE2902());                   
  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
			CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_NOTIFY    | BLECharacteristic::PROPERTY_WRITE 	);
  pRxCharacteristic->addDescriptor(new BLE2902());
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  printf("Waiting a client connection to notify...\n");


}

void loop() {

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        printf("start advertising\n");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) 
      {	   	// do stuff here on connecting
        sprintf(sptext,"%s",__FILENAME__);  char *Filename; Filename = strtok(sptext,"."); 
        printf("%s\n",Filename);
        oldDeviceConnected = deviceConnected;
      }

  if (ReceivedMessageBLE.length()>0)
   {
    SendMessageBLE(ReceivedMessageBLE);
    sprintf(sptext,"%s",ReceivedMessageBLE);

    UGUI* gui = pocuter->ugui; 
     gui->UG_PutString(20, 30, sptext);
 
    ReceivedMessageBLE = "";
   }

}

void SendMessageBLE(std::string Message)
{
 if(deviceConnected) 
  {
    pTxCharacteristic->setValue(Message); 
    pTxCharacteristic->notify();
    delay(10); // bluetooth stack will go into congestion, if too many packets are sent
  } 
}
