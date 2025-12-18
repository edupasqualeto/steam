#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char* DIRETORIO_BASE = "..\\udesc\\ESD-USB\\trabalhofinalC";

#define LINHA 100
FILE *arquivo = NULL;

void menuPrincipal(int idLogado);
void menuLoja(int idLogado);
void menuBiblioteca(int idLogado);
void menuPerfil(int idLogado);
int listarloja();
int transferir(int jogo, int idLogado);
int listarbiblioteca(int idLogado);
void abrirArquivo();
int validarLogin(char* email, char* senha);
void exibirPerfilPorId(int idProcurado);
int adicionarPerfil(char* nome, char* email, char* senha);
int emailJaExiste(char* emailParaVerificar);
int obterProximoId(char* nomeArquivo);
void adicionarSaldo(int id, int valorAdicional);
void alterarNome(int idLogado, char* novoNome);
int obterCustoJogo(int idJogo);
int comprarJogo(int idPerfil, int idJogo);


int main() {
    int opcao = 0;
    int idLogado = 0;
    char email[100], senha[50], nome[50];
    while (opcao != 1 && opcao != 2){
        printf("Para qual opção você deseja seguir:\n");
        printf("1 - Login (Já tenho uma conta)\n");
        printf("2 - Cadastro (Não tenho uma conta)\n");
        printf("Escolha: ");
        scanf("%i",&opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    if (opcao == 1) {
    while (idLogado == 0){
        printf("Login:\n");
        printf("Email de login: ");
        fgets(email, 100, stdin);
        email[strcspn(email, "\n")] = 0;
        printf("Senha de login: ");
        fgets(senha, 50, stdin);
        senha[strcspn(senha, "\n")] = 0;

        idLogado = validarLogin(email, senha);
        if (idLogado == 0){
            printf("Email ou senha incorretos.\n\n");
        }
    }
    printf("Sucesso no login!\n\n");
    }
    if (opcao == 2){
        while (idLogado <= 0){
            printf("Cadastro:\n");
            printf("Nome do perfil: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Email de login: ");
            fgets(email, 100, stdin);
            email[strcspn(email, "\n")] = 0;
            printf("Senha de login: ");
            fgets(senha, 50, stdin);
            senha[strcspn(senha, "\n")] = 0;

            idLogado = adicionarPerfil(nome, email, senha);
            if (idLogado <= 0){
                printf("Email ou senha incorretos.\n\n");
            }
        }
        printf("Sucesso no cadastro!\n\n");
    }
    menuPrincipal(idLogado);
    fclose(arquivo);
    return 0;
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausa() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void menuPrincipal(int idLogado){
    int opcao = 0;

    while (opcao != 4){
        limparTela();
        printf("=== STEAM TERMINAL ===\n");
        printf("1 - Loja\n");
        printf("2 - Biblioteca\n");
        printf("3 - Perfil\n");
        printf("4 - Sair\n");
        printf("======================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                menuLoja(idLogado);
                break;
            case 2:
                menuBiblioteca(idLogado);
                break;
            case 3:
                menuPerfil(idLogado);
                break;
            case 4:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
        }

    }
}

void menuLoja(int idLogado) {
    int opcao = 0;
    int jogo;
    bool comprar = false;
    char teste;
    int compra = 0;

    while (opcao != 2){
        limparTela();
        printf("=== LOJA ===\n");
        printf("1 - Comprar jogo\n");
        printf("2 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                abrirArquivo();
                printf("\nListando jogos disponíveis...\n");
                listarloja();
                printf("\nDeseja comprar algum jogo? (digite S ou N)\n");
                scanf(" %c", &teste);
                if (teste == 'S' || teste == 's') { 
                    comprar = true;
                } else {
                    printf("Compra cancelada.\n");
                }
                
                if(comprar == true) {
                    printf("Digite o codigo do jogo: ");
                    scanf("%i", &jogo);
                    compra = comprarJogo(idLogado, jogo);
                    if (compra == 1) {
                        abrirArquivo();
                        transferir(jogo, idLogado);
                        printf("\nCompra bem sucedida. \n");
                    }
                }
                pausa();
                break;
            case 2:
                printf("\nVoltando ao menu principal...\n");
                pausa();
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
        }
    }
}

void menuBiblioteca(int idLogado) {
    int opcao = 0;
    while (opcao != 2){
        limparTela();
        printf("=== BIBLIOTECA ===\n");
        printf("1 - Ver jogos comprados\n");
        printf("2 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nMostrando seus jogos: \n");
                listarbiblioteca(idLogado);
                pausa();
                break;
            case 2:
                printf("\nIniciando simulacao de jogo...\n");
                pausa();
                break;
            case 3:
                printf("\nVoltando ao menu principal...\n");
                pausa();
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
        }
    }
}

void menuPerfil(int idLogado) {
    char nome[50];
    int valoramais = 0;
    int opcao = 0;
    while (opcao != 4){
        limparTela();
        printf("=== PERFIL ===\n");
        printf("1 - Ver dados\n");
        printf("2 - Adicionar saldo\n");
        printf("3 - Editar nome\n");
        printf("4 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                exibirPerfilPorId(idLogado);
                pausa();
                break;
            case 2:

                printf("\nDeseja adicionar quanto de saldo? \n");
                scanf("%i", &valoramais);
                while ((c = getchar()) != '\n' && c != EOF);
                adicionarSaldo(idLogado, valoramais);
                pausa();
                break;
            case 3:
                printf("Digite um novo nome: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;
                alterarNome(idLogado, nome);
                pausa();
                break;
            case 4:
                printf("\nVoltando ao menu principal...\n");
                pausa();
                break;
            default:
                printf("\nOpcao invalida!\n");
                pausa();
        }
    }
}

void abrirArquivo() {
    char caminholoja[1024];
    snprintf(caminholoja, sizeof(caminholoja), "%s\\%s", DIRETORIO_BASE, "loja.txt");
    if (arquivo == NULL) {
        arquivo = fopen(caminholoja, "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir loja.txt\n");
        }
    }
}

int listarloja() {
    char linha[LINHA];
    char *id, *nome, *preco;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("ID\tJogo\t\t\t\tPreco\n");
    printf("-----------------------------------------------\n");

    while (fgets(linha, LINHA, arquivo) != NULL) {

        id = strtok(linha, ";");
        nome = strtok(NULL, ";");
        preco = strtok(NULL, ";");

        if (id && nome && preco) {
            printf("%s\t%-25s\tR$ %s", id, nome, preco);
        }
    }

    fclose(arquivo);
    arquivo = NULL;
    return 0;
}

int listarbiblioteca(int idLogado) {
    char linha[LINHA];
    char *id, *nome, *preco, *idperfil;
    int idPerfilArq;
    long resultado_long;
    char *endptr;
    FILE *biblioteca;
    char caminhoBib[1024];
    snprintf(caminhoBib, sizeof(caminhoBib), "%s\\%s", DIRETORIO_BASE, "biblioteca.txt");
    biblioteca = fopen(caminhoBib, "r");

    if (biblioteca == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    printf("ID\tJogo\t\t\t\tPreco\n");
    printf("-----------------------------------------------\n");

    while (fgets(linha, LINHA, biblioteca) != NULL) {

        idperfil = strtok(linha, ";");
        id = strtok(NULL, ";");
        nome = strtok(NULL, ";");
        preco = strtok(NULL, ";");
        resultado_long = strtol(idperfil, &endptr, 10);
        int idPerfilArq = (int)resultado_long;

        if (id && nome && preco && idPerfilArq == idLogado) {
            printf("%s\t%-25s\tR$ %s", id, nome, preco);
        }
    }

    fclose(biblioteca);
    return 0;
}

int transferir(int jogo, int idLogado) {
    FILE *destino;
    char linha[LINHA];
    char id[LINHA];

    sprintf(id, "%d", jogo);
    char caminhoBib[1024];
    snprintf(caminhoBib, sizeof(caminhoBib), "%s\\%s", DIRETORIO_BASE, "biblioteca.txt");
    destino = fopen(caminhoBib, "a");

    if (arquivo == NULL || destino == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    while (fgets(linha, LINHA, arquivo) != NULL) {
        if (strncmp(linha, id, strlen(id)) == 0) {

            linha[strcspn(linha, "\n")] = 0; 

            fprintf(destino, "%d;%s\n", idLogado, linha);

            break; 
        }
    }
    fclose(arquivo);
    fclose(destino);
    arquivo = NULL;
    return 0;
}

int validarLogin(char* email, char* senha) {
    char caminhoCompleto[1024];
    const char* NOME_ARQUIVO_DESTA_FUNCAO = "perfis.txt";
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s",
        DIRETORIO_BASE,
        NOME_ARQUIVO_DESTA_FUNCAO);
    
    FILE* arquivo = fopen(caminhoCompleto, "r");
    
    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo de perfis para validacao");
        return 0;
    }

    char linhaBuffer[1024];
    int idDoArquivo;
    char emailDoArquivo[256];
    char senhaDoArquivo[256];

    while (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) != NULL) {
        int camposLidos = sscanf(
            linhaBuffer, "%d; %*[^;]; %255[^;]; %255[^;];",
            &idDoArquivo,
            emailDoArquivo, 
            senhaDoArquivo
        );
        
        if (camposLidos == 3) {
            
            if (strcmp(emailDoArquivo, email) == 0 && strcmp(senhaDoArquivo, senha) == 0) {
                fclose(arquivo);
                return idDoArquivo;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

int obterProximoId(char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        return 1;
    }

    int maiorId = 0;
    int idAtual = 0;
    char linhaBuffer[1024];

    while (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) != NULL) {
        
        if (sscanf(linhaBuffer, "%d;", &idAtual) == 1) {
            if (idAtual > maiorId) {
                maiorId = idAtual;
            }
        }
    }

    fclose(arquivo);

    return maiorId + 1;
}

int emailJaExiste(char* emailParaVerificar) {
    char caminhoCompleto[1024];
    const char* NOME_ARQUIVO_DESTA_FUNCAO = "perfis.txt";
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s",
        DIRETORIO_BASE,
        NOME_ARQUIVO_DESTA_FUNCAO);

    FILE* arquivo = fopen(caminhoCompleto, "r");
    if (arquivo == NULL) {
        return 0; 
    }

    char linhaBuffer[1024];
    char emailExtraido[256];

    while (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) != NULL) {
        if (sscanf(linhaBuffer, "%*d;%*[^;];%255[^;];", emailExtraido) == 1) {
            if (strcmp(emailExtraido, emailParaVerificar) == 0) {
                fclose(arquivo);
                return 1;
            }
        }
    }

    fclose(arquivo);
    return 0;
}

int adicionarPerfil(char* nome, char* email, char* senha) {
    
    if (emailJaExiste(email)) {
        fprintf(stderr, "ERRO: O email '%s' ja esta cadastrado. Perfil nao adicionado.\n", email);
        return 0;
    }

    char caminhoCompleto[1024];
    const char* NOME_ARQUIVO_DESTA_FUNCAO = "perfis.txt";
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s",
        DIRETORIO_BASE,
        NOME_ARQUIVO_DESTA_FUNCAO);

    int novoId = obterProximoId(caminhoCompleto);
    
    FILE* arquivo = fopen(caminhoCompleto, "a");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 0;
    }

    int jogosPadrao = 0;
    int saldoPadrao = 0;

    fprintf(arquivo, "%d;%s;%s;%s;%d;%d\n",
        novoId,
        nome,
        email,
        senha,
        jogosPadrao,
        saldoPadrao);

    fclose(arquivo);

    printf("Perfil para '%s' adicionado com sucesso com o ID %d!\n", nome, novoId);

    return novoId;
}

void exibirPerfilPorId(int idProcurado) {
    char caminhoCompleto[1024];
    const char* NOME_ARQUIVO_DESTA_FUNCAO = "perfis.txt";
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s",
        DIRETORIO_BASE,
        NOME_ARQUIVO_DESTA_FUNCAO);

    FILE* arquivo = fopen(caminhoCompleto, "r");

    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo (exibirPerfilPorId)");
        return;
    }

    char linhaBuffer[1024];
    int perfilEncontrado = 0;

    int idArquivo;
    char nomeArquivo[256];
    char emailArquivo[256];
    char senhaArquivo[256];
    int jogosArquivo;
    int saldoArquivo;

    while (fgets(linhaBuffer, sizeof(linhaBuffer), arquivo) != NULL) {
        if (sscanf(linhaBuffer, "%d;", &idArquivo) == 1) {
            
            if (idArquivo == idProcurado) {
                int camposLidos = sscanf(linhaBuffer, "%d; %255[^;]; %255[^;]; %255[^;]; %d; %d",
                    &idArquivo,
                    nomeArquivo,
                    emailArquivo,
                    senhaArquivo,
                    &jogosArquivo,
                    &saldoArquivo);
                
                if (camposLidos == 6) {
                    printf("\n--- Exibindo Perfil ID %d ---\n", idArquivo);
                    printf("Nome: \t%s\n", nomeArquivo);
                    printf("Email: \t%s\n", emailArquivo);
                    printf("Senha: \t*******\n");
                    printf("Jogos Possuidos: %d\n", jogosArquivo);
                    printf("Saldo em Conta: %d\n", saldoArquivo);
                    printf("---------------------------------\n");
                    
                    perfilEncontrado = 1;
                    break;
                }
            }
        }
    }

    fclose(arquivo);

    if (!perfilEncontrado) {
        printf("\nERRO: Perfil com ID %d nao encontrado.\n", idProcurado);
    }
}

void adicionarSaldo(int id, int valorAdicional){
    char caminhoCompleto[1024];
    const char* NOME_ARQUIVO_DESTA_FUNCAO = "perfis.txt";
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s",
        DIRETORIO_BASE,
        NOME_ARQUIVO_DESTA_FUNCAO);

    FILE* arquivo = fopen(caminhoCompleto, "r+");
    if (arquivo == NULL) {
        perror("ERRO: Não foi possível abrir o arquivo para leitura");
        return;
    }

    long posicaoInicioLinha;
    char linha[1024];
    int idArquivo, jogos, saldo;
    char nome[256], email[256], senha[256];

    while (1) {
        posicaoInicioLinha = ftell(arquivo);
        if (fgets(linha, sizeof(linha), arquivo) == NULL)
            break;

        if (sscanf(linha, "%d;%99[^;];%99[^;];%99[^;];%d;%d",
                   &idArquivo, nome, email, senha, &jogos, &saldo) == 6) {

            if (idArquivo == id) {
                saldo = saldo + valorAdicional;

                fseek(arquivo, posicaoInicioLinha, SEEK_SET);

                fprintf(arquivo, "%d;%s;%s;%s;%d;%d\n",
                        idArquivo, nome, email, senha, jogos, saldo);

                printf("Saldo atualizado: %d\n", saldo);
                fclose(arquivo);
                return;
            }
        }   
    }

    fclose(arquivo);
}

void alterarNome(int idLogado, char* novoNome) {
    char caminhoCompleto[1024];
    char caminhoTemp[1024];
    const char* NOME_ARQUIVO = "perfis.txt";
    const char* NOME_TEMP = "temp_perfis.txt";

    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s", DIRETORIO_BASE, NOME_ARQUIVO);
    snprintf(caminhoTemp, sizeof(caminhoTemp), "%s\\%s", DIRETORIO_BASE, NOME_TEMP);

    FILE* arquivoOrigem = fopen(caminhoCompleto, "r");
    FILE* arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivoOrigem == NULL || arquivoTemp == NULL) {
        perror("ERRO: Nao foi possivel manipular os arquivos");
        if (arquivoOrigem) fclose(arquivoOrigem);
        if (arquivoTemp) fclose(arquivoTemp);
        return;
    }

    char linha[1024];
    int idArquivo, jogos, saldo;
    char nomeAntigo[256], email[256], senha[256];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivoOrigem) != NULL) {
        if (sscanf(linha, "%d;", &idArquivo) == 1) {
            
            if (idArquivo == idLogado) {
                sscanf(linha, "%d;%255[^;];%255[^;];%255[^;];%d;%d", 
                       &idArquivo, nomeAntigo, email, senha, &jogos, &saldo);

                fprintf(arquivoTemp, "%d;%s;%s;%s;%d;%d\n", 
                        idArquivo, novoNome, email, senha, jogos, saldo);
                
                encontrou = 1;
                printf("Nome alterado de '%s' para '%s'.\n", nomeAntigo, novoNome);
            } else {
                fputs(linha, arquivoTemp);
            }
        } else {
            fputs(linha, arquivoTemp);
        }
    }

    fclose(arquivoOrigem);
    fclose(arquivoTemp);

    if (encontrou) {
        remove(caminhoCompleto);
        rename(caminhoTemp, caminhoCompleto);
    } else {
        remove(caminhoTemp);
        printf("ID %d nao encontrado.\n", idLogado);
    }
}

int obterCustoJogo(int idJogo) {
    char caminhoLoja[1024];
    snprintf(caminhoLoja, sizeof(caminhoLoja), "%s\\%s", DIRETORIO_BASE, "loja.txt");

    FILE* arqLoja = fopen(caminhoLoja, "r");
    if (arqLoja == NULL) {
        perror("ERRO: Nao foi possivel abrir loja.txt");
        return -1;
    }

    char linha[256];
    int idLido, custoLido;
    char nomeJogo[200];

    while (fgets(linha, sizeof(linha), arqLoja) != NULL) {
        if (sscanf(linha, "%d;%199[^;];%d", &idLido, nomeJogo, &custoLido) == 3) {
            if (idLido == idJogo) {
                fclose(arqLoja);
                return custoLido;
            }
        }
    }

    fclose(arqLoja);
    return -1;
}

int comprarJogo(int idPerfil, int idJogo) {
    int custoJogo = obterCustoJogo(idJogo);
    if (custoJogo == -1) {
        printf("ERRO: Jogo com ID %d nao encontrado na loja.\n", idJogo);
        return 0;
    }

    char caminhoCompleto[1024];
    char caminhoTemp[1024];
    const char* NOME_ARQUIVO = "perfis.txt";
    const char* NOME_TEMP = "perfis_temp.txt";

    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s\\%s", DIRETORIO_BASE, NOME_ARQUIVO);
    snprintf(caminhoTemp, sizeof(caminhoTemp), "%s\\%s", DIRETORIO_BASE, NOME_TEMP);

    FILE* arquivoOrigem = fopen(caminhoCompleto, "r");
    FILE* arquivoTemp = fopen(caminhoTemp, "w");

    if (arquivoOrigem == NULL || arquivoTemp == NULL) {
        perror("ERRO: Nao foi possivel manipular arquivos de perfil");
        if (arquivoOrigem) fclose(arquivoOrigem);
        if (arquivoTemp) fclose(arquivoTemp);
        return 0;
    }

    char linha[1024];
    int idLido, jogos, saldo;
    char nome[256], email[256], senha[256];
    
    int perfilEncontrado = 0;
    int sucessoCompra = 0;

    while (fgets(linha, sizeof(linha), arquivoOrigem) != NULL) {
        if (sscanf(linha, "%d;%255[^;];%255[^;];%255[^;];%d;%d", 
                   &idLido, nome, email, senha, &jogos, &saldo) == 6) {

            if (idLido == idPerfil) {
                perfilEncontrado = 1;
                if (saldo >= custoJogo) {
                    saldo -= custoJogo;
                    jogos += 1;
                    
                    printf("Compra aprovada! Novo saldo: %d. Total de jogos: %d\n", saldo, jogos);
                    sucessoCompra = 1;

                    fprintf(arquivoTemp, "%d;%s;%s;%s;%d;%d\n", 
                            idLido, nome, email, senha, jogos, saldo);
                } else {
                    printf("ERRO: Saldo insuficiente. (Saldo: %d / Custo: %d)\n", saldo, custoJogo);
                    fputs(linha, arquivoTemp);
                }
            } else {
                fputs(linha, arquivoTemp);
            }
        } else {
            fputs(linha, arquivoTemp);
        }
    }

    fclose(arquivoOrigem);
    fclose(arquivoTemp);

    if (!perfilEncontrado) {
        printf("ERRO: Perfil ID %d nao encontrado.\n", idPerfil);
        remove(caminhoTemp);
        return 0;
    }

    if (sucessoCompra) {
        remove(caminhoCompleto);
        rename(caminhoTemp, caminhoCompleto);
        return 1;
    } else {
        remove(caminhoTemp);
        return 0;
    }
}