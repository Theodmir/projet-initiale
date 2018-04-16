#include <PJON.h>
//#include <SPI.h>
//#include <PJONMaster.h>  // Include PJONMaster class
//#include <PJONSlave.h>
    uint8_t bus_id[] = {0, 0, 0, 1}; // réseaux sur lequelle le bus de donné se trouve
    PJON<SoftwareBitBang> bus(1); // numéro du BUS 
    int pinLed;
    int pinBouton; 
    boolean etat;
    char packet1[] = "********";
    char packet2[]= "********";
    

void setup() {
  bus.set_communication_mode(PJON_HALF_DUPLEX);//description du genre de communication(simple, Half-Duplex)
  bus.strategy.set_pin(12);//pin ou le l'on définie le BUS
  pinMode (pinBouton,INPUT);
  pinBouton=2;
  bus.begin();//début de descirption de ce que va faire le bus de donné
  attachInterrupt (0, bouton1, CHANGE);
  bus.set_receiver(receiver_function1);
}

void bouton1() //programme permettant le retour de la valeur du bouton et donc de la led pour plus tard
{
  boolean etat=digitalRead(pinBouton);//description de la variable (0 ou 1)et lecture de la variable
      if (etat == HIGH)
  {
  bus.send_packet(2, packet1 , 10); // si bouton fermé alors on envoie "A" au bus numéro 2, une seule fois
  }
  else if (etat == LOW)
  {
  bus.send_packet(2, packet2 , 10);// sinon on envoie "B" Une seule fois
  }
}
void receiver_function1(
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
 // else
  //{
   // digitalWrite(11, LOW);//si le tableau à la valeur 0 n'a rien alors le Pin13(LED) sera à
  //}                       // l'état bas
}
void loop() {
  bus.receive(1000);
  bus.update();//en attente d'un changement du Bus
}
