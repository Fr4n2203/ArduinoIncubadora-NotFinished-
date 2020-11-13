                                                                              //~CODIGO DE LA INCUBADORA~//
                                                                              //ENRIQUEZ,KASPARIAN,LUNA/
                                                                                      //7°1°// 
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h> // Para el display
#define DHTPIN 5// el pin digital donde se conecta el sensor
#define DHTTYPE DHT22// el tipo de sensor, en este caso el 22
 
 bool state = 0; // control del funcionamiento de la celda (si esta aumentando o disminuyendo la temp)
 
 volatile float Tempmax= 38.00; // asignar la tolerancia de temperatura (los pollos necesitan 37,7°C aprox y 0,3 esta dentro de los limites aceptables)
 
 volatile float Tempmin= 37.40; // lo mismo pero el valor minimo 
 
 int pin=8;
 
 const int bot1; //botón de aumento de temperatura

 const int bot2; //botón de disminución de temperatura

 int aumen;

 int dismin;
 
DHT dht(DHTPIN, DHTTYPE);// se activa el sensor DHT
 
void setup() {
  
  Serial.begin(9600);// Inicializamos comunicación serie
 
  dht.begin();// inicio de el sensor DHT
  
  pinMode(bot1, INPUT);
  
  pinMode(bot2, INPUT);
}
 
void loop() {
    
  delay(5000);// delay de 5 segundos entre mediciones
 
  float h = dht.readHumidity();// leer la humedad relativa
  
  float t = dht.readTemperature();// leer la temperatura en grados centígrados 
 
 
  if (isnan(h) || isnan(t)) { // se comprueba si hubo algún error en la lectura
   Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  aumen = digitalRead(bot1); //define el aumento como el botón 1
  
  dismin = digitalRead(bot2); //define la disminución como el botón 2

  if(dismin==LOW && aumen==HIGH){

  Tempmax++;

  Tempmin=Tempmax-0.6;
  }

  if(aumen==LOW && dismin==HIGH){
  
  Tempmax--;
  
  Tempmin=Tempmin-0.6;
  }
  
  celda(t); //llama al control de la celda de peltier
  
  pantalla(t,h); // se imprimen las mediciones (En caso de usar un display se mostrará en el display, pero si no es util para calibración del programa)
 
}
//Funciones

bool celda(float tmp){//controla la celda de peltier
  if(state == 0 && tmp > Tempmax)
  {
      state = 1;
      analogWrite(pin, 190);   //PWM al  70% aprox. se prende la celda
  }
  if(state == 1 && tmp < Tempmin)
  {
      state = 0;
      analogWrite(pin, 50);   // PWM en un % muy bajo. la celda esta casi apagada
  }
  }
void pantalla(float temp,float hum){ //imprime los datos de temperatura y humedad medidos
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print(" °C ");
  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.print(" %\t");
  }
  
                                                                                 
                                                                                 
                                                                                 //FIN....?//1.3v
