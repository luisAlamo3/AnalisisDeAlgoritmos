#include <stdio.h>
#include <stdlib.h>
#include "tiempo.h"

int busqBin(int* numero, int cant, int busqueda, int max){
    
    int i, min, med;
    min = max / 2;
    
    if(max > cant){
        max = cant;
    }
    med = (min + max) / 2;
    
    while(min <= max){
        med = (min + max) / 2;
        
        if(busqueda == numero[med]){
            return med + 1;
        }    
        else if(busqueda < numero[med]){
            max = med - 1;
        }
        else{
            min = med + 1;
        }
    }
    
    return -1;
}

int busqExp(int* numero, int max, int busqueda){
    int i = 1;
    
    if(numero[0] == busqueda){
        return 0;
    }
    
    while(i < max && numero[i] <= busqueda){
            i *= 2;
    }
    
    return busqBin(numero, max, busqueda, i);
    
}

int main(int argc, char *argv[]){
    
    int n = 0, i = 0, b;
    int *numero;
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
                
                b = busqExp(numero, n, busqueda[i]);
                
                if(b == -1){
                    flag = 'n';
                }
                else{
                    flag = 's';
                }
                
                uswtime(&utime1, &stime1, &wtime1);
                
                printf("\n");
                printf("%d\t| %d\t| %.10f\t| %c",busqueda[i], n, wtime1 - wtime0, flag);
                printf("\n");
            }
        }
}
    return 0;
}