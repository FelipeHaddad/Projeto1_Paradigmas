#ifndef __POLI_H__
#define __POLI_H__

typedef struct{
    int *coeficientes;
    int grau; // testar se o termo do grau foi inserido corretamente.
    int termos; // conta quantidade de termos que nao sao igua a zero =>  5x^2 + 0x^1 + 3 => 2 termos.
}polinomio;

polinomio *poli_create(int grau);
void poli_destroy(polinomio **p); 

/* As funções  poli_ins_termo e poli_get_termo devolvem 
 * 1 se exp (expoente) é válido e a operação foi bem sucedida
 * 0 caso contrário
 * 
 * Se for inserir um termo em expoente com valor este é substituido
 * No caso de poli_get_termo, o valor é retornado na variável apontada por *coef.
 */
int poli_ins_termo(polinomio *p, int exp, int coef);
int poli_get_termo(polinomio *p, int exp, int *coef);

int calcula_px(polinomio *p, int x);

polinomio * poli_soma(polinomio *p, polinomio *q);

polinomio * poli_mult(polinomio *p, polinomio *q);

polinomio * poli_div(polinomio *p, polinomio *q);

#endif