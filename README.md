# MathExpressionSystem

Proposta 4 — Sistema de avaliação de expressões matemáticas
Contexto
Uma calculadora de terminal que avalia expressões matemáticas simples digitadas pelo usuário, mostrando o histórico de cálculos realizados na sessão.

Descrição do sistema
O sistema recebe uma expressão matemática como string (ex.: 3 + 5 * 2), valida se a expressão está correta, calcula o resultado respeitando a precedência dos operadores e mantém um histórico das expressões calculadas. O usuário pode buscar uma expressão anterior pelo resultado numérico.

Menu do sistema

Op.	Ação	O que o sistema faz
1	Avaliar expressão = Recebe uma expressão como texto, valida, calcula recursivamente e exibe o resultado.

2	Exibir histórico = Lista todas as expressões calculadas na sessão com seus resultados.

3	Buscar por resultado = Localiza expressões no histórico via busca binária (histórico ordenado por resultado).

4	Ordenar histórico =	Ordena o histórico por resultado numérico para permitir busca binária.

5	Limpar histórico =	Remove todas as expressões do histórico da sessão.

0	Sair = Encerra o programa.

Requisitos técnicos obrigatórios

    •Busca binária no histórico ordenado por resultado numérico para localizar expressões anteriores (opção 3).
    • Ordenação do histórico por resultado usando Selection Sort, Bubble Sort ou Quicksort. 
      Se usar Quicksort, a implementação já cumpre o requisito de recursão e o grupo deve explicar o algoritmo no seminário, comparando seu O(n log n) com o O(n²) dos demais.
    • Recursão obrigatória na avaliação da expressão — a função que calcula o resultado deve ser recursiva, processando a expressão operador por operador (opção 1).
    • Pilha para processar os operadores e operandos durante a avaliação da expressão matemática.
    • Análise de complexidade Big-O do algoritmo de avaliação e das operações de busca e ordenação no histórico, apresentada no seminário.
    
Requisitos do seminário — válidos para todos os grupos

    • Duração de 15 a 20 minutos por grupo.
    • Demonstração ao vivo do programa funcionando no terminal.
    • Explicação de pelo menos uma função recursiva implementada — o professor pode escolher qual.
    • Apresentação da análise de Big-O com a tabela de crescimento.
    • Todos os integrantes do grupo devem falar.
    • O professor pode fazer perguntas técnicas a qualquer integrante.
