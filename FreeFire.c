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
//-DESAFIO FREE-FIRE AVANÇADO MESTRE
//--TORRE DE FUGA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//--VARIAVEL GLOBAL
#define MAX_COMPONENTES 20

//--ESTRUTURA
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

//--PROTOTIPOS DE FUNCOES
void menuMontagemTorre();
void menuOrdenacao();
void limparBuffer();
void adicionarComponentes(Componente partes[], int *n);
void removerComponentes(Componente partes[], int *n);
void listarComponentes(Componente partes[], int n);
//--BUSCA BINARIA (por nome)
int buscaBinariaPorNome(Componente partes[], int n, char chave[], int *comparacaoBinaria);

//---ORDENAÇAO
int bubbleSortNome(Componente partes[], int n); //--ordenar por nome
int insertionSortTipo(Componente partes[], int n); //--ordenar por tipo
int selectionSortPrioridade(Componente partes[], int n); //--ordenar por prioridade
//--NOTA: a opçao de busca por componente é feita por meio da busca binaria
//por nome, assim sera feita pelo metodo bubbleSort; os outros metodos sao
//mais para exemplo de uso



int main() {
    Componente componentes[MAX_COMPONENTES]; //--vetor de struct
    int quantidade = 0; //--guarda quantos componentes sao salvos
    int opcao, escolha; //--menus
    char chave[30];
    int comparacoes = 0;
    clock_t inicio, fim;
    double tempo_execucao;

    do {
        menuMontagemTorre();
        scanf("%d", &escolha);
        limparBuffer();

        switch (escolha) {
            case 1:
                adicionarComponentes(componentes, &quantidade);
                break;
            case 2:
                removerComponentes(componentes, &quantidade);
                break;
            case 3:
                listarComponentes(componentes, quantidade);
                break;
            case 4:
                buscaBinariaPorNome(componentes, quantidade, chave, &comparacoes);
                break;
            case 5:
                menuOrdenacao();
                scanf("%d", &opcao);
                limparBuffer();

                switch(opcao){
                    case 1:
                        inicio = clock(); //--para as comparacoes
                        comparacoes = bubbleSortNome(componentes, quantidade);
                        fim = clock();
                        tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("\nComponentes ordenados por NOME (Bubble Sort):\n");
                        listarComponentes(componentes, quantidade);
                        printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo_execucao);
                    break;
                    case 2:
                        inicio = clock();
                        comparacoes = insertionSortTipo(componentes, quantidade);
                        fim = clock();
                        tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("\nComponentes ordenados por TIPO (Insertion Sort):\n");
                        listarComponentes(componentes, quantidade);
                        printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo_execucao);
                    break;
                    case 3:
                        inicio = clock();
                        comparacoes = selectionSortPrioridade(componentes, quantidade);
                        fim = clock();
                        tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
                        printf("\nComponentes ordenados por PRIORIDADE (Selection Sort):\n");
                        listarComponentes(componentes, quantidade);
                        printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo_execucao);
                    break;
                    case 0:
                        printf("\nSaindo...\n");
                        break;

                    default:
                        printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
                        getchar();
                        break;
                }
            case 6:
                printf("============================================\n");
                printf("######## TORRE DE RESGATE ATIVADA! ########\n");
                printf("============================================\n");
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpcao invalida. Pressione Enter para tentar novamente.");
                getchar();
                break;

        } 
    } while (escolha != 0);
return 0; //--termina
}

//--menu principal
void menuMontagemTorre() {
    printf("============================================\n");
    printf("   SISTEMA DE MONTAGEM DA TORRE DE RESGATE\n");
    printf("============================================\n");
    printf("1. Adicionar Componente\n");
    printf("2. Descartar Componente\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Busca Binária de Componente (por Nome)\n");
    printf("5. Organizar Mochila (Ordenar Componentes)\n");
    printf("6. Ativar Torre\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

//--menu ordenaçao
void menuOrdenacao(){
    printf("--------------------------------------------\n");
    printf("         Estrategia de Organizaçao\n");
    printf("--------------------------------------------\n");
    printf("Como deseja ordenar os componentes?\n");
    printf("1. Por Nome (Ordem Alfabetica)\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade\n");
    printf("0. Voltar \n");
    printf("Escolha o metodo de ordenaçao: ");
}

//---limpar buffer de entrada para evitar problema de leitura consecutiva de scanf e getchar
void limparBuffer(){
    int buffer;
    while ((buffer = getchar()) != '\n' && buffer != EOF);
}

//--adicionar componentes
void adicionarComponentes(Componente partes[], int *n) {
    //--verifica se a capacidade da mochila foi excedida
    if (*n >= MAX_COMPONENTES){
        printf("\n------------------------------------------------------------\n");
        printf("Limite maximo atingido.\n");
        printf("Voce nao pode cadastrar mais componentes.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }

    //--cadastro de itens
    printf("\n-------------------------------------------\n");
    printf("            Adicionar Componente \n");
    printf("-------------------------------------------\n\n");

    printf("Nome: ");
    fgets(partes[*n].nome, 30, stdin);
    partes[*n].nome[strcspn(partes[*n].nome, "\n")] = '\0';

    printf("Tipo (Estrutura, Eletronico, Energia): ");
    fgets(partes[*n].tipo, 20, stdin);
    partes[*n].tipo[strcspn(partes[*n].tipo, "\n")] = '\0';

    printf("Prioridade: ");
    scanf("%d", &partes[*n].prioridade);
    limparBuffer();

    (*n)++;
    printf("--------------------------------------------\n");
    printf("     Componente cadastrado com sucesso!\n");
    printf("--------------------------------------------\n");

    printf("Pressione Enter para Continuar...\n");
    getchar();
}

//--descartar componentes
void removerComponentes(Componente partes[], int *n){
    //--descarte de itens
    printf("\n-------------------------------------------\n");
    printf("            Descartar Componente \n");
    printf("-------------------------------------------\n\n");

    int i, pos = -1;
    if (*n == 0){
        printf("\n------------------------------------------------------------\n");
        printf("         Voce nao tem componentes para descartar.\n");
        printf("------------------------------------------------------------\n\n");
        return;
    }

    char descarte[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(descarte, sizeof(descarte), stdin);
    descarte[strcspn(descarte, "\n")] = '\0';

    for (i = 0; i < *n; i++){
        if (strcmp(partes[i].nome, descarte) == 0){
            pos = i;
            break;
        }
    }
    //-- se o loop terminar e o pos continuar -1, o item nao foi encontrado
    if (pos == -1){
        printf("\n-------------------------------------------\n");
        printf("   Item não encontrado. Tente novamente.\n");
        printf("-------------------------------------------\n\n");
        return;
    }

    for (i = pos; i < *n - 1; i++){
        partes[i] = partes[i + 1];
    }
    //--atualiza o contador
    (*n)--;
    printf("\n-------------------------------------------\n");
    printf("         Item removido com sucesso.\n");
    printf("-------------------------------------------\n\n");

    printf("Pressione Enter para Continuar...\n");
    getchar();
}

//--exibiçao de componentes
void listarComponentes(Componente partes[], int n) {
    if (n == 0){
        printf("\n-------------------------------------------\n");
        printf("         Voce nao tem componentes.\n");
        printf("-------------------------------------------\n");
        return;
    }

    for (int i = 0; i < n; i++){
        printf("\n-------------------------------------------\n");
        printf("    Componentes no seu Inventario [%d/20] \n", i +1);
        printf("-------------------------------------------\n");
        printf("Nome: %s\n", partes[i].nome);
        printf("Tipo: %s\n", partes[i].tipo);
        printf("Prioridade: %d\n\n", partes[i].prioridade);
    }

    printf("Pressione Enter para Continuar...\n");
    getchar();
}

//--busca por nome com bubblesort
int bubbleSortNome(Componente partes[], int n) {
    int i, j, trocou;
    Componente temp;
    //--laço externo controla o numero de passagens
    //--apos cada passagem 'i', o i-esimo maior elemento estara no lugar correto
    for (i = 0; i < n - 1; i++) {
        //--laço interno percorre a lista, comparando elementos adjacentes
        for (j = 0; j < n - i - 1; j++) {
            trocou++;
            if (strcmp(partes[j].nome, partes[j + 1].nome) > 0) {
                temp = partes[j];
                partes[j] = partes[j + 1];
                partes[j + 1] = temp;
            }
        }
    }
    return trocou;
}

//--busca por tipo com insertionsort
int insertionSortTipo(Componente partes[], int n) {
    int i, j, comp = 0;
    Componente chave;
    //--começa do segundo elemento
    for (i = 1; i < n; i++) {
        chave = partes[i];
        j = i - 1; //--aponta para o ultimo elemento da parte ordenada
        while (j >= 0 && strcmp(partes[j].tipo, chave.tipo) > 0) {
            partes[j + 1] = partes[j];
            j--;
            comp++;
        }
        if (j >= 0) comp++;
        //--insere a 'chave' na posiçao correta
        partes[j + 1] = chave;
    }
    return comp;
}

//--busca por prioridade com selectionsort
int selectionSortPrioridade(Componente partes[], int n) {
    int i, j, indice_min, comp = 0;
    Componente temp;

    //--laço externo percorre a lista para definir a fronteira entre parte
    //ordenada e nao ordenada
    for (i = 0; i < n - 1; i++) {
        //--assume que o primeiro elemento da parte nao ordenada é o menor
        indice_min = i;

        //--laço interno percorre a parte nao ordenada para encontrar o menor elemento
        for (j = i + 1; j < n; j++) {
            comp++;
            //--se encontrar um elemento menor que o minimo atual, atualiza o indice do minimo
            if (partes[j].prioridade < partes[indice_min].prioridade) {
                indice_min = j;
            }
        }
        //--se o menor elemento nao for o primeiro da parte nao ordenada, troca eles de lugar
        if (indice_min != i) {
            temp = partes[i];
            partes[i] = partes[indice_min];
            partes[indice_min] = temp;
        }
    }
    return comp;
}

//--busca binaria por nome
int buscaBinariaPorNome(Componente partes[], int n, char chave[], int *comparacaoBinaria) {

     if (n == 0){
        printf("-------------------------------------------\n");
        printf("          Voce nao tem componentes.\n");
        printf("-------------------------------------------\n\n");
        return 1;
    }

    printf("Digite o nome do componente para buscar: ");
    fgets(chave, 30, stdin);
    chave[strcspn(chave, "\n")] = '\0';

    int inicio = 0;
    int fim = n - 1;
    int meio;
    comparacaoBinaria = 0;

    while(inicio <= fim){
        //--calcula o indice do meio
        //--usar inicio + (fim - inicio) / 2 evita overflow para listas muito grandes
        meio = inicio + (fim - inicio) / 2;
        comparacaoBinaria++;

        int comparacao = strcmp(partes[meio].nome, chave);

        if(comparacao == 0){
            printf("\n-------------------------------------------\n");
            printf("             Item encontrado!\n");
            printf("-------------------------------------------\n");
            printf("Nome %s\n", partes[meio].nome);
            printf("Tipo: %s\n", partes[meio].tipo);
            printf("Prioridade %d\n", partes[meio].prioridade);
            printf("Comparacoes: %d\n", comparacaoBinaria);
            return 0;
        } else if(comparacao > 0){
            fim = meio - 1;
        } else{
            inicio = meio + 1;
        }
    }

    printf("-------------------------------------------\n");
    printf(" Componente nao encontrado. Tente novamente.\n");
    printf("-------------------------------------------\n");
}