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
        if(novo == NULL) return;
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
                if(aux->ant != NULL){
                    aux->ant->prox = novo;
                }else{
                    inicio = novo;
                }
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
    if(novo == NULL) return;
   
    novo->code_product = produto->code_product;
    novo->tipo_produto = produto->tipo_produto;
    novo->descricao = produto->descricao;
    novo->preco = produto->preco;

    novo->nome_cliente = nome_cliente;
    novo->cpf = cpf;
    novo->cep = cep;
    novo->nome_rua = nome_rua;
    novo->numero_casa = numero_casa;
    novo->complemento = complemento;
    
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
    // ETAPA 1: RECEBIMENTO DE PRODUTOS (50 produtos)
    printf("========================================\n");
    printf("   TATI SURF CO. - LOJA DE SURF\n");
    printf("========================================\n");
    printf("ETAPA 1: RECEBIMENTO DE PRODUTOS\n");
    printf("Adicionando 50 produtos ao estoque...\n\n");

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

    printf("Total de produtos em estoque: %d\n\n", tam);

    imprimir();
 
    // SÃO ALGUNS DADOS FICTICIOS PARA 25 CLIENTES

    char *nomes[25] = {
        "Joao Silva", "Maria Santos", "Carlos Oliveira", "Ana Souza",
        "Pedro Lima", "Juliana Costa", "Lucas Pereira", "Fernanda Almeida",
        "Rafael Martins", "Beatriz Rocha", "Gabriel Barbosa", "Larissa Dias",
        "Thiago Correia", "Amanda Freitas", "Felipe Nascimento", "Camila Ribeiro",
        "Diego Cardoso", "Vanessa Araujo", "Bruno Cavalcanti", "Patricia Castro",
        "Eduardo Moreira", "Tatiana Fonseca", "Rodrigo Teixeira", "Isabela Campos",
        "Leonardo Andrade"
    };
    char *cpfs[25] = {
        "123.456.789-01", "234.567.890-12", "345.678.901-23", "456.789.012-34",
        "567.890.123-45", "678.901.234-56", "789.012.345-67", "890.123.456-78",
        "901.234.567-89", "012.345.678-90", "112.233.445-56", "223.344.556-67",
        "334.455.667-78", "445.566.778-89", "556.677.889-90", "667.788.990-01",
        "778.899.001-12", "889.900.112-23", "990.011.223-34", "101.112.334-45",
        "202.223.445-56", "303.334.556-67", "404.445.667-78", "505.556.778-89",
        "606.667.889-90"
    };
    char *ceps[25] = {
        "01001000", "02002000", "03003000", "04004000",
        "05005000", "06006000", "07007000", "08008000",
        "09009000", "10010000", "11011000", "12012000",
        "13013000", "14014000", "15015000", "16016000",
        "17017000", "18018000", "19019000", "20020000",
        "21021000", "22022000", "23023000", "24024000",
        "25025000"
    };
    char *ruas[25] = {
        "Rua das Flores", "Av. Paulista", "Rua do Comercio", "Rua 7 de Setembro",
        "Av. Brasil", "Rua XV de Novembro", "Rua da Praia", "Av. Atlantica",
        "Rua do Sol", "Rua das Acacias", "Av. Central", "Rua da Matriz",
        "Rua do Porto", "Av. Independencia", "Rua dos Pinheiros", "Rua Augusta",
        "Av. Rio Branco", "Rua da Liberdade", "Rua do Imperador", "Rua das Palmeiras",
        "Av. Beira Mar", "Rua do Farol", "Rua da Igreja", "Rua do Mercado",
        "Av. das Americas"
    };
    int numeros[25] = {
        100, 250, 380, 50, 720, 45, 910, 180, 65, 320,
        500, 88, 150, 430, 77, 600, 210, 340, 95, 820,
        160, 550, 30, 400, 270
    };
    char *complementos[25] = {
        "Apto 101", "Casa", "Apto 202", "Casa 2", "Apto 305",
        "Casa 5", "Apto 410", "Bloco A", "Casa 10", "Apto 603",
        "Casa 15", "Bloco B Apto 12", "Apto 801", "Casa 20", "Apto 504",
        "Bloco C", "Apto 702", "Casa 3", "Bloco D Apto 8", "Apto 901",
        "Casa 7", "Apto 1102", "Casa 12", "Apto 303", "Bloco E"
    };
    // ETAPA 2: REVENDA (25 compras)
    NO_LISTA *produto_comprado;
    int compras_realizadas = 0;
    int codigos_compra[25] = {
        1001, 1003, 1005, 1007, 1009, 1011, 1013, 1015,
        1017, 1019, 1021, 1023, 1025, 1027, 1029, 1031,
        1033, 1035, 1037, 1039, 1041, 1043, 1045, 1047, 1049
    };

    printf("========================================\n");
    printf("   ETAPA 2: PROCESSO DE REVENDA\n");
    printf("========================================\n");
    printf("Simulando a compra de 25 produtos...\n\n");

    for(int i = 0; i < 25; i++){
        produto_comprado = comprar(codigos_compra[i]);

        if(produto_comprado != NULL){
            compras_realizadas++;
            printf("Compra #%d: codigo %d - %s - R$ %.2f - Cliente: %s\n",
                   i+1, produto_comprado->code_product, produto_comprado->descricao,
                   produto_comprado->preco, nomes[i]);

            adicionar_fila_entrega(produto_comprado, nomes[i], cpfs[i], ceps[i],
                                   ruas[i], numeros[i], complementos[i]);

            free(produto_comprado);
        }else{
            printf("Produto codigo %d ja vendido ou inexistente!\n", codigos_compra[i]);
        }
    }

    printf("\nTotal de compras realizadas: %d\n", compras_realizadas);
    printf("Produtos restantes em estoque: %d\n\n", tam);

    imprimir_fila_entrega();

    pesquisa("Parafina");
    pesquisar_por_preco(30.00, 60.00);

    int entregas_realizadas = 0;
    float total_recebido = 0.0;

    printf("========================================\n");
    printf("   ETAPA 3: PROCESSO DE ENTREGA E PAGAMENTO\n");
    printf("========================================\n");
    printf("Simulando a entrega de 18 produtos...\n\n");

    for(int i = 0; i < 18; i++){
        if(inicio_fila == NULL){
            printf("Fila de entrega vazia! Entregas encerradas.\n");
            break;
        }

        total_recebido += inicio_fila->preco;
        remover_fila_entrega();
        entregas_realizadas++;

        printf("--- Entregador %d recebeu o pagamento ---\n\n",
               (entregas_realizadas % 3 == 0 ? 3 : entregas_realizadas % 3));
    }

    printf("Total de entregas realizadas: %d\n", entregas_realizadas);
    printf("Valor total recebido: R$ %.2f\n\n", total_recebido);
    printf("========================================\n");
    printf("   RESUMO DO EXPEDIENTE - TATI SURF CO.\n");
    printf("========================================\n");
    printf("Produtos restantes em estoque:    %d\n", tam);
    printf("Total de vendas realizadas:       %d\n", compras_realizadas);
    printf("Total de entregas realizadas:     %d\n", entregas_realizadas);
    printf("Valor total recebido:             R$ %.2f\n", total_recebido);
    printf("Pedidos ainda na fila:            %d\n", tamanho_fila_entrega());
    printf("========================================\n");

    return 0;
}       