/*
Questão 2
Chaves Periódicas
Aluna: Maria Clara Canuto Gontijo - 232005352
*/

#include <stdio.h>


// calcula o mdc utilizando o algoritmo de euclides
int mdc(int a, int b) {
    if (b == 0) {
        return a;
    }

    return mdc(b, a % b);
}

// Calcula o mínimo múltiplo comum usando a propriedade: MMC(a, b) = (a * b) / MDC(a, b)
int mmc(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }

    return (a / mdc(a, b)) * b;
}

int main() {
    printf("\nExercicio 2\nFeito por Maria Clara Canuto Gontijo - 232005352\n");
    printf("\nInsira dois numeros inteiros: \n- N sendo o numero de chaves \n- Ci representando o ciclo de ativacao.\n\n");
    printf("Considere as restricoes de N e Ci: \n- 1 <= N <= 10. \n- 2 <= Ci <= 20\n\n");

    int N;
    int C[100];
    char buffer[100];

    while (1) {
        printf("Digite N, pressione Enter para confirmar: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) return 1;
        if (sscanf(buffer, " %d", &N) != 1 || N < 1 || N > 10) {
            printf("Numero invalido, digite novamente.\n");
            continue;
        }
        break;
    }

    for (int i = 0; i < N; i++) {
        while (1) {
            printf("Digite o ciclo C[%d] (2 a 20): ", i + 1);
            if (!fgets(buffer, sizeof(buffer), stdin)) return 1;

            if (sscanf(buffer, " %d", &C[i]) != 1 || C[i] < 2 || C[i] > 20) {
                printf("Valor invalido para ciclo %d, digite novamente.\n", i + 1);
                continue;
            }
            break;
        }
    }

    printf("\n\n# Passo a Passo:\n");
    int res = C[0];
    printf("# Ciclo inicia em: %d\n", res);
    
    for (int i = 1; i < N; i++) {
        int ant = res;

        res = mmc(res, C[i]);
        printf("Calculando MMC(%d, %d) = %d\n", ant, C[i], res);
    }

    printf("\nResposta Final\n");

    if (res <= 50) {
        printf("Primeiro ano sincronizado: %d\n", res);
    }

    else printf("Nao eh possivel sincronizar dentro do limite de 50 anos");
    
}