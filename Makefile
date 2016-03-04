# Para compilar o programa para correr sem LEDs e com sensor dummy (PC ou Raspberry):
#      make teste
#
# Para compilar o programa para correr com LEDs e sensor (so Raspberry);
#      make AAC_RASPBERRY=1 teste 

CFLAGS = -Wall
LDFLAGS = -lm

ifdef AAC_RASPBERRY
LDFLAGS += -lwiringPi
CFLAGS += -DAAC_RASPBERRY=$(AAC_RASPBERRY)
endif

teste: teste.c dht11ler.c
	gcc $(CFLAGS) -o teste  teste.c dht11ler.c $(LDFLAGS) -w
	gcc testeLer.c -o testeLer -w

clean: 
	rm teste
