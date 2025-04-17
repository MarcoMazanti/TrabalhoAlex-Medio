#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_VEICULOS 100

typedef struct {
    char placa[11];
    char tipo[10];
    int anoFabricacao;
    float quilometragem;
} Veiculo;

int exibirMenu();
void cadastrarVeiculo(Veiculo frota[], int *total);
void consultarVeiculo(Veiculo frota[], int total, char placa[]);
void gerarRelatorio(Veiculo frota[], int total);
void atualizarQuilometragem(Veiculo frota[], int total, char placa[], float novaKm);
int validarPlaca(char placa[]);
int validarAno(int ano);
int encontrarVeiculo(Veiculo frota[], int total, char placa[]);

int main() {
    setlocale(LC_ALL, "");

    Veiculo frota[MAX_VEICULOS];
    int total = 0;
    int opcao;

    do {
        opcao = exibirMenu();

        char placa[11];
        float novaKm;

        switch (opcao) {
            case 1:
                cadastrarVeiculo(frota, &total);
                break;
            case 2:
                printf("Digite a placa do veiculo: ");
                scanf("%s", placa);
                consultarVeiculo(frota, total, placa);
                break;
            case 3:
                gerarRelatorio(frota, total);
                break;
            case 4:
                printf("Digite a placa do veiculo: ");
                scanf("%s", placa);
                printf("Digite a nova quilometragem: ");
                scanf("%f", &novaKm);
                atualizarQuilometragem(frota, total, placa, novaKm);
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

int exibirMenu() {
    int opcao;
    printf("\n=== SISTEMA DE GERENCIAMENTO DE FROTA ===\n");
    printf("1. Cadastrar veiculo\n");
    printf("2. Consultar veiculo\n");
    printf("3. Gerar relatorio da frota\n");
    printf("4. Atualizar quilometragem\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void cadastrarVeiculo(Veiculo frota[], int *total) {
    if (*total >= MAX_VEICULOS) {
        printf("Limite maximo de veiculos atingido!\n");
        return;
    }

    Veiculo v;

    // Valida placa
    do {
        printf("Digite a placa do veiculo (formato ABC1234): ");
        scanf("%s", v.placa);
        if (!validarPlaca(v.placa)) {
            printf("Placa invalida! Use o formato ABC1234.\n");
        }
    } while (!validarPlaca(v.placa));

    // Menu de selecao do tipo
    int opcaoTipo;
    do {
        printf("Selecione o tipo do veiculo:\n");
        printf("1. Carro\n");
        printf("2. Moto\n");
        printf("3. Caminhao\n");
        printf("Opcao: ");
        scanf("%d", &opcaoTipo);

        switch (opcaoTipo) {
            case 1:
                strcpy(v.tipo, "Carro");
                break;
            case 2:
                strcpy(v.tipo, "Moto");
                break;
            case 3:
                strcpy(v.tipo, "Caminhao");
                break;
            default:
                printf("Opcao invalida! Selecione 1, 2 ou 3.\n");
                opcaoTipo = 0;
        }
    } while (opcaoTipo < 1 || opcaoTipo > 3);

    // Valida ano
    do {
        printf("Digite o ano de fabricacao (1980 a 2025): ");
        scanf("%d", &v.anoFabricacao);
        if (!validarAno(v.anoFabricacao)) {
            printf("Ano invalido! Deve estar entre 1980 e 2025.\n");
        }
    } while (!validarAno(v.anoFabricacao));

    // Valida quilometragem
    do {
        printf("Digite a quilometragem atual: ");
        scanf("%f", &v.quilometragem);
        if (v.quilometragem <= 0) {
            printf("Quilometragem invalida! Deve ser positiva.\n");
        }
    } while (v.quilometragem <= 0);

    frota[*total] = v;
    (*total)++;
    printf("Veiculo cadastrado com sucesso!\n");
}

void consultarVeiculo(Veiculo frota[], int total, char placa[]) {
    int i = encontrarVeiculo(frota, total, placa);
    if (i == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    printf("=== DADOS DO VEICULO ===\n");
    printf("Placa: %s\n", frota[i].placa);
    printf("Tipo: %s\n", frota[i].tipo);
    printf("Ano de fabricacao: %d\n", frota[i].anoFabricacao);
    printf("Quilometragem: %.1f km\n", frota[i].quilometragem);
}

void gerarRelatorio(Veiculo frota[], int total) {
    if (total == 0) {
        printf("Nenhum veiculo cadastrado.\n");
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

    printf("=== RELATORIO DA FROTA ===\n");
    printf("Total de veiculos: %d\n", total);
    printf("Media de quilometragem: %.1f km\n", somaKm / total);
    printf("Veiculo mais antigo: %s (%d)\n", frota[maisAntigo].placa, frota[maisAntigo].anoFabricacao);
    printf("Veiculo mais novo: %s (%d)\n", frota[maisNovo].placa, frota[maisNovo].anoFabricacao);
}

void atualizarQuilometragem(Veiculo frota[], int total, char placa[], float novaKm) {
    int i = encontrarVeiculo(frota, total, placa);
    if (i == -1) {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    if (novaKm < frota[i].quilometragem) {
        printf("Erro: nova quilometragem nao pode ser menor que a atual.\n");
        return;
    }

    frota[i].quilometragem = novaKm;
    printf("Quilometragem atualizada com sucesso!\n");
}

int validarPlaca(char placa[]) {
    if (strlen(placa) != 7)
        return 0;
    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i])) return 0;
    }
    for (int i = 3; i < 7; i++) {
        if (!isdigit(placa[i])) return 0;
    }
    return 1;
}

int validarAno(int ano) {
    return ano >= 1980 && ano <= 2025;
}

int encontrarVeiculo(Veiculo frota[], int total, char placa[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(frota[i].placa, placa) == 0)
            return i;
    }
    return -1;
}
