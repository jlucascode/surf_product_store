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

void add(int code_product, char * tipo_produto, char * descricao, float preco){
   
    if(preco >= 0){

        NO_LISTA * novo = malloc(sizeof(NO_LISTA));
        novo->code_product = code_product;
        novo->tipo_produto = tipo_produto;
        novo->descricao = descricao;
        novo->preco = preco;
        novo->prox = NULL;
        novo->ant = NULL;

        if(inicio == NULL){
            inicio = novo;
            fim = novo;
            tam++;
        }else{
        
            if(novo->preco < inicio->preco){
                novo->prox = inicio;
                inicio->ant = novo;
                inicio = novo;
                tam++;

            }else if(novo->preco > fim->preco){
                fim->prox = novo;
                novo->ant = fim;
                fim = novo;
                tam++;
            }else{
                NO_LISTA* aux = inicio;
                while(aux->prox != NULL && aux->preco <= novo->preco){
                    aux = aux->prox;
                }
                novo->prox = aux;
                novo->ant = aux->ant;
                aux->ant->prox = novo;
                aux->ant = novo;
                tam++;
            }
        }
    }
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

NO_LISTA* comprar(int code_product){
    NO_LISTA *aux = inicio;
    
    while(aux != NULL){
        if(aux->code_product == code_product){
            if(aux == inicio && aux == fim){
                inicio = NULL;
                fim = NULL;
            }else if(aux == inicio){
                inicio = aux->prox;
                inicio->ant = NULL;
            }else if(aux == fim){
                fim = aux->ant;
                fim->prox = NULL;
            }else{
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
            }
            
            tam--;
            aux->prox = NULL;
            aux->ant = NULL;
            return aux;
        }
        aux = aux->prox;
    }
    
    return NULL;
}

void remover(int cod){

    if(cod >= 0 && cod < tam){

        if(cod == 0){
            NO_LISTA *lixo = inicio;
            inicio = inicio->prox;
            if(tam == 1){
               fim = NULL;
            }else{
               inicio->ant = NULL;
            }
            free(lixo);
            tam--;
        }else if(cod == tam-1){
           
            NO_LISTA *lixo = fim;
            fim->ant->prox = NULL;
            fim = fim->ant;
            free(lixo);
            tam--;
        }else{
            NO_LISTA *aux = inicio;
            for(int i = 0; i < cod; i++){
                aux = aux->prox;
            }
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
            free(aux);
            tam--;
        }
    }

}

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

int tamanho_fila_entrega(){
    int count = 0;
    NO_FILA *aux = inicio_fila;
    while(aux != NULL){
        count++;
        aux = aux->prox;
    }
    return count;
}

void imprimir_fila_entrega(){
    if(inicio_fila == NULL){
        printf("\n!!! FILA DE ENTREGA VAZIA !!!\n");
        return;
    }
    
    NO_FILA *aux = inicio_fila;
    int i = 1;
    printf("== FILA DE ENTREGA ==\n\n");
    while(aux != NULL){
        printf("--- Pedido %d ---\n", i);
        printf("Codigo do produto: %d\n", aux->code_product);
        printf("Tipo: %s\n", aux->tipo_produto);
        printf("Descricao: %s\n", aux->descricao);
        printf("Preco: R$ %.2f\n", aux->preco);
        printf("Cliente: %s\n", aux->nome_cliente);
        printf("CPF: %s\n", aux->cpf);
        printf("Endereco: %s, %d - %s\n", aux->nome_rua, aux->numero_casa, aux->complemento);
        printf("CEP: %s\n", aux->cep);
        printf("-----------------------------\n");
        aux = aux->prox;
        i++;
    }
    printf("Total de pedidos na fila: %d\n\n", tamanho_fila_entrega());
}

int main() {
   
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

    int opcao;
    char tipo[50];
    float preco_min, preco_max;
    int codigo_compra;
    NO_LISTA *produto_comprado;
    char nome_cliente[100];
    char cpf[20];
    char cep[20];
    char nome_rua[100];
    int numero;
    char complemento[100];

    printf("\n====================================\n");
    printf("   TATI SURF CO. - LOJA DE SURF\n");
    printf("====================================\n");
    printf("Total de produtos em estoque: %d\n\n", tam);

    do {
        printf("\n====================================\n");
        printf("   TATI SURF CO. - MENU PRINCIPAL\n");
        printf("====================================\n");
        printf("1. Ver produtos disponiveis\n");
        printf("2. Ver produtos por categoria\n");
        printf("3. Ver produtos por intervalo de preco\n");
        printf("4. Comprar produto\n");
        printf("5. Ver fila de entrega\n");
        printf("6. Entregar proximo produto da fila\n");
        printf("7. Encerrar atendimento\n");
        printf("\nEscolha uma opcao: ");
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
                    
                    printf("\n--- DADOS PARA ENTREGA ---\n");
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
                    
                    adicionar_fila_entrega(produto_comprado, nome_cliente, cpf, cep, nome_rua, numero, complemento);
                    printf("\nPedido adicionado a fila de entrega com sucesso!\n");
                    
                    free(produto_comprado);
                } else {
                    printf("\nProduto com codigo %d nao encontrado!\n", codigo_compra);
                }
                break;
                
            case 5:
                imprimir_fila_entrega();
                break;
                
            case 6:
                remover_fila_entrega();
                break;
                
            case 7:
                printf("\nObrigado por usar o sistema TATI SURF CO.!\n");
                printf("Produtos restantes em estoque: %d\n", tam);
                printf("Pedidos na fila de entrega: %d\n\n", tamanho_fila_entrega());
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while(opcao != 7);

 return 0;
}
