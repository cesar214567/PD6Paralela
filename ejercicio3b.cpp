/*  MPI_Reduce  */
// Cesar Madera, Enrique Sobrados, Stephano Württele
#include <omp.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <chrono>
#define N 320
using namespace std;

void MatVecMult(double matrix[N][N], double v[N],int threads){
    double result[N]={0};
    #pragma omp parallel for  num_threads(threads)
    for (int i=0;i<N;i++){
        //printf("la iteracion i:%d la hizo el proceso: %d \n",i,omp_get_thread_num());
        for (int j=0;j<N;j++){
            result[i]+=( matrix[i][j]*v[j]);
        }
    }
}

int main(){
    srand(time(NULL));
    double matrix[N][N], v[N];
    for(int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrix[i][j]=rand()%10;
        }
        v[i] = rand()%10;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    MatVecMult(matrix,v,2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout<<"time was with 2 threads: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"microsegundos"<<endl;
    begin = std::chrono::steady_clock::now();
    MatVecMult(matrix,v,4);
    end = std::chrono::steady_clock::now();
    cout<<"time was with 4 threads: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"microsegundos"<<endl;
    begin = std::chrono::steady_clock::now();
    MatVecMult(matrix,v,8);
    end = std::chrono::steady_clock::now();
    cout<<"time was with 8 threads: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"microsegundos"<<endl;
    begin = std::chrono::steady_clock::now();
    MatVecMult(matrix,v,16);
    end = std::chrono::steady_clock::now();
    cout<<"time was with 16 threads: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()<<"microsegundos"<<endl;
}
