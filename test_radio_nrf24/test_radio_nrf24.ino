/*
   ______               _                  _///  _           _                   _
  /   _  \             (_)                |  __\| |         | |                 (_)
  |  [_|  |__  ___  ___ _  ___  _ __      | |__ | | ___  ___| |_ _ __ ___  _ __  _  ___  _   _  ___
  |   ___/ _ \| __|| __| |/ _ \| '_ \_____|  __|| |/ _ \/  _|  _| '__/   \| '_ \| |/   \| | | |/ _ \
  |  |  | ( ) |__ ||__ | | ( ) | | | |____| |__ | |  __/| (_| |_| | | (_) | | | | | (_) | |_| |  __/
  \__|   \__,_|___||___|_|\___/|_| [_|    \____/|_|\___|\____\__\_|  \___/|_| |_|_|\__  |\__,_|\___|
                                                                                      | |
                                                                                      \_|
  Fichier:      HelloWorldNRF24L01-Emetteur
  Description:  Emission d'un "Hello World" via un NRF24L01
  Auteur:       Passion-Électronique

  Librairie utilisée : https://github.com/nRF24/RF24

  Créé le 19.03.2021
*/
#include <SPI.h>
#include <RF24.h>

#define pinCE 7         // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN 8        // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel "PIPE1"  // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

RF24 radio(pinCE, pinCSN);  // Instanciation du NRF24L01

const byte adresse[6] = tunnel;            // Mise au format "byte array" du nom du tunnel
const char message[] = "Hello World !!!";  // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)

// LED_BUILTIN won't work as SPI uses pin 13 too
const int ledPin = 6;  // the number of the LED pin

void setup() {
  Serial.begin(9600);  // opens serial port, sets data rate to 9600 bps
  Serial.println("Start");
  pinMode(ledPin, OUTPUT); 
  radio.begin();                   // Initialisation du module NRF24
  radio.openWritingPipe(adresse);  // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);   // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.stopListening();           // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)
  Serial.println("Ready");
}

void loop() {
  Serial.println("Loop");
  bool rslt;
  rslt = radio.write(&message, sizeof(message));  // Envoi de notre message
  // Always use sizeof() as it gives the size as the number of bytes.
  Serial.print("Data Sent ");
  Serial.print(message);
  if (rslt) {
    Serial.println(" > Acknowledge received");
    digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);                      // wait for a second
    digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
    delay(500);                             // wait for a second
  } else {
    Serial.println(" > Tx failed");
    digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);                      // wait for a second
    digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
    delay(1400);                             // wait for a second  
  }
}
