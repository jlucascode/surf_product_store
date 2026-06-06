# TATI SURF CO. - Sistema de Gerenciamento de Loja de Surf

Sistema completo de gerenciamento de vendas e estoque para loja de surf, implementado em linguagem C utilizando lista duplamente encadeada.

## 📚 Sobre o Projeto

Este projeto implementa um sistema integrado de gerenciamento de loja de surf que realiza a gestão completa desde o recebimento dos produtos até a revenda e saída para entrega. O sistema utiliza uma estrutura de dados de lista duplamente encadeada, mantendo os produtos sempre organizados em ordem crescente de preço.

## 🏄 Produtos Gerenciados

O sistema gerencia 4 tipos principais de produtos:
1. **Parafina** - Ceras para prancha de surf
2. **Leash** - Cordinha de segurança
3. **Quilha** - Quilhas para pranchas
4. **Deck** - Decks antiderrapantes

## 📊 Estrutura de Dados

### Elemento (Node - NO)
Cada produto é armazenado em um nó com os seguintes dados:

| Campo | Tipo | Descrição |
|-------|------|-----------|
| `code_product` | int | Código único do produto |
| `tipo_produto` | char* | Categoria (Parafina, Leash, Quilha, Deck) |
| `descricao` | char* | Marca e informações do produto |
| `preco` | float | Preço do produto |
| `prox` | NO* | Ponteiro para próximo nó |
| `ant` | NO* | Ponteiro para nó anterior |

### Lista de Produtos
- **Tipo**: Lista Duplamente Encadeada
- **Ordenação**: Sempre mantida em ordem crescente de preço
- **Inserção automática**: Produtos inseridos mantêm a ordem
- **Critério de desempate**: Ordem de chegada (FIFO)

## 💡 Funcionalidades Principais

### 1️⃣ Processo de Recebimento de Produtos
- **Função**: `void add(int code_product, char *tipo_produto, char *descricao, float preco)`
- **Descrição**: Adiciona produtos novos ao catálogo de vendas
- **Validação**: Verifica se o preço é válido (>= 0)
- **Inserção automática**: Mantém a lista ordenada por preço crescente
- **Implementação**: Trata 3 casos:
  - Inserção no início (preço menor)
  - Inserção no fim (preço maior)
  - Inserção no meio (mantendo ordem)

**Produtos cadastrados para teste**: 20 produtos diferentes

### 2️⃣ Processo de Revenda - Visualização

#### 2.1 Visualizar todos os produtos disponíveis
- **Função**: `void imprimir()`
- **Exibe**: Todos os produtos em ordem crescente de preço
- **Informações**: Código, tipo, descrição e preço

#### 2.2 Pesquisar por categoria
- **Função**: `void pesquisa(char *tipo)`
- **Parâmetro**: Categoria (Parafina, Leash, Quilha ou Deck)
- **Resultado**: Lista de produtos da categoria em ordem de preço
- **Validação**: Informa se nenhum produto foi encontrado

#### 2.3 Pesquisar por intervalo de preço
- **Função**: `void pesquisar_por_preco(float preco_min, float preco_max)`
- **Parâmetros**: Preço mínimo e máximo
- **Resultado**: Produtos dentro do intervalo especificado
- **Ordenação**: Mantém ordem de preço crescente

### 3️⃣ Processo de Revenda - Compra

#### Comprar Produto
- **Função**: `NO* comprar(int code_product)`
- **Parâmetro**: Código único do produto
- **Operação**: 
  - Remove o produto da lista de disponíveis
  - Mantém integridade da lista duplamente encadeada
- **Retorno**: Retorna os dados do produto removido (sem liberar memória)
- **Casos tratados**:
  - Produto único na lista
  - Primeiro produto
  - Último produto
  - Produto no meio da lista
- **Validação**: Retorna NULL se o produto não existir

## 🚀 Como Usar

### Compilação

```bash
gcc -Wall -Wextra -o surf_main surf_main.c
```

### Execução

```bash
./surf_main
```

## 📋 Menu Interativo

O programa oferece um menu com as seguintes opções:

```
1. Ver produtos disponíveis para compra
2. Ver produtos por categoria
3. Ver produtos por intervalo de valores
4. Comprar item
5. Encerrar atendimento
```

## 🧪 Testes Realizados

### Teste 1: Recebimento de Produtos
✅ 20 produtos cadastrados automaticamente no sistema com variação de tipos e preços:
- Parafinas (4 produtos): R$ 18.00 a R$ 22.50
- Leash (5 produtos): R$ 32.00 a R$ 50.00
- Quilhas (5 produtos): R$ 45.90 a R$ 90.00
- Decks (6 produtos): R$ 40.00 a R$ 85.00

### Teste 2: Visualização de Produtos
✅ Lista completa de produtos ordernados por preço crescente

### Teste 3: Busca por Categoria
✅ Pesquisas de categorias testadas:
- Parafina
- Leash
- Quilha
- Deck

### Teste 4: Busca por Intervalo de Preço
✅ Buscas com diferentes faixas de preço:
- Produtos até R$ 40.00
- Produtos entre R$ 40.00 e R$ 70.00
- Produtos acima de R$ 70.00

### Teste 5: Compra de Produtos
✅ Minimo 5 produtos distintos foram removidos com sucesso:
- Produto código 1001 (Parafina Premium Surfwax - R$ 19.90)
- Produto código 1006 (Quilha Future - R$ 45.90)
- Produto código 1012 (Deck Economico - R$ 40.00)
- Produto código 1014 (Leash 8ft XL - R$ 42.00)
- Produto código 1019 (Quilha Quad - R$ 90.00)

**Resultado**: Sistema mantém integridade da lista após remoções

## 🔧 Dependências

- **Compilador C**: gcc, clang ou equivalente
- **Bibliotecas**: stdlib.h, stdio.h, string.h

## 📝 Detalhes de Implementação

### Complexidade de Operações

| Operação | Complexidade |
|----------|-------------|
| Adicionar produto | O(n) |
| Visualizar todos | O(n) |
| Pesquisar por categoria | O(n) |
| Pesquisar por preço | O(n) |
| Comprar (remover) | O(n) |

### Gerenciamento de Memória

- Produtos adicionados são alocados dinamicamente com `malloc()`
- Produtos comprados são removidos da lista e liberam memória
- Ponteiros mantêm referências bidirecionais (anterior e próximo)

## 📊 Exemplo de Saída

### Visualizar todos os produtos

Exemplo compilando a lista:

```bash
gcc -o lista lista.c
```

### Execução

```bash
./saida
```

### Compilação com Flags de Aviso

Para uma compilação mais rigorosa:

```bash
gcc -Wall -Wextra -o saida nome_arquivo.c
```

## 📋 Estrutura de Dados em Detalhes

### Listas Encadeadas
Estruturas de dados onde cada nó armazena um valor e referências (ponteiros) para outros nós. Permitem inserção e remoção eficiente em qualquer posição.

- **Lista Simples**: Cada nó aponta apenas para o próximo
- **Lista Duplamente Encadeada**: Cada nó aponta para o próximo E para o anterior

### Filas
Estrutura FIFO onde elementos são inseridos no final e removidos do início. Útil para processamento em ordem de chegada.

### Pilhas
Estrutura LIFO onde elementos são inseridos e removidos do topo. Útil para algoritmos recursivos, análise de expressões e desfazer operações.

## 🔧 Dependências

- Compilador C (gcc, clang ou similar)
- Biblioteca padrão C (stdlib.h, stdio.h, string.h)

## � Exemplo de Saída

### Visualizar todos os produtos
```
== PRODUTOS DISPONIVEIS ==

Codigo do produto: 1009
Tipo do produto: Parafina
Descricao: Parafina Basecoat
Preco: 18.00
-----------------------------

Codigo do produto: 1001
Tipo do produto: Parafina
Descricao: Parafina Premium Surfwax
Preco: 19.90
-----------------------------
```

### Pesquisar por categoria
```
== PRODUTOS DA CATEGORIA: Quilha ==

Codigo do produto: 1006
Tipo do produto: Quilha
Descricao: Quilha Future
Preco: R$ 45.90
-----------------------------

Codigo do produto: 1005
Tipo do produto: Quilha
Descricao: Quilha FCS II
Preco: R$ 65.00
-----------------------------
```

### Comprar um produto
```
=== COMPRA REALIZADA ===
Codigo: 1001
Tipo: Parafina
Descricao: Parafina Premium Surfwax
Preco: R$ 19.90
Produtos restantes em estoque: 19
```

## 🎯 Objetivos Alcançados

✅ Implementação completa de lista duplamente encadeada
✅ Gestão de estoque com inserção automática ordenada
✅ Sistema de busca e visualização de produtos
✅ Processo de compra com remoção da lista
✅ Preservação de integridade dos dados
✅ Menu interativo para o usuário
✅ Validação de entrada de dados
✅ Testes com 20 produtos e 5+ operações de compra

## 🛠️ Possíveis Extensões Futuras

- Implementar persistência de dados em arquivo
- Adicionar sistema de carrinho de compras
- Implementar pedidos e entregas
- Adicionar sistema de estoque por quantidade
- Interface gráfica
- Relatórios de vendas

## 📄 Autor

Desenvolvido como projeto educacional de estruturas de dados em C.

---

**Última atualização**: Maio 2026
- Praticar manipulação de ponteiros
- Comparar diferentes implementações da mesma estrutura
- Aplicar conhecimento em exemplos práticos

## 📄 Licença

Este projeto é educacional e pode ser usado livremente para fins de aprendizado.

## 👤 Autor

Desenvolvido como material de estudo em estruturas de dados.

---

**Última atualização**: Junho de 2026
