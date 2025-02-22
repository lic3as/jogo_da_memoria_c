#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

// Definindo constantes para o tamanho máximo do tabuleiro e das strings
#define TAM_MAX 10
#define TAM_MIN 4
#define MAX_STRING 20

// Estrutura para representar uma carta
typedef struct Carta {
    char palavra[MAX_STRING];
    char revelado;
} Carta;

// Funções para iniciar o jogo, embaralhar, exibir o tabuleiro e jogar
void iniciar(int tam, char tema[TAM_MAX][MAX_STRING], int qtdPares);
void embaralhar(Carta tema[TAM_MAX][TAM_MAX], int tamanho);
void exibirTabuleiro(Carta tema[TAM_MAX][TAM_MAX], int tamanho);
void jogar(Carta tema[TAM_MAX][TAM_MAX], int tamanho);

int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios
    
    // Vetor com temas
    char temas[3][TAM_MAX][MAX_STRING] = {
        {"Gato", "Cachorro", "Pato", "Vaca", "Cavalo", "Borboleta", "Peixe", "Pinguim", "Leão", "Girafa"},  // Tema 0: Animais
        {"Maçã", "Banana", "Laranja", "Goiaba", "Manga", "Melancia", "Limão", "Morango", "Caju", "Cajarana"},   // Tema 1: Frutas
        {"++", "--", "##", "{}", "//", "&&", "$$", "()", "[]", "@@"}    // Tema 2: Símbolos
    };
    
    // Selecionar tema
    char selecionarTema[0];
    int tema;
    // decidir se quer ou não continuar
    char continuar;
    int tamanho = 4;    //tabuleiro de tamanho 4
    do{
            printf("Bem-vindo ao Jogo da Memória!\nTemas:\n");
            printf("0 - Animais\n");
            printf("1 - Frutas\n");
            printf("2 - Símbolos\n");
            printf("Informe o tema: ");
            scanf(" %s", selecionarTema); //recebe o valor em string
            
            // testar se o tema é válido

            if (selecionarTema[0] != '0' && selecionarTema[0] != '1' && selecionarTema[0] != '2'){ 
                while (true)
                {
                    printf("Opção inválida! Tente novamente.\n"); 
                    printf("Informe o tema valido: ");
                    scanf(" %s", selecionarTema);
                    if(selecionarTema[0] == '0' || selecionarTema[0] == '1' || selecionarTema[0] == '2'){ //se for uma string válida tranformar em inteiro
                        if(isdigit(selecionarTema[0])){
                            tema = selecionarTema[0] - '0'; //tranforma no numero inteiro correspondente na tabela asci
                            break;  
                        }
                    }
                }
                
            }  
            else if (selecionarTema[0] == '0' || selecionarTema[0] == '1' || selecionarTema[0] == '2')
            {
                isdigit(selecionarTema[0]);
                tema = selecionarTema[0] - '0'; //tranforma no numero inteiro correspondente na tabela asci     
            }
            
        // Iniciar o jogo
        iniciar(tamanho, temas[tema], tamanho * tamanho / 2);   // Chama a função para criar as cartas do tabuleiro
        //conferir se quer jogar novamente após concluir o jogo
        printf("Deseja continuar? [s/n] ");
        scanf(" %c", &continuar);
    } while(continuar == 's' || continuar == 'S');  // continuar enquanto o usuário digitar sim

    return 0;
}

void iniciar(int tam, char tema[TAM_MAX][MAX_STRING], int qtdPares) {
    Carta carta[TAM_MAX][TAM_MAX];
    // Preenche o tabuleiro com as cartas e palavras do tema
    int cartaTema = 0;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j += 2) {
            strcpy(carta[i][j].palavra, tema[cartaTema]);  // Atribui a palavra para a carta
            strcpy(carta[i][j + 1].palavra, tema[cartaTema]);  // Atribui a mesma palavra para a carta seguinte
            carta[i][j].revelado = 0;  // Inicializa as cartas como não reveladas
            carta[i][j + 1].revelado = 0;
            cartaTema++;  // Passa para a próxima palavra do tema
            if (cartaTema >= qtdPares) cartaTema = 0;  // Impede ultrapassar as palavras do tema
        }
    }
    // Embaralha as cartas
    embaralhar(carta, tam);
    // inicia o jogo
    jogar(carta, tam); 
}


//função para embaralhar o tabuleiro
void embaralhar(Carta tema[TAM_MAX][TAM_MAX], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            int r1 = rand() % tamanho;  //gerar número aleatório com a função rand de acordo com o tamanho
            int r2 = rand() % tamanho;
            Carta temp = tema[i][j];    //distribuir de forma aleatória
            tema[i][j] = tema[r1][r2];
            tema[r1][r2] = temp;
        }
    }
}


//função para exibir o tabuleiro
void exibirTabuleiro(Carta tema[TAM_MAX][TAM_MAX], int tamanho) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (tema[i][j].revelado)    //se a palavra já foi revelada
                printf(" %s ", tema[i][j].palavra);
            else
                printf(" * ");  //se ainda não foi revelada, coloca um *
        }
        printf("\n");
    }
}

// função parar jogar
void jogar(Carta tema[TAM_MAX][TAM_MAX], int tamanho) {
    int x1, y1, x2, y2, tentativas = 0, paresEncontrados = 0;
    char linha[0], coluna[0];

    while (paresEncontrados < (tamanho * tamanho) / 2) {    //enquanto a quantidade de pares for menor que a metade do jogo
        exibirTabuleiro(tema, tamanho);
        //escolher a primeira carta

        do{
            printf("\nEscolha a primeira carta: ");
            printf("\nDigite uma linha (1 a %d): ", tamanho);
            scanf("%s", linha);

            if(linha[0] == '1' || linha[0] == '2' || linha[0] == '3' || linha[0] == '4'){ //verificar se o caractere é valido
                if(isdigit(linha[0])){
                            x1 = linha[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            x1 = x1 - 1; // usuario digitar a linha comecando em 1
                }
            }

            else if(linha[0] != '1' && linha[0] != '2' && linha[0] != '3' && linha[0] != '4'){ //verificar se o numero de linha é valido
                while (true)
                {
                    printf("ERRO! escolha um numero entre 1 e %d.\n", tamanho);
                    printf("Digite uma linha (1 a %d): ", tamanho);
                    scanf("%s", linha);
                    if(linha[0] == '1' || linha[0] == '2' || linha[0] == '3' || linha[0] == '4'){ // quando for valido quebrar o laco
                        if(isdigit(linha[0])){
                            x1 = linha[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            x1 = x1 - 1; // usuario digitar a linha comecando em 1
                            break;
                        }
                    }
                }
            }    

            printf("Digite uma coluna (1 a %d): ", tamanho);
            scanf("%s", coluna);

            if(coluna[0] == '1' || coluna[0] == '2' || coluna[0] == '3' || coluna[0] == '4'){ //verificar se o caractere é valido
                if(isdigit(coluna[0])){
                            y1 = coluna[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            y1 = y1 - 1; // usuario digitar a coluna comecando em 1
                }
            }

            else if(coluna[0] != '1' && coluna[0] != '2' && coluna[0] != '3' && coluna[0] != '4'){ //verificar se o numero de coluna é valido
                while (true)
                {
                    printf("ERRO! escolha um numero entre 1 e %d.\n", tamanho);
                    printf("Digite uma coluna (1 a %d): ", tamanho);
                    scanf("%s", coluna);
                    if(coluna[0] == '1' || coluna[0] == '2' || coluna[0] == '3' || coluna[0] == '4'){ // quando for valido quebrar o laco
                        if(isdigit(coluna[0])){
                            y1 = coluna[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            y1 = y1 - 1; // usuario digitar a linha comecando em 1
                            break;
                        }
                    }
                }
            }    

            //checar se a carta já foi revelada e se está no intervalo de números válidos, se não, pedir novamente pra digitar
            if(tema[x1][y1].revelado == 1) printf("Erro! Escolha cartas não reveladas e válidas.\n");

        } while((tema[x1][y1].revelado == 1));

        //revelar carta e mostrar o tabuleiro
        tema[x1][y1].revelado = 1; 

        exibirTabuleiro(tema, tamanho);
        
        //escolher a segunda carta
        do{
            printf("Escolha a segunda carta: ");
            printf("\nDigite uma linha (1 a %d): ", tamanho);
            scanf("%s", linha);

            if(linha[0] == '1' || linha[0] == '2' || linha[0] == '3' || linha[0] == '4'){ //verificar se o caractere é valido
                if(isdigit(linha[0])){
                            x2 = linha[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            x2 = x2 - 1; // usuario digitar a linha comecando em 1
                }
            }

            else if(linha[0] != '1' && linha[0] != '2' && linha[0] != '3' && linha[0] != '4'){ //verificar se o numero de linha é valido
                while (true)
                {
                    printf("ERRO! escolha um numero entre 1 e %d.\n", tamanho);
                    printf("Digite uma linha (1 a %d): ", tamanho);
                    scanf("%s", linha);
                    if(linha[0] == '1' || linha[0] == '2' || linha[0] == '3' || linha[0] == '4'){ // quando for valido quebrar o laco
                        if(isdigit(linha[0])){
                            x2 = linha[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            x2 = x2 - 1; // usuario digitar a linha comecando em 1
                            break;
                        }
                    }
                }
            }   

            printf("Digite uma coluna (1 a %d): ", tamanho);
            scanf("%s", coluna);

            if(coluna[0] == '1' || coluna[0] == '2' || coluna[0] == '3' || coluna[0] == '4'){ //verificar se o caractere é valido
                if(isdigit(coluna[0])){
                            y2 = coluna[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            y2 = y2 - 1; // usuario digitar a coluna comecando em 1
                }
            }

            else if(coluna[0] != '1' && coluna[0] != '2' && coluna[0] != '3' && coluna[0] != '4'){ //verificar se o numero de coluna é valido
                while (true)
                {
                    printf("ERRO! escolha um numero entre 1 e %d.\n", tamanho);
                    printf("Digite uma coluna (1 a %d): ", tamanho);
                    scanf("%s", coluna);
                    if(coluna[0] == '1' || coluna[0] == '2' || coluna[0] == '3' || coluna[0] == '4'){ // quando for valido quebrar o laco
                        if(isdigit(coluna[0])){
                            y2 = coluna[0] - '0'; //tranformar no inteiro correspondente ao caractere valido
                            y2 = y2 - 1; // usuario digitar a linha comecando em 1
                            break;
                        }
                    }
                }
            }    


            //checar se a carta já foi revelada e se está no intervalo de números válidos, se não, pedir novamente pra digitar
            if(tema[x2][y2].revelado == 1) printf("Erro! Escolha cartas não reveladas e válidas.\n");
        } while(tema[x2][y2].revelado == 1);

        if (x1 == x2 && y1 == y2) { //verificar se o usuário escolheu as mesmas cartas
            printf("Erro! Escolha duas cartas diferentes!\n");
            continue;
        } 
        //revelar carta e mostrar o tabuleiro
        tema[x2][y2].revelado = 1;
        exibirTabuleiro(tema, tamanho);

        //se tiver formado um par, avisar, deixar as cartas reveladas e incrementar as reveladas
        if (strcmp(tema[x1][y1].palavra, tema[x2][y2].palavra) == 0) {
            printf("Par encontrado!\n");
            tema[x1][y1].revelado = 1;
            tema[x2][y2].revelado = 1;
            paresEncontrados++;
        } else {    //senão tiver formado um par, avisar e esconder as cartas novamente
            printf("Não formou um par. Tente novamente.\n");
            tema[x1][y1].revelado = 0;
            tema[x2][y2].revelado = 0;
        }

        //incrementar as tentativas a cada nova jogada
        tentativas++;
    }

    //após fazer todos os pares, parabenizar e mostrar as tentativas
    printf("Parabéns! Você completou o jogo em %d tentativas.\n", tentativas);
}
