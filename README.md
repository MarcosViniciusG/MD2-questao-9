# Questão 9 da prova 1 de MD2

## Explicação das funções do código
- **`euclides_algorithm(long long a, long long b)`**  
  Calcula o máximo divisor comum (mdc) de _a_ e _b_ usando o algoritmo de Euclides por sucessivas divisões.  
  **Complexidade:** O(log min(a, b))

- **`extended_euclides_algorithm(long long a, long long b)`**  
  Executa o algoritmo estendido de Euclides para achar inteiros _x_ e _y_ tais que _ax + by = mdc(a, b)_ (retorna _y_, o inverso de _b_ em ℤₐ).  
  **Complexidade:** O(log min(a, b))

- **Leitura de valores**  
  - **`read_H(long long *H)`**, **`read_G(long long *G)`**, **`read_n(long long *n)`**, **`read_x(long long *x)`**, **`read_n1(long long *n1)`**  
    Lê um inteiro do usuário via `scanf` e armazena no ponteiro fornecido.  
    **Complexidade:** O(1)

- **`are_coprimes(long long G, long long n)`**  
  Verifica se _G_ e _n_ são coprimos calculando o MDC (usa `euclides_algorithm`) e comparando a 1.
  **Complexidade:** O(log min(G, n))

- **`totient(long long n)`**  
  Calcula o totiente de Euler φ(n) subtraindo frações conforme fatores primos, percorrendo divisores até √n.  
  **Complexidade:** O(√n)

- **`is_prime(long long n)`**  
  Testa primalidade de _n_ contando divisores até √n; retorna verdadeiro se houver exatamente dois (1 e _n_).  
  **Complexidade:** O(√n)

- **`binary_exponentiation(long long a, long long x, long long n1)`**  
  Calcula _a^x mod n1_ por exponenciação binária (quadrados sucessivos) em tempo logarítmico no expoente.  
  **Complexidade:** O(log x)