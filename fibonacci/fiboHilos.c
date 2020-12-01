#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tiempo.h"



typedef struct struct_dato{
    int *numero;
    int n;
    int busqueda;
    char flag;
}dato;

int min(int x, int y){
    return (x<=y) ? x : y;
}

void *busqFibo(void* args){
    int penultimo = 0, ultimo = 1, offset = -1, actual = penultimo + ultimo, i;
    dato* dato1 = (dato*)args;
    void* ofs;
    
    while(actual < dato1->n){
        penultimo = ultimo;
        ultimo = actual;
        actual = penultimo + ultimo;
    }
    
    while(actual > 1){
        i = min(offset + penultimo, dato1->n-1);
        
        if(dato1->numero[i] < dato1->busqueda){
            actual = ultimo;
            ultimo = penultimo;
            penultimo = actual - ultimo;
            offset = i;
        }
        else if(dato1->numero[i] > dato1->busqueda){
            actual = penultimo;
            ultimo = ultimo - penultimo;
            penultimo = actual - ultimo;
        }
        else{
            dato1->flag = 's';
            pthread_exit(0);
        }
    }
    
    if(ultimo && dato1->numero[offset+1] == dato1->busqueda){
        dato1->flag = 's';
        pthread_exit(0);
    }
    
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    
    int i = 0, j, b, n;
    int *numero;
    int *num1;
    int *num2;
    pthread_t hilo1, hilo2;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    int busqueda[20]={322486, 14700764, 3128036, 6337399, 61396, 10393545, 2147445644, 1295390003, 450057883, 187645041, 1980098116, 152503, 5000, 1493283650, 214826, 1843349527, 1260839354, 2109248666, 2147470852, 0};
    dato dato1, dato2;
    char flag_int='n';
    
    if(argc < 2){
        printf("Modo de ejecucion: \"%s cantNum\"\n", argv[0]);
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
            
            num1 = malloc(sizeof(int) * n/2);
            num2 = malloc(sizeof(int) * n/2);
            
            for(i = 0; i < n/2; i++){
                num1[i] = numero[i];
            }
            for(i = 0, j = n/2; i < n/2; i++){
                num2[i] = numero[j];
                j++;
            }
            
            dato1.numero = num1;
            dato1.n = n/2;
        
            dato2.numero = num2;
            dato2.n = n/2;
            
            
            for(i = 0; i < 20; i++){
                dato1.flag = 'n';
                dato2.flag = 'n';
                
                dato1.busqueda = busqueda[i];
                dato2.busqueda = busqueda[i];
                
                uswtime(&utime0, &stime0, &wtime0);
                pthread_create(&hilo1, NULL, busqFibo, (void*)&dato1);
                pthread_create(&hilo2, NULL, busqFibo, (void*)&dato2);
                
                pthread_join(hilo1, NULL);
                pthread_join(hilo1, NULL);
                
                uswtime(&utime1, &stime1, &wtime1);
                
                if(dato1.flag == 's' || dato2.flag == 's')
                    flag_int='s';
                else
                    flag_int='n';
                
                printf("\n");
                printf("%d\t| %d\t| %.10f\t| %c",busqueda[i], n, wtime1 - wtime0, flag_int);
                printf("\n");
            }
        
            free(numero);
            free(num1);
            free(num2);
        }
    }
    
    return 0;
}
