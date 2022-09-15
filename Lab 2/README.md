# ANOTAÇÕES ACERCA DA ATIVIDADE:

## Testando para diferentes matrizes, temos:

**Matriz de Dimensão 500x500:**

- Teste 1:

  - Inicialização: 0.001613 ms
  - Processamento: 0.904848 ms
  - Finalização: 0.000878 ms

- Teste 2:

  - Inicialização: 0.001706 ms
  - Processamento: 1.015437 ms
  - Finalização: 0.001067 ms

- Teste 3:

  - Inicialização: 0.001132 ms
  - Processamento: 0.928532 ms
  - Finalização: 0.001026 ms

- Média:

  - Inicialização: 0.001483 ms
  - Processamento: 0.949605 ms
  - Finalização: 0.000990 ms

**Matriz de Dimensão 1000x1000:**

- Teste 1:

  - Inicialização: 0.006904 ms
  - Processamento: 7.711139 ms
  - Finalização: 0.003651 ms

- Teste 2:

  - Inicialização: 0.007520 ms
  - Processamento: 7.853003 ms
  - Finalização: 0.003811 ms

- Teste 3:

  - Inicialização: 0.006567 ms
  - Processamento: 7.794003 ms
  - Finalização: 0.011389 ms

- Média:

  - Inicialização: 0,006997 ms
  - Processamento: 7,786048 ms
  - Finalização: 0,006283 ms

**Matriz de Dimensão 2000x2000:**

- Teste 1:

  - Inicialização: 0.019249 ms
  - Processamento: 62.498013 ms
  - Finalização: 0.020256 ms

- Teste 2:

  - Inicialização: 0.016035 ms
  - Processamento: 61.323655 ms
  - Finalização: 0.013596 ms

- Teste 3:

  - Inicialização: 0.019183 ms
  - Processamento: 63.098122 ms
  - Finalização: 0.029190 ms

- Média:

  - Inicialização: 0.018155 ms
  - Processamento: 62.306596 ms
  - Finalização: 0.021014 ms

## Ganho de desempenho teórico de acordo com a _Lei de Amdahl_:

Fórmula: _Speedup = (1/(1-f + f/n)_

**Matriz 500x500:**

f = 0.949605/(0.001483 + 0.949605 + 0.000990)
f = 0,997402524
Ganho de desempenho teórico = (1/(1-0,997402524 + 0,997402524/2) = 1,994818507
Ganho de desempenho teórico ≈ 199.4%

**Matriz 1000x1000:**

f = 7.786048/(0.006997 + 7.786048 + 0.006283)
f = 0,998297289
Ganho de desempenho teórico = (1/(1-0,998297289 + 0,998297289/2))
Ganho de desempenho teórico ≈ 199.6%

**Matriz 2000x2000:**

f = 62.306596/0.018155 + 62.306596 + 0.021014)
f = 0,999371746
Ganho de desempenho teórico = (1/(1-0,999371746 + 0,999371746/2))
Ganho de desempenho teórico ≈ 199.8%
