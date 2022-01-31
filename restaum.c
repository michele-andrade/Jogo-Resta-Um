#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  
#define ANSI_BOLD             "\x1b[1m"  
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

typedef struct {
    int linhas;//dimensão do tabuleiro.
    int colunas;
    int pecas;//quantidade de peças existentes no tabuleiro.
    char **tabuleiro;
} Jogo;

//Protótipos das funções utilizadas

void salva_tabuleiro(Jogo jogo, char nome_arquivo[50]);
Jogo le_tabuleiro(char nomearquivo[50]);
void imprime_jogo(Jogo jogo);
void imprime_menu();
int le_comando(Jogo *jogo);
void movimento_baixo (Jogo *jogo, char posicaoLin, char posicaoCol);
void movimento_cima (Jogo *jogo, char posicaoLin, char posicaoCol);
void movimento_direita (Jogo *jogo, char posicaoLin, char posicaoCol);
void movimento_esquerda (Jogo *jogo, char posicaoLin, char posicaoCol);
void ajuda_movimento(Jogo *jogo, int n);
int perdeu_ganhou(Jogo jogo);
void liberaMemoria(Jogo jogo);

void salva_tabuleiro(Jogo jogo, char nome_arquivo[50]){

    FILE *saida = fopen(nome_arquivo, "w+");

    fprintf(saida, "%d %d\n", jogo.linhas, jogo.colunas);
    for (int i = 0; i < jogo.linhas; i++){
        for(int j = 0; j < jogo.colunas; j++){
            fprintf(saida, "%c ", jogo.tabuleiro[i][j]);
        }
        fprintf(saida, "\n");
    }
    printf("jogo salvo");
    fclose(saida);
}

Jogo le_tabuleiro(char nomearquivo[50]){
    
    FILE *entrada;
    entrada = fopen(nomearquivo, "r");

    Jogo temp;
    temp.pecas = 0;

    //lendo as dimensões da matriz no arquivo.
    fscanf(entrada, "%d", &temp.linhas);
    fscanf(entrada, "%d\n", &temp.colunas);

    // lendo as peças do jogo.
    temp.tabuleiro = malloc(temp.linhas * sizeof(char*));
    for (int i = 0; i < temp.linhas; i++){
        temp.tabuleiro[i] = malloc(temp.colunas * sizeof(char));
    }

    for(int i = 0; i < temp.linhas; i++){
        for(int j = 0; j < temp.colunas; j++){
            fscanf(entrada, "%c\n", &temp.tabuleiro[i][j]);
            if(temp.tabuleiro[i][j] == '+'){
                temp.pecas++;
            }
        }
    }
    fclose(entrada);
    return temp;

}

void imprime_jogo(Jogo jogo){
    printf("\n");
    printf(CYAN(BOLD("DIMENSÕES DO TABULEIRO: %d X %d\n\n")), jogo.linhas, jogo.colunas);
    printf(BOLD("TABULEIRO\n\n"));
    
    printf("    ");
    for (int i = 0; i < jogo.colunas; i++){
        char coluna = (char) i + 65;
        printf(BG_WHITE(BLACK(BOLD("%c   "))), coluna);
    }
    printf("\n");

    for(int i = 0; i < jogo.linhas; i++){
        char linha = (char) i + 65;
        printf(BG_WHITE(BLACK(BOLD("%c   "))), linha);
        for(int j = 0; j < jogo.colunas; j++){
            if(jogo.tabuleiro[i][j] == '+'){
                printf(GREEN("%c   "), jogo.tabuleiro[i][j]);
            }
            else if(jogo.tabuleiro[i][j] == '-'){
                printf(BLUE("%c   "), jogo.tabuleiro[i][j]);
            }
            else {
                printf(RED("%c   "), jogo.tabuleiro[i][j]);
            }
        }
        printf("\n");
        printf(BG_WHITE(BLACK(BOLD("    "))));
        printf("\n");
    }
}

void imprime_menu(){

    printf(BG_WHITE(BLACK(BOLD("COMANDO   RESULTADO")))"\n");
    printf(BOLD("------------------------------------------\n"));
    printf(BOLD(RED("c         ")));
    printf(GREEN("Movimentar o pino (+) para cima\n"));
    printf(BOLD(RED("b         ")));
    printf(GREEN("Movimentar o pino (+) para baixo\n"));
    printf(BOLD(RED("e         ")));
    printf(GREEN("Movimenta  o pino (+) para esquerda\n"));
    printf(BOLD(RED("d         ")));
    printf(GREEN("Movimenta o pino (+) para direita\n"));
    printf(BOLD(RED("ajuda     ")));
    printf(GREEN("Sugestão e execução de movimentos\n"));
    printf(BOLD(RED("salvar    ")));
    printf(GREEN("Salvar o seu jogo \n"));
    printf(BOLD(RED("sair      ")));
    printf(GREEN("Encerrar o programa\n"));
    printf("\n");

}

int le_comando(Jogo *jogo){
    char comando[50];
    char posicao_linha, posicao_coluna;
    int n_movimentos;
    char nome_arquivo[50];
    int loop = 0;
    
    do{
        printf(CYAN(BOLD("Digite o comando: ")));
        scanf("%s", comando);
        if(strcmp(comando, "b") == 0 || strcmp(comando, "c") == 0 || strcmp(comando, "d") == 0 || strcmp(comando, "e") == 0){
            printf(CYAN(BOLD("Digite as posições: ")));
            scanf("\n%c%c", &posicao_linha, &posicao_coluna);
            loop = 0;
            if(strcmp(comando, "b") == 0){
                movimento_baixo (jogo, posicao_linha, posicao_coluna);
            }
            else if (strcmp(comando, "c") == 0){
                movimento_cima(jogo, posicao_linha, posicao_coluna);
            }
            else if (strcmp(comando, "d") == 0){
                movimento_direita(jogo, posicao_linha, posicao_coluna);
            }
            else if(strcmp(comando, "e") == 0){
                movimento_esquerda(jogo, posicao_linha, posicao_coluna);
            }
        }
        else if(strcmp(comando, "ajuda") == 0){
            printf(CYAN(BOLD("Quantos movimentos deseja que faça: ")));
            scanf("%d", &n_movimentos);
            ajuda_movimento(jogo, n_movimentos);
            loop = 0;
        }
        else if(strcmp(comando, "salvar") == 0){
            printf(CYAN(BOLD("Qual o nome do novo arquivo: ")));
            scanf("%s", nome_arquivo);
            loop = 0;
            salva_tabuleiro(*jogo, nome_arquivo);
        }
        else if(strcmp(comando, "sair") == 0){
            printf(BOLD(RED("JOGO ENCERRADO!\n")));
            loop = 0;
            return 1;
            
        }
        else {
            printf(RED("Comando inválido!\n"));
            loop = 1;
        }
    } while(loop == 1);

    return 0;
}

void movimento_baixo (Jogo *jogo, char posicaoLin, char posicaoCol){
    posicaoLin = toupper(posicaoLin);
    posicaoCol = toupper(posicaoCol);
    int aux1 = (int) posicaoLin - 65;
    int aux2 = (int) posicaoCol - 65;

    if(aux1 + 2 > jogo->linhas){
        printf(RED("Movimento invalido\n"));
    }
    else if (jogo->tabuleiro[aux1][aux2] == '+'){
        if (jogo->tabuleiro[aux1 + 1][aux2] == '+' && jogo->tabuleiro[aux1 + 2][aux2] == '-'){
            jogo->tabuleiro[aux1 + 2][aux2] = '+';
            jogo->tabuleiro[aux1 + 1][aux2] = '-';
            jogo->tabuleiro[aux1][aux2] = '-';
            jogo->pecas -= 1;
        }
        else{
            printf(RED("Movimento invalido!\n"));
        }
    }
    else{
        printf(RED("Movimento invalido!\n"));
    }
}

void movimento_cima (Jogo *jogo, char posicaoLin, char posicaoCol){
    posicaoLin = toupper(posicaoLin);
    posicaoCol = toupper(posicaoCol);
    int aux1 = (int) posicaoLin - 65;
    int aux2 = (int) posicaoCol - 65;

    if(aux1 - 2 > jogo->linhas){
        printf(RED("Movimento invalido\n"));
    }
    else if (jogo->tabuleiro[aux1][aux2] == '+'){
        if (jogo->tabuleiro[aux1 - 1][aux2] == '+' && jogo->tabuleiro[aux1 - 2][aux2] == '-'){
            jogo->tabuleiro[aux1 - 2][aux2] = '+';
            jogo->tabuleiro[aux1 - 1][aux2] = '-';
            jogo->tabuleiro[aux1][aux2] = '-';
            jogo->pecas-= 1;
        }
        else{
            printf(RED("movimento invalido!\n"));
        }
    }
    else{
        printf(RED("movimento invalido!\n"));
    }
}
void movimento_esquerda (Jogo *jogo, char posicaoLin, char posicaoCol){
    posicaoLin = toupper(posicaoLin);
    posicaoCol = toupper(posicaoCol);
    int aux1 = (int) posicaoLin - 65;
    int aux2 = (int) posicaoCol - 65;

    if(aux2 - 2 > jogo->colunas){
        printf(RED("movimento invalido\n"));
    }
    else if (jogo->tabuleiro[aux1][aux2] == '+'){
        if (jogo->tabuleiro[aux1][aux2 - 1] == '+' && jogo->tabuleiro[aux1][aux2 - 2] == '-'){
            jogo->tabuleiro[aux1][aux2 - 2] = '+';
            jogo->tabuleiro[aux1][aux2 - 1] = '-';
            jogo->tabuleiro[aux1][aux2] = '-';
            jogo->pecas-= 1;
        }
        else{
            printf(RED("movimento invalido!\n"));
        }
    }
    else{
        printf(RED("movimento invalido!\n"));
    }
}
void movimento_direita (Jogo *jogo, char posicaoLin, char posicaoCol){
    posicaoLin = toupper(posicaoLin);
    posicaoCol = toupper(posicaoCol);
    int aux1 = (int) posicaoLin - 65;
    int aux2 = (int) posicaoCol - 65;

    if(aux2 + 2 > jogo->colunas){
        printf(RED("Movimento invalido\n"));
    }
    else if (jogo->tabuleiro[aux1][aux2] == '+'){
        if (jogo->tabuleiro[aux1][aux2 + 1] == '+' && jogo->tabuleiro[aux1][aux2 + 2] == '-'){
            jogo->tabuleiro[aux1][aux2 + 2] = '+';
            jogo->tabuleiro[aux1][aux2 + 1] = '-';
            jogo->tabuleiro[aux1][aux2] = '-';
            jogo->pecas-= 1;
        }
        else{
            printf(RED("movimento invalido!\n"));
        }
    }
    else{
        printf(RED("movimento invalido!\n"));
    }
}

void ajuda_movimento(Jogo *jogo, int n){
    int cont = 0;
    int jogadas = 0;
    while (cont <= n){
        for (int i = 0; i < jogo->linhas; i++) {
            for (int j = 0; j < jogo->colunas; j++){
                if (jogo->tabuleiro[i][j] == '+'){
                    if (j + 2 < jogo->colunas && jogo->tabuleiro[i][j + 1] == '+' && jogo->tabuleiro[i][j + 2] == '-'){
                        jogadas = 1;
                        char posicao_linha = (char) i + 65;
                        char posicao_coluna = (char) j + 65;
                        movimento_direita(jogo, posicao_linha, posicao_coluna);
                        break;
                    }
                    else if (j - 2 > jogo->colunas && jogo->tabuleiro[i][j - 1] == '+' && jogo->tabuleiro[i][j - 2] == '-'){ 
                        jogadas = 1;
                        char posicao_linha = (char) i + 65;
                        char posicao_coluna = (char) j + 65;
                        movimento_esquerda(jogo, posicao_linha, posicao_coluna);
                        break;  
                    }
                    else if(i + 2 < jogo->linhas && jogo->tabuleiro[i + 1][j] == '+' && jogo->tabuleiro[i + 2][j] == '-'){
                        jogadas = 1;
                        char posicao_linha = (char) i + 65;
                        char posicao_coluna = (char) j + 65;
                        movimento_baixo (jogo, posicao_linha, posicao_coluna);
                        break;
                    }
                    else if(i - 2 > jogo->linhas && jogo->tabuleiro[i - 1][j] == '+' && jogo->tabuleiro[i - 2][j] == '-'){ 
                        jogadas = 1;
                        char posicao_linha = (char) i + 65;
                        char posicao_coluna = (char) j + 65;
                        movimento_cima(jogo, posicao_linha, posicao_coluna);
                        break;
                    }
                }
            }
            if (jogadas != 0){
                break;
            }
        }
        cont++;
        jogadas = 0;
    }
}

Jogo jogo_aleatorio(){
    //sorteando o numero de 3 a 26. 
    //Escolhi fazer o tabuleiro do tamanho da quantidade das letras do alfabeto.
    Jogo aleatorio;
    srand(time(NULL));
    aleatorio.linhas = (rand() % 22) + 4;
    aleatorio.colunas = (rand() % 22) + 4;
    aleatorio.pecas = 0;

    //alocando memoria do tabuleiro.
    aleatorio.tabuleiro = malloc(aleatorio.linhas * sizeof(char*));
    for (int i = 0; i < aleatorio.linhas; i++){
        aleatorio.tabuleiro[i] = malloc(aleatorio.colunas * sizeof(char));
    }
    for(int i = 0; i < aleatorio.linhas; i++){
        for(int j = 0; j < aleatorio.colunas; j++){
            int caractere = (rand() % 5);
            if (caractere == 0 || caractere == 1){
                aleatorio.tabuleiro[i][j] = '+';
                aleatorio.pecas++;
            }
            else if(caractere == 2 || caractere == 3){
                aleatorio.tabuleiro[i][j] = '-';
            }
            else {
                aleatorio.tabuleiro[i][j] = '*';
            }
        }
    }
    return aleatorio;
}

int perdeu_ganhou(Jogo jogo){

    if(jogo.pecas == 1){
        return 1;
    }
    for(int i = 0; i < jogo.linhas; i++){
        for(int j = 0; j < jogo.colunas; j++){
            if (jogo.tabuleiro[i][j] == '+'){
                if (j + 2 < jogo.colunas){ 
                    if(jogo.tabuleiro[i][j + 1] == '+' && jogo.tabuleiro[i][j + 2] == '-'){
                        return 0;
                    }       
                }
                else if (j - 2 > jogo.colunas){ 
                    if(jogo.tabuleiro[i][j - 1] == '+' && jogo.tabuleiro[i][j - 2] == '-'){
                        return 0;
                    }
                }
                else if(i + 2 < jogo.linhas){
                    if(jogo.tabuleiro[i + 1][j] == '+' && jogo.tabuleiro[i + 2][j] == '-'){
                        return 0;
                    }
                }
                else if(i - 2 > jogo.linhas){ 
                    if(jogo.tabuleiro[i - 1][j] == '+' && jogo.tabuleiro[i - 2][j]== '-'){
                        return 0;
                    }
                }
            }
        }
    }
    return -1;
}

void liberaMemoria(Jogo jogo)
{
   for (int i = 0; i < jogo.linhas; i++)
      free(jogo.tabuleiro[i]);
   free(jogo.tabuleiro);
}

int main(int argc, char *argv[]){
    
    int saida = 0;
    int sair = 0;
    system("clear");
    printf(BOLD(GREEN("Bem vindo ao jogo Resta UM!\n")));
    printf("\n");
    
    printf(BOLD("Lendo tabuleiro...\n"));
    Jogo jogo;
    if(argv[1] == (NULL)){
        jogo = jogo_aleatorio();
    }
    else{
        jogo = le_tabuleiro(argv[1]); 
    }
    printf(BOLD("Tabuleiro carregado!!\n"));
    printf("\n");

    imprime_menu();

    while(saida == 0 || sair == 0){
        imprime_jogo(jogo); 
        saida = le_comando(&jogo);
        if(saida == 1){
            break;
        }

        int verifica_vitoria = perdeu_ganhou(jogo); 
        if (verifica_vitoria == 1){
            printf(BOLD(RED("PARABÉEEEENS!!!!\n")));
            printf(BOLD(RED("Você venceu o jogo RESTA UM!\n")));
            sair = 1;
            break;
        }
        else if(verifica_vitoria == -1){
            printf(BOLD(RED("Você perdeu!! \nTente outra vez...\n")));
            sair = 1;
            break;
        }
        else {
            sair = 0;
        }
    }

    liberaMemoria(jogo);

    return 0;
}