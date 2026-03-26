#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    // Aloca espaço na memória
    polinomio *p = malloc(sizeof(polinomio)); 
     
    if(p == NULL){   
        return NULL;
    }

    p->grau = grau;
    p->termos = 0;

    // Aloca o vetor de coeficientes, utilizando o tamanho grau + 1 já que precisa
    // incluir o coeficiente 0 que não tem x
    // Chama calloc para alocar 0 em todos os coeficientes 
    p->coeficientes = (int*) calloc(grau + 1, sizeof(int));

    // Em caso de falha, libera o "p" para não ter vazamento
    if(p->coeficientes == NULL){
        free(p);
        return NULL;
    }

    return p;
}

void poli_destroy(polinomio **p){
    // Libera o vetor interno de coeficientes
    free((*p)->coeficientes);
    // Libera a estrutura do polinômio
    free(*p);

    // Define o ponteiro original como NULL
    *p = NULL;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // Valida se o expoente está dentro do limite definido na criação e se não é negativo
    if (exp > p->grau || exp < 0){
        return 0;
    }

    // Se a posição estava zerada e estamos inserindo um valor útil, incrementa o contador de termos
    if(p->coeficientes[exp] == 0 && coef != 0){
        p->termos++;
    } 
    // Caso o termo inserido no expoente seja 0, decrementa a 
    // variável "termos"
    else if (p->coeficientes[exp] != 0 && coef == 0){
        p->termos--;
    }

    // Coloca o coeficiente no expoente passado
    p->coeficientes[exp] = coef;

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // Verifica se o ponteiro de retorno é válido
    if(coef == NULL){
        return 0;
    }
    
    // Verifica se o expoente passado não está dentro do grau do 
    // polinômio passado
    if(exp < 0 || exp > p->grau){
        return 0;
    }

    // Se o coeficiente for zero, retorna 0, indicando que
    // não há coeficiente no expoente pedido
    if(p->coeficientes[exp] == 0){
        return 0;
    }
    
    // Passa o valor para a variável apontada por coef
    *coef = p->coeficientes[exp];

    return 1;
}

int calcula_px(polinomio *p, int x){
    int somaTotal = 0;
    // Potencia de X começa no grau 0, para somar a parte
    // que não tem x multiplicando
    long long potenciaDeX = 1;

    // Percorre todos os coeficiente a partir do grau 0 até o 
    // último grau do polinômio
    for (int i = 0; i <= p->grau; i++) {
        somaTotal += p->coeficientes[i] * potenciaDeX;
        // Atualiza o valor da potencia de x para o proximo grau
        potenciaDeX *= x;
    }

    return somaTotal;
}


polinomio * poli_soma(polinomio *p, polinomio *q){
    // O polinomio pós soma terá o grau do maior polinomio entre
    // os dois somados
    int maiorGrau = (p->grau >= q->grau) ? p->grau : q->grau;
    polinomio *w = poli_create(maiorGrau);

    for (int i = 0; i <= maiorGrau; i++){
        // Ao acessar o coeficiente do polinomio, verifica se 
        // o "i" atual valor maior que o grau do polinomio, pois
        // se tiver, atribui 0
        int pol1 = (i <= p->grau) ? p->coeficientes[i] : 0;
        int pol2 = (i <= q->grau) ? q->coeficientes[i] : 0;

        // No novo polinomio, insere a soma dos polinomios em
        // cada grau
        poli_ins_termo(w, i, (pol1 + pol2));
    }

    return w;
}


polinomio * poli_mult(polinomio *p, polinomio *q){
    // O grau do polinomio final é a soma dos graus dos
    // polinômios
    int grauMult = p->grau + q->grau;

    polinomio *m = poli_create(grauMult);

    if(m == NULL){   
        return NULL;
    }

    // Distribuitiva: cada termo de 'p' multiplica cada termo de 'q'
    for(int i = 0; i <= p->grau; i++){
        for(int j = 0; j <= q->grau; j++){
            // O expoente resultante da multiplicação é a soma dos expoentes (i + j)
            m->coeficientes[i + j] += p->coeficientes[i] * q->coeficientes[j];
        }
    }

    return m;
}

polinomio * poli_div(polinomio *p, polinomio *q) {
    // Se um ou outro polinomio for nulo não tem divisão
    // Se o divisor tiver grau 0, não tem divisão
    if (q == NULL || p == NULL || q->coeficientes[q->grau] == 0) {
        return NULL;
    }

    // Se o dividendo tiver grau menor que o divisor, o resultado é zero
    if (p->grau < q->grau) {
        return poli_create(0); 
    }

    int grau_quociente = p->grau - q->grau;
    polinomio *quociente = poli_create(grau_quociente);
    
    // Cria um polinomio que vai servir como o dividendo durante as operações, ou seja
    // vai reduzindo conforme forem feitas as divisões. Vamos usar ele para identificar se
    // o grau menor que o grau do divisor
    polinomio *dividendo_aux = poli_create(p->grau);
    for (int i = 0; i <= p->grau; i++) {
        dividendo_aux->coeficientes[i] = p->coeficientes[i];
    }

    // Grau que será utilizado na comparação com o grau do divisor
    int grau_atual = dividendo_aux->grau;
    
    // Loop para fazer as operações até o grau do resto ser menor que o grau do divisor
    while (grau_atual >= q->grau) {
        // Divide o coeficiente de maior grau do dividendo pelo de maior grau do divisor
        int coef_q = dividendo_aux->coeficientes[grau_atual] / q->coeficientes[q->grau];
        int exp_q = grau_atual - q->grau;

        // Armazena no polinômio quociente
        poli_ins_termo(quociente, exp_q, coef_q);

        // Subtrai do dividendo o resultado da multiplicação
        for (int i = 0; i <= q->grau; i++) {
            int valor_subtrair = coef_q * q->coeficientes[i];
            dividendo_aux->coeficientes[i + exp_q] -= valor_subtrair;
        }

        // 5. Atualiza a variavel "grau_atual" pulando os termos que foram zerados na
        // subtração
        while (grau_atual >= 0 && dividendo_aux->coeficientes[grau_atual] == 0) {
            grau_atual--;
        }
    }

    // Limpeza de memória do dividendo temporário para não ter vazamento
    poli_destroy(&dividendo_aux);

    return quociente;
}