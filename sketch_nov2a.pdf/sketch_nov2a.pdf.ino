/*#####Codigo hecho por Guido Ariel Mix, en el trabajo mientras toma cafe ######
#######-------------Incluyo el bluetooth para el joystick XD--------############
##############################################################################*/
//#include <BluetoothSerial.h> -> BleSerial by Avinab Malla on Library Manager
#include <BleSerial.h>
//BluetoothSerial SerialBT; -> BleSerial SerialBT
BleSerial SerialBT;
//####Extra####
const int BUFFER_SIZE = 8192;
uint8_t bleReadBuffer[BUFFER_SIZE];
//##FIN DE EXTRA####

//variables para las salidas
//motor A
static const int MotorA = 14;
static const int Motodere1 = 27;
static const int Motodere2 = 26;
//motor B
static const int MotorB = 25;
static const int Motoizq1 = 33;
static const int Motoizq2 = 32;
//PWM para los analog del jostin
int PWMvelocidadglobal = 0;
//long PWMdireccion = 0; -> auto PWNdireccion = 0;
auto PWMdireccion = 0;

void setup() {
  //inicio comunicacion para chekeos
  SerialBT.begin("ESP32"); //Cambio, ahora es un objeto ble, pero como lleva el mismo nombre parece no variar
  Serial.begin(115200);
  //##Extra##
  Serial.setRxBufferSize(BUFFER_SIZE);
  Serial.setTimeout(10);
  //##Fin de Extra, Configuraste un tamanioi de buffer de lectura Rx del tamanio 8192 que son 13 bits
  Serial.println("Iniciando programa...");
  //declaro los pines
  pinMode(MotorA, OUTPUT);
  pinMode(MotorB, OUTPUT);
  //motor derecha salidas
  pinMode(Motodere1, OUTPUT);
  pinMode(Motodere2, OUTPUT);
  //motor izquierda salidas
  pinMode(Motoizq1, OUTPUT);
  pinMode(Motoizq2, OUTPUT);
}
void loop() {
  //lee lo que mando por BT
  /* en este caso estoy haciendo que siempre valla a
  la maxima velocidad
  */
  if (SerialBT.available()) {
    //guardo lo que mande a mi variable direccion
    //PWMdireccion = SerialBT.available(); -> Lees los bits con readBytes(variable de lectura del buffer, tamanio del buffer);
    PWMdireccion = SerialBT.readBytes(bleReadBuffer, BUFFER_SIZE);
    Serial.write(bleReadBuffer, PWMdireccion);
  }
  delay(20);
  //Como vos no vas a mandar del serial arduino al serial ble del esp, el resto del codigo queda intacto
  if (PWMdireccion==1){
    izquierda();
    delay(20);
  }
  if (PWMdireccion==2){
    derecha();
    delay(20);
  }
  if (PWMdireccion==3){
    adelante();
    delay(20);
  }
  if (PWMdireccion==4){
    atras();
    delay(20);
  }
  if (PWMdireccion==0){
    freno();
  }
}
//Creo sub rutinas de maxima velocidad

void derecha() {
  digitalWrite(Motodere1, 0);
  digitalWrite(Motodere2, 1);
  digitalWrite(Motoizq1, 1);
  digitalWrite(Motoizq2, 0);
  Serial.print("DERECHA\n");
}
void izquierda() {
  digitalWrite(Motodere1, 1);
  digitalWrite(Motodere2, 0);
  digitalWrite(Motoizq1, 0);
  digitalWrite(Motoizq2, 1);
  Serial.print("Izquierda");
}
void atras() {
  digitalWrite(Motodere1, 0);
  digitalWrite(Motodere2, 1);
  digitalWrite(Motoizq1, 0);
  digitalWrite(Motoizq2, 1);
  Serial.write("ATRAS");
}
void adelante() {
  digitalWrite(Motodere1, 1);
  digitalWrite(Motodere2, 0);
  digitalWrite(Motoizq1, 1);
  digitalWrite(Motoizq2, 0);
  Serial.println("DERECHA");
}
void freno() {
  digitalWrite(Motodere1, 0);
  digitalWrite(Motodere2, 0);
  digitalWrite(Motoizq1, 0);
  digitalWrite(Motoizq2, 0);
  Serial.println("FRENO");
  }