
//Credit du code : https://arduino-france.site/capteur-luminosite/

#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

/* Luminosité_Grove est un programme qui allume une led lorsque un capteur de luminosité détecte une baisse de lumière*/
 
#define capteur A1                                 // affectation des broches  
#define led 2
                               
int lumiere;

void setup() {
  pinMode(capteur, INPUT);
  pinMode(led, OUTPUT);                       // la broche led est en sortie
  
  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();     
  
  Serial.begin(9600); 
}

void loop() {
 lumiere = analogRead(capteur);         // conversion AN              
  Serial.print("Lumiere = ");                  // affichage dans le moniteur série de la valeur de la luminosité
  Serial.println(lumiere);

  if(lumiere<100)                                   // si la luminosité est faible
  {
    digitalWrite(led, HIGH);                      // on allume la led
  }
  else
  {
    digitalWrite(led, LOW);                      // on éteint la led
  } 
  delay(1000);

  appendPayload("luminosite", lumiere);  //Ajout de la donnée luminosite au message MQTT
  sendPayload();         
}
