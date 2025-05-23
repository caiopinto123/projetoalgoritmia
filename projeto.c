#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>


void salvarTabuleiroComNome(char **tabuleiro, int linhas, int colunas);

int leInteiro(const char *mensagem) {
    int valor;
    char c;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return valor;
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
}

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

void preencherTabuleiro(char **tabuleiro, int linhas, int colunas) {
    char letras[] = {'a', 'b', 'c', 'd', 'e'};
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int indice = rand() % 5;
            tabuleiro[i][j] = letras[indice];
        }
    }
}

void imprimirTabuleiro(char **tabuleiro, int linhas, int colunas) {
    printf("\nTabuleiro %dx%d:\n", linhas, colunas);
    printf("   ");
    for (int j = 0; j < colunas; j++) printf("%2d ", j);
    printf("\n");
    for (int i = 0; i < linhas; i++) {
        printf("%2d ", i);
        for (int j = 0; j < colunas; j++) {
            printf(" %c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void modificarCasa(char **tabuleiro, char **tabuleiro_original, int linha, int coluna, int acao, int linhas, int colunas) {
    int count_hashC = 0;
    int count_hashB = 0;
    int count_hashE = 0;
    int count_hashD = 0;

    // Mudar o caractere para maiúsculo ou minúsculo
    if (acao == 1) {
        if (islower(tabuleiro[linha][coluna])) {
            tabuleiro[linha][coluna] = toupper(tabuleiro[linha][coluna]);
        } else if (isupper(tabuleiro[linha][coluna])) {
            tabuleiro[linha][coluna] = tolower(tabuleiro[linha][coluna]);
        }
    }

    // Contar '#' ao redor
    if (linha + 2 < linhas && tabuleiro[linha + 2][coluna] == '#') count_hashC++;
    if (linha + 1 < linhas && coluna - 1 >= 0 && tabuleiro[linha + 1][coluna - 1] == '#') count_hashC++;
    if (linha + 1 < linhas && coluna + 1 < colunas && tabuleiro[linha + 1][coluna + 1] == '#') count_hashC++;

    if (linha - 2 >= 0 && tabuleiro[linha - 2][coluna] == '#') count_hashB++;
    if (linha - 1 >= 0 && coluna - 1 >= 0 && tabuleiro[linha - 1][coluna - 1] == '#') count_hashB++;
    if (linha - 1 >= 0 && coluna + 1 < colunas && tabuleiro[linha - 1][coluna + 1] == '#') count_hashB++;

    if (coluna + 2 < colunas && tabuleiro[linha][coluna + 2] == '#') count_hashE++;
    if (linha - 1 >= 0 && coluna + 1 < colunas && tabuleiro[linha - 1][coluna + 1] == '#') count_hashE++;
    if (linha + 1 < linhas && coluna + 1 < colunas && tabuleiro[linha + 1][coluna + 1] == '#') count_hashE++;

    if (coluna - 2 >= 0 && tabuleiro[linha][coluna - 2] == '#') count_hashD++;
    if (linha - 1 >= 0 && coluna - 1 >= 0 && tabuleiro[linha - 1][coluna - 1] == '#') count_hashD++;
    if (linha + 1 < linhas && coluna - 1 >= 0 && tabuleiro[linha + 1][coluna - 1] == '#') count_hashD++;

    // Lógica de modificação dependendo da ação
    if (acao == 2 && tabuleiro[linha][coluna] == '#') {
        tabuleiro[linha][coluna] = tabuleiro_original[linha][coluna];
        if (linha + 1 < linhas && count_hashC == 0) {
            tabuleiro[linha + 1][coluna] = tolower(tabuleiro[linha + 1][coluna]);
        }
        if (linha - 1 >= 0 && count_hashB == 0) {
            tabuleiro[linha - 1][coluna] = tolower(tabuleiro[linha - 1][coluna]);
        }
        if (coluna + 1 < colunas && count_hashE == 0) {
            tabuleiro[linha][coluna + 1] = tolower(tabuleiro[linha][coluna + 1]);
        }
        if (coluna - 1 >= 0 && count_hashD == 0) {
            tabuleiro[linha][coluna - 1] = tolower(tabuleiro[linha][coluna - 1]);
        }
    } else if (acao == 2) {
        tabuleiro[linha][coluna] = '#';
        if (linha + 1 < linhas) tabuleiro[linha + 1][coluna] = toupper(tabuleiro[linha + 1][coluna]);
        if (linha - 1 >= 0) tabuleiro[linha - 1][coluna] = toupper(tabuleiro[linha - 1][coluna]);
        if (coluna + 1 < colunas) tabuleiro[linha][coluna + 1] = toupper(tabuleiro[linha][coluna + 1]);
        if (coluna - 1 >= 0) tabuleiro[linha][coluna - 1] = toupper(tabuleiro[linha][coluna - 1]);
    }
}

void liberarTabuleiro(char **tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++) free(tabuleiro[i]);
    free(tabuleiro);
}

void copiarTabuleiro(char **destino, char **origem, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++)
        for (int j = 0; j < colunas; j++)
            destino[i][j] = origem[i][j];
}

void salvarTabuleiroParaFicheiro(char **tabuleiro, int linhas, int colunas) {
    FILE *fp = fopen("tabuleiro_salvo.txt", "w");
    if (!fp) {
        printf("Erro ao salvar o tabuleiro.\n");
        return;
    }
    fprintf(fp, "%d %d\n", linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fprintf(fp, "%c", tabuleiro[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Jogo salvo com sucesso em 'tabuleiro_salvo.txt'.\n");
}

void salvarTabuleiroComNome(char **tabuleiro, int linhas, int colunas) {
    char nome[100];
    printf("Deseja guardar o jogo com um nome específico? (s/n): ");
    char resp;
    scanf(" %c", &resp);
    getchar();
    if (resp == 's' || resp == 'S') {
        printf("Digite o nome do ficheiro (sem extensão): ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;
        if (strcmp(nome, "saves") == 0) {
            printf("Erro: 'saves' é o nome da pasta. Escolha outro nome!\n");
            return;
        }
        char caminho[150];
        snprintf(caminho, sizeof(caminho), "saves/%s.txt", nome);
        FILE *fp = fopen(caminho, "w");
        if (!fp) {
            printf("Erro ao guardar o ficheiro '%s'.\n", caminho);
            return;
        }
        fprintf(fp, "%d %d\n", linhas, colunas);
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                fprintf(fp, "%c", tabuleiro[i][j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
        printf("Jogo guardado como '%s'.\n", caminho);
    } else {
        salvarTabuleiroParaFicheiro(tabuleiro, linhas, colunas);
    }
}

void verificaRegras(char **tabuleiro, int l, int c, char *mensagem) {
    int i, j, k;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            for (k = j + 1; k < c; k++) {
                if (tabuleiro[i][j] == '#' && tabuleiro[i][k] == '#') {
                    sprintf(mensagem, "Repetição '#' na linha %d nas colunas %d e %d", i, j, k);
                    return;
                }
            }
        }
    }
    for (j = 0; j < c; j++) {
        for (i = 0; i < l - 1; i++) {
            if (tabuleiro[i][j] == '#' && tabuleiro[i + 1][j] == '#') {
                 sprintf(mensagem, "Repetição '#' na coluna %d nas linhas %d e %d", j, i, i + 1);
                 return;
            }
        }
    }
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            for (k = j + 1; k < c; k++) {
                if (tabuleiro[i][j] != '#' && tabuleiro[i][k] != '#' && toupper(tabuleiro[i][j]) == toupper(tabuleiro[i][k])) {
                    sprintf(mensagem, "Repetição '%c' na linha '%d'", tabuleiro[i][j], i );
                    return;
                }
            }
        }
    }
    strcpy(mensagem, "nada a verificar");
}









typedef struct {
    int linha;
    int coluna;
} Posicao;

bool casasBrancasEstaoConectadas(char **tabuleiro, int linhas, int colunas) {
    if (linhas == 0 || colunas == 0) return true;
    
    Posicao inicio = {-1, -1};
    int contadorBrancas = 0;
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (isupper(tabuleiro[i][j])) {
                contadorBrancas++;
                if (inicio.linha == -1) {
                    inicio.linha = i;
                    inicio.coluna = j;
                }
            }
        }
    }
    
    if (contadorBrancas == 0) return true;
    
    bool **visitado = malloc(linhas * sizeof(bool *));
    for (int i = 0; i < linhas; i++) {
        visitado[i] = calloc(colunas, sizeof(bool));
    }
    
    Posicao *fila = malloc(linhas * colunas * sizeof(Posicao));
    int frente = 0;
    int tras = 0;
    
    fila[tras++] = inicio;
    visitado[inicio.linha][inicio.coluna] = true;
    int contadorConectadas = 1;
    
    int direcoes[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (frente < tras) {
        Posicao atual = fila[frente++];
        
        for (int i = 0; i < 4; i++) {
            int novaLinha = atual.linha + direcoes[i][0];
            int novaColuna = atual.coluna + direcoes[i][1];
            
            if (novaLinha >= 0 && novaLinha < linhas && novaColuna >= 0 && novaColuna < colunas) {
                if (!visitado[novaLinha][novaColuna] && isupper(tabuleiro[novaLinha][novaColuna])) {
                    visitado[novaLinha][novaColuna] = true;
                    fila[tras++] = (Posicao){novaLinha, novaColuna};
                    contadorConectadas++;
                }
            }
        }
    }
    
    for (int i = 0; i < linhas; i++) {
        free(visitado[i]);
    }
    free(visitado);
    free(fila);
    
    return contadorConectadas == contadorBrancas;
}













char leLetra(const char *mensagem) {
    char letra;
    printf("%s", mensagem);

    while (1) {
        letra = getchar();

        if (letra != '\n' && letra != ' ') {
            while (getchar() != '\n'); 
            return letra;
        }
    }
}




int main(void) {
    mkdir("saves", 0777);
    int linhas = 0, colunas = 0;
    char **tabuleiro = NULL;
    char **tabuleiro_original = NULL; //
    char **tabuleiroAnterior = NULL;
    char mensagem[100] = "";
    int jogadas = 0;
    int opcao = -1;

    char sair2 = 's';


while(sair2 == 's') {
    while (opcao != 1 && opcao != 2 && opcao != 0 && opcao != 3 && opcao != 1253654214) {
        printf("=====================================\n");
        printf("            MENU INICIAL             \n");
        printf("=====================================\n");
        printf("1 - Novo jogo\n");
        printf("2 - Carregar jogo anterior\n");
        printf("3 - Configurações\n");
        printf("0 - Sair\n");
        printf("=====================================\n");
        opcao = leInteiro("Escolha a opção: ");
    }

    if (opcao == 0) {
        printf("A sair do jogo...\n");
        return 0;
    }

    if (opcao == 2) {
        DIR *dir;
        struct dirent *entry;
        char ficheiros[100][100];
        int total = 0;

        dir = opendir("saves");
        if (!dir) {
            printf("Erro ao abrir a pasta de saves. Um novo jogo será iniciado.\n");
            opcao = 1;
        } else {
            printf("=====================================\n");
            printf("         JOGOS DISPONÍVEIS           \n");
            printf("=====================================\n");

            while ((entry = readdir(dir)) != NULL) {
                if (strstr(entry->d_name, ".txt")) {
                    printf("%d - %s\n", total + 1, entry->d_name);
                    strcpy(ficheiros[total], entry->d_name);
                    total++;
                }
            }
            closedir(dir);

            if (total == 0) {
                printf("Nenhum jogo encontrado. Um novo será iniciado.\n");
                opcao = 1;
            } else {
                int escolha = -1;
                while (escolha < 0 || escolha > total) {
                    escolha = leInteiro("Escolha o número do jogo a carregar (0 para cancelar): ");
                }

                if (escolha == 0) {
                    printf("A carregar novo jogo em vez de save...\n");
                    opcao = 1;
                } else {
                    char caminho[150];
                    snprintf(caminho, sizeof(caminho), "saves/%s", ficheiros[escolha - 1]);

                    FILE *fp = fopen(caminho, "r");
                    if (!fp) {
                        printf("Erro ao abrir ficheiro '%s'. Novo jogo será iniciado.\n", caminho);
                        opcao = 1;
                    } else {
                        fscanf(fp, "%d %d\n", &linhas, &colunas);
                        tabuleiro = criarTabuleiro(linhas, colunas);
                        tabuleiro_original = criarTabuleiro(linhas, colunas);
                        tabuleiroAnterior = criarTabuleiro(linhas, colunas);
                        for (int i = 0; i < linhas; i++) {
                            for (int j = 0; j < colunas; j++) {
                                tabuleiro[i][j] = fgetc(fp);
                            }
                            fgetc(fp);
                        }
                        fclose(fp);
                        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
                        copiarTabuleiro(tabuleiro_original, tabuleiro, linhas, colunas);
                    }
                }
            }
        }
    }

    if (opcao == 1) {
        linhas = leInteiro("Digite o número de linhas: ");
        colunas = leInteiro("Digite o número de colunas: ");
        tabuleiro = criarTabuleiro(linhas, colunas);
        tabuleiro_original = criarTabuleiro(linhas, colunas);
        tabuleiroAnterior = criarTabuleiro(linhas, colunas);
        if (!tabuleiro || !tabuleiroAnterior) {
            printf("Erro ao alocar memória.\n");
            return 1;
        }
        preencherTabuleiro(tabuleiro, linhas, colunas);
        copiarTabuleiro(tabuleiro_original, tabuleiro, linhas, colunas);
        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
        opcao = -1;
        sair2 = 1;
    }

    if (opcao == 3) {
        printf("=====================================\n");
        printf("         CONTROLOS           \n");
        printf("=====================================\n");
        printf("\n");
        printf("g - gravar jogo\n");
        printf("l - ler o estado do jogo num ficheiro\n");
        printf("b - substituir pela maiúscula\n");
        printf("r - riscar peça\n");
        printf("v - verificar o estado do jogo e apontar todas as restrições violadas\n");
        printf("a - ajudar mudando o estado de todas as casas que se conseguem inferir através do estado atual do tabuleiro\n");
        printf("A - invocar o comando a enquanto o jogo sofrer alterações\n");
        printf("R - resolver o jogo\n");
        printf("d - desfazer o último comando executado\n");
        printf("s - sair para o menu\n");
        printf("0 - terminar o programa\n");
        sair2 = leLetra("voltar ao inicio: ");
        if (sair2 == 's') opcao = -1;
        continue;
    }
   
    int sair = 0;
    int primeiraVez = 1;
    char linhaInput[100];
   
    
    if (opcao == 1253654214) {
        printf("\n");
        printf("=====================================\n");
        printf("         CONTROLOS           \n");
        printf("=====================================\n");
        printf("\n");
        printf("g - gravar jogo\n");
        printf("l - ler o estado do jogo num ficheiro\n");
        printf("b - substituir pela maiúscula\n");
        printf("r - riscar peça\n");
        printf("v - verificar o estado do jogo e apontar todas as restrições violadas\n");
        printf("a - ajudar mudando o estado de todas as casas que se conseguem inferir através do estado atual do tabuleiro\n");
        printf("A - invocar o comando a enquanto o jogo sofrer alterações\n");
        printf("R - resolver o jogo\n");
        printf("d - desfazer o último comando executado\n");
        printf("s - sair do programa\n");
        printf("c - controlos\n");
        opcao = 1; sair = 0; sair2 = 'a';
        getchar();
        
    }

    while (!sair) {
        imprimirTabuleiro(tabuleiro, linhas, colunas);
        
         if (strlen(mensagem) > 0) {
        printf("\n%s\n\n", mensagem);
        mensagem[0] = '\0'; // Limpa a mensagem após exibir
    }
    
        printf("Jogadas realizadas: %d\n", jogadas);
        if (primeiraVez) {
            printf("Clique 'c' para acessar os controlos.\n");
        }


        if (fgets(linhaInput, sizeof(linhaInput), stdin) != NULL) {
            linhaInput[strcspn(linhaInput, "\n")] = 0;

            if (strcmp(linhaInput, "0") == 0) {
                sair = 1;
            } else if (strcmp(linhaInput, "d") == 0 || strcmp(linhaInput, "D") == 0) {
                copiarTabuleiro(tabuleiro, tabuleiroAnterior, linhas, colunas);
                if (jogadas > 0) jogadas --;
                strcpy(mensagem, "Última jogada anulada.");
            } else if (strcmp(linhaInput, "v") == 0 || strcmp(linhaInput, "V") == 0) {
                verificaRegras(tabuleiro, linhas, colunas, mensagem);
            } else if (strcmp(linhaInput, "s") == 0 || strcmp(linhaInput, "S") == 0) {
                            sair2 = 's'; sair = 1;
                            if (sair2 == 's') opcao = -1;
            } else if (strcmp(linhaInput, "g") == 0 || strcmp(linhaInput, "G") == 0) {
                salvarTabuleiroComNome(tabuleiro, linhas, colunas);
            } else if (strcmp(linhaInput, "p") == 0) {
                bool conectado = casasBrancasEstaoConectadas(tabuleiro, linhas, colunas);
                if (strcmp(linhaInput, "p") == 0) {
                    bool conectado = casasBrancasEstaoConectadas(tabuleiro, linhas, colunas);
                    sprintf(mensagem, "As casas brancas %s estao conectadas.", conectado ? "" : "NAO ");
                }
            } else if (strcmp(linhaInput, "c") == 0) {
                        opcao = 1253654214; sair = 1; sair2 = 's';
            } else {
                char acao;
                int lin, col;
                int res = sscanf(linhaInput, " %c %d %d", &acao, &lin, &col);

                if (res == 3) {
                    if (lin >= 0 && lin < linhas && col >= 0 && col < colunas) {
                        copiarTabuleiro(tabuleiroAnterior, tabuleiro, linhas, colunas);
                        jogadas ++;
                        if (acao == 'b') {
                            modificarCasa(tabuleiro,tabuleiro_original, lin, col, 1, linhas, colunas);
                            primeiraVez = 0;
                        } else if (acao == 'r') {
                            modificarCasa(tabuleiro,tabuleiro_original, lin, col, 2, linhas, colunas);
                            primeiraVez = 0;
                        } else {
                            strcpy(mensagem, "Ação inválida!\n");
                        }
                    } else {
                        strcpy(mensagem, "Posição inválida!\n");
                    }
                } else {
                    strcpy(mensagem, "Formato inválido! Use: r linha coluna ou b linha coluna\n");
                }
            }
        } else {
            strcpy(mensagem, "Erro na leitura!\n");
            sair = 1;
        }
    }
}
    printf("\nEstado final do tabuleiro:\n");
    imprimirTabuleiro(tabuleiro, linhas, colunas);
    liberarTabuleiro(tabuleiro, linhas);
    liberarTabuleiro(tabuleiroAnterior, linhas);
    liberarTabuleiro(tabuleiro_original, linhas); //
    return 0;
}
