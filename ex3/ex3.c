/*
Questão 3
A Razão de Eficiência de um Número
Aluna: Maria Clara Canuto Gontijo - 232005352
*/
#include <stdio.h>
#include <math.h>

#define MAX_FATORES 100

// Função para fatoração prima
int fat_prima(int N, int f[], int exp[]) {
    int count = 0;
    int og = N;

    printf("\n# Passo 1: Fatoracao prima de %d\n", N);

    int e = 0;
    while (N % 2 == 0) {
        N /= 2;
        e++;
    }
    if (exp > 0) { 
        f[count] = 2;
        exp[count] = e;
        count++;
        printf("Fator 2 ^ %d\n", e); // fator 2
    }

    for (int i = 3; i*i <= N; i += 2) {
        e = 0;
        while (N % i == 0) {
            N /= i;
            exp++;
        }
        if (exp > 0) {
            f[count] = i;
            exp[count] = e;
            count++;
            printf("Fator %d ^ %d\n", i, e); // fatores impares
        }
    }

    if (N > 1) {
        f[count] = N;
        exp[count] = 1;
        count++;
        printf("Fator %d ^ 1\n", N); //primo restante
    }

    return count;
}

// Função para calcular tau(N)
long long tau(int count, int exp[]) {
    long long t = 1;
    printf("\n# Passo 2: Calculando tau(N)\n");
    for (int i = 0; i < count; i++) {
        t *= (exp[i] + 1);
        printf("tau parcial com fator %d: %lld\n", i+1, t);
    }
    return t;
}

// calculo de sigma(n) usando a formula
long long sigma(int count, int f[], int exp[]) {
    long long s_total = 1;
    printf("\n# Passo 3: Calculando sigma(N)\n");
    for (int i = 0; i < count; i++) {
        long long p = f[i];
        long long a = exp[i];
        long long s = 0;
        long long p_pow = 1;
        for (int j = 0; j <= a; j++) {
            s += p_pow;
            p_pow *= p;
        }
        s_total *= s;
        printf("sigma parcial com fator %d: %lld\n", f[i], s_total);
    }
    return s_total;
}

// função para calcular a Razão de Eficiência
double razaoEf(long long sigmaN, long long tauN, int N) {
    return (double)sigmaN / (N * tauN);
}

int main() {
    int N;

    printf("\nExercicio 3\nFeito por Maria Clara Canuto Gontijo - 232005352\n");
    printf("\nInsira um numero inteiro N, sendo que (1 <= N <= 105).\n");


    printf("Digite N, pressione Enter para confirmar: ");
    scanf(" %d", &N);

    if (N < 1 || N > 100000) {
        printf("Numero fora do intervalo permitido.\n");
        return 1;
    }

    int fats[MAX_FATORES], exps[MAX_FATORES];
    int count = fat_prima(N, fats, exps);

    long long t = tau(count, exps);
    long long s = sigma(count, fats, exps);

    printf("\n# Passo 4: Calculando Razao de Eficiencia = sigma / (N * tau)\n");
    double razao = razaoEf(s, t, N);

    printf("Razao de Eficiencia de %d: %.2lf\n", N, razao);

    return 0;
}