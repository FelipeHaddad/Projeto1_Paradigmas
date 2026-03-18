#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create

    polinomio *p = malloc(sizeof(polinomio)); 
     
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
    int somaTotal = 0;
    // potenciaDeX começa em 1, pois esta incluindo o coeficiente[0]
    int potenciaDeX = 1;

    // Vai lendo o polinomio do menor grau até o maior grau, incrementando a potencia de x
    for (int i = 0; i <= p->grau; i++) {
        somaTotal += p->coeficientes[i] * potenciaDeX;
        potenciaDeX *= x;
    }

    return somaTotal;
}


polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro
    // Pega o maior grau entre os polinomios para poder percorrer na soma
    int maiorGrau = (p->grau >= q->grau) ? p->grau : q->grau;
    // Inicializa novo polinomio que servira como resultado da soma dos polinomios p e q
    polinomio *w = poli_create(maiorGrau);

    for (int i = 0; i <= maiorGrau; i++){
        // Verifica se o grau do polinomio é menor que o grau atual, para caso seja menor retornar 0 para a variavel
        int pol1 = (i <= p->grau) ? p->coeficientes[i] : 0;
        int pol2 = (i <= q->grau) ? q->coeficientes[i] : 0;

        poli_ins_termo(w, i, (pol1 + pol2));
    }

    return w;
}


polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}