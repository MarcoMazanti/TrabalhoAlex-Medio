#include <stdio.h>      // Biblioteca para entrada e saída de dados (printf, scanf)
#include <string.h>     // Biblioteca para manipulação de strings
#include <ctype.h>      // Biblioteca para manipulação de caracteres (ex: tolower)
#include <locale.h>     // Biblioteca para configuração regional (ex: acentuação)

#define MAX_VEICULOS 100  // Define o máximo de veículos que podem ser cadastrados

// Estrutura que representa os dados de um veículo
typedef struct {
    char placa[11];         // Placa do veículo (ex: ABC1234)
    char tipo[10];          // Tipo (Carro, Moto, Caminhão)
    int anoFabricacao;      // Ano de fabricação
    float quilometragem;    // Quilometragem atual
} Veiculo;

// Declaração das funções
int exibirMenu();
void cadastrarVeiculo(Veiculo frota[], int *total);
void consultarVeiculo(Veiculo frota[], int total, char placa[]);
void gerarRelatorio(Veiculo frota[], int total);
void atualizarQuilometragem(Veiculo frota[], int total, char placa[], float novaKm);
int validarPlaca(char placa[]);
int validarTipo(char tipo[]);
int validarAno(int ano);
int encontrarVeiculo(Veiculo frota[], int total, char placa[]);

int main() {
    setlocale(LC_ALL, "");  // Ativa suporte à acentuação com base na configuração do sistema

    Veiculo frota[MAX_VEICULOS]; // Vetor que armazena os veículos
    int total = 0;               // Contador de veículos cadastrados
    int opcao;                   // Variável para armazenar a opção escolhida

    do {
        opcao = exibirMenu();  // Mostra o menu e armazena a escolha do usuário

        char placa[11];        // Para entrada da placa
        float novaKm;          // Para nova quilometragem

        switch (opcao) {
            case 1:
                cadastrarVeiculo(frota, &total);  // Cadastra novo veículo
                break;
            case 2:
                printf("Digite a placa do veículo: ");
                scanf("%s", placa);
                consultarVeiculo(frota, total, placa);  // Consulta veículo pela placa
                break;
            case 3:
                gerarRelatorio(frota, total);  // Mostra relatório da frota
                break;
            case 4:
                printf("Digite a placa do veículo: ");
                scanf("%s", placa);
                printf("Digite a nova quilometragem: ");
                scanf("%f", &novaKm);
                atualizarQuilometragem(frota, total, placa, novaKm);  // Atualiza KM
                break;
            case 5:
                printf("Encerrando o programa...\n");  // Sai do programa
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);  // Repete até o usuário escolher sair

    return 0;
}

// Função que mostra o menu principal e retorna a escolha
int exibirMenu() {
    int opcao;
    printf("\n=== SISTEMA DE GERENCIAMENTO DE FROTA ===\n");
    printf("1. Cadastrar veículo\n");
    printf("2. Consultar veículo\n");
    printf("3. Gerar relatório da frota\n");
    printf("4. Atualizar quilometragem\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

// Função para cadastrar novo veículo
void cadastrarVeiculo(Veiculo frota[], int *total) {
    if (*total >= MAX_VEICULOS) {
        printf("Limite máximo de veículos atingido!\n");
        return;
    }

    Veiculo v;

    printf("Digite a placa do veículo (formato ABC1234): ");
    scanf("%s", v.placa);
    if (!validarPlaca(v.placa)) {
        printf("Placa inválida!\n");
        return;
    }

    printf("Digite o tipo do veículo (Carro, Moto ou Caminhão): ");
    scanf("%s", v.tipo);
    if (!validarTipo(v.tipo)) {
        printf("Tipo inválido! Use Carro, Moto ou Caminhão.\n");
        return;
    }

    printf("Digite o ano de fabricação (1980 a 2025): ");
    scanf("%d", &v.anoFabricacao);
    if (!validarAno(v.anoFabricacao)) {
        printf("Ano de fabricação inválido!\n");
        return;
    }

    printf("Digite a quilometragem atual: ");
    scanf("%f", &v.quilometragem);
    if (v.quilometragem <= 0) {
        printf("Quilometragem inválida!\n");
        return;
    }

    frota[*total] = v;   // Adiciona veículo no vetor
    (*total)++;          // Atualiza o total de veículos
    printf("Veículo cadastrado com sucesso!\n");
}

// Função para consultar um veículo pela placa
void consultarVeiculo(Veiculo frota[], int total, char placa[]) {
    int i = encontrarVeiculo(frota, total, placa);
    if (i == -1) {
        printf("Veículo não encontrado!\n");
        return;
    }

    printf("=== DADOS DO VEÍCULO ===\n");
    printf("Placa: %s\n", frota[i].placa);
    printf("Tipo: %s\n", frota[i].tipo);
    printf("Ano de fabricação: %d\n", frota[i].anoFabricacao);
    printf("Quilometragem: %.1f km\n", frota[i].quilometragem);
}

// Gera relatório com estatísticas da frota
void gerarRelatorio(Veiculo frota[], int total) {
    if (total == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    float somaKm = 0;
    int maisAntigo = 0, maisNovo = 0;

    for (int i = 0; i < total; i++) {
        somaKm += frota[i].quilometragem;

        if (frota[i].anoFabricacao < frota[maisAntigo].anoFabricacao)
            maisAntigo = i;

        if (frota[i].anoFabricacao > frota[maisNovo].anoFabricacao)
            maisNovo = i;
    }

    printf("=== RELATÓRIO DA FROTA ===\n");
    printf("Total de veículos: %d\n", total);
    printf("Média de quilometragem: %.1f km\n", somaKm / total);
    printf("Veículo mais antigo: %s (%d)\n", frota[maisAntigo].placa, frota[maisAntigo].anoFabricacao);
    printf("Veículo mais novo: %s (%d)\n", frota[maisNovo].placa, frota[maisNovo].anoFabricacao);
}

// Atualiza a quilometragem do veículo
void atualizarQuilometragem(Veiculo frota[], int total, char placa[], float novaKm) {
    int i = encontrarVeiculo(frota, total, placa);
    if (i == -1) {
        printf("Veículo não encontrado!\n");
        return;
    }

    if (novaKm < frota[i].quilometragem) {
        printf("Erro: nova quilometragem não pode ser menor que a atual.\n");
        return;
    }

    frota[i].quilometragem = novaKm;
    printf("Quilometragem atualizada com sucesso!\n");
}

// Verifica se a placa é válida (mínimo 7 caracteres)
int validarPlaca(char placa[]) {
    return strlen(placa) >= 7;
}

// Valida se o tipo é Carro, Moto ou Caminhão (case insensitive)
int validarTipo(char tipo[]) {
    char tipoFormatado[10];
    for (int i = 0; i < strlen(tipo); i++) {
        tipoFormatado[i] = tolower(tipo[i]);
    }
    tipoFormatado[strlen(tipo)] = '\0';

    return (strcmp(tipoFormatado, "carro") == 0 ||
            strcmp(tipoFormatado, "moto") == 0 ||
            strcmp(tipoFormatado, "caminhão") == 0);
}

// Verifica se o ano está no intervalo permitido
int validarAno(int ano) {
    return ano >= 1980 && ano <= 2025;
}

// Procura veículo pela placa e retorna índice (ou -1 se não encontrado)
int encontrarVeiculo(Veiculo frota[], int total, char placa[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(frota[i].placa, placa) == 0)
            return i;
    }
    return -1;
}
