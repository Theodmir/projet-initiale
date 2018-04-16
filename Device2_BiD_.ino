#include <PJON.h>
//#include <PJONMaster.h> 
//#include <PJONSlave.h>  
  uint8_t bus_id[] = {0, 0, 0, 1};
  PJON<SoftwareBitBang> bus(2);
  int pinLed;
  int pinBouton; 
  boolean etat;
  char packet1[] = "********";
  char packet2[]= "********";
    
void setup() {
  bus.set_communication_mode(PJON_HALF_DUPLEX);//description du genre de communication(simple, Half-Duplex)
  pinLed=11;
  pinBouton=2;
  pinMode(pinLed, OUTPUT);
  bus.strategy.set_pin(12);
  bus.begin();
  bus.set_receiver(receiver_function2); // appelle d'une fonction de réception qui prendra la valeur
                                       //de celle-ci
  attachInterrupt (0, bouton2, CHANGE);
}
void bouton2() //programme permettant le retour de la valeur du bouton et donc de la led pour plus tard
{
  boolean etat=digitalRead(pinBouton);//description de la variable (0 ou 1)et lecture de la variable
      if (etat == HIGH)
      
  {
  bus.send(1, packet1 , 5); // si bouton fermé alors on envoie "A" au bus numéro 2, une seule fois
  
  }
  else if (etat == LOW)
  {
  bus.send(1, packet2 , 5);// sinon on envoie "B" Une seule fois
  }
}
void receiver_function2(
  uint8_t *payload, 
  uint16_t length, 
  const PJON_Packet_Info &packet_info
)//fonction de réception contenant un tableau, lal ongueur de celui-ci et une constante
{
  if(payload[0] == 'A') 
  {
    digitalWrite(11, HIGH);//si le tableau à la valeur 0 a le caractère 'A' alors le Pin13(LED) sera à
  }                        // l'état haut
  else if (payload[0]=='B')
  {
    digitalWrite(11, LOW);//si le tableau à la valeur 0 a le caractère 'B' alors le Pin13(LED) sera à
  }                       // l'état bas
  else
  {
    digitalWrite(11, LOW);//si le tableau à la valeur 0 n'a rien alors le Pin13(LED) sera à
  }                       // l'état bas
}

void loop() {
  bus.receive(1000); // attente de 1 secondes entre chaque réception
   bus.update();//en attente d'un changement du Bus
}


