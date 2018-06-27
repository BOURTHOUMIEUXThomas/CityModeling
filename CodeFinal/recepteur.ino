#include <VirtualWire.h>

int i;
char id[] = "tuture : ";
int conteur;

void setup() {
  Serial.begin(9600);
  Serial.println("Debut de la communication......");
  vw_set_rx_pin(8);
  vw_setup(2000); 
  vw_rx_start();
}

void loop() {
    uint8_t message[VW_MAX_MESSAGE_LEN];
    uint8_t  messlenght = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(message, messlenght)) // Non-blocking
    {
      conteur = 0;
      for(i = 0 ; i < sizeof(message) ; i++){
        if(id[i] == message[i]){
          conteur++;
        }
      }
      if(conteur == 9){
        vw_wait_rx();
         char valeur[VW_MAX_MESSAGE_LEN];
         char received[VW_MAX_MESSAGE_LEN];
         if (vw_get_message(valeur, messlenght)) // Non-blocking
         {
          Serial.print("La distance est :");
          Serial.println("\n");
          Serial.println(valeur); //affiche le vrai char
          for (i = 0; valeur[i] != '\0'; i++) { 
            Serial.print(char(valeur[i] - 1)); //décryptage
            received[i] = valeur[i] - 1;
          }
          Serial.println("\n");
}
          Serial.println(valeur);
          Serial.println(received);
         }
      }else{
        //Serial.println("Message d'une autre voiture");
      }
} 



