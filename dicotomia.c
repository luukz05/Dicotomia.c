#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

float calculoK(float a, float b, float erro);
void aloca(float **x, float **y, int **z, float **err, float **med, int tam);
float funcaoX(float ponto, float *grauTermos, int grauMaximo);

int main() {
    int cont = 0;
    char opLoop = 'y';
    int i = 0;
    int *k = NULL;
    float *a = NULL;
    float *b = NULL;
    float *erro = NULL;
    float *m = NULL;
    int grauMax = 0;
				float *grauTermos = NULL;

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
        scanf("%d", &grauMax);

        grauTermos = (float *)realloc(grauTermos, (grauMax + 1) * sizeof(float));
								if (grauTermos == NULL) {
								    printf("Erro na alocação de memória para grauTermos\n");
								    exit(1);
								}

        for (i = grauMax; i >= 0; i--) {
            printf("Informe o fator multiplicador de x^%d: ", i);
            scanf("%f", &grauTermos[i]);
        }

        printf("A função recebida foi: ");
        for (i = grauMax; i >= 0; i--) {
            if (grauTermos[i] != 0) {
                if (i == grauMax)
                    printf("%.2fx^%d", grauTermos[i], i);
                else if (i == 0)
                    printf(" %+.2f = 0", grauTermos[i]);
                else
                    printf(" %+.2fx^%d", grauTermos[i], i);
            }
        }
        printf("\n\n");

        printf("Resumo: Você irá calcular a função acima no intervalo [%.2f; %.2f] com erro = %.2f por %d iterações. Está correto?\n",
               *a, *b, *erro, *k);

        float fa = funcaoX(*a, grauTermos, grauMax);
        float fb = funcaoX(*b, grauTermos, grauMax);

        if (fa * fb < 0) {
            printf("Existe pelo menos uma raiz no intervalo!\n");
        } else {
            printf("Não há garantia de uma raiz no intervalo. Tente outro intervalo que deixe a sua multiplicação negativa\n");
            do{
                printf("Digite um valor para a.\n");
                scanf("%f", a);
                printf("Digite um valor para b.\n");
                scanf("%f", b);
                fa = funcaoX(*a, grauTermos, grauMax);
                fb = funcaoX(*b, grauTermos, grauMax);
                *m = (*a + *b) / 2;
            }while(fa * fb >= 0);
            printf("Agora [%f,%f] é seu novo intervalo e %f é seu valor médio.\n", *a, *b,*m);
        }
        printf("Deseja continuar? (s/n): ");
        scanf(" %c", &opLoop);


        printf("\n%-5s%-15s%-15s%-15s%-15s%-15s%-15s\n", "k", "a", "b", "m", "fa", "fb", "fm");
        while(int z = 0 <= *k){
        	fa = funcaoX(*a, grauTermos, grauMax);
            fb = funcaoX(*b, grauTermos, grauMax);
            float fm = funcaoX(*m, grauTermos, grauMax);

            
            printf("%-5d%-15.4f%-15.4f%-15.4f%-15.4f%-15.4f%-15.4f\n", z+1, *a, *b, *m, fa, fb, fm);

            
            if (fa * fm < 0) {
                *b = *m;
                *m = (*a + *b) / 2;
            }
            else if (fb * fm < 0) {
                *a = *m;
                *m = (*a + *b) / 2;
            }

            if (fabs(*b - *a) < *erro) {
                printf("\nPrecisão alcançada! Intervalo [%.4f, %.4f] com erro desejado %.4f.\n", *a, *b, *erro);
                break;
            }

			i++;
		}
    } while (opLoop != 'n' && opLoop != 'N');

    return 0;
}

float funcaoX(float ponto, float *grauTermos, int grauMaximo) {
    float resultado = 0;
    for (int i = 0; i <= grauMaximo; i++) {
        resultado += grauTermos[i] * pow(ponto, i);
    }
    return resultado;
}

float calculoK(float a, float b, float erro) {
    return ceil((log10(b - a) - log10(erro)) / log10(2));
}

void aloca(float **x, float **y, int **z, float **err, float **med, int tam) {
    if ((*x = (float *)realloc(*x, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para x\n");
        exit(1);
    }
    if ((*y = (float *)realloc(*y, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para y\n");
        exit(1);
    }
    if ((*z = (int *)realloc(*z, tam * sizeof(int))) == NULL) {
        printf("Erro na alocação de memória para z\n");
        exit(1);
    }
    if ((*err = (float *)realloc(*err, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para err\n");
        exit(1);
    }
    if ((*med = (float *)realloc(*med, tam * sizeof(float))) == NULL) {
        printf("Erro na alocação de memória para med\n");
        exit(1);
    }
}
