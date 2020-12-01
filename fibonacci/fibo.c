#include<stdio.h>
#include<stdlib.h>
#include "tiempo.h"

int min(int x, int y){
    return (x<=y) ? x : y;
}

int busqFibo(int* numero, int n, int busqueda){
    int penultimo = 0, ultimo = 1, offset = -1, actual = penultimo + ultimo, i;
    
    while(actual < n){
        penultimo = ultimo;
        ultimo = actual;
        actual = penultimo + ultimo;
    }
    
    while(actual > 1){
        i = min(offset + penultimo, n-1);
        
        if(numero[i] < busqueda){
            actual = ultimo;
            ultimo = penultimo;
            penultimo = actual - ultimo;
            offset = i;
        }
        else if(numero[i] > busqueda){
            actual = penultimo;
            ultimo = ultimo - penultimo;
            penultimo = actual - ultimo;
        }
        else{
            return i+1;
        }
    }
    
    if(ultimo && numero[offset+1] == busqueda)
        return offset+1;
    
    return -1;
}

int main(int argc, char *argv[]){
    
    int i = 0, b;
    int *numero;
    int n = 0;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    int busqueda[20]={322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1260839354, 2109248666, 2147470852, 0};
    char flag = 'n';
    
    if(argc < 2){
        printf("Modo de ejecucion: \"%s cantNum NumBusq\"\n", argv[0]);
        return -1;
    }
    else{
        n = atoi(argv[1]);
        numero = malloc(sizeof(int) * n);
        
        
        if(numero == NULL){
            printf("Error al asignar memoria dinamica.\n");
            return -1;
        }
        else{
            
            for(i = 0; i < n; i++){
                scanf("%d", &numero[i]);
            }
            
            printf("Número a buscar\t| Tamaño de n\t| Tiempo real\t| Encontrado");
            
            for(i = 0; i < 20; i++){
                uswtime(&utime0, &stime0, &wtime0);

                b = busqFibo(numero, n, busqueda[i]);
                
                if(b == -1){
                    //printf("No se encontró el número.\n");
                    flag = 'n';
                }
                else{
                    //printf("El número se encuentra en la posicion: %d\n", b);
                    flag = 's';
                }
                
                uswtime(&utime1, &stime1, &wtime1);
                
                printf("\n");
                printf("%d\t| %d\t| %.10f\t| %c",busqueda[i], n, wtime1 - wtime0, flag);
                printf("\n");
                /*
                printf("\n");
                printf("real (Tiempo total) %.10f s\n", wtime1 - wtime0);
                printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
                printf("sys (Tiempo en acciones de E/S) %.10f s\n", stime1 - stime0);
                printf("CPU/Wall %10.f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 -wtime0));
                printf("\n");
                
                printf("\n");
                printf("real (Tiempo total) %.10e s\n", wtime1 -wtime0);
                printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
                printf("sys (Tiempo en acciones de E/S) %.10e s\n", stime1 - stime0);
                printf("CPU/Wall %10.f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 -wtime0));
                printf("\n");
                */
            }
            
        }
    }
    return 0;
}
