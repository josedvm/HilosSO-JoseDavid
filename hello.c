#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *myTid(void *null){

pthread_t tid = pthread_self();
	printf("Hola %ld\n", (long)tid);
	pthread_exit(NULL);
}  

int main(int argc, char **argv){

	int hilos =0;
int aux = 0;
int j = 0;
	if(argc != 2){

		printf("Por favor digite un numero hilos a usar.\n");
		return EXIT_FAILURE;
	}

	hilos = atoi(argv[1]);
	pthread_t ids[hilos];

	for(j = 0; j < hilos; j++){

		aux = pthread_create(&ids[j], NULL, myTid, NULL);
		
		if(aux){
			
			printf("!Error en la creacion de los hilos!\n");
			return EXIT_FAILURE;
		}

	}
for(j = 0; j < hilos; j++){
pthread_join(ids[j], NULL);
}
	pthread_exit(NULL);
	return EXIT_SUCCESS;
}
