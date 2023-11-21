#include <BleSerial.h>
const int BUFFER_SIZE = 8192;
BleSerial ble;
uint8_t bleReadBuffer[BUFFER_SIZE];
long count =0;
void setup()
{
	//Start the BLE Serial
	//Enter the Bluetooth name here
	ble.begin("BleSerialTest");
  Serial.begin(115200);
  Serial.setRxBufferSize(BUFFER_SIZE);
  Serial.setTimeout(10);
}

void loop()
{
  //Hablar del BLE al Serial arduino
  if(ble.available())
  {
    count = ble.readBytes(bleReadBuffer, BUFFER_SIZE);
    Serial.write(bleReadBuffer, count);
  }
  delay(20);

  //Se repite para hablar del Serial Arduino al BLE
  if(Serial.available())
  {
    count = Serial.readBytes(bleReadBuffer, BUFFER_SIZE);
    ble.write(bleReadBuffer, count);
  }
  delay(20);
}
//wiii ful-duplex!!!//