/*
 * Nome: Yuri Jose dos Santos Serrano
 * TIA:  4141434-9
 *
 * Descricao do Programa
 *
 * Este programa simula uma maquina de estado finito,que consegue
 * reconhecer um automato finito especifico.
 * Configurando-se os estados e simbolos consegue-se resolver qualquer
 * automato.
 * Esta versao utiliza-se da leitura de arquivos para obter os dados
 * referentes ao alfabeto,estados dentre outros,sendo que permite
 * uma maior facilidade quando se trata de automatos com estados
 * ou alfabetos grandes,pois assim nao perde-se tempo cadastrando-os
 * pelo cmd, mas sim lendo pelo arquivo
 * Deixei a opcao de poder ler varios arquivos.
 * A include locale permite a acentuacao das palavras na linguagem C.
 *
 *
 *
 * EXEMPLO DO MODO COMO O TXT DEVE SER MONTADO
 *
 * ################################################################################
  Lê o arquivo txt no seguinte formato.
  Exemplo: L={w|w possui aa ou bb como subpalavra}
  ab --alfabeto
  0 --estado_inicial
  4 --nº de estados
  1 --nº de estados finais
  3 --estado final
  0 a 1
  0 b 2
  1 a 3
  1 b 2
  2 a 1
  2 b 3
  3 a 3
  3 b 3
################################################################################
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void leDoArquivo(int*** mat, int** final, int* nestados, int* estado_inicial, int* qfinais)
{
    int** m = NULL, * finais = NULL;
    FILE* arq = NULL;
    int i, j, k, x, fim;
    char nomearq[20], y, alfabeto[26];
    printf("\nDigite o nome do arquivo: (Ex:. nome_do_arquivo.txt) ->");
    gets(nomearq);
    arq = fopen(nomearq, "r");
    if(arq == NULL) {
        printf("\n!!!ERRO!!! na abertura do arquivo\n");
        printf("Arquivo nao existe ou falta a extensao .txt\n");
        system("Pause");
        exit(1);
    }
    fscanf(arq, "%s", alfabeto);
    fscanf(arq, "%i", estado_inicial);
    fscanf(arq, "%i", nestados);
    fscanf(arq, "%i", qfinais);
    printf("Alfabeto: %s\n", alfabeto);
    printf("Estado inicial: %i\n", *estado_inicial);
    printf("Numero de estados: %i\n", *nestados);
    printf("Numero de estados finais: %i\n", *qfinais);
    /*aloca a funcao programa, no qual eh uma matriz*/
    m = (int**)malloc((*nestados) * sizeof(int*));
    if(m == NULL) {
        printf("\n!!!ERRO!!! Falha na alocacao!!!\n");
        system("Pause");
        exit(1);
    }
    for(i = 0; i < (*nestados); i++) {
        m[i] = (int*)malloc(strlen(alfabeto) * sizeof(int));
        if(m[i] == NULL)
            exit(1);
    }
    /*aloca o conjunto de estados finais, no qual eh um vetor*/
    finais = (int*)malloc((*qfinais) * sizeof(int));
    if(finais == NULL) {
        printf("\n!!!ERRO Falha ao alocar o vetor de estados finais.\n");
        system("Pause");
        exit(1);
    }
    for(k = 0; k < (*qfinais); k++) {
        fscanf(arq, "%i", &fim);
        finais[fim] = fim;
        printf("finais[%i]=%i\t", fim, finais[fim]);
    }
    printf("\nTabela de Transicao do Automato\n");
    for(i = 0; i < (*nestados); i++) {
        for(j = 0; j < strlen(alfabeto); j++) {
            fscanf(arq, "%i %c %i", &x, &y, &m[i][j]);
            printf("%i\t%c\t%i\n", x, y, m[i][j]);
        }
    }
    (*mat) = m;
    (*final) = finais;
    fclose(arq); /*fecha o arquivo*/
}

void automato(int*** mat, int** final, int* estado_inicial, char simbolo[100])
{
    int i, estado, ** m = NULL, * finais = NULL;
    m = *mat;
    finais = *final;
    estado = (*estado_inicial);
    i = 0;
    while(i < strlen(simbolo)) {
        estado = m[estado][simbolo[i] - 'a'];
        printf("\nLeu simbolo %c foi para o estado %i\n", simbolo[i], estado);
        i++;
    }
    if(finais[estado] == estado)
        printf("\nA Palavra %s foi Aceita. O estado de parada foi: %i\n", simbolo, estado);
    else
        printf("\nA Palavra %s foi Rejeitada. O estado de parada foi: %i\n", simbolo, estado);
}

int main()
{
    int** m = NULL, * finais = NULL;
    int i, j, k, estado_inicial, nestados, qfinais;
    char simbolo[100], escolha;
    system("Versao 3 ---------- Coder Yuri Serrano ----------");
    system("color 4a");
    do {
        fflush(stdin);
        system("cls");
        printf("\n\tVersao 3 ---------- Coder Yuri Serrano ----------");
        printf("\n\tAutomato Finito Deterministico - AFD\n");
        leDoArquivo(&m, &finais, &nestados, &estado_inicial, &qfinais);
        fflush(stdin);
        printf("\nDigite uma palavra: ");
        fflush(stdin);
        scanf("%s", simbolo);
        automato(&m, &finais, &estado_inicial, simbolo);
        /*Laco para liberar a matriz*/
        for(i = (nestados - 1); i >= 0; i--) {
            free(m[i]);
        }
        free(m);
        free(finais);
        printf("\nDesejar entrar com outro arquivo - (S/N)?");
        scanf("%s", &escolha);
    } while(escolha == 'S' || escolha == 's');
    system("Pause");
    return 0;
}
