/*
  Titre      : DEMO AIIA - MKR 1000 - Thingsboard
  Auteur     : Daniel
  Date       : 05/12/2022
  Description: lecture du capteur DFR0026 et envoie de cette valeur a une fréquences spécifique sur la plateforme IDO Thingsbaord
  Droits     : Reproduction permise pour usage pédagogique
  Version    : 0.0.1
*/

#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

/*
  Variables de base pour la lecture de la 
  sortie du TMP36 a partir d'une broche digitale
*/

const int PinLum  = A1;   
int ValeurLue = 0;
 double Tension = 0.0;    



// Variable de controle générales tel les délais, etc...

const int MS_DELAI = 1000;    // Nombre de milliseconde de délais

// La fonction setup sert, entre autre chose, a configurer les broches du uC

void setup() {
  
  Serial.begin(9600);             // Activation du port série pour affichage dans le moniteur série

  wifiConnect();                  //Branchement au réseau WIFI
  MQTTConnect();                  //Branchement au broker MQTT

  pinMode(PinLum, INPUT);     // Pour une bonne lecture, la broche analogique doit être placé en mode entré explicitment
}

// Boucle infinie qui permet au uC de faire une ou plusieurs taches sans arrêt

void loop() {

  ValeurLue = analogRead(PinLum);                  // Lecture de la broche analogue et sauvegarde de valeur
  
  Tension = (ValeurLue * 3.3) / 1023;     // Transfert de la lecture de la broche en tension

 
  // Impression dans le moniteur série

  Serial.print("La valeur obtene par la broche analogue est ");
  Serial.println(ValeurLue);

  Serial.print("La valeur de tension obtenue par la broche analogue est ");
  Serial.print(Tension);
  Serial.println(" V");

  // Envoi des données à thingboard
  
  appendPayload("Luminosité", ValeurLue);  //Ajout de la donnée température au message MQTT
  sendPayload();                                   //Envoie du message via le protocole MQTT

  delay(MS_DELAI);    // Délai de sorte a ce qu'on puisse lire les valeurs et ralentir le uC
}
