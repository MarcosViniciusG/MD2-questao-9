// Marcos Vinicius Gundel da Silva
#include <stdio.h>

long long euclides_algorithm(long long a, long long b) {
    printf("\nCalculo do mdc de %d e %d utilizando o algoritmo de Euclides: \n", a, b);
    printf("mdc(%d, %d)= ", a, b);
    while(b!=0) {
        printf("\n");
        a %= b;
        long long temp = b;
        b = a;
        a = temp;
        printf("mdc(%d, %d)= ", a, b);
    }

    printf("%d\n\n", a);
    return a;
}

long long extended_euclides_algorithm(long long a, long long b) {
    /*
        Algoritmo de divisoes sucessivas para encontrar 
        x e y tal que ax + by = mdc(a, b).
        OBS: retorna apenas o y (G^-1)
    */

    printf("\nAlgoritmo de divisoes sucessivas para encontrar %d^-1 em Z_%d: \n", b, a);
    long long r1 = a, r2 = b;
    long long s1 = 1, s2 = 0;
    long long t1 = 0, t2 = 1;

    while (r2 != 0) {
        // Teorema da divisao
        long long q = r1 / r2; // Calcula o quociente 
        long long r = r1 % r2; // Calcula o resto 
        
        // Encontra o resto de
        long long s = s1 - q * s2;
        long long t = t1 - q * t2;

        printf("%d = %d * %d + %d\n", r1, q, r2, r);

        // Atualiza valores
        r1 = r2; r2 = r;
        s1 = s2; s2 = s;
        t1 = t2; t2 = t;
    }
    printf("\n");

    return t1;
}

void read_H(long long *H) {
    printf("Digite o H: ");
    scanf("%d", H);
}

void read_G(long long *G) {
    printf("Digite o G: ");
    scanf("%d", G);
}

void read_n(long long *n) {
    printf("Digite o n: ");
    scanf("%d", n);
}

void read_x(long long *x) {
    printf("Digite o x: ");
    scanf("%d", x);
}

void read_n1(long long *n1) {
    printf("Digite o n1: ");
    scanf("%d", n1);
}

long long are_coprimes(long long G, long long n) {
    long long mdc = euclides_algorithm(G, n);
    if(mdc==1) {
        printf("%d e %d sao coprimos, pois o mdc entre eles eh 1\n", G, n);
        return 1;
    }
    else 
        printf("%d e %d nao sao coprimos, pois o mdc entre eles eh %d != 1, logo a divisão nao eh possivel\n", G, n, mdc);
    return 0;
}

long long totient(long long n) {
    /*
        Calcula o totiente de Euler
        (numero de coprimos menor ou igual a n).
        Utiliza os fatores primos de n para realizar o calculo
        O(sqrt(n))
    */
    
    long long og = n;
    long long res = n;

    for(long long i=2; i*i <= n; i++) {
        while(n % i==0) {
            n /= i;
        }
        res -= res / i;
    }

    if (n > 1)
        res -= res / n;

    return res;
}

long long is_prime(long long n) {
    /*
        Calcula se n e primo em O(sqrt(n))
    */ 

    long long n_divs = 1;
    for(long long i=1; i*i<=n; i++) {
        if(n % i==0) {
            if(i!=1 && i*i != n)
                n_divs+=2;
            else
                n_divs++;
        }
    }

    if(n_divs==2) {
        printf("%d eh primo pois so tem 2 divisores\n", n);
        return 1;
    }

    printf("%d nao eh primo pois tem %d != 2 divisores\n", n, n_divs);
    return 0;
}

long long binary_exponentiation(long long a, long long x, long long n1) {
    /*
        Calcula a^x em O(log n) usando
        exponenciacao binaria
    */

    printf("Calcula %d^%d com exponenciacao binaria:\n", a, x);

    long long res=1;
    while(x > 0) {
        if(x & 1) // Se for impar 
            res = (res*a) % n1;
        a = (a*a) % n1;
        x >>= 1; // Divide x por 2
    }    
    return res;
}

long long main() {
    long long H, G, n, x, n1;

    // Variavel para sinalizar o fim do programa
    long long end_program=0;
    read_H(&H);
    read_G(&G);
    read_n(&n);

    end_program = !are_coprimes(G, n);

    if(!end_program) {
        long long G_1 = extended_euclides_algorithm(n, G);

        /*
            Caso o valor resultante das divisoes sucessivas
            nao resulte em um valor dentro de Z_n, entao realize
            o modulo do valor obtido por n
        */
        if(G_1 >= n || G_1 < 0) {
            long long new_G_1;
            if(G_1 >= n)
                new_G_1 = G_1 % n;  
            else
                new_G_1 = G_1 + n;

            printf("O valor resultante das divisoes sucessivas (%d) nao existe em Z_%d, logo devemos realizar o módulo de %d por %d que resulta em %d\n\n", G_1, n, G_1, n, new_G_1);
            G_1 = new_G_1;
        }
        printf("O inverso de %d em Z_%d eh %d\n", G, n, G_1);
        long long a = (H * G_1) % n;
        printf("a = (%d / %d) mod %d\n", H, G, n);
        printf("a = (%d * %d) mod %d\n", H, G_1, n);
        printf("a = %d\n", a);

        read_x(&x);
        read_n1(&n1);

        long long coprimes = are_coprimes(x, n1);
        long long x1=x;
        if(is_prime(n1)) {
            /*
                Se n1 for primo, entao
                aplica o Pequeno Teorema de Fermat
            */
            printf("n1 eh primo, logo podemos aplicar o Pequeno Teorema de Fermat\n");
            printf("x1 = %d-1\n", n1);
            x1 = n1-1;
        }
        else if(coprimes) {
            /* 
                Se n nao for primo e x e n1 forem coprimos, 
                entao aplica o Teorema de Euler 
            */

            printf("n1 nao e primo, mas x e n1 sao coprimos, logo podemos o Teorema de Euler\n");
            printf("x1 = phi(%d)\n", n1);
            x1 = totient(n1); 
        }
        printf("x1 = %d\n", x1);
        
        // Teorema da divisao
        long long q = x / x1; // Calcula o quociente 
        long long r = x % x1; // Calcula o resto
        
        printf("\nDecomposicao do expoente x em x1 usando o teorema da divisao: \n");
        printf("%d = %d*%d + %d\n", x, x1, q, r);
        printf("\nNova equacao:\n");
        printf("%d^%d mod %d = (((%d^%d)^%d mod %d))*(%d^%d mod %d)) mod %d\n", a, x, n1, a, x1, q, n1, a, r, n1, n1);
        
        printf("\nCalculo dos valores intermediarios:\n");
        long long x2 = 1; // O resultado sempre vai ser 1
        printf("x2 = %d^%d mod %d\n", a, x1, n1);
        printf("x2 = %d\n", x2);
        printf("x2^%d mod %d = 1\n", q, n1);

        long long res = binary_exponentiation(a, r, n1);
        printf("%d^%d mod %d = %d\n", a, r, n1, res);

        res %= n1;
        printf("\nFinalmente, juntamos todos os resultados:\n");
        printf("(%d^%d)*(%d^%d) mod %d = %d\n", x2, q, a, r, n1, res);
        printf("Logo o resto de %d^%d por %d eh %d\n", a, x, n1, res);
    }

    printf("\nFim do programa :)\n");
    return 0;
}