/*
Compile com:
gcc -g poli.c teste_poli.c -o teste_poli

Verifique os testes com

./teste_poli

Testando o valgrind
valgrind --leak-check=yes ./teste_poli

*/
#include <stdio.h>
#include <stdlib.h>
#include "poli.h"

// Macro test_assert
#define test_assert(expr, str) { if(!(expr)) { printf("%s: [FALHA] %s in %s:%d\n\n", __func__, str, __FILE__, __LINE__); exit(-1); } }


int testa_creation_destroy() {
    polinomio *p = poli_create(4);
    test_assert(p != NULL, "create retornou NULL!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    test_assert(p->grau == 4, "Grau do polinomio diferente de 4!");
    test_assert(p->termos == 0, "Quantidade de validos deve ser igual 0!");

    poli_destroy(&p);
    test_assert(p == NULL, "p nao foi setado como NULL apos destroy!");

    return 1;
}

int testa_termo() {
    polinomio *p = poli_create(4);
    test_assert(p != NULL, "create retornou NULL para polinomio p!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    test_assert(poli_ins_termo(p, -1, 5) == 0, "deveria falhar, expoente existente!");
    test_assert(poli_ins_termo(p, 5, 1) == 0, "deveria falhar, expoente existente!");
    // preenche os coeficientes para o polinomio
    // p(x) = 2x^4 + 3x^1 - 5
    poli_ins_termo(p, 4, 2); 
    poli_ins_termo(p, 1, 3); 
    poli_ins_termo(p, 0, -5);
    test_assert(p->termos == 3, "Polinomio deveria ter 3 termos válidos");

    int coef;
    test_assert(poli_get_termo(p, -1, &coef) == 0, "deveria falhar, expoente inexistente!");
    test_assert(poli_get_termo(p, 5, &coef) == 0, "deveria falhar, expoente inexistente!");
    test_assert(poli_get_termo(p, 2, &coef) == 0, "deveria falhar, expoente inexistente!");
    test_assert(poli_get_termo(p, 0, &coef) == 1, "deveria obter coeficente no expoente 0!");
    test_assert(coef == -5, "Retornou valor do coeficente errado para no expoente 0!");
    test_assert(poli_get_termo(p, 4, &coef) == 1, "deveria obter coeficente no expoente 4!");
    test_assert(coef == 2, "Retornou valor do coeficente errado para no expoente 4!");

    poli_destroy(&p);

    return 1;
}
int testa_calcula_px() {
    polinomio *p = poli_create(4);
    test_assert(p != NULL, "create retornou NULL para polinomio p!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    // preenche os coeficientes para o polinomio
    // p(x) = 2x^4 + 3x^3 - 5
    poli_ins_termo(p, 4, 2); 
    poli_ins_termo(p, 3, 3); 
    poli_ins_termo(p, 0, -5);

    test_assert(calcula_px(p, 1) == 0, "P(1) != 0");
    test_assert(calcula_px(p, 0) == -5, "P(0) != -5");
    test_assert(calcula_px(p, -1) == -6, "P(-1) != -6");
    // p(2) = 2x^4 + 3x^3 - 5 => 2*16 + 3*8 - 5 => 32 + 24 - 5 => 56 -5 = 51
    test_assert(calcula_px(p, 2) == 51, "P(2) != 51"); 
    
    poli_destroy(&p);

    return 1;
}

int testa_soma_poli(){
    polinomio *p = poli_create(4);
    polinomio *q = poli_create(3);
    test_assert(p != NULL, "create retornou NULL para polinomio p!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    test_assert(q != NULL, "create retornou NULL para polinomio q!");
    test_assert(q->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    // preenche os coeficientes para o polinomio 1
    // p(x) = 2x^4 + 3x^3 - 5
    poli_ins_termo(p, 4, 2); 
    poli_ins_termo(p, 3, 3); 
    poli_ins_termo(p, 0, -5);

    // preenche os coeficientes para o polinomio 2
    // q(x) = -3x^3 + 3x^2 + x 
    poli_ins_termo(q, 3, -3); 
    poli_ins_termo(q, 2, 3); 
    poli_ins_termo(q, 1, 1);
    
    polinomio *s = poli_soma(p,q);
    test_assert(s != NULL, "soma_poli retornou NULL para polinomio s!");
    test_assert(s->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    
    // polinomio somado
    // s(x) = 2x^4 + 3x^2 + x - 5
    int coef;
    test_assert(poli_get_termo(s, 4, &coef) == 1, "Retornou 0 para coeficente no expoente 4!");
    test_assert(coef == 2, "Retornou valor do coeficente errado para no expoente 0!");
    test_assert(poli_get_termo(s, 3, &coef) == 0, "Retornou 1 para expoente inexistente!");
    test_assert(poli_get_termo(s, 2, &coef) == 1, "Retornou 0 para coeficente no expoente 2!");
    test_assert(coef == 3, "Retornou valor do coeficente errado para no expoente 2!");
    test_assert(poli_get_termo(s, 1, &coef) == 1, "Retornou 0 para coeficente no expoente 1!");
    test_assert(coef == 1, "Retornou valor do coeficente errado para no expoente 2!");
    test_assert(poli_get_termo(s, 0, &coef) == 1, "Retornou 0 para coeficente no expoente 0!");
    test_assert(coef == -5, "Retornou valor do coeficente errado para no expoente 0!");
    
    poli_destroy(&p);
    poli_destroy(&q);
    poli_destroy(&s);

    return 1;

}

int testa_mult_poli(){

    polinomio *p = poli_create(4);
    polinomio *q = poli_create(3);
    test_assert(p != NULL, "create retornou NULL para polinomio p!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    test_assert(q != NULL, "create retornou NULL para polinomio q!");
    test_assert(q->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    // preenche os coeficientes para o polinomio 1
    // p(x) = x^4 - 3x^2 + 10
    poli_ins_termo(p, 4, 1);
    poli_ins_termo(p, 2, -3); 
    poli_ins_termo(p, 0, 10);

    // preenche os coeficientes para o polinomio 2
    // q(x) = 2x^3 + x  
    poli_ins_termo(q, 3, 2); 
    poli_ins_termo(q, 1, 1); 

    
    polinomio *m = poli_mult(p,q);
    test_assert(m != NULL, "soma_mult retornou NULL para polinomio m!");
    test_assert(m->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    test_assert(m->grau == 7, "Erro no calculdo do grau do polinomio resultante, esperado grau == 7!");

    
    // resultado do polinomio multiplicado
    // m(x) = p(x) · q(x) = 2x^7 - 5x^5 + 17x^3 + 10x
    int coef;
    test_assert(poli_get_termo(m, 7, &coef) == 1, "Retornou 0 para coeficente no expoente 7!");
    test_assert(coef == 2, "Retornou valor do coeficente errado para no expoente 0!");
    test_assert(poli_get_termo(m, 6, &coef) == 0, "Retornou 1 para expoente inexistente!");
    test_assert(poli_get_termo(m, 5, &coef) == 1, "Retornou 0 para coeficente no expoente 5!");
    test_assert(coef == -5, "Retornou valor do coeficente errado para no expoente 5!");
    test_assert(poli_get_termo(m, 3, &coef) == 1, "Retornou 0 para coeficente no expoente 3!");
    test_assert(coef == 17, "Retornou valor do coeficente errado para no expoente 2!");
    test_assert(poli_get_termo(m, 1, &coef) == 1, "Retornou 0 para coeficente no expoente 1!");
    test_assert(coef == 10, "Retornou valor do coeficente errado para no expoente 0!");
    
    poli_destroy(&p);
    poli_destroy(&q);
    poli_destroy(&m);
    return 1;
}

int testa_div_poli(){
    polinomio *p = poli_create(2);
    polinomio *q = poli_create(1);
    test_assert(p != NULL, "create retornou NULL para polinomio p!");
    test_assert(p->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    test_assert(q != NULL, "create retornou NULL para polinomio q!");
    test_assert(q->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");

    // preenche os coeficientes para o polinomio 1
    // p(x) = 2x^2 + 5x + 3 
    poli_ins_termo(p, 2, 2);
    poli_ins_termo(p, 1, 5); 
    poli_ins_termo(p, 0, 3);

    // preenche os coeficientes para o polinomio 2
    // q(x) = x + 1  
    poli_ins_termo(q, 1, 1); 
    poli_ins_termo(q, 0, 1); 

    
    polinomio *d = poli_div(p,q);
    test_assert(d != NULL, "soma_mult retornou NULL para polinomio m!");
    test_assert(d->coeficientes != NULL, "Vetor de coeficentes nao alocado corretamente!");
    test_assert(d->grau == 1, "Erro no calculdo do grau do polinomio resultante, esperado grau == 1!");

    // divisao 2x^2 + 5x + 3 / x + 1  
    // d(x) = resultado final 2x + 3
    int coef;
    test_assert(poli_get_termo(d, 1, &coef) == 1, "Retornou 0 para coeficente no expoente 1!");
    test_assert(coef == 2, "Retornou valor do coeficente errado para no expoente 1!");
    test_assert(poli_get_termo(d, 0, &coef) == 1, "Retornou 0 para coeficente no expoente 0!");
    test_assert(coef == 3, "Retornou valor do coeficente errado para no expoente 0!");


    poli_destroy(&p);
    poli_destroy(&q);
    poli_destroy(&d);

    return 1;
}


int main() {
    printf("Executando testes ...\n");
    printf("=====================\n\n");

    testa_creation_destroy();
    printf("testa_creation_destroy [PASS] - Nota 2.0\n\n");

    testa_termo();
    printf("testa_termo [PASS] - Nota 3.0 \n\n");

    testa_calcula_px();
    printf("testa_calcula_px [PASS] - Nota 4.0  \n\n");

    testa_soma_poli();
    printf("testa_soma_poli [PASS] - Nota 6.0 \n\n");

    testa_mult_poli();
    printf("testa_mult_poli [PASS] - Nota 8.0 \n\n");

    testa_div_poli();
    printf("testa_div_poli [PASS] - Nota 10.0 \n\n");

    printf("=====================\n");
    printf("TODOS TESTES PASS\n");

    return 0;
}


