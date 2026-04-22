#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar() {
    system("cls");
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void menu() {
    limpar();
    printf("========= CADASTRO DE PRODUTOS =========\n");
    printf("1 - Cadastrar produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Buscar produto\n");
    printf("4 - Atualizar produto\n");
    printf("5 - Deletar produto\n");
    printf("0 - Sair\n");
    printf("========================================\n");
    printf("Opcao: ");
}

// 1. CADASTRAR (CRIAR arquivo .txt)
void cadastrar() {
    limpar();
    printf("======== CADASTRAR PRODUTO ========\n\n");
    
    int codigo, quantidade;
    char nome[50];
    float preco;
    
    printf("Codigo: ");
    scanf("%d", &codigo);
    getchar();
    
    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    printf("Preco: ");
    scanf("%f", &preco);
    
    printf("Quantidade: ");
    scanf("%d", &quantidade);
    getchar();
    
    FILE *arq = fopen("produtos.txt", "a");
    if (arq == NULL) {
        printf("Erro ao abrir arquivo!\n");
        pausar();
        return;
    }
    
    fprintf(arq, "%d;%s;%.2f;%d\n", codigo, nome, preco, quantidade);
    fclose(arq);
    
    printf("\nProduto cadastrado com sucesso!\n");
    pausar();
}

// 2. LISTAR (LER arquivo .txt)
void listar() {
    limpar();
    printf("======== LISTA DE PRODUTOS ========\n\n");
    
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Nenhum produto cadastrado.\n");
        pausar();
        return;
    }
    
    int codigo, quantidade;
    char nome[50];
    float preco;
    int achou = 0;
    
    printf("CODIGO  NOME                          PRECO      QTD\n");
    printf("--------------------------------------------------------\n");
    
    while (fscanf(arq, "%d;%[^;];%f;%d\n", &codigo, nome, &preco, &quantidade) == 4) {
        printf("%-7d %-30s R$%-8.2f %d\n", codigo, nome, preco, quantidade);
        achou = 1;
    }
    
    if (!achou) {
        printf("Nenhum produto cadastrado.\n");
    }
    
    fclose(arq);
    pausar();
}

// 3. BUSCAR (LER especifico)
void buscar() {
    limpar();
    printf("======== BUSCAR PRODUTO ========\n\n");
    
    int codBusca;
    printf("Digite o codigo: ");
    scanf("%d", &codBusca);
    getchar();
    
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        pausar();
        return;
    }
    
    int codigo, quantidade;
    char nome[50];
    float preco;
    int achou = 0;
    
    while (fscanf(arq, "%d;%[^;];%f;%d\n", &codigo, nome, &preco, &quantidade) == 4) {
        if (codigo == codBusca) {
            printf("\nProduto encontrado:\n");
            printf("Codigo: %d\n", codigo);
            printf("Nome: %s\n", nome);
            printf("Preco: R$ %.2f\n", preco);
            printf("Quantidade: %d\n", quantidade);
            achou = 1;
            break;
        }
    }
    
    if (!achou) {
        printf("\nProduto nao encontrado!\n");
    }
    
    fclose(arq);
    pausar();
}

// 4. ATUALIZAR
void atualizar() {
    limpar();
    printf("======== ATUALIZAR PRODUTO ========\n\n");
    
    int codBusca;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codBusca);
    getchar();
    
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        pausar();
        return;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    int codigo, quantidade;
    char nome[50];
    float preco;
    int achou = 0;
    
    while (fscanf(arq, "%d;%[^;];%f;%d\n", &codigo, nome, &preco, &quantidade) == 4) {
        if (codigo == codBusca) {
            achou = 1;
            printf("\nProduto atual: %s\n", nome);
            printf("Novo nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            
            printf("Novo preco: ");
            scanf("%f", &preco);
            
            printf("Nova quantidade: ");
            scanf("%d", &quantidade);
            getchar();
        }
        fprintf(temp, "%d;%s;%.2f;%d\n", codigo, nome, preco, quantidade);
    }
    
    fclose(arq);
    fclose(temp);
    
    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");
    
    if (achou) {
        printf("\nProduto atualizado!\n");
    } else {
        printf("\nProduto nao encontrado!\n");
    }
    
    pausar();
}

// 5. DELETAR
void deletar() {
    limpar();
    printf("======== DELETAR PRODUTO ========\n\n");
    
    int codBusca;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codBusca);
    getchar();
    
    FILE *arq = fopen("produtos.txt", "r");
    if (arq == NULL) {
        printf("Arquivo nao encontrado!\n");
        pausar();
        return;
    }
    
    FILE *temp = fopen("temp.txt", "w");
    int codigo, quantidade;
    char nome[50];
    float preco;
    int achou = 0;
    
    while (fscanf(arq, "%d;%[^;];%f;%d\n", &codigo, nome, &preco, &quantidade) == 4) {
        if (codigo == codBusca) {
            achou = 1;
            printf("\nDeletando: %s\n", nome);
        } else {
            fprintf(temp, "%d;%s;%.2f;%d\n", codigo, nome, preco, quantidade);
        }
    }
    
    fclose(arq);
    fclose(temp);
    
    remove("produtos.txt");
    rename("temp.txt", "produtos.txt");
    
    if (achou) {
        printf("\nProduto deletado!\n");
    } else {
        printf("\nProduto nao encontrado!\n");
    }
    
    pausar();
}

int main() {
    int opcao;
    
    do {
        menu();
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: buscar(); break;
            case 4: atualizar(); break;
            case 5: deletar(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpcao invalida!\n"); pausar();
        }
        
    } while (opcao != 0);
    
    return 0;
}
