#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Lê um inteiro com verificação de entrada
int leInteiro(const char *mensagem) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
            return valor;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF); // limpa buffer
        }
    }
}

// Aloca memória para o tabuleiro
char **criarTabuleiro(int linhas, int colunas) {
    char **tabuleiro = malloc(linhas * sizeof(char *));
    if (!tabuleiro) return NULL;

    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = malloc(colunas * sizeof(char));
        if (!tabuleiro[i]) {
            for (int j = 0; j < i; j++) free(tabuleiro[j]);
            free(tabuleiro);
            return NULL;
        }
    }
    return tabuleiro;
}

// Preenche o tabuleiro com letras aleatórias
void preencherTabuleiro(char **tabuleiro, int linhas, int colunas) {
    char letras[] = {'a', 'b', 'c', 'd', 'e'};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int indice = rand() % 5;
            tabuleiro[i][j] = letras[indice];
        }
    }
}

// Imprime o tabuleiro
void imprimirTabuleiro(char **tabuleiro, int linhas, int colunas) {
    printf("\nTabuleiro %dx%d:\n", linhas, colunas);
    printf("   ");
    for (int j = 0; j < colunas; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < linhas; i++) {
        printf("%2d ", i);
        for (int j = 0; j < colunas; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Modifica uma casa do tabuleiro
void modificarCasa(char **tabuleiro, int linha, int coluna, char acao) {
    if (acao == 'm' && islower(tabuleiro[linha][coluna])) {
        tabuleiro[linha][coluna] = toupper(tabuleiro[linha][coluna]);
    } else if (acao == 'c') {
        tabuleiro[linha][coluna] = '#';
    }
}

// Libera a memória do tabuleiro
void liberarTabuleiro(char **tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++)
        free(tabuleiro[i]);
    free(tabuleiro);
}

// Função principal
int main() {
    int linhas = leInteiro("Digite o número de linhas: ");
    int colunas = leInteiro("Digite o número de colunas: ");

    srand(time(NULL));
    char **tabuleiro = criarTabuleiro(linhas, colunas);
    if (!tabuleiro) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    preencherTabuleiro(tabuleiro, linhas, colunas);
    
    int lin, col;
    char cond;
    int opcao;

do {

printf("\nMenu\n");
printf("1 - Jogar\n");
printf("0 - Sair\n");
printf("Escolha uma opção: ");
scanf("%d", &opcao);


while (getchar() != '\n');

if (opcao == 1) {
    int continuar = 1;
    
    do {
        imprimirTabuleiro(tabuleiro, linhas, colunas);
        printf("Informe a condição, linha e a coluna (ou 0 para sair): ");

        char entrada[20];
        fgets(entrada, sizeof(entrada), stdin);

        if (entrada[0] == '0' && entrada[1] == '\n') {
            continuar = 0;
            } else {
                if (sscanf(entrada, "%c %d %d", &cond, &lin, &col) != 3) {
                    printf("Entrada inválida! Tente de novo.\n");
                } else if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                    modificarCasa(tabuleiro, lin, col, cond);
                } else {
                    printf("Posição inválida!\n");
                }
            }
        } while (continuar);
    }
} while (opcao != 0); 


printf("\nEstado final do tabuleiro:\n");
imprimirTabuleiro(tabuleiro, linhas, colunas);
liberarTabuleiro(tabuleiro, linhas);
return 0;}
