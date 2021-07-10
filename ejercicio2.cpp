/*  MPI_Reduce  */
// Cesar Madera, Enrique Sobrados, Stephano Württele

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

/* Asignar valor cualquiera a los vectores (para prueba) */
void calculo_a(double  a[], int n){
    for( int i = 0; i < n; i++){
        a[i] *= i;
    }
}
void calculo_b(double  a[], int n){
    for( int i = 0; i < n; i++){
        a[i] *= i;
    }
}
void calculo_c(double  a[], int n){
    for( int i = 0; i < n; i++){
        a[i] *= i;
    }
}

double OpVec(double A[], double B[], double C[], int n) {
    int i, j;
    double s1, s2, a, res;
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            calculo_a(A, n); /*  funcion  calculo a */
        }
        #pragma omp section
        {
            calculo_b(B, n); /*  funcion  calculo a */
        }
        #pragma omp section
        {
            calculo_c(C, n); /*  funcion  calculo a */
        }
    }

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (i = 0; i < n; i++) {
                /*  primer  bucle  for*/
                s1 = 0;
                for (j = 0; j < n; j++) s1 += A[i] * B[i];
                for (j = 0; j < n; j++) A[i] *= s1;
            }
        }
        #pragma omp section
        {
            for (i = 0; i < n; i++) {
                /*  segundo  bucle  for */
                s2 = 0;
                for (j = 0; j < n; j++) s2 += B[i] * C[i];
                for (j = 0; j < n; j++) C[i] *= s2;
            } /*  calculo  final  */
        }
    }
    a = s1 / s2;
    res = 0;
    for (i = 0; i < n; i++) res += a * C[i];
    return res;
}



int main(){
    srand(time(NULL));
    int n = 4;
    double a[n], b[n], c[n];
    for(int i=0;i<n;i++){
        a[i] = rand()%10;
        b[i] = rand()%10;
        c[i] = rand()%10;
    }
    cout << OpVec(a,b,c,n) << endl;
}
