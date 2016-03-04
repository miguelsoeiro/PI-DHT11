/*
 ============================================================================
 Name        : teste.c
 Autors      : Miguel Soeiro, Andre Cervera, Joao Batista
 Versao      : 0.10
 Descriçao   : Esta é  a versão é a versao final  que tem o principal modo e o
 			modo simulado em comentario, visto que exitem coisas que nao dao
			executar em ser no Raspberry PI
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>

#ifdef AAC_RASPBERRY
	#include <wiringPi.h>
#endif


/* CONSTANTES */
/* usei red e green, porque se destingue melhor que vermelho e verde */
#define greenPIN 37 // corresponde ao #26 (led verde) [LED1]
#define redPIN 35 // corresponde ao #19 (led vermelho)[LED2]
#define botaoPIN 33 // corresponde ao #13

 void confirma(){
 	char resp[4];
 	printf("Tem a Certeza que quer SAIR ? (Escreva 'sim' para sair)\n");
 	scanf("%3s",resp);
 	if(strcmp("sim",resp)) {
 		printf("Nao saiu\n");
 	} else {
 		printf("Saiu\n");
 		exit(0);
 	}
 }

 char * nome_ficheiro()
 {
 	static char filename[30];
 	struct timeval tv;
 	time_t timenow;

 	gettimeofday(&tv, NULL);
 	timenow=tv.tv_sec;

 	strftime(filename,sizeof(filename),"log_%Y-%m-%d_%H-%M-%S.bin",localtime(&timenow));
 	return filename;

 }

 int erros(int ERR, int T){
 	if (ERR > 120) {
 		exit(0);
 	}else{
		#ifdef AAC_RASPBERRY
	 		digitalWrite(redPIN, HIGH);
	 		delay(T);
	 		digitalWrite(redPIN, LOW);
	 		delay(T);
		#endif
 	}
 }

 struct informacao
 {
 	uint8_t h;
 	uint8_t t;
 	char time[20];
 };


 int main(void){

	#ifdef AAC_RASPBERRY
 	wiringPiSetup();
	#endif

 	char *filename;
 	filename = nome_ficheiro();
 	signal(SIGINT, confirma);

	struct informacao info;// Inicialicialização
	struct timeval tv;

	int ERR = 0, T = 0;

	for (;;) {
/*		ERR = 0;
		#ifdef AAC_RASPBERRY
			digitalWrite(redPIN, LOW);
			digitalWrite(greenPIN, HIGH);
		#endif
		int b=1; // para quando está fora do raspberry PI
		do {
			if( b==1 ){ //(chdir("/media/diymount/") == 0) || (fopen(filename, "wb") != NULL){  USB OK
			FILE *fileout;
			fileout = fopen(filename, "wb");
				for(;;){
					if(ler_sensor(&info.h,&info.t) == 0){
						// implementação do tempo /
						gettimeofday(&tv, NULL);
						time_t timenow = tv.tv_sec;
						strftime(info.time,sizeof(info.time),"%Y-%m-%d %T",localtime(&timenow));
						printf("%s, %u, %u\n", info.time, info.h, info.t);
						fwrite(&info, sizeof(struct informacao), 1, fileout);

						if (fwrite != 0) {
							ERR = 0;
							#ifdef AAC_RASPBERRY
								digitalWrite(greenPIN, HIGH);
							#endif
						}else{
							ERR = ERR + 1;
							T = 1000;
							erros(ERR,T);
						}
					}else {
						printf("já estou no desespero!\n");
					}
				}
				fclose(fileout);

			}else{ // USB não OK
				T= 500;
				ERR = ERR +1; // ERR += 1;
				erros(ERR, T);
			}
		} while(b==1); // para testar em modo simulados, sem digitalRead
	}
*/
	#ifdef AAC_RASPBERRY
		ERR = 0;
		#ifdef AAC_RASPBERRY
			digitalWrite(redPIN, LOW);
			digitalWrite(greenPIN, HIGH);
		#endif
		int b=1; // para quando está fora do raspberry PI
		do {
			if((chdir("/media/diymount/") == 0) || (fopen(filename, "wb") != NULL){ // USB OK
			FILE *fileout;
			fileout = fopen(filename, "wb");
				for(;;){
					if(ler_sensor(&info.h,&info.t) == 0){
						// implementação do tempo /
						gettimeofday(&tv, NULL);
						time_t timenow = tv.tv_sec;
						strftime(info.time,sizeof(info.time),"%Y-%m-%d %T",localtime(&timenow));
						printf("%s, %u, %u\n", info.time, info.h, info.t);
						fwrite(&info, sizeof(struct informacao), 1, fileout);

						if (fwrite != 0) {
							ERR = 0;
							#ifdef AAC_RASPBERRY
								digitalWrite(greenPIN, HIGH);
							#endif
						}else{
							ERR = ERR + 1;
							T = 1000;
							erros(ERR,T);
						}
					}else {
						printf("já estou no desespero!\n");
					}
				}
				fclose(fileout);

			}else{ // USB não OK
				T= 500;
				ERR = ERR +1; // ERR += 1;
				erros(ERR, T);
			}
		} while(digitalRead(botaoPIN)== HIGH);
	#endif // ESTE É PARA QUANDO ESTIVER NO RASPBERRY PI
	//return EXIT_SUCCESS;;
	}
	return 0;
}
