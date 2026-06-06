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
    char * nome_cliente;
    char * cpf;
    char * cep;
    char * nome_rua;
    int numero_casa;
    char * complemento;
    //mecanismo de uniao de NO_FILA
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
    NO_LISTA * aux = inicio;
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

// Funcao para adicionar pedido a fila de entrega
void adicionar_fila_entrega(NO_LISTA* produto, char* nome_cliente, char* cpf, char* cep, 
                            char* nome_rua, int numero_casa, char* complemento){
    
    NO_FILA *novo = malloc(sizeof(NO_FILA));
    novo->code_product = produto->code_product;
    novo->tipo_produto = malloc(strlen(produto->tipo_produto) + 1);
    strcpy(novo->tipo_produto, produto->tipo_produto);
    novo->descricao = malloc(strlen(produto->descricao) + 1);
    strcpy(novo->descricao, produto->descricao);
    novo->preco = produto->preco;
    
    novo->nome_cliente = malloc(strlen(nome_cliente) + 1);
    strcpy(novo->nome_cliente, nome_cliente);
    novo->cpf = malloc(strlen(cpf) + 1);
    strcpy(novo->cpf, cpf);
    novo->cep = malloc(strlen(cep) + 1);
    strcpy(novo->cep, cep);
    novo->nome_rua = malloc(strlen(nome_rua) + 1);
    strcpy(novo->nome_rua, nome_rua);
    novo->numero_casa = numero_casa;
    novo->complemento = malloc(strlen(complemento) + 1);
    strcpy(novo->complemento, complemento);
    
    novo->prox = NULL;
    
    if(inicio_fila == NULL){
        inicio_fila = novo;
        fim_fila = novo;
    }else{
        fim_fila->prox = novo;
        fim_fila = novo;
    }
}

// Funcao para remover da fila e simular entrega
void remover_fila_entrega(){
    if(inicio_fila == NULL){
        printf("\n!!! FILA DE ENTREGA VAZIA !!!\n");
        return;
    }
    
    printf("\n=====================================\n");
    printf("Produto saindo para entrega...\n");
    printf("=====================================\n\n");
    
    printf("Codigo do produto: %d\n", inicio_fila->code_product);
    printf("Tipo do produto: %s\n", inicio_fila->tipo_produto);
    printf("Descricao: %s\n", inicio_fila->descricao);
    printf("Preco: R$ %.2f\n\n", inicio_fila->preco);
    
    printf("--- DADOS DO CLIENTE ---\n");
    printf("Nome: %s\n", inicio_fila->nome_cliente);
    printf("CPF: %s\n", inicio_fila->cpf);
    printf("CEP: %s\n", inicio_fila->cep);
    printf("Rua: %s\n", inicio_fila->nome_rua);
    printf("Numero: %d\n", inicio_fila->numero_casa);
    printf("Complemento: %s\n", inicio_fila->complemento);
    printf("=====================================\n\n");
    
    NO_FILA *lixo = inicio_fila;
    
    if(inicio_fila == fim_fila){
        inicio_fila = NULL;
        fim_fila = NULL;
    }else{
        inicio_fila = inicio_fila->prox;
    }
    
    free(lixo->tipo_produto);
    free(lixo->descricao);
    free(lixo->nome_cliente);
    free(lixo->cpf);
    free(lixo->cep);
    free(lixo->nome_rua);
    free(lixo->complemento);
    free(lixo);
}

// Funcao para exibir tamanho da fila de entrega
int tamanho_fila_entrega(){
    int count = 0;
    NO_FILA *aux = inicio_fila;
    while(aux != NULL){
        count++;
        aux = aux->prox;
    }
    return count;
}

int main() {
   
    // 50 produtos para venda - Recebimento de Produtos
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
    
    // 30 produtos adicionais
    add(1021, "Parafina", "Parafina Ice Cold", 23.00);
    add(1022, "Parafina", "Parafina Mr. Zog", 25.50);
    add(1023, "Leash", "Leash Kevlar 6ft", 48.00);
    add(1024, "Leash", "Leash Flex 7ft", 41.00);
    add(1025, "Quilha", "Quilha Five Fin", 75.00);
    add(1026, "Quilha", "Quilha Twin Fin", 68.00);
    add(1027, "Deck", "Deck Comfort Pro", 70.00);
    add(1028, "Deck", "Deck Grip Max", 65.00);
    add(1029, "Parafina", "Parafina Extra Grip", 19.50);
    add(1030, "Leash", "Leash Neon 8ft", 44.00);
    add(1031, "Quilha", "Quilha Bonzer", 95.00);
    add(1032, "Deck", "Deck Racing", 82.00);
    add(1033, "Parafina", "Parafina Sticky", 24.00);
    add(1034, "Leash", "Leash Reinforced 6ft", 39.00);
    add(1035, "Quilha", "Quilha Keel", 85.00);
    add(1036, "Deck", "Deck Wave Rider", 78.00);
    add(1037, "Parafina", "Parafina Heritage", 21.50);
    add(1038, "Leash", "Leash Double Swivel", 55.00);
    add(1039, "Quilha", "Quilha Retro Fish", 88.00);
    add(1040, "Deck", "Deck Extreme", 92.00);
    add(1041, "Parafina", "Parafina Eco", 26.00);
    add(1042, "Leash", "Leash Pro Wave", 52.00);
    add(1043, "Quilha", "Quilha Wave Slicer", 98.00);
    add(1044, "Deck", "Deck Carbon", 105.00);
    add(1045, "Parafina", "Parafina Gold", 29.00);
    add(1046, "Leash", "Leash Speed", 45.50);
    add(1047, "Quilha", "Quilha Fusion", 72.00);
    add(1048, "Deck", "Deck Pro Series", 88.00);
    add(1049, "Parafina", "Parafina Ultimate", 27.00);
    add(1050, "Leash", "Leash Flex Pro", 47.00);

    // PARTE 2: TESTES
    printf("\n\n");
    printf("========================================\n");
    printf("ETAPA 1: RECEBIMENTO DE PRODUTOS\n");
    printf("========================================\n");
    printf("Total de produtos adicionados ao estoque: %d\n", tam);
    imprimir();
    
    printf("\n\n");
    printf("========================================\n");
    printf("ETAPA 2: PROCESSO DE REVENDA (COMPRA)\n");
    printf("Simulando visualizacao/compra de 20 produtos distintos\n");
    printf("========================================\n\n");
    
    // Array com 20 codigos de produtos para comprar
    int codigos_compra[20] = {1001, 1003, 1005, 1007, 1009, 1011, 1013, 1015, 1017, 1019, 
                              1021, 1023, 1025, 1027, 1029, 1031, 1033, 1035, 1037, 1039};
    
    NO_LISTA *produto_comprado;
    
    for(int i = 0; i < 20; i++){
        produto_comprado = comprar(codigos_compra[i]);
        if(produto_comprado != NULL){
            printf("\n--- COMPRA %d ---\n", i+1);
            printf("Codigo: %d | Tipo: %s | Descricao: %s | Preco: R$ %.2f\n", 
                   produto_comprado->code_product, 
                   produto_comprado->tipo_produto,
                   produto_comprado->descricao, 
                   produto_comprado->preco);
            printf("Status: COMPRA REALIZADA\n");
            
            // Aguardar dados do cliente para criar pedido de entrega
            char nome_cliente[100];
            char cpf[20];
            char cep[20];
            char nome_rua[100];
            int numero;
            char complemento[100];
            
            printf("Digite nome do cliente: ");
            scanf(" %[^\n]", nome_cliente);
            printf("Digite CPF (formato xxx.xxx.xxx-xx): ");
            scanf(" %[^\n]", cpf);
            printf("Digite CEP (somente numeros): ");
            scanf(" %[^\n]", cep);
            printf("Digite nome da rua: ");
            scanf(" %[^\n]", nome_rua);
            printf("Digite numero da casa: ");
            scanf("%d", &numero);
            printf("Digite complemento (apto, bloco, etc): ");
            scanf(" %[^\n]", complemento);
            
            // Adicionar a fila de entrega
            adicionar_fila_entrega(produto_comprado, nome_cliente, cpf, cep, nome_rua, numero, complemento);
            
            free(produto_comprado);
            printf("Pedido adicionado a fila de entrega!\n");
        }
    }
    
    printf("\n\nProdutos restantes em estoque: %d\n", tam);
    printf("Total de pedidos na fila de entrega: %d\n\n", tamanho_fila_entrega());
    
    printf("\n\n");
    printf("========================================\n");
    printf("ETAPA 3: ENTREGA E PAGAMENTO\n");
    printf("Simulando entrega de 15 produtos vendidos\n");
    printf("========================================\n\n");
    
    for(int i = 0; i < 15; i++){
        printf("\n[ENTREGA %d]\n", i+1);
        remover_fila_entrega();
        printf("Produto entregue e pagamento realizado!\n");
    }
    
    printf("\n\nPedidos restantes na fila: %d\n\n", tamanho_fila_entrega());
    printf("========================================\n");
    printf("TESTE CONCLUIDO COM SUCESSO!\n");
    printf("========================================\n\n");
    
    return 0;
}