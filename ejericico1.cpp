/*  MPI_Reduce  */
// Cesar Madera, Enrique Sobrados, Stephano Württele

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main(int argc, char *argv[]) {
    int me, numprocs;
	int data,number ;
    int cont,right_guesses;
    vector<int> guesses; 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    
    srand(time(NULL)+me);

    if(me==0){
        guesses.resize(numprocs);
        number = rand()%100;
        right_guesses = 0;
    }


    for (int i=0;i<1000;i++){ 
        if(me == 0){
            cont=0;
            for(int j = 1;j<numprocs;j++){
                MPI_Recv(&guesses[j],1,MPI_INT,j,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
                if(guesses[j] == number) cont++;
            }
            if(cont==numprocs-1){
                right_guesses++;
            }
        }else{
            int guess = rand()%100;
            MPI_Send(&guess,1,MPI_INT,0,i,MPI_COMM_WORLD);
        }
    }	

    if (me == 0){
        printf("right guesses: %d",right_guesses);
    }
	
    MPI_Finalize();
}
    
// Considerando la probabilidad de 1/10000000 de que realmente todos acierten en alguno de los mil intentos, tiene que de 0 al ejecutarlo, pues es muy improbable que suceda.