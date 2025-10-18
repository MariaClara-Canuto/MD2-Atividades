# Respostas da Questão 4

1. Com o código completo e preenchido corretamente, qual seria a saída com os valores: H: 7, G: 3, Zn: 11, x: 10, n1: 13.

Resposta: A saída é 4 com os valores dados.

2. Considere o código abaixo, que realiza o cálculo da divisão modular H ÷ G (mod Zn) e depois computa a^x mod n1, aplicando o Pequeno Teorema de Fermat ou o Teorema de Euler, conforme a natureza de n1, classifique como Verdadeiro (V) ou Falso (F) cada uma das afirmativas a seguir:

```c
int inversoModular(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;    
    while (m != 0) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}
```

( **V** ) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

( **F** ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.

( **V** ) A operação (H * inverso) % Zn representa a divisão modular de H por G.

( **V** ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de a^x mod n1.

( **F** ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas sem otimização.

( **V** ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

( **V** ) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.
