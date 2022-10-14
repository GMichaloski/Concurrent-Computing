## Avaliação de resultados

    Observando diversas operações (com diferentes configurações), torna-se evidente que a quantidade de threads em certa operação reflete diretamente no número de vezes que tal operação será realizada em relação à outras com menos threads. Além disso, é notável, também, que quanto mais threads temos executando as operações em simultâneo, mais bloqueios são realizados (isso se dá, certamente, pois quanto mais threads estão operando, maior a chance delas "se esbarrarem" nas áreas críticas).
