/*
Questão 1
Sistema RSA com Fatoração ρ de Pollard e
Aplicação de Teoremas Modulares em Três Etapas
Aluna: Maria Clara Canuto Gontijo - 232005352
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/*
A função verifica se o número n é primo, dividindo n por 2 até sqrt(n). 
Se nenhum número de 2 até sqrt(n) divide n,  então n não possui divisores menores ou iguais a raiz, 
logo n não possui nenhum divisor além de 1 e n.
Portanto, n é primo.
*/
int seriaPrimo(int n) {
    if (n < 2) return 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }

    return 1;
}

/*
A função procura um divisor i de n e depois divide n por i para obter um segundo fator j
depois verifica se ambos são primos.
*/
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
    return 0;
}

// Algoritmo de Euclides para máximo divisor comum
int mdcEuclides(int a, int b) {
    if (b == 0) {
        return a;
    }

    return mdcEuclides(b, a % b);
}

//Função de geração g(x) = x^2 + 1 , ela foi implementada como função para facilitar a legibilidade do código
int g(int x, int y){
    long long s = ((1LL * x * x) + 1) % y;
    return s;
}

/*
Implementação do Pollard Rho com semente x0 = 2 e função g(x)
Imprime cada iteração (x1, x2, mdc(|x1-x2|, n))
Retorna um fator não trivial ou -1 se falhar (d == n) 
*/
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
            printf("# Interacão %d\n", i);
            printf("# x1 = %d, x2 = %d \n# mdc(%d, %d) = %d\n\n", x1, x2, x, n, d);
            i++;
        }

        if (d == n) return -1;

        return d;
    } 
}

// Gera o menor expoente público e tal que 1 < e < n e mdc(e, z)=1.
int expPub (int n, int z) {
    int e;
    
    for (e = 2; e < n; e++) {
        if (mdcEuclides(e, z) == 1) {
            return e;
        } 
    }
}

/*
Algoritimo de Euclides extendido
retorna mdc(a, b) na qual satisfaz a*x + b*y = mdc (a, b), encontrando os valores de x e y
o uso de ponteiros é necessário pois a função precisava retornar mais de um valor sendo eles: x, y e o mdc
*/
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

// calcula o inverso modular de e mod z para obter d, tal que d*e ≡ 1 mod z.
// retorna -1 se não existir
int invrs_mod (int e, int z) {
    int x, y;

    if (euclidesEXT(e, z, &x, &y) != 1) {
        return -1;
    }

    return (x % z + z) % z; // essa parte garante que d não é negativo no intervalo de [0, z-1]
}

// exponenciacão modular simples, retorna m^e mod n
int modEXPsimple (int m, int e, int n) {
    int r = 1;
    m = m % n;

    while (e > 0) {
        if (e % 2 == 1) {
            r = (r * m) % n;
        }
        e = e / 2;
        m = (m * m) % n;

    }

    return r;
}

// totiente de Eulerr phi(n), fatoração por tentativa
int phiEuler(int n) {
    int r = n;

    for(int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) (n /= i);
            r -= r / i;
        }
    }
    if (n > 1) (r -= r / n);

    return r;
} 

int main () {
    int N1, N2;
    int valid1 = 0;
    int valid2 = 0;

    printf("\nExercicio 1\nFeito por Maria Clara Canuto Gontijo - 232005352\n");
    printf("\nInsira dois numeros inteiros, N1 e N2, com cada numero contendo de 3 a 4 dígitos.\nObs.: Cada Ni deve ser o produto de primos distintos para que o Método Pollard Rho seja efetivo.\n");
    printf("\n1) Fatoracao Iterativa\n\n");


    //entradas iniciais e verificao de restricao n1 e n2 -----------------------'''''''
    printf("# Entrada de Dados\n");

    while (!valid1) { 
        printf("Digite N1, pressione Enter para confirmar: ");
        if (scanf(" %d", &N1) != 1) {
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
                printf("Numero Inválido, tente novamente.\n\n");
            }
        }
    }


    while (!valid2) { 
        printf("Digite N2, pressione Enter para confirmar: ");
        if (scanf(" %d", &N2) != 1) {
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

    // Pollard Rrho para N1 e N2 --------------------------------------
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

    printf("# Identificacao dos primos RSA\n");
    printf("p = %d\nq = %d\n", p, q);

    // geracão das chaves RSA -----------------------------
    printf("\n2) Geracao das chaves RSA\n");
    int n = p * q;
    printf("\n# Calculo do modulo\n");
    printf("n = %d * %d = %d\n", p, q, n);

    int z = (p - 1) * (q - 1);
    printf("\n# Totiente de Euler\n");
    printf("z(n) = (p - 1) * (q - 1) = %d\n", z);

    int e;

    e = expPub(n, z);

    printf("\n# Escolha do expoente publico\n");
    printf("# Precisa-se escolher o menor E > 1 e E < n tal que mdc (E, z(n))=1\n");
    printf("Calculado E = %d\n\n", e);

    printf("# Calculo do expoente privado: D * e ≡ 1 mod z\n");
    int D = invrs_mod(e, z);
    printf("Calculado D = %d\n\n", D);

    printf("# Assim se obtem as chaves:\n# chave publica: (%d, %d)\n# chave privada: (%d, %d)\n\n", n, e, n, D);
 
    // criptografia --------------------------------
    printf("3) Criptografia\n\n");

    char msg[200];
    int m[400];
    int count = 0;
    int c[400];

    printf("Digite uma mensagem de ate 200 digitos, pressione Enter para continuar: ");
    scanf(" %[^\n]", msg);

    // pre codificacão ------------------
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

    // codificacão ------------------------------------
    printf("\n\n# Para codificar usando RSA, faz-se C congruente a M^e mod n para cada bloco m formado pelos números da mensagem.\n");
    printf("# E para isso, eh necessario reduzir o expoente utilizando um dos 3 teoremas de reducão de expoente: Fermat, Euler e Divisão Euclidiana.\n\n");
    

    for (int i = 0; i < count ; i++){
        int newE = e;

        printf("# Bloco %02d => M = %02d\n", i + 1, m[i]);

        if (seriaPrimo(n)) {
            newE = e % (n - 1);

            printf("\n- Vamos usar o [ Pequeno Teorema de Fermat ] para esse caso, pois:\n");
            printf("- n = %d eh primo e isso confere as restricoes do teorema. Entao faz-se E mod (n - 1).");
            printf("- E mod (n - 1) = %d mod %d = %d\n", e, n - 1, newE);
        }

        else if (mdcEuclides(m[i], n) == 1) {
            int phi = phiEuler(n);
            newE = e % phi;

            printf("\n- Vamos usar o [ Teorema de Euler ] para esse caso, pois:\n");
            printf("- n = %d nao eh primo e mdc(m, n) = 1, conferindo com as restricoes do teorema. Entao faz-se E mod phi(n).\n");
            printf("- phi(%d) = %d\n", n, phi);
            printf("- E mod phi(n) = %d mod %d = %d\n", e, phi, newE);
        }

        else {
            newE = e % n;

            printf("\n- Vamos usar o [ Teorema da Divisao Euclidiana ] para esse caso, pois:\n");
            printf("- Já que n = %d nao eh primo e mdc(m, n) != 1, por eliminacao, este teorema e escolhido. Entao faz-se E mod n.\n");
            printf("- E mod n = %d mod %d = %d\n", e, n, newE);
        }
        
        printf("- Faz-se C_i = %d^%d mod %d\n", m[i], newE, n);
        c[i] = modEXPsimple(m[i], newE, n);
        printf("C_%d = %d\n\n", i + 1, c[i]);
    }

    printf("# Mensagem codificada (vetor C):\n[ ");
    for (int i = 0; i < count; i++) {
        printf("%d ", c[i]);
    }
    printf("]\n\n");

    printf("4) Descriptografia\n\n");

    printf("# Para decodificar, faz-se M congruente a C^D mod n para cada bloco c cifrado.\n");
    printf("# E para isso, eh necessario reduzir o expoente utilizando um dos 3 teoremas de reducao de expoente: Fermat, Euler e Divisao Euclidiana.\n\n");

    for (int i = 0; i < count ; i++){
        int newD = D;

        printf("# Bloco %02d => C = %02d\n", i + 1, c[i]);

        if (seriaPrimo(n)) {
            newD = D % (n - 1);

            printf("\n- Vamos usar o [ Pequeno Teorema de Fermat ] para esse caso, pois:\n");
            printf("- n = %d eh primo e isso confere as restricoes do teorema. Entao faz-se E mod (n - 1).");
            printf("- E mod (n - 1) = %d mod %d = %d\n", D, n - 1, newD);
        }

        else if (mdcEuclides(m[i], n) == 1) {
            int phi = phiEuler(n);
            newD = D % phi;

            printf("\n- Vamos usar o [ Teorema de Euler ] para esse caso, pois:\n");
            printf("- n = %d nao eh primo e mdc(m, n) = 1, conferindo com as restricoes do teorema. Entao faz-se E mod phi(n).\n");
            printf("- phi(%d) = %d\n", n, phi);
            printf("- E mod phi(n) = %d mod %d = %d\n", D, phi, newD);
        }

        else {
            newD = D % n;

            printf("\n- Vamos usar o [ Teorema da Divisao Euclidiana ] para esse caso, pois:\n");
            printf("- Ja que n = %d nao eh primo e mdc(m, n) != 1, por eliminacao, este teorema e escolhido. Entao faz-se E mod n.\n");
            printf("- E mod n = %d mod %d = %d\n", D, n, newD);
        }
        
        printf("- Faz-se M_i = %d^%d mod %d\n", c[i], newD, n);
        m[i] = modEXPsimple(c[i], newD, n);
        printf("M_%d = %d\n\n", i + 1, m[i]);
    }

    printf("# Mensagem QUASE Decodificada (vetor M):\n[ ");
    for (int i = 0; i < count; i++) {
        printf("%d ", m[i]);
    }
    printf("]\n\n");

    printf("# E finalmente, eh necessario converter os numeros em letras novamente.\n");

    char msg_dec[100];
    int pos = 0;
    for (int i = 0; i < count; i++) {
        if (m[i] == 0)
            msg_dec[pos++] = ' ';

        else if (m[i] >= 11 && m[i] <= 36)
            msg_dec[pos++] = (char)('a' + (m[i] - 11));
    }
    msg_dec[pos] = '\0';

    printf("# Mensagem decodificada: %s\n", msg_dec);

    printf("\n");

    printf("# Confirmacao de equivalencia entre original e decodificada:\n");
    printf("-> Original (normalizada para minusculas e sem pontuacao): ");

    char original_norm[400];
    int p2 = 0;

    for (int i = 0; msg[i] != '\0'; i++) {
        char cc = tolower((unsigned char)msg[i]);
        if (cc == ' ' || (cc >= 'a' && cc <= 'z')) {
            original_norm[p2++] = cc;
        }
    }
    original_norm[p2] = '\0';

    printf("%s\n", original_norm);
    printf("-> Mensagem Decodificada: %s\n", msg_dec);

    if (strcmp(original_norm, msg_dec) == 0) {
        printf("\nMensagem decodificada eh IDENTICA a mensagem original (apos normalizacao).\n");
    } else {
        printf("\nMensagem decodificada eh DIFERENTE da original (apos normalizacao).\n");
        printf("Verifique pontuacao, acentos ou caracteres ignorados na pre-codificacao.\n");
    }

    return 0;
}