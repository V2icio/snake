#include<stdio.h>

#define MAX 800


	typedef struct fila{

		int item[MAX];
		int ini, fim, cont;
	}fila;

	void iniFila(fila *f1){

		f1->ini = 0;
		f1->fim = 0;
		f1->cont = 0;
	}

	int filaCheia(fila *f1){

		if(f1->cont == MAX){

			return 1;
		}else{

			return 0;
		}
	}

	int filaVazia(fila *f1){

		if(f1->cont == 0){

			return 1;
		}else{

			return 0;
		}
	}

	int push(fila *f1, int x){

		if(filaCheia(f1) == 1){

			return 1;
		}else{

			f1->item[f1->fim] = x;
			f1->cont++;
			if(f1->fim == MAX - 1){

				f1->fim = 0;
			}else{

				f1->fim++;
			}
			return 0;
		}
	}

	int pop(fila *f1, int *x){

		if(filaVazia(f1) == 1){

			return 1;
		}else{

			*x = f1->item[f1->ini];
			f1->cont--;
			if(f1->ini == MAX - 1){

				f1->ini = 0;
			}else{

				f1->ini++;
			}
			return 0;
		}
	}

	void imprimeFila(fila *f1){

        int aux = f1->ini, i;
        for(i = 0; i < f1->cont; i++){

            printf("%d  ", f1->item[aux]);
            if(aux == MAX - 1){
                aux = 0;
            } else {
            aux ++;
            }
        }
	}

	int mostraCont(fila *f1){

        return f1->cont;
	}
