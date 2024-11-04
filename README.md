# Projeto de Árvore Rubro-Negra

## Descrição

Este projeto implementa uma Árvore Rubro-Negra em C, uma estrutura de dados de árvore binária de busca auto-balanceada. O projeto inclui operações para inserção e remoção de nós, garantindo que as propriedades da árvore sejam mantidas após cada operação. A árvore é usada para otimizar a busca e manipulação de dados.

## Funcionalidades

- **Inserção**: Adiciona um novo valor à árvore, ajustando a estrutura conforme necessário.
- **Remoção**: Remove um valor da árvore e reestrutura a árvore para manter as propriedades da Árvore Rubro-Negra.
- **Percursos**: Implementação de percursos em pré-ordem, in-ordem e pós-ordem para exibir os elementos da árvore.

## Estrutura do Código

O código é dividido nas seguintes partes:

- **rb.h**: Define a estrutura do nó da árvore e as funções que operam sobre a árvore.
- **main.c**: Implementa a lógica principal para interagir com o usuário e executar operações na árvore.

### Estruturas de Dados

- `Node`: Representa um nó da árvore, contendo um valor (key), uma cor (color), e ponteiros para o nó pai (father) e seus filhos (left e right).
- `Tree`: Tipo definido para representar a árvore, que é um ponteiro para `Node`.

### Cores

As cores dos nós são definidas por um enum:
- `RED`: Nó vermelho.
- `BLACK`: Nó preto.
- `DOUBLE_BLACK`: Usado durante a remoção para tratar nós que têm um "buraco".

## Compilação e Execução

Para compilar o projeto, use o seguinte comando:

```bash
gcc -o rb_tree main.c rb.c
