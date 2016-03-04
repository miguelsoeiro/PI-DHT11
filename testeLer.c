/*
 ============================================================================
 Name        : testeLer.c
 Autor       : Miguel Soeiro
 Versao      : 0.5
 Descriçao   : le do ficheiro bin e escreve no ficheiro .csv
 			(ainda tem o erro de spamar a ultima medição)
 ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

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

  strftime(filename,sizeof(filename),"log_%Y-%m-%d_%H-%M-%S.csv",localtime(&timenow));
  return filename;

}

struct informacao
{
	uint8_t h;
	uint8_t t;
	char time[20];

};


int main(int argc, char ** argv){

	if (argc != 2) {
		printf("Utilização -> nomeDoPrograma ficheiroQueSeQuerAbrir \n");
		printf("\n");
		return 0;
	}

	char *filename;
	filename = nome_ficheiro();

	char *c1 = argv[1];
	int tamanho = sizeof(c1);

	struct informacao infoRead;

    FILE* filein = fopen(c1, "rb");
	FILE* stream = fopen(filename, "w");

	signal(SIGINT, confirma);

	for(;;){
		fread(&infoRead, sizeof(struct informacao), 1, filein);
		printf("%s %u %u\n", infoRead.time, infoRead.h, infoRead.t);
		fprintf(stream,"%s,%u,%u\n", infoRead.time, infoRead.h, infoRead.t);
	}

	fclose(filein);
	fclose(stream);

 	return 0;
}
