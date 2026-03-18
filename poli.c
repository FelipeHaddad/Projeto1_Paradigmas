#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create

    polinomio *p = malloc(sizeof(p) * grau); 
     
    if(p == NULL){   
        return NULL;
    }

    p->grau = grau;
    p->termos = 0;

    p->coeficientes = (int*) calloc(grau + 1, sizeof(int));

    if(p->coeficientes == NULL){
        free(p);
        return NULL;
    }

    return p;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy

    free((*p)->coeficientes);
    free(*p);

    *p = NULL;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente

    if (exp > p->grau || exp < 0){
        return 0;
    }

    if(p->coeficientes[exp] == 0 && coef != 0){
        p->termos++;
    }

    p->coeficientes[exp] = coef;

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente

    if(coef == NULL){
        return 0;
    }
    
    if(exp < 0 || exp > p->grau){
        return 0;
    }

    if(p->coeficientes[exp] == 0){
        return 0;
    }
    
    *coef = p->coeficientes[exp];

    return 1;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    int expTotal = p->grau;
    int somaTotal = 0;
    
    while(expTotal != 0){
        int potencia = x;
        for (int i = 1; i <= expTotal; i++){
           potencia *= i;  
        }
        somaTotal = ((p->coeficientes[expTotal]) * potencia) ;
        expTotal--;
    }

    return (somaTotal + (p->coeficientes[0]*x));
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}