#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
A funcao verifica se o numero n e primo, dividindo n por 2 ate sqrt(n). 
Se nenhum numero de 2 ate sqrt(n) divide n,  entao n nao possui divisores menores ou iguais a raiz, 
logo n nao possui nenhum divisor alem de 1 e n.
Portanto, n e primo.
*/
int seriaPrimo(int n) {
    if (n < 2) return 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }

    return 1;
}

// A funcao procura um divisor i de n e depois divide n por i para obter um segundo fator j, depois verifica se ambos sao primos.
int seriaPP(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0){
            int j = n / i;

            if (seriaPrimo(i) && seriaPrimo(j)) {
                return 1;
            }

            else return 0;
        }
    }
}

int mdcEuclides(int a, int b) {
    if (b == 0) {
        return a;
    }

    return mdcEuclides(b, a % b);
}

// A funcao e a funcao de geracao, ela foi implementada como funcao para facilitar a legibilidade do codigo
int g(int x, int y){
    long long s = ((1LL * x * x) + 1) % y;
    return s;
}

int rhoPollard(int n) {
    if(n % 2 == 0) return 2;

    int d = 1;
    int i = 1;

    while (1) {

        int x1 = 2;
        int x2 = 2;

        while (d == 1) {
            x1 = g(x1, n);
            x2 = g(g(x2, n), n);

            int x = abs(x1 - x2);

            d = mdcEuclides(x, n);
            printf("# Interacao %d\n", i);
            printf("# x1 = %d, x2 = %d \n# mdc(%d, %d) = %d\n\n", x1, x2, x, n, d);
            i++;
        }

        if (d == n) return -1;

        return d;
    } 
}

int expP (int n, int z) {
    int e;
    
    for (e = 2; e < n; e++) {
        if (mdcEuclides(e, z) == 1) {
            return e;
        }
        
    }

}

int euclidesEXT(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int m = euclidesEXT(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return m;
}

int invrs_mod (int e, int z) {
    int x, y;

    if (euclidesEXT(e, z, &x, &y) != 1) {
        return -1;
    }

    return (x % z + z) % z; // essa parte garante que d nao e negativo
}

int modEXP (int m, int e, int n) {
    int r = 1;
    m = m % n;

    printf("\n # Calculo de %d^%d mod %d:\n", m, e, n);

    while (e > 0) {
        printf("e = %d | m = %d | resultado = %d\n", e, m, r);

        if (e % 2 == 1) {
            r = (r * m) % n;
            printf(" - Multiplica: resultado = %d\n", r);
        }

        e = e / 2;
        m = (m * m) % n;
        printf(" - Eleva m^2 mod %d = %d\n\n", n, m);
    }

    return r;
}

int main () {
    int N1, N2;
    int valid1 = 0;
    int valid2 = 0;

    printf("\nExercicio 1\nFeito por Maria Clara Canuto Gontijo - 232005352\n");
    printf("\nInsira dois numeros inteiros, N1 e N2, com cada numero contendo de 3 a 4 digitos.\nObs.: Cada Ni deve ser o produto de primos distintos para que o Metodo Pollard Rho seja efetivo.\n");
    printf("\n1) Fatoracao Iterativa\n\n");


//verificao de restricao n1 e n2
    printf("# Entrada de Dados\n");

    while (!valid1) { 
        printf("Digite N1, pressione Enter para confirmar: ");
        if (scanf("%d", &N1) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Numero Invalido, tente novamente.\n\n");
            continue;
        } 

        if (N1 < 100 || N1 > 9999) {
            printf("Numero Invalido, tente novamente.\n\n");
        } 

        else {
            valid1 = 1; 
            
            if (seriaPP(N1)) {
                printf("Numero aceito. N1 = %d\n\n", N1);
                break;
            }

            else {
                printf("Numero Invalido, tente novamente.\n\n");
            }
        }
    }


    while (!valid2) { 
        printf("Digite N2, pressione Enter para confirmar: ");
        if (scanf("%d", &N2) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Numero Invalido, tente novamente.\n\n");
            continue;
        } 

        if (N2 < 100 || N2 > 9999) {
            printf("Numero Invalido, tente novamente.\n\n");
        } 

        else {
            valid2 = 1; 
            
            if (seriaPP(N2)) {
                printf("Numero aceito. N2 = %d\n\n", N2);
                break;
            }

            else {
                printf("Numero Invalido, tente novamente.\n\n");
            }
        }
    }

// pollard rho. Adicione uma explicacao aqui

    printf("# Implementacao do Metodo Rho de Pollard\n\n");

    int p, q;

    printf("- Funcao de iteracao: g(x) = (x * x) + 1\n- Semente: x0 = 2\n- Faz-se mdc(|x1 - x2|, N1) ate encontrar um fator p nao trivial de N1\n\n");
    p = rhoPollard(N1);

    if(p != -1) {
        printf("Fator nao trivial de N1 = %d encontrado: p = %d\n\n", N1, p);
    }
    else {
        printf("Nao foi possivel encontrar o fator nao trivial de N1 com a semente atual, Tente novamente com outro valor.\n\n");
        exit(EXIT_FAILURE);
    }


    printf("- Funcao de iteracao: g(x) = (x * x) + 1\n- Faz-se mdc(|x1 - x2|, N2) ate encontrar um fator q nao trivial de N2\n\n");
    q = rhoPollard(N2);

    if(q != -1) {
        printf("Fator nao trivial de N2 = %d encontrado: q = %d\n\n", N2, q);
    }
    else {
        printf("Nao foi possivel encontrar o fator nao trivial de N2 com a semente atual, Tente novamente com outro valor.\n\n");
        exit(EXIT_FAILURE);
    }

    printf("\n# Identificacao dos primos RSA\n");
    printf("\np = %d\nq = %d\n", p, q);
    printf("\n2) Geracao das chaves RSA\n");

    int n = p * q;
    printf("\n# Calculo do modulo\n");
    printf("n = %d * %d = %d\n", p, q, n);

    int z = (p - 1) * (q - 1);
    printf("\n# Totiente de Euler\n");
    printf("z(n) = (p - 1) * (q - 1) = %d\n", z);

    int e;

    e = expP(n, z);

    printf("\n# Escolha do expoente publico\n");
    printf("# Precisa-se escolher o menor E > 1 e E < n tal que mdc (E, z(n))=1\n");
    printf("Calculado E = %d\n\n", e);

    printf("# Calculo do expoente privado: D * e ≡ 1 mod z\n");
    int D = invrs_mod(e, z);
    printf("Calculado D = %d\n\n", D);

    printf("# Assim se obtem as chaves:\n# chave publica: (%d, %d)\n# chave privada: (%d, %d)\n\n", n, e, n, D);
 
    // criptografia


    printf("3) Criptografia e Descriptografia\n\n");

    char msg[200];
    int m[400];
    int count = 0;
    int cod[400];

    printf("Digite uma mensagem de ate 200 digitos, pressione Enter para continuar: ");
    scanf(" %[^\n]", msg);

    printf("\n# Mensagem pre-codificada:\n");
    for (int i = 0; msg[i] != '\0'; i++) {
        char c = tolower(msg[i]);

        if (c == ' ') {
            printf("[00]");
            m[count++] = 0;
        }
        else if (c >= 'a' && c <= 'z') {
            int pcod = 11 + (c - 'a');
            printf("[%02d]", pcod);
            m[count++] = pcod;
        }
    }
    printf("\nTotal de blocos (m): %d", count);

    printf("\n\n# Para codificar usando RSA, cada bloco m formado pelos numeros da mensagem, faz-se C ≡ M^e mod n\n");

    for (int i = 0; i < count; i++) {
        int M = m[i];
        printf("\nBloco %02d - M = %d", i + 1, M);

        cod[i] = modEXP(M, e, n);
        printf("C = %d\n", cod[i]);
    }

    printf("\n# Mensagem Criptografada (vetor C):\n[ ");
    for (int i = 0; i < count; i++) {
        printf("%d ", cod[i]);
    }
    printf("]\n");

    return 0;
}