# ANOTAÇÕES ACERCA DA ATIVIDADE:

## Testando a concorrência para diferentes matrizes:

Quantidade de núcleos de processamento utilizados: **8**

**Matriz de Dimensão 500x500:**

- Teste 1:

  - Inicialização: 0.002298 ms
  - Processamento: 0.214877 ms
  - Finalização: 0.001079 ms

- Teste 2:

  - Inicialização: 0.001830 ms
  - Processamento: 0.219400 ms
  - Finalização: 0.000949 ms

- Teste 3:

  - Inicialização: 0.002161 ms
  - Processamento: 0.259729 ms
  - Finalização: 0.001305 ms

- Média:

  - Inicialização: 0,002096 ms
  - Processamento: 0,231335 ms
  - Finalização: 0,001111 ms

**Matriz de Dimensão 1000x1000:**

- Teste 1:

  - Inicialização: 0.008177 ms
  - Processamento: 1.320010 ms
  - Finalização: 0.003544 ms

- Teste 2:

  - Inicialização: 0.007700 ms
  - Processamento: 1.193078 ms
  - Finalização: 0.003561 ms

- Teste 3:

  - Inicialização: 0.004603 ms
  - Processamento: 1.227695 ms
  - Finalização: 0.003318 ms

- Média:

  - Inicialização: 0,006826 ms
  - Processamento: 1,246927 ms
  - Finalização: 0,003474 ms

**Matriz de Dimensão 2000x2000:**

- Teste 1:

  - Inicialização: 0.019927 ms
  - Processamento: 11.352953 ms
  - Finalização: 0.012448 ms

- Teste 2:

  - Inicialização: 0.017018 ms
  - Processamento: 11.312445 ms
  - Finalização: 0.012918 ms

- Teste 3:

  - Inicialização: 0.017637 ms
  - Processamento: 12.275305 ms
  - Finalização: 0.012609 ms

- Média:

  - Inicialização: 0,018194 ms
  - Processamento: 11,646901 ms
  - Finalização: 0,012658 ms

## Ganho de desempenho teórico de acordo com a _Lei de Amdahl_:

Para maior explicitação dos cálculos, verificar o README do Lab 2

Fórmula: _Speedup = (1/(1-f + f/n)_

**Matriz 500x500:**

Ganho de desempenho teórico ≈ 785.7%

**Matriz 1000x1000:**

Ganho de desempenho teórico ≈ 790.6%

**Matriz 2000x2000:**

Ganho de desempenho teórico ≈ 796.5%

## Ganho de desempenho real

Fórmula: _Speedup = (Tsequencial/Tconcorrente)_

**Matriz 500x500:**

Ganho de desempenho = (0,952078/0,234542)
Ganho de desempenho = 4,059307 ≈ 405.9%

**Matriz 1000x1000:**
Ganho de desempenho = (7,799328/1,257227)
Ganho de desempenho = 6,203595 ≈ 620.3%

**Matriz 2000x2000:**
Ganho de desempenho = (62,345765/11,677753)
Ganho de desempenho = 5,338849 ≈ 533.9%

## Comparação ganho de desempenho teórico e real

**Matriz 500x500:**

Ganho de desempenho teórico ≈ 785.7%
Ganho de desempenho real≈ 405.9%

**Matriz 1000x1000:**

Ganho de desempenho teórico ≈ 790.6%
Ganho de desempenho real ≈ 620.3%

**Matriz 2000x2000:**

Ganho de desempenho teórico ≈ 796.5%
Ganho de desempenho real ≈ 533.9%
