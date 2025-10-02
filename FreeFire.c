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
//-DESAFIO FREE-FIRE INTERMEDIARIO

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

//--criar um vetor de structs (lista sequencial) chamado mochilaSequencial
typedef struct
{
    Item mochila[MAX_CAPACIDADE]; //-- 10 itens permitidos
    int totalItens;               //--contador, informa quantos itens estao realmente na lista
} ListaMochilaSequencial;

//--criar uma lista encadeada chamada mochilaEncadeada
typedef struct No{
    Item dados;
    struct No* proximo;
} No;

typedef No *ListaMochilaEncadeada; //isso é um atalho, em vez de escrever No* sempre
//quisermos nos referir a nossa lista, podemos simplesmente usar ListaMochilaEncadeada,
//a lista em si é apenas um ponteiro para o primeiro nó (a "cabeca" da lista)

//--contadores globais de comparaçao (sequencial e binaria)
int comparacaoSequencial = 0;
int comparacaoBinaria = 0;

//----------------------------PROTOTIPOS DAS FUNCOES
//--menus e buffer
void menuVersoes();
void menuMochilaSequencial();
void menuMochilaEncadeada();
void limparBuffer();

//--funcoes de lista sequencial
void inicializarItemSequencial(ListaMochilaSequencial *ptrMochila);
void inserirItemSequencial(ListaMochilaSequencial *ptrMochila, Item novo);
void removerItemSequencial(ListaMochilaSequencial *ptrMochila);
void listarItensSequencial(ListaMochilaSequencial *ptrMochila);
void buscarItensSequencial(ListaMochilaSequencial *ptrMochila);
void buscarItensBinario(ListaMochilaSequencial *ptrMochila);
void ordenarItens(ListaMochilaSequencial *ptrMochila);

//--funcoes de lista encadeada
void inicializarItemEncadeada(ListaMochilaEncadeada *ptrMochila);
void inserirItemEncadeada(ListaMochilaEncadeada *ptrMochila, Item novo);
void removerItemEncadeada(ListaMochilaEncadeada *ptrMochila);
void listarItensEncadeada(ListaMochilaEncadeada ptrMochila);
void buscarItensEncadeada(ListaMochilaEncadeada *ptrMochila);

//--liberar memoria da lista encadeada
void liberarMochilaEncadeada(ListaMochilaEncadeada *ptrMochila); //funcao para limpar a memoria

int main()
{
    int opcao, versao;

    ListaMochilaSequencial mochila;
    ListaMochilaEncadeada lista;
    Item novo;
    //--inicializacao do inventario da mochila
    inicializarItemSequencial(&mochila);

    // laco
    do
    {
        menuVersoes();
        scanf("%d", &versao);
        limparBuffer();

        if(versao == 1){

            menuMochilaSequencial();
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao)
                {
                case 1:
                    inserirItemSequencial(&mochila, novo);
                    listarItensSequencial(&mochila);
                    break;
                case 2:
                    removerItemSequencial(&mochila);
                    listarItensSequencial(&mochila);
                    break;
                case 3:
                    listarItensSequencial(&mochila);
                    break;
                case 4:
                    buscarItensSequencial(&mochila);
                    break;
                case 5:
                    buscarItensEncadeada(&lista);
                    break;
                case 6:
                    ordenarItens(&mochila);
                    break;
                case 0:
                    printf("\nSaindo...\n");
                    break;

                default:
                    printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
                    getchar();
                    break;
                }

        } else if(versao == 2){

            menuMochilaEncadeada();
            scanf("%d", &opcao);
            limparBuffer();

            switch (opcao)
                {
                case 1:
                    inserirItemEncadeada(&lista, novo);
                    listarItensEncadeada(lista);
                    break;
                case 2:
                    removerItemEncadeada(&lista);
                    listarItensEncadeada(lista);
                    break;
                case 3:
                    listarItensEncadeada(lista);
                    break;
                case 4:
                    buscarItensEncadeada(&lista);
                    break;
                case 0:
                    printf("\nSaindo...\n");
                    break;

                default:
                    printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
                    getchar();
                    break;
                }
        } else{
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}

//--exibe o menu inicial da escolha de versoes
void menuVersoes(){
    printf("\n===============================================\n");
    printf("          MOCHILA DE SOBREVIVENCIA\n");
    printf("================================================\n");
    printf("Antes de acessar a sua Mochila, escolha a versao que deseja ver.\n");
    printf("1. Versao SEQUENCIAL.\n");
    printf("2. Versao ENCADEADA.\n");
    printf("Sua escolha: ");
}

//--exibe o menu da mochila de sobrevivencia
void menuMochilaSequencial(){
    printf("\n===============================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - VERSAO [SEQUENCIAL]\n");
    printf("================================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens na Mochila\n");
    printf("4. Buscar item (Busca Sequencial)\n");
    printf("5. Buscar item (Busca Binaria)\n");
    printf("6. Ordenar itens na Mochila.\n");
    printf("0. Sair\n");
    printf("-------------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void menuMochilaEncadeada(){
    printf("\n===============================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - VERSAO [ENCADEADA]\n");
    printf("================================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens na Mochila\n");
    printf("4. Buscar item (Busca Sequencial)\n");
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

//--------------------------------------------LISTA SEQUENCIAL
//--inicializa a lista sequencial(mochila)
void inicializarItemSequencial(ListaMochilaSequencial *ptrMochila)
{
    ptrMochila->totalItens = 0;
    for (int i = 0; i < MAX_CAPACIDADE; i++)
    {
        strcpy(ptrMochila->mochila[i].nome, "");
        strcpy(ptrMochila->mochila[i].tipo, "");
        ptrMochila->mochila[i].quantidade = 0;
    }
}

//--insere itens na lista da mochila
void inserirItemSequencial(ListaMochilaSequencial *ptrMochila, Item novo)
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

void removerItemSequencial(ListaMochilaSequencial *ptrMochila)
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
    //--atualiza o contador
    ptrMochila->totalItens--;
    printf("\n-------------------------------------------\n");
    printf("         Item removido com sucesso.\n");
    printf("-------------------------------------------\n\n");
}

void listarItensSequencial(ListaMochilaSequencial *ptrMochila)
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
            printf("     Itens na Mochila (Sequencial) [%d/10] \n", i +1);
            printf("-------------------------------------------\n");
            printf("Nome do Item: %s\n", ptrMochila->mochila[i].nome);
            printf("Tipo do Item: %s\n", ptrMochila->mochila[i].tipo);
            printf("Quantidade: %d\n\n", ptrMochila->mochila[i].quantidade);
        }
}

void buscarItensSequencial(ListaMochilaSequencial *ptrMochila)
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

    comparacaoSequencial = 0;
    for (int i = 0; i < ptrMochila->totalItens; i++)
    {
        comparacaoSequencial++;
        if (strcmp(ptrMochila->mochila[i].nome, nome) == 0)
        {
            printf("\n-------------------------------------------\n");
            printf("             Item encontrado!\n");
            printf("-------------------------------------------\n");
            printf("Nome do item: %s\n", ptrMochila->mochila[i].nome);
            printf("Tipo do item: %s\n", ptrMochila->mochila[i].tipo);
            printf("Quantidade: %d\n", ptrMochila->mochila[i].quantidade);
            printf("Comparacoes: %d\n", comparacaoSequencial);
            return;
        }
    }
    printf("-------------------------------------------\n");
    printf("    Item nao encontrado. Tente novamente.\n");
    printf("-------------------------------------------\n");
}

void buscarItensBinario(ListaMochilaSequencial *ptrMochila)
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

    int inicio = 0;
    int fim = ptrMochila->totalItens - 1;
    int meio;
    comparacaoBinaria = 0;

    while(inicio <= fim){
        //--calcula o indice do meio
        //--usar inicio + (fim - inicio) / 2 evita overflow para listas muito grandes
        meio = inicio + (fim - inicio) / 2;
        comparacaoBinaria++;

        int comparacao = strcmp(ptrMochila->mochila[meio].nome, nome);

        if(comparacao == 0){
            printf("\n-------------------------------------------\n");
            printf("             Item encontrado!\n");
            printf("-------------------------------------------\n");
            printf("Nome do item: %s\n", ptrMochila->mochila[meio].nome);
            printf("Tipo do item: %s\n", ptrMochila->mochila[meio].tipo);
            printf("Quantidade: %d\n", ptrMochila->mochila[meio].quantidade);
            printf("Comparacoes: %d\n", comparacaoSequencial);
            return;
        } else if(comparacao > 0){
            fim = meio - 1;
        } else{
            inicio = meio + 1;
        }
    }

    printf("-------------------------------------------\n");
    printf("    Item nao encontrado. Tente novamente.\n");
    printf("-------------------------------------------\n");
}

void ordenarItens(ListaMochilaSequencial *ptrMochila){
        comparacaoBinaria = 0;
    for (int i = 0; i < ptrMochila->totalItens - 1; i++) {
        for (int j = 0; j < ptrMochila->totalItens - i - 1; j++) {
            comparacaoBinaria++;
            if (strcmp(ptrMochila->mochila[j].nome, ptrMochila->mochila[j + 1].nome) > 0) {
                Item temp = ptrMochila->mochila[j];
                ptrMochila->mochila[j] = ptrMochila->mochila[j + 1];
                ptrMochila->mochila[j + 1] = temp;
            }
        }
    }
    printf("-------------------------------------------\n");
    printf("       Mochila ordenada com sucesso!\n");
    printf("-------------------------------------------\n");
    printf("Comparacoes: %d\n", comparacaoBinaria);
}

//--------------------------------------------LISTA ENCADEADA
void inicializarItemEncadeada(ListaMochilaEncadeada *ptrMochila){
    *ptrMochila = NULL;
}

void inserirItemEncadeada(ListaMochilaEncadeada *ptrMochila, Item novo){

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

    //--alocar memoria para o NOVO NÓ; nonoNo agora para essa memoria
    No *novoNo = (No*) malloc(sizeof(No));

    if(novoNo == NULL){
        printf("Falha ao alocar memoria.\n");
        return;
    }

    novoNo->dados = novo;
    novoNo->proximo = *ptrMochila;
    *ptrMochila = novoNo;

    printf("\n------------------------------------------\n");
    printf("       Item adicionado com sucesso!\n");
    printf("------------------------------------------\n\n");
}

void removerItemEncadeada(ListaMochilaEncadeada *ptrMochila){
    char nome[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    //usamos dois ponteiros, atual e anterior, para percorrer a lista. atual avança e anterior o segue
    //paramos quando atual aponta para o no a ser removido
    No *atual = *ptrMochila;
    No *anterior = NULL;

    while(atual != NULL && strcmp(atual->dados.nome, nome) != 0){
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL){
        printf("Erro: Item \"%s\" nao encontrado\n", nome);
        return;
    }

    /*
    se o no a ser removido for o primeiro (anterior == NULL), a cabeça da lista (*lista) passa a ser o segundo
    (atual). se estiver no meio/fim, o ponteiro proximo do no anterior "pula" o atual e aponta para
    atual->proximo*/
    if(anterior == NULL){
        *ptrMochila = atual->proximo;
    } else{
        anterior->proximo = atual->proximo;
    }

    /*
    liberacao de memoria
    primeiro, free(atual->dado): libera a memoria que foi usada para guardar o texto
    depois, free(atual): libera a memoria do proprio no. nao pode fazer ao contrario*/
    //ANTES de liberar o no, precismao liberar a string DENTRO dele
    free(atual->dados.nome);
    //AGORA podemos liberar o no
    free(atual);
    printf("Item %s removido com sucesso\n", nome);
}

void listarItensEncadeada(ListaMochilaEncadeada ptrMochila){
    No *temp = ptrMochila;
    if(temp == NULL){
        printf("\n-------------------------------------------\n");
        printf("         Sua mochila esta vazia.\n");
        printf("-------------------------------------------\n");
        return;
    }
    
    int i = 0;
    while (temp != NULL){
        printf("\n-------------------------------------------\n");
        printf("         Itens na Mochila (Encadeada) [%d/10] \n", i +1);
        printf("-------------------------------------------\n");
        printf("Nome do Item: %s\n", temp->dados.nome);
        printf("Tipo do Item: %s\n", temp->dados.tipo);
        printf("Quantidade: %d\n\n", temp->dados.quantidade);

        temp = temp->proximo;
    }

}
void buscarItensEncadeada(ListaMochilaEncadeada *ptrMochila){

    No *atual = *ptrMochila;

    char nome[30];
    printf("Digite o nome do item para buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    comparacaoSequencial = 0;

    while(atual != NULL){
        comparacaoSequencial++;
        if(strcmp(atual->dados.nome, nome) == 0){
            printf("\n-------------------------------------------\n");
            printf("             Item encontrado!\n");
            printf("-------------------------------------------\n");
            printf("Nome do item: %s\n", atual->dados.nome);
            printf("Tipo do item: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparacoes: %d\n", comparacaoSequencial);
            return;
        }
        atual = atual->proximo;
    }

    printf("-------------------------------------------\n");
    printf("    Item nao encontrado. Tente novamente.\n");
    printf("-------------------------------------------\n");
}

//funcao para liberar toda a memoria da lista encadeada no final
void liberarMochilaEncadeada(ListaMochilaEncadeada *ptrMochila){
    No *atual = *ptrMochila;
    No *proximo;
    while(atual != NULL){
        proximo = atual->proximo;
        free(atual->dados.nome);//libera a string
        free(atual);//libera o no
    }
}