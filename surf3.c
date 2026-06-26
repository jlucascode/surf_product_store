#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ============================================================
// DECISAO 1: estrutura da ABB com esq/dir
// A lista tinha prox/ant (duplamente encadeada). Na ABB,
// cada no tem no maximo 2 filhos: esquerda (codigos menores)
// e direita (codigos maiores). Sem ponteiro "ant" porque a
// navegacao e recursiva, nao linear.
// ============================================================
typedef struct NO {
    int code_product;
    char *tipo_produto;
    char *descricao;
    float preco;
    struct NO *esq;
    struct NO *dir;
} NO;

NO *raiz = NULL;
int tam = 0;

// ============================================================
// DECISAO 2: fila de entrega IDENTICA a Parte 2
// Nao tem motivo pra mudar: fila continua sendo FIFO,
// estrutura continua a mesma (com nome, cpf, endereco).
// ============================================================
typedef struct NO_FILA {
    int code_product;
    char *tipo_produto;
    char *descricao;
    float preco;
    char *nome_cliente;
    char *cpf;
    char *cep;
    char *nome_rua;
    int numero_casa;
    char *complemento;
    struct NO_FILA *prox;
} NO_FILA;

NO_FILA *inicio_fila = NULL;
NO_FILA *fim_fila = NULL;

// ============================================================
// DECISAO 3: inserir recursivo
// Compara code_product:
//   menor -> esq, maior -> dir, igual -> ignora (codigo unico)
// Retorna a nova raiz (ou a raiz atualizada) pra manter a
// arvore conectada. Por isso usamos "raiz = inserir(raiz...)".
// ============================================================
NO* inserir(NO* raiz, int code, char* tipo, char* desc, float preco) {
    if (raiz == NULL) {
        NO* novo = malloc(sizeof(NO));
        novo->code_product = code;
        novo->tipo_produto = tipo;
        novo->descricao = desc;
        novo->preco = preco;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (code < raiz->code_product)
        raiz->esq = inserir(raiz->esq, code, tipo, desc, preco);
    else if (code > raiz->code_product)
        raiz->dir = inserir(raiz->dir, code, tipo, desc, preco);
    return raiz;
}

// ============================================================
// DECISAO 4: ver por categoria usa IN-ORDEM (esq -> raiz -> dir)
// O enunciado pede in-ordem. Isso mostra os produtos em ordem
// crescente de codigo (natural da ABB), filtrados pelo tipo.
// ============================================================
void imprimir_por_categoria(NO* raiz, char* tipo) {
    if (raiz == NULL) return;
    imprimir_por_categoria(raiz->esq, tipo);
    if (strcmp(tipo, raiz->tipo_produto) == 0)
        printf("Cod %d | %s | %s | R$ %.2f\n",
               raiz->code_product, raiz->tipo_produto,
               raiz->descricao, raiz->preco);
    imprimir_por_categoria(raiz->dir, tipo);
}

// ============================================================
// DECISAO 5: ver por preco usa POS-ORDEM (esq -> dir -> raiz)
// O enunciado pede pos-ordem. Processa filhos antes da raiz.
// ============================================================
void imprimir_por_preco(NO* raiz, float min, float max) {
    if (raiz == NULL) return;
    imprimir_por_preco(raiz->esq, min, max);
    imprimir_por_preco(raiz->dir, min, max);
    if (raiz->preco >= min && raiz->preco <= max)
        printf("Cod %d | %s | %s | R$ %.2f\n",
               raiz->code_product, raiz->tipo_produto,
               raiz->descricao, raiz->preco);
}

// ============================================================
// DECISAO 6: imprimir tudo (in-ordem sem filtro)
// ============================================================
void imprimir_tudo(NO* raiz) {
    if (raiz == NULL) return;
    imprimir_tudo(raiz->esq);
    printf("Cod %d | %s | %s | R$ %.2f\n",
           raiz->code_product, raiz->tipo_produto,
           raiz->descricao, raiz->preco);
    imprimir_tudo(raiz->dir);
}

// ============================================================
// DECISAO 7: remover 100% recursivo
// Segue EXATAMENTE o esqueleto que voce mostrou:
//
//   if (aux == NULL) -> nao achou
//   else if (achou)
//     folha         -> free, retorna NULL
//     1 filho dir   -> free, retorna o filho
//     1 filho esq   -> free, retorna o filho
//     2 filhos      -> substitui pelo MAIOR DOS MENORES
//                      (no mais a direita da subarvore esquerda)
//   else if (id <)  -> vai pra esquerda
//   else            -> vai pra direita
//
// Escolhi "maior dos menores" em vez de "menor dos maiores"
// porque e mais intuitivo: pega o maior no da esquerda.
// ============================================================
NO* maior_menores(NO* raiz) {
    while (raiz->dir != NULL)
        raiz = raiz->dir;
    return raiz;
}

NO* remover(NO* raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id < raiz->code_product)
        raiz->esq = remover(raiz->esq, id);
    else if (id > raiz->code_product)
        raiz->dir = remover(raiz->dir, id);
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        } else if (raiz->esq == NULL) {
            NO* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NO* temp = raiz->esq;
            free(raiz);
            return temp;
        } else {
            NO* sub = maior_menores(raiz->esq);
            raiz->code_product = sub->code_product;
            raiz->tipo_produto = sub->tipo_produto;
            raiz->descricao = sub->descricao;
            raiz->preco = sub->preco;
            raiz->esq = remover(raiz->esq, sub->code_product);
        }
    }
    return raiz;
}

// ============================================================
// DECISAO 8: buscar (auxiliar para a compra)
// Antes de remover, a gente busca o no para copiar os dados.
// Depois chama remover(). Isso resolve o problema de o no
// ser liberado dentro do remover e nao podermos mais ler os
// dados depois.
// ============================================================
NO* buscar(NO* raiz, int id) {
    if (raiz == NULL || raiz->code_product == id)
        return raiz;
    if (id < raiz->code_product)
        return buscar(raiz->esq, id);
    return buscar(raiz->dir, id);
}

// ============================================================
// Funcoes da fila (identicas a Parte 2)
// ============================================================
void adicionar_fila_entrega(NO* produto, char* nome_cliente, char* cpf,
                            char* cep, char* nome_rua, int num, char* complemento) {
    NO_FILA *novo = malloc(sizeof(NO_FILA));
    if (!novo) return;
    novo->code_product = produto->code_product;
    novo->tipo_produto = produto->tipo_produto;
    novo->descricao = produto->descricao;
    novo->preco = produto->preco;
    novo->nome_cliente = nome_cliente;
    novo->cpf = cpf;
    novo->cep = cep;
    novo->nome_rua = nome_rua;
    novo->numero_casa = num;
    novo->complemento = complemento;
    novo->prox = NULL;
    if (inicio_fila == NULL) {
        inicio_fila = novo;
        fim_fila = novo;
    } else {
        fim_fila->prox = novo;
        fim_fila = novo;
    }
}

void remover_fila_entrega() {
    if (!inicio_fila) { printf("  Fila vazia!\n"); return; }
    printf("  Entregue: Cod %d | %s | %s | R$ %.2f | Cliente: %s\n",
           inicio_fila->code_product, inicio_fila->tipo_produto,
           inicio_fila->descricao, inicio_fila->preco,
           inicio_fila->nome_cliente);
    NO_FILA *lixo = inicio_fila;
    if (inicio_fila == fim_fila) {
        inicio_fila = NULL;
        fim_fila = NULL;
    } else {
        inicio_fila = inicio_fila->prox;
    }
    free(lixo);
}

int tam_fila() {
    int c = 0;
    NO_FILA *aux = inicio_fila;
    while (aux) { c++; aux = aux->prox; }
    return c;
}

// ============================================================
// main()
// ============================================================
int main() {
    printf("========================================\n");
    printf("   TATI SURF CO. - PARTE 3 (ABB)\n");
    printf("========================================\n\n");

    // --- ETAPA 1: RECEBER 100 PRODUTOS ---
    printf("=== ETAPA 1: RECEBENDO 100 PRODUTOS ===\n\n");

    char* tipos[4] = {"Parafina", "Leash", "Quilha", "Deck"};
    char* descs[4][10] = {
        {"Premium Surfwax", "Cold Water", "Basecoat", "Tropical", "Eco",
         "Extra Grip", "Mr. Zog", "Ice", "Heritage", "Ultimate"},
        {"6ft Standard", "7ft Pro", "8ft XL", "Double Swivel", "Flex",
         "Kevlar", "Neon", "Reinforced", "Speed", "Pro Wave"},
        {"FCS II", "Future", "Thruster", "Single Fin", "Quad",
         "Five Fin", "Twin Fin", "Bonzer", "Keel", "Fusion"},
        {"Antiderrapante", "Premium Grip", "Professional", "Racing", "Carbon",
         "Comfort Pro", "Grip Max", "Wave Rider", "Pro Series", "Extreme"}
    };
    float precos_base[4] = {20.0, 35.0, 60.0, 50.0};

    int cod = 1001;
    for (int i = 0; i < 100; i++) {
        int t = i % 4;
        int d = (i / 4) % 10;
        float p = precos_base[t] + (d * 3.0) + (i % 5) * 1.5;
        raiz = inserir(raiz, cod, tipos[t], descs[t][d], p);
        tam++;
        cod++;
    }
    printf("Total de produtos em estoque: %d\n\n", tam);

    printf("--- Todos os produtos (IN-ORDEM) ---\n");
    imprimir_tudo(raiz);
    printf("\n");

    printf("--- Produtos 'Parafina' (IN-ORDEM) ---\n");
    imprimir_por_categoria(raiz, "Parafina");
    printf("\n");

    printf("--- Produtos entre R$ 30 e R$ 60 (POS-ORDEM) ---\n");
    imprimir_por_preco(raiz, 30.0, 60.0);
    printf("\n");

    // --- ETAPA 2: COMPRAR 20 PRODUTOS ---
    printf("=== ETAPA 2: COMPRANDO 20 PRODUTOS ===\n\n");

    char* nomes[20] = {
        "Joao Silva", "Maria Santos", "Carlos Oliveira", "Ana Souza",
        "Pedro Lima", "Julia Costa", "Lucas Pereira", "Fernanda Almeida",
        "Rafael Martins", "Beatriz Rocha", "Gabriel Barbosa", "Larissa Dias",
        "Thiago Correia", "Amanda Freitas", "Felipe Nascimento", "Camila Ribeiro",
        "Diego Cardoso", "Vanessa Araujo", "Bruno Cavalcanti", "Patricia Castro"
    };
    char* cpfs[20] = {
        "111.111.111-11","222.222.222-22","333.333.333-33","444.444.444-44",
        "555.555.555-55","666.666.666-66","777.777.777-77","888.888.888-88",
        "999.999.999-99","000.000.000-00","121.212.121-21","232.323.232-32",
        "343.434.343-43","454.545.454-54","565.656.565-65","676.767.676-76",
        "787.878.787-87","898.989.898-98","909.090.909-09","010.101.010-10"
    };

    int compras = 0;
    // Comprar 20 produtos com codigos pares (1002, 1004, ... 1040)
    for (int i = 0; i < 20; i++) {
        int cod_compra = 1002 + i * 2;

        NO* prod = buscar(raiz, cod_compra);
        if (prod != NULL) {
            int c = prod->code_product;
            char* t = prod->tipo_produto;
            char* d = prod->descricao;
            float p = prod->preco;

            // Remove da ABB (100% recursivo)
            raiz = remover(raiz, cod_compra);
            tam--;

            // Cria o processo de venda (adiciona na fila de entrega)
            NO temp = {c, t, d, p, NULL, NULL};
            adicionar_fila_entrega(&temp, nomes[compras], cpfs[compras],
                                   "00000-000", "Rua das Flores", 100 + compras,
                                   "Casa");

            printf("Compra %2d: Cod %d | %s | %s | R$ %.2f | Cliente: %s\n",
                   compras+1, c, t, d, p, nomes[compras]);
            compras++;
        }
    }
    printf("\nTotal de compras: %d\n", compras);
    printf("Produtos restantes em estoque: %d\n", tam);
    printf("Pedidos na fila de entrega: %d\n\n", tam_fila());

    // --- ETAPA 3: ENTREGAR 10 PRODUTOS ---
    printf("=== ETAPA 3: ENTREGANDO 10 PRODUTOS ===\n\n");

    float total_recebido = 0;
    int entregas = 0;
    for (int i = 0; i < 10 && inicio_fila != NULL; i++) {
        total_recebido += inicio_fila->preco;
        remover_fila_entrega();
        entregas++;
    }

    printf("\nTotal de entregas: %d\n", entregas);
    printf("Valor total recebido: R$ %.2f\n\n", total_recebido);

    // --- RESUMO ---
    printf("========================================\n");
    printf("   RESUMO DO EXPEDIENTE\n");
    printf("========================================\n");
    printf("Produtos em estoque:      %3d\n", tam);
    printf("Vendas realizadas:         %2d\n", compras);
    printf("Entregas realizadas:       %2d\n", entregas);
    printf("Valor total recebido:   R$ %.2f\n", total_recebido);
    printf("Pedidos na fila:           %2d\n", tam_fila());
    printf("========================================\n");

    return 0;
}
