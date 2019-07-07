//Autores:Zambrano Bryan, Alex Arevalo
//Estudiantes de la Escuela Politécnica Nacional, Quito Ecuador
//Para la materia de Computación Distribuida
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<time.h>

/** @brief funcion para generar numeros randomicos con MPI
	@details esta función permite generar los números de manera paralela sin que estos se repitan
	@param semilla: es la semilla que cambia en cada invocacion para generar los números
	@return retorna el número aleatorio
*/
int piensa_un_numero(int semilla){
//semilla aleatoria
	srand(time(NULL)*semilla);
//obtencion de numero randomico desde 0 a 10
	int num=rand()%10;
return num;	
}


int main (int argc,char** argv){
//declaracion de varibales, id= identificador proceso, numP= numero de procesos
//dato= dato a enviar a todos los procesos, c= contador de intentos
//fin= indica si se finaliza el proceso
	int id,numP;
	int dato=0;
	int fin=0;
	int c=0;
//inicializa MPI
	MPI_Init(&argc,&argv);
//obtener el numero de procesos
	MPI_Comm_size(MPI_COMM_WORLD,&numP);
//variable donde se almacenará los datos enviados por los procesos
	int datos[numP];
//obtener el id de cada proceso
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
//bucle while, termina cuando se han echo 1000 comparaciones o todos los numeros son iguales
while(fin==0 && c<1000){
//seteamos dato aleatorio a enviar
	dato=piensa_un_numero(id+c+dato);
//enviamos a todos los procesos con allgather
	MPI_Allgather(&dato,1,MPI_INT,&datos,1,MPI_INT,MPI_COMM_WORLD);
//dado que utilizamos allgather cualquier proceso puede realizar la comparacion, en este caso utilizaremos el master
	if(id==0){
		for(int i=0;i<numP-1;i++)
		if(datos[i]==datos[i+1])
		fin=1;
		else{
		fin=0;
		break;
		}
	}
//todos los procesos aumentan el contador debido a que, la semilla depende tambien del contador
	c++;
	//fin del bucle
	}
//master imprime los datos de todos los procesos y el numero de intentos
//en el caso de ser iguales los datos
//caso contrario imprime la terminacion del juego
	if(id==0){
		if(fin==1){
		for(int i=0; i<numP;i++)
		printf("Dato del proceso %d es :%d\n",i,datos[i]);
		printf("Numero de intentos antes de terminar el juego: %d\n",c);
		return 0;
		}else{
		printf("Numero de intentos superado, fin del juego %d\n",c);
		}
	}
//finaliza el proceso MPI
MPI_Finalize();
}
