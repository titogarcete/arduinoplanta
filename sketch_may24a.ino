#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
const int bomba = 3; // Definir el pin de la bomba
const int sensorHumedad = A3; // Definir el pin del sensor de humedad

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light
  pinMode(bomba, OUTPUT); // Configurar el pin de la bomba como salida
  pinMode(A1, INPUT);
  digitalWrite(bomba, LOW); // Encender la bomba
}

void loop() {
  int humedad = readSensor(); // Leer el valor del sensor de humedad
  humedad = 100.0 - (humedad / 1024.0 * 100.0);
  // Verificar el valor de humedad y controlar la bomba
  if (humedad >= 40) {
    digitalWrite(bomba, LOW); // Apagar la bomba
  } else {
    digitalWrite(bomba, HIGH); // Encender la bomba
  }

  lcd.setCursor(0,0); //Defining positon to write from first row,first column .
  lcd.print(" Porcentaje "); //You can write 16 Characters per line .
  delay(1000);//Delay used to give a dynamic effect
  lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
  lcd.print(humedad);
  
  Serial.println(humedad); // Imprimir el valor de humedad en el monitor serie
  
  delay(2000); // Esperar medio segundo antes de la siguiente lectura
  lcd.clear();
}

int readSensor(){
  int val = analogRead(A1);
  return val;
}
