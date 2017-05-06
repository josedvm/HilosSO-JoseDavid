#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE;	// Longitud en el eje X.
double numRectxThread = (double)(MAXRECT / MAXTHREAD);	// Cuantos rectangulos por hilo.
double base_length = 0;	// Variable que tiene el ancho de cada rectangulo.
double sumTotal = 0;	// Variable que tendra la suma total.
double partialSums[MAXTHREAD];	// Variable que tiene la suma parcial de cada hilo.

// Funcion a la que se le calculara la integral desde 0 hasta 1.
double function(double x){
	
	return x * x; 
}

void *calcular(void *arg){
	
	int id = (int)arg;
	// Loslimit es la posicion inicial del hilo.
	double loslimit = (base_length * numRectxThread * id);
	// Inicializar la variable de la suma de las areas de cada hilo.
	partialSums[id] = 0;
	int i = 0;
	
	for(i = 0; i < numRectxThread; i++){
		
		partialSums[id] += (base_length * function(loslimit));
		loslimit += base_length;
	}

	printf("El hilo %d calculo una suma parcial de %lf.\n", id, partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	
	// Vectores para almacenar los identificadores de los hilos.
	pthread_t hilos[MAXTHREAD];
	int taskids[MAXTHREAD];




	int aux = 0, i = 0;

	base_length = (double)(length / MAXRECT);
	printf("Base length: %lf y numRectxThread: %lf\n", base_length, numRectxThread);
	
	// Creacion de los hilos 
	for (i = 0; i < MAXTHREAD; i++){
		
		taskids[i] = i;
		aux = pthread_create(&hilos[i], NULL, calcular, (void *)taskids[i]);
		
		if(aux){
			
			printf("!Error en la creacion de los hilos!\n");
			exit(-1);
		}
	}
	
	
	for(i = 0; i < MAXTHREAD; i++){
		// Ciclo donde se espera el resultado de cada hilo.
		pthread_join(hilos[i], NULL);
		sumTotal += partialSums[i];
	}
	
	printf("Suma total: %lf\n", sumTotal);
	pthread_exit(NULL);
}								
