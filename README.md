# TATI SURF CO. - Sistema de Gerenciamento de Loja de Surf

Sistema completo de gerenciamento de vendas e estoque para loja de surf, implementado em linguagem C. O projeto evolui em 3 versões, cada uma explorando estruturas de dados diferentes.

## Arquivos do Projeto

| Arquivo | Linhas | Estrutura | Produtos | Interface |
|---------|--------|-----------|----------|-----------|
| `surf_main.c` | 293 | Lista Duplamente Encadeada | 20 | Menu interativo |
| `surf2.c` | 472 | Lista Duplamente Encadeada + Fila de Entrega | 50 | Menu interativo |
| `surf2_simulado.c` | 502 | Lista Duplamente Encadeada + Fila de Entrega | 50 | Script automatizado |
| `surf3.c` | 353 | Árvore Binária de Busca (ABB) + Fila de Entrega | 100 | Script automatizado |

## Versão 1 — `surf_main.c`

Lista duplamente encadeada ordenada por preço crescente. Gerencia 4 tipos de produto:

1. **Parafina** — Ceras para prancha de surf
2. **Leash** — Cordinha de segurança
3. **Quilha** — Quilhas para pranchas
4. **Deck** — Decks antiderrapantes

### Funcionalidades

| Função | Descrição |
|--------|-----------|
| `add()` | Insere produto mantendo ordem por preço |
| `imprimir()` | Exibe todos os produtos |
| `pesquisa()` | Busca por categoria |
| `pesquisar_por_preco()` | Busca por faixa de preço |
| `comprar()` | Remove produto da lista (compra) |

### Menu Interativo

```
1. Ver produtos disponíveis para compra
2. Ver produtos por categoria
3. Ver produtos por intervalo de valores
4. Comprar item
5. Encerrar atendimento
```

### Compilar e Executar

```bash
gcc -Wall -Wextra -o surf_main surf_main.c
./surf_main
```

---

## Versão 2 — `surf2.c`

Adiciona uma **fila FIFO de entregas** ao lado da lista de produtos. Cada pedido na fila contém dados completos do cliente:

- Nome, CPF
- Endereço (CEP, rua, número, complemento)

### Funcionalidades Adicionais

| Função | Descrição |
|--------|-----------|
| `adicionar_fila()` | Insere pedido na fila de entrega |
| `entregar()` | Remove da fila e registra pagamento |
| `listar_fila_entrega()` | Exibe todos os pedidos pendentes |
| `gerar_relatorio()` | Exibe resumo financeiro |

### Menu (7 opções)

```
1. Ver produtos disponíveis
2. Ver produtos por categoria
3. Ver produtos por intervalo de valores
4. Comprar item
5. Exibir fila de entrega
6. Entregar produto (FIFO)
7. Encerrar atendimento
```

### Compilar e Executar

```bash
gcc -Wall -Wextra -o surf2 surf2.c
./surf2
```

---

## Versão 2 (Simulação) — `surf2_simulado.c`

Mesma estrutura e lógica do `surf2.c`, porém **totalmente automatizada** (sem menu interativo):

1. Recebe 50 produtos
2. Simula 25 compras (códigos ímpares) com 25 clientes fictícios
3. Adiciona todos à fila de entrega
4. Entrega 18 produtos com rodízio de 3 entregadores
5. Exibe resumo do expediente

### Compilar e Executar

```bash
gcc -Wall -Wextra -o surf2_simulado surf2_simulado.c
./surf2_simulado
```

---

## Versão 3 — `surf3.c`

Substitui a lista encadeada por uma **Árvore Binária de Busca (ABB)** organizada por código do produto.

### Diferenças da ABB

- Nós com ponteiros `esq`/`dir` em vez de `prox`/`ant`
- Inserção, remoção e travessia recursivas
- Remoção pelo critério do "maior dos menores" (antecessor em-ordem)

### Travessias Suportadas

| Percurso | Uso |
|----------|-----|
| In-ordem (esq → raiz → dir) | Listar todos os produtos / filtrar por categoria |
| Pós-ordem (esq → dir → raiz) | Filtrar por faixa de preço |

### Fluxo Automatizado

1. Gera 100 produtos (4 tipos × 10 descrições × preço por fórmula)
2. Remove 20 produtos (códigos pares `1002`–`1040`)
3. Entrega 10 produtos
4. Exibe resumo do expediente

### Compilar e Executar

```bash
gcc -Wall -Wextra -o surf3 surf3.c
./surf3
```

---

## Complexidade das Operações

### Lista Duplamente Encadeada (v1 e v2)

| Operação | Complexidade |
|----------|-------------|
| Inserir produto | O(n) |
| Listar todos | O(n) |
| Buscar por categoria | O(n) |
| Buscar por preço | O(n) |
| Comprar (remover) | O(n) |

### Árvore Binária de Busca (v3)

| Operação | Complexidade média | Pior caso |
|----------|--------------------|-----------|
| Inserir | O(log n) | O(n) |
| Buscar | O(log n) | O(n) |
| Remover | O(log n) | O(n) |
| Percorrer (in-ordem) | O(n) | O(n) |

---

## Dependências

- Compilador C (gcc, clang ou similar)
- Biblioteca padrão C (`stdlib.h`, `stdio.h`, `string.h`)

---

## Autor

Projeto educacional por [jlucascode](https://github.com/jlucascode).  
Última atualização: Junho 2026.
