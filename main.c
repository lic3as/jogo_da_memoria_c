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
        {"Gato", "Cachorro", "Pato", "Vaca", "Cavalo", "Borboleta", "Peixe", "Pinguim", "Abelha", "Girafa"},  // Tema 0: Animais
        {"Uva", "Banana", "Laranja", "Goiaba", "Manga", "Melancia", "Acerola", "Morango", "Caju", "Cajarana"},   // Tema 1: Frutas
        {"++", "--", "##", "{}", "//", "&&", "$$", "()", "[]", "@@"}    // Tema 2: Símbolos
    };
    
    int tema;
    // decidir se quer ou não continuar
    char continuar;
    int tamanho = 4;    //tabuleiro de tamanho 4
    do{
        do {
            printf("Bem-vindo ao Jogo da Memoria!\nTemas:\n");
            printf("0 - Animais\n");
            printf("1 - Frutas\n");
            printf("2 - Simbolos\n");
            printf("Informe o tema: ");
            scanf("%d", &tema);
            if (tema < 0 || tema > 2) printf("Opcao invalida! Tente novamente.\n"); // testar se o tema é válido
        } while (tema < 0 || tema > 2);
        
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

    while (paresEncontrados < (tamanho * tamanho) / 2) {    //enquanto a quantidade de pares for menor que a metade do jogo
        exibirTabuleiro(tema, tamanho);
        //escolher a primeira carta
        do{
            printf("\nEscolha a primeira carta: ");
            printf("\nDigite uma linha (0 a %d): ", tamanho-1);
            scanf("%d", &x1);
            printf("Digite uma coluna (0 a %d): ", tamanho-1);
            scanf("%d",&y1);
            //checar se a carta já foi revelada e se está no intervalo de números válidos, se não, pedir novamente pra digitar
            if((tema[x1][y1].revelado == 1) || (x1 < 0 || x1 >= tamanho) || (y1 < 0 || y1 >= tamanho)) printf("Erro! Escolha cartas nao reveladas e validas.\n");
        } while((tema[x1][y1].revelado == 1) || (x1 < 0 || x1 >= tamanho) || (y1 < 0 || y1 >= tamanho));
        //revelar carta e mostrar o tabuleiro
        tema[x1][y1].revelado = 1;  
        exibirTabuleiro(tema, tamanho);
        
        //escolher a segunda carta
        do{
            printf("Escolha a segunda carta: ");
            printf("\nDigite uma linha (0 a %d): ", tamanho-1);
            scanf("%d", &x2);
            printf("Digite uma coluna (0 a %d): ", tamanho-1);
            scanf("%d",&y2);
            //checar se a carta já foi revelada e se está no intervalo de números válidos, se não, pedir novamente pra digitar
            if((tema[x2][y2].revelado == 1) || (x2 < 0 || x2 >= tamanho) || (y2 < 0 || y2 >= tamanho)) printf("Erro! Escolha cartas nao reveladas e validas.\n");
        } while((tema[x2][y2].revelado == 1) || (x2 < 0 || x2 >= tamanho) || (y2 < 0 || y2 >= tamanho));

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
            printf("Nao formou um par. Tente novamente.\n");
            tema[x1][y1].revelado = 0;
            tema[x2][y2].revelado = 0;
        }

        //incrementar as tentativas a cada nova jogada
        tentativas++;
    }

    //após fazer todos os pares, parabenizar e mostrar as tentativas
    printf("Parabens!!! Você completou o jogo em %d tentativas.\n", tentativas);
}