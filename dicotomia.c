#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float calculoK(float a, float b, float erro);
void aloca(float **x, float **y, int **z, float **err, float **med, int tam);

int main() {
    int cont = 0;
    char opLoop = 's';

    int *k = NULL;
    float *a = NULL;
    float *b = NULL;
    float *erro = NULL;
    float *m = NULL;

    int grauMax = 0;

    do {
    	cont++;
        printf("Calculando K - Numero de Repeticoes\n");
        aloca(&a, &b, &k, &erro, &m, cont);

        printf("Digite o valor de a: ");
        scanf("%f", a);

        printf("Digite o valor de b: ");
        scanf("%f", b);

        *m = (*a + *b) / 2;

        printf("Digite o erro: ");
        scanf("%f", erro);

        *k = calculoK(*a, *b, *erro);

        printf("a = %f\n", *a);
        printf("b = %f\n", *b);
        printf("m = %f\n", *m);
        printf("erro = %f\n", *erro);
        printf("k = %d\n", *k);

        printf("Digite o grau da equacao (min 2): ");
        scanf("%i", &grauMax);

        float grauTermos[grauMax + 1];

        for (int i = grauMax; i >= 0; i--) {
            printf("Informe o fator multiplicador de x^%i: ", i);
            scanf("%f", &grauTermos[i]);
        }

        printf("A funcao recebida foi: ");
        for (int i = grauMax; i >= 0; i--) {
            if (grauTermos[i] != 0) { // Evita imprimir coeficientes zero
                if (i == grauMax)
                    printf("%.2fx^%i", grauTermos[i], i);
                else if (i == 0)
                    printf(" %+.2f = 0", grauTermos[i]);
                else
                    printf(" %+.2fx^%i", grauTermos[i], i);
            }
        }

        printf("\n\nResumo: Voce ira calcular a funcao acima no intervalo [%.2f; %.2f] com o erro = %.2f por %d iteracoes. Está correto?\n",
               *a, *b, *erro, *k);
		system("pause");
        
        
    } while (opLoop != 'n' && opLoop != 'N');

    return 0;
}

float calculoK(float a, float b, float erro) {
    float fValorK;
    fValorK = (log10(b - a) - log10(erro)) / log10(2);
    return ceil(fValorK);
}

void aloca(float **x, float **y, int **z, float **err, float **med, int tam) {
    if ((*x = (float*)realloc(*x, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para x\n");
        exit(1);
    }
    if ((*y = (float*)realloc(*y, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para y\n");
        exit(1);
    }
    if ((*z = (int*)realloc(*z, tam * sizeof(int))) == NULL) {
        printf("Erro na alocação de memória para z\n");
        exit(1);
    }
    if ((*err = (float*)realloc(*err, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para err\n");
        exit(1);
    }
    if ((*med = (float*)realloc(*med, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para med\n");
        exit(1);
    }
}

