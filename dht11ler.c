/*
 * Funcao para leitura do sensor DHT-11.
 */
#include <stdint.h>
 
#ifdef AAC_RASPBERRY
#include <wiringPi.h>
#endif

#include "dht11ler.h"

/*
 * Recebe com argumentos dois apontadores para inteiros de 8 bits.
 * Guarda a humidade na variavel apontada pelo primeiro argumento.
 * Guarda a temperatura na variavel apontada pelo segundo argumento.
 * Retorna 0 se os valores forem validos, != 0 se houve erro na leitura.
 */
int ler_sensor(uint8_t *humidade_ptr, uint8_t *temperatura_ptr)
{
#ifdef AAC_RASPBERRY
  //Start
  pinMode(PINO,OUTPUT);
  digitalWrite(PINO,LOW);
  delay(18);
  digitalWrite(PINO,HIGH);
  delayMicroseconds(40);
  
  //Modo leitura
  pinMode(PINO,INPUT);
  int i;
  int ultimo_estado = 1;
  int contador = 0;
  uint8_t dados[5];
  dados[0] = dados[1] = dados[2] = dados[3] = dados[4] = 0;
  int j=0;
  for (i=0; i<85; i++) {
    contador = 0;
    while(digitalRead(PINO) == ultimo_estado) {
      contador++;
      delayMicroseconds(1);
      if (contador == 255)
        break;
    }
    ultimo_estado = digitalRead(PINO);
    
    if (contador == 255)
      break;
    
    if (i<4)
      continue;
      
    if (i%2 == 0) {
      dados[j/8] <<= 1;
      if (contador > 16) {
        dados[j/8] |= 1;
      }
      j++;
    }
    
  }
  
  //verificar integridade
  int integridade = (j >= 40) &&
  	(dados[4] == (dados[0]+dados[1]+dados[2]+dados[3]) & 0xFF);
  
  if (integridade) {
    *humidade_ptr = dados[0];
    *temperatura_ptr = dados[2];
  }
  
  return integridade;
#else
  *humidade_ptr = 80;
  *temperatura_ptr = 22;
  return 0;
#endif
}
