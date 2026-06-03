#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NO_LISTA{

    //dados da aplicacao
    int code_product;
    char * tipo_produto;
    char * descricao;
    float preco;
    //mecanismo de uniao de NO_LISTAs
    struct NO_LISTA * prox;
    struct NO_LISTA *ant;
}NO_LISTA;

NO_LISTA *inicio = NULL;
NO_LISTA *fim = NULL;
int tam = 0;

//==================================================

typedef struct NO_FILA{

    //dados da aplicacao
    int code_product;
    char * tipo_produto;
    char * descricao;
    float preco;
    //mecanismo de uniao de NO_LISTAs
    struct NO_FILA * prox;

}NO_FILA;

NO_FILA *inicio_fila = NULL;
NO_FILA *fim_fila  = NULL;
int tam = 0;

void add(int code_product, char * tipo_produto, char * descricao, float preco){
   
    if(preco >= 0){

        NO_LISTA * novo = malloc(sizeof(NO_LISTA));
        novo->code_product = code_product;
        novo->tipo_produto = tipo_produto;
        novo->descricao = descricao;
        novo->preco = preco;
        novo->prox = NULL;
        novo->ant = NULL;

        //tratar como inserir 

        if(inicio == NULL){ //lista vazia
            //operacao de encaixe
            inicio = novo;
            fim = novo;
            tam++;
        }else{ // lista nao esta vazia...
        
            if(novo-> preco < inicio -> preco ){ // caso do inicio
                novo->prox = inicio;
                inicio->ant = novo;
                inicio = novo;
                tam++;

            }else if(novo -> preco > fim-> preco){ //caso do fim
                fim->prox = novo;
                novo->ant = fim;
                fim = novo;
                tam++;
            }else{
                //meio ...
                NO_LISTA* aux = inicio;
                while(aux->prox != NULL && aux->preco <= novo->preco){
                    aux = aux->prox;
                }
                novo->prox = aux;
                novo->ant = aux -> ant;
                aux->ant->prox = novo;
                aux->ant = novo;
                tam++;
            }
            //printf("=============================\n");
        }
    }/*else{
        printf("Preco invalido! Isso aqui e uma lista!");
    }*/
}

void imprimir(){
    NO * aux = inicio;
    printf("== PRODUTOS DISPONIVEIS ==\n\n");
    while(aux != NULL){
        printf("Codigo do produto: %d \n", aux->code_product);
        printf("Tipo do produto: %s \n", aux->tipo_produto);
        printf("Descricao: %s \n", aux->descricao);
        printf("Preco: %.2f \n", aux->preco);
        printf("----------------------------\n\n");
        aux = aux->prox;
    }
}

// Funcao para comprar um produto atraves do codigo - Remove da lista e retorna os dados
NO_LISTA* comprar(int code_product){
    NO_LISTA *aux = inicio;
    
    // Procura o produto pelo codigo
    while(aux != NULL){
        if(aux->code_product == code_product){
            // Encontrou o produto, agora remove da lista
            if(aux == inicio && aux == fim){ // unico elemento
                inicio = NULL;
                fim = NULL;
            }else if(aux == inicio){ // primeiro elemento
                inicio = aux->prox;
                inicio->ant = NULL;
            }else if(aux == fim){ // ultimo elemento
                fim = aux->ant;
                fim->prox = NULL;
            }else{ // elemento no meio
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
            }
            
            tam--;
            // Retorna o no removido (sem liberar memoria, pois sera usada)
            aux->prox = NULL;
            aux->ant = NULL;
            return aux;
        }
        aux = aux->prox;
    }
    
    // Produto nao encontrado
    return NULL;
}

void remover(int cod){

    if(cod >= 0 && cod < tam){

        if(cod == 0){ //inicio
            NO_LISTA *lixo = inicio;
            inicio = inicio->prox;
            inicio->ant = NULL;
            if(tam == 1){
               fim = NULL;
            }
            free(lixo);
            tam--;
        }else if(cod == tam-1){ // fim
           
            NO_LISTA *lixo = fim;
            fim->ant->prox = NULL;
            fim= fim->ant;
            //OUTRO MODO:
            // lixo->ant->prox=NULL;
            // fim=lixo->ant;
            free(lixo);
            tam--;
        }else{
            //meio....
            NO_LISTA *aux = inicio;
        /*   for(cod){
                aux = aux->prox;
            }  */ 
           
            aux->ant->prox= aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
            tam--;
        }
    }

}


// Funcao para pesquisar produtos por categoria (tipo)
void pesquisa(char* tipo){
    NO_LISTA * aux = inicio;
    int encontrado = 0;
    printf("\n== PRODUTOS DA CATEGORIA: %s ==\n\n", tipo);
    while(aux != NULL){
        if(strcmp(tipo,aux->tipo_produto) == 0){
            printf("Codigo do produto: %d \n", aux->code_product);
            printf("Tipo do produto: %s \n", aux->tipo_produto);
            printf("Descricao: %s \n", aux->descricao);
            printf("Preco: R$ %.2f \n", aux->preco);
            printf("-----------------------------\n");
            encontrado++;
        }
        aux = aux->prox;
    }
    if(encontrado == 0){
        printf("Nenhum produto encontrado nessa categoria!\n");
    }
    printf("Total de produtos encontrados: %d\n\n", encontrado);
}

// Funcao para pesquisar produtos dentro de um intervalo de preco
void pesquisar_por_preco(float preco_min, float preco_max){
    NO_LISTA * aux = inicio;
    int encontrado = 0;
    printf("\n== PRODUTOS ENTRE R$ %.2f E R$ %.2f ==\n\n", preco_min, preco_max);
    while(aux != NULL){
        if(aux->preco >= preco_min && aux->preco <= preco_max){
            printf("Codigo do produto: %d \n", aux->code_product);
            printf("Tipo do produto: %s \n", aux->tipo_produto);
            printf("Descricao: %s \n", aux->descricao);
            printf("Preco: R$ %.2f \n", aux->preco);
            printf("-----------------------------\n");
            encontrado++;
        }
        aux = aux->prox;
    }
    if(encontrado == 0){
        printf("Nenhum produto encontrado nesse intervalo de preco!\n");
    }
    printf("Total de produtos encontrados: %d\n\n", encontrado);
}

int main() {
   
    // 20 produtos para venda - Recebimento
    add(1001, "Parafina", "Parafina Premium Surfwax", 19.90);
    add(1002, "Parafina", "Parafina Cold Water", 22.50);
    add(1003, "Leash", "Leash 6ft Standard", 35.00);
    add(1004, "Leash", "Leash 7ft Preto", 38.50);
    add(1005, "Quilha", "Quilha FCS II", 65.00);
    add(1006, "Quilha", "Quilha Future", 45.90);
    add(1007, "Deck", "Deck Antiderrapante 2.0", 55.00);
    add(1008, "Deck", "Deck Premium Grip", 60.00);
    add(1009, "Parafina", "Parafina Basecoat", 18.00);
    add(1010, "Leash", "Leash 5.5ft Compacta", 32.00);
    add(1011, "Quilha", "Quilha Thruster", 70.00);
    add(1012, "Deck", "Deck Economico", 40.00);
    add(1013, "Parafina", "Parafina Warm Water", 21.00);
    add(1014, "Leash", "Leash 8ft XL", 42.00);
    add(1015, "Quilha", "Quilha Single Fin", 80.00);
    add(1016, "Deck", "Deck Professional", 75.00);
    add(1017, "Parafina", "Parafina Tropical", 20.50);
    add(1018, "Leash", "Leash Importada", 50.00);
    add(1019, "Quilha", "Quilha Quad", 90.00);
    add(1020, "Deck", "Deck Ultimate Grip", 85.00);

    int opcao;
    char tipo[50];
    float preco_min, preco_max;
    int codigo_compra;
    NO_LISTA *produto_comprado;

    do {
        printf("\n====================================\n");
        printf("   TATI SURF CO. - LOJA DE SURF\n");
        printf("====================================\n");
        printf("\n-> Opcao 1: Ver produtos disponiveis para compra\n");
        printf("-> Opcao 2: Ver produtos por categoria\n");
        printf("-> Opcao 3: Ver produtos por intervalo de valores\n");
        printf("-> Opcao 4: Comprar item\n");
        printf("-> Opcao 5: Encerrar atendimento\n");
        printf("\nEscolha uma opcao de acao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                imprimir();
                break;
                
            case 2:
                printf("\nDigite a categoria (Parafina, Leash, Quilha, Deck): ");
                scanf("%s", tipo);
                pesquisa(tipo);
                break;
                
            case 3:
                printf("\nDigite o preco minimo: ");
                scanf("%f", &preco_min);
                printf("Digite o preco maximo: ");
                scanf("%f", &preco_max);
                pesquisar_por_preco(preco_min, preco_max);
                break;
                
            case 4:
                printf("\nDigite o codigo do produto a comprar: ");
                scanf("%d", &codigo_compra);
                produto_comprado = comprar(codigo_compra);
                if(produto_comprado != NULL) {
                    printf("\n=== COMPRA REALIZADA ===\n");
                    printf("Codigo: %d\n", produto_comprado->code_product);
                    printf("Tipo: %s\n", produto_comprado->tipo_produto);
                    printf("Descricao: %s\n", produto_comprado->descricao);
                    printf("Preco: R$ %.2f\n", produto_comprado->preco);
                    printf("Produtos restantes em estoque: %d\n", tam);
                    free(produto_comprado);
                } else {
                    printf("\nProduto com codigo %d nao encontrado!\n", codigo_compra);
                }
                break;
                
            case 5:
                printf("\nObrigado por usar o sistema TATI SURF CO.!\n");
                printf("Total de produtos restantes: %d\n\n", tam);
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 5);

 return 0;
}