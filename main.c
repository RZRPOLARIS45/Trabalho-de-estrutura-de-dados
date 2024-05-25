#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma fruta
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

// Estrutura para representar um nó da lista de frutas
typedef struct Node {
    Fruta *fruta;
    struct Node *prox;
} Node;

// Função para cadastrar uma fruta
void cadastrarFruta(Node **lista) {
    Fruta *novaFruta = (Fruta *)malloc(sizeof(Fruta));
    if (novaFruta == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    printf("Digite o código da fruta: ");
    scanf("%d", &novaFruta->codigo);

    // Verifica se o código já existe na lista
    Node *atual = *lista;
    while (atual != NULL) {
        if (atual->fruta->codigo == novaFruta->codigo) {
            printf("Código já existente. Tente novamente.\n");
            free(novaFruta);
            return;
        }
        atual = atual->prox;
    }

    printf("Digite o nome da fruta: ");
    scanf("%s", novaFruta->nome);

    printf("Digite a quantidade da fruta: ");
    scanf("%d", &novaFruta->quantidade);

    printf("Digite o preço da fruta: ");
    scanf("%f", &novaFruta->preco);

    Node *novoNo = (Node *)malloc(sizeof(Node));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória.\n");
        free(novaFruta);
        return;
    }

    novoNo->fruta = novaFruta;
    novoNo->prox = *lista;
    *lista = novoNo;

    printf("Fruta cadastrada com sucesso.\n");
}

// Função para listar todas as frutas
void listarFrutas(Node *lista) {
    printf("Lista de frutas:\n");
    while (lista != NULL) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", lista->fruta->codigo, lista->fruta->nome, lista->fruta->quantidade, lista->fruta->preco);
        lista = lista->prox;
    }
}

// Função para buscar uma fruta pelo código
void buscarFruta(Node *lista, int codigo) {
    while (lista != NULL) {
        if (lista->fruta->codigo == codigo) {
            printf("Fruta encontrada:\n");
            printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", lista->fruta->codigo, lista->fruta->nome, lista->fruta->quantidade, lista->fruta->preco);
            return;
        }
        lista = lista->prox;
    }
    printf("Fruta não encontrada.\n");
}

// Função para alterar uma fruta
void alterarFruta(Node *lista, int codigo) {
    while (lista != NULL) {
        if (lista->fruta->codigo == codigo) {
            printf("Digite o novo nome da fruta: ");
            scanf("%s", lista->fruta->nome);

            printf("Digite a nova quantidade da fruta: ");
            scanf("%d", &lista->fruta->quantidade);

            printf("Digite o novo preço da fruta: ");
            scanf("%f", &lista->fruta->preco);

            printf("Fruta alterada com sucesso.\n");
            return;
        }
        lista = lista->prox;
    }
    printf("Fruta não encontrada.\n");
}

// Função para excluir uma fruta pelo código
void excluirFruta(Node **lista, int codigo) {
    Node *atual = *lista;
    Node *anterior = NULL;

    while (atual != NULL) {
        if (atual->fruta->codigo == codigo) {
            if (anterior == NULL) {
                *lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual->fruta);
            free(atual);
            printf("Fruta excluída com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Fruta não encontrada.\n");
}

// Função para vender uma fruta
void venderFruta(Node *lista, int codigo, int quantidade) {
    while (lista != NULL) {
        if (lista->fruta->codigo == codigo) {
            if (quantidade > lista->fruta->quantidade) {
                printf("Quantidade solicitada maior que o estoque disponível.\n");
                return;
            }
            lista->fruta->quantidade -= quantidade;

            // Registrar a venda no arquivo vendas.txt
            FILE *arquivo = fopen("vendas.txt", "a");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo de vendas.\n");
                return;
            }
            fprintf(arquivo, "Código: %d, Nome: %s, Quantidade vendida: %d, Preço unitário: %.2f, Total: %.2f\n", lista->fruta->codigo, lista->fruta->nome, quantidade, lista->fruta->preco, quantidade * lista->fruta->preco);
            fclose(arquivo);

            printf("Venda realizada com sucesso.\n");
            return;
        }
        lista = lista->prox;
    }
    printf("Fruta não encontrada.\n");
}

// Função principal
int main() {
    Node *lista = NULL;
    int opcao, codigo, quantidade;

    do {
        printf("\n");
        printf("1. Cadastrar fruta\n");
        printf("2. Listar frutas\n");
        printf("3. Buscar fruta\n");
        printf("4. Alterar fruta\n");
        printf("5. Excluir fruta\n");
        printf("6. Vender fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFruta(&lista);
                break;
            case 2:
                listarFrutas(lista);
                break;
            case 3:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                buscarFruta(lista, codigo);
                break;
            case 4:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                alterarFruta(lista, codigo);
                break;
            case 5:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                excluirFruta(&lista, codigo);
                break;
            case 6:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                printf("Digite a quantidade a ser vendida: ");
                scanf("%d", &quantidade);
                venderFruta(lista, codigo, quantidade);
                break;
            case 7:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 7);

    // Liberar memória alocada para as frutas
    Node *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux->fruta);
        free(aux);
    }

    return 0;
}
