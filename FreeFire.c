/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>*/

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

//int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    //return 0;
//}

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.

//----------------------------------------------------------------------------------------------------
//-DESAFIO FREE-FIRE NOVATO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACIDADE 10 //--tamanha maximo de itens permitido na mochila

//--criar uma estrutura chamada Item, contendo nome, tipo e quantidade
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

//--criar um vetor de structs (lista sequencial) chamado mochila
typedef struct
{
    Item mochila[MAX_CAPACIDADE]; //-- 10 itens permitidos
    int totalItens;               //--contador, informa quantos itens estao realmente na lista
} ListaMochila;

//--prototipaçao de funçoes
void menuMochila();
void limparBuffer();
void inicializarItem(ListaMochila *ptrMochila);
void inserirItem(ListaMochila *ptrMochila, Item novo);
void removerItem(ListaMochila *ptrMochila);
void listarItens(ListaMochila *ptrMochila);
void buscarItens(ListaMochila *ptrMochila);

int main()
{
    int opcao;

    ListaMochila mochila;
    Item novo;
    //--inicializacao do inventario da mochila
    inicializarItem(&mochila);

    // laco
    do
    {
        menuMochila();
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao)
        {
        case 1:
            inserirItem(&mochila, novo);
            listarItens(&mochila);
            break;
        case 2:
            removerItem(&mochila);
            listarItens(&mochila);
            break;
        case 3:
            listarItens(&mochila);
            break;
        case 4:
            buscarItens(&mochila);
            break;
        case 0:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
            getchar();
            break;
        }

    } while (opcao != 0);

    return 0;
}

//--exibe o menu inicial da mochila de sobrevivencia
void menuMochila(){
    printf("\n==========================================\n");
    printf("           MOCHILA DE SOBREVIVENCIA       \n");
    printf("===========================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens na Mochila\n");
    printf("4. Buscar item\n");
    printf("0. Sair\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

//---limpar buffer de entrada para evitar problema de leitura consecutiva de scanf e getchar
void limparBuffer()
{
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF)
        ;
}

//--inicializa a lista sequencial(mochila)
void inicializarItem(ListaMochila *ptrMochila)
{
    ptrMochila->totalItens = 0; 
    for (int i = 0; i < MAX_CAPACIDADE; i++)
    {//--inicializa todos os valores em 0 ou nulo
        strcpy(ptrMochila->mochila[i].nome, "");
        strcpy(ptrMochila->mochila[i].tipo, "");
        ptrMochila->mochila[i].quantidade = 0;
    }
}

//--insere itens na lista da mochila
void inserirItem(ListaMochila *ptrMochila, Item novo)
{
    //--verifica se a capacidade da mochila foi excedida
    if (ptrMochila->totalItens >= MAX_CAPACIDADE)
    {
        printf("\n------------------------------------------------------------\n");
        printf("Sua mochila esta cheia. Remova algum item e tente novamente.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }
    //--cadastro de itens
    printf("\n-------------------------------------------\n");
    printf("              Adicionar Item \n");
    printf("-------------------------------------------\n\n");

    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o tipo do item (ex: arma, municao, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    limparBuffer();

    ptrMochila->mochila[ptrMochila->totalItens++] = novo;

    printf("\n------------------------------------------\n");
    printf("       Item adicionado com sucesso!\n");
    printf("------------------------------------------\n\n");
}

void removerItem(ListaMochila *ptrMochila)
{
    int i, pos = -1;
    if (ptrMochila->totalItens == 0)
    {
        printf("\n------------------------------------------------------------\n");
        printf("  Sua mochila esta vazia. Adicione itens e tente novamente.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    //--para comparar strings, usamos strcmp(string1, string2)
    //essa funcao retorna 0 se as strings forem identicas, se encontrar, guarda a posicao pos e para o loop
    for (i = 0; i < ptrMochila->totalItens; i++)
    {
        if (strcmp(ptrMochila->mochila[i].nome, nome) == 0)
        {
            pos = i;
            break;
        }
    }
    //-- se o loop terminar e o pos continuar -1, o item nao foi encontrado
    if (pos == -1)
    {
        printf("\n-------------------------------------------\n");
        printf("   Item não encontrado. Tente novamente.\n");
        printf("-------------------------------------------\n\n");
        return;
    }

    for (i = pos; i < ptrMochila->totalItens - 1; i++)
    {
        ptrMochila->mochila[i] = ptrMochila->mochila[i + 1];
    }
    //--atualiza o contador para mostrar que a lsita tem um item a menos
    ptrMochila->totalItens--;
    printf("\n-------------------------------------------\n");
    printf("         Item removido com sucesso.\n");
    printf("-------------------------------------------\n\n");
}

void listarItens(ListaMochila *ptrMochila)
{
    if (ptrMochila->totalItens == 0)
    {
        printf("\n-------------------------------------------\n");
        printf("         Sua mochila esta vazia.\n");
        printf("-------------------------------------------\n");
        return;
    }
        for (int i = 0; i < ptrMochila->totalItens; i++)
        {
            printf("\n-------------------------------------------\n");
            printf("             Itens na Mochila [%d/10] \n", i +1);
            printf("-------------------------------------------\n");
            printf("Nome do Item: %s\n", ptrMochila->mochila[i].nome);
            printf("Tipo do Item: %s\n", ptrMochila->mochila[i].tipo);
            printf("Quantidade: %d\n\n", ptrMochila->mochila[i].quantidade);
        }
}

void buscarItens(ListaMochila *ptrMochila)
{
    if (ptrMochila->totalItens == 0)
    {
        printf("-------------------------------------------\n");
        printf("               Lista vazia.\n");
        printf("-------------------------------------------\n\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < ptrMochila->totalItens; i++)
    {
        if (strcmp(ptrMochila->mochila[i].nome, nome) == 0)
        {
            printf("\n-------------------------------------------\n");
            printf("             Item encontrado!\n");
            printf("-------------------------------------------\n");
            printf("Nome do item: %s\n", ptrMochila->mochila[i].nome);
            printf("Tipo do item: %s\n", ptrMochila->mochila[i].tipo);
            printf("Quantidade: %d\n", ptrMochila->mochila[i].quantidade);
            return;
        }
    }
    printf("-------------------------------------------\n");
    printf("    Item nao encontrado. Tente novamente.\n");
    printf("-------------------------------------------\n");
}
