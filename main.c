#include <stdio.h> // Funções de entrada e saída (ex: printf, scanf)
#include <string.h> // Funções para manipulação de strings (ex: strcmp, strcpy, strlen)
#include <locale.h> // Suporte a acentuação e localização (ex: setlocale)
#include <ctype.h>// Testes e manipulação de caracteres (ex: isalpha, isdigit, isupper)

#define TAMANHO_FROTA 100 // Define o tamanho máximo da frota

// Estrutura que representa um veículo da frota
struct Veiculo {
    char placa[10];         // Placa do veículo no formato ABC-1234
    char tipo[20];          // Tipo do veículo (Carro, Moto, Caminhão)
    int anoFabricacao;      // Ano de fabricação do veículo
    float quilometragem;    // Quilometragem atual
};

// Exibe o menu principal do sistema e retorna a opção escolhida pelo usuário
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
    return opcao; // Retorna a opção escolhida
}

// Valida se a placa está no formato correto ABC-1234
int validarPlaca(char placa[]) {
    // Verifica se a placa tem 8 caracteres e o caractere '-' está na posição 3
    if (strlen(placa) != 8 || placa[3] != '-') return 0;

    // Verifica se os três primeiros caracteres são letras maiúsculas
    for (int i = 0; i < 3; i++) {
        if (!isalpha(placa[i]) || !isupper(placa[i])) return 0;
    }

    // Verifica se os quatro últimos caracteres são dígitos numéricos
    for (int i = 4; i < 8; i++) {
        if (!isdigit(placa[i])) return 0;
    }

    return 1; // A placa está válida
}

// Cadastra um novo veículo na frota
void cadastrarVeiculo(struct Veiculo frota[], int* totalVeiculos) {
    // Verifica se já atingiu o limite da frota
    if (*totalVeiculos >= TAMANHO_FROTA) {
        printf("Limite de veículos atingido.\n");
        return;
    }

    struct Veiculo v; // Cria uma variável temporária do tipo Veiculo

    // Solicita a placa e valida o formato
    printf("Digite a placa do veículo (formato ABC-1234): ");
    scanf("%s", v.placa);

    if (!validarPlaca(v.placa)) {
        printf("Placa inválida!\n");
        return;
    }

    // Solicita o tipo do veículo
    printf("Digite o tipo do veículo (Carro, Moto, Caminhão): ");
    scanf("%s", v.tipo);

    // Solicita o ano de fabricação e valida o intervalo
    printf("Digite o ano de fabricação (1980 a 2025): ");
    scanf("%d", &v.anoFabricacao);
    if (v.anoFabricacao < 1980 || v.anoFabricacao > 2025) {
        printf("Ano inválido!\n");
        return;
    }

    // Solicita a quilometragem atual e valida se é não negativa
    printf("Digite a quilometragem atual: ");
    scanf("%f", &v.quilometragem);
    if (v.quilometragem < 0) {
        printf("Quilometragem inválida!\n");
        return;
    }

    // Adiciona o veículo no array da frota
    frota[*totalVeiculos] = v;
    (*totalVeiculos)++; // Atualiza o total de veículos cadastrados

    printf("Veículo cadastrado com sucesso!\n");
}

// Consulta um veículo pela placa
void consultarVeiculo(struct Veiculo frota[], int totalVeiculos, char placa[]) {
    // Percorre todos os veículos cadastrados
    for (int i = 0; i < totalVeiculos; i++) {
        // Compara as placas para encontrar o veículo
        if (strcmp(frota[i].placa, placa) == 0) {
            // Exibe os dados do veículo encontrado
            printf("\nDADOS DO VEÍCULO:\n");
            printf("Placa: %s\n", frota[i].placa);
            printf("Tipo: %s\n", frota[i].tipo);
            printf("Ano de Fabricação: %d\n", frota[i].anoFabricacao);
            printf("Quilometragem: %.2f\n", frota[i].quilometragem);
            return;
        }
    }
    // Se não encontrar
    printf("Veículo não encontrado.\n");
}

// Gera e exibe o relatório da frota
void gerarRelatorio(struct Veiculo frota[], int totalVeiculos) {
    // Verifica se há veículos cadastrados
    if (totalVeiculos == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    float somaKm = 0;
    int maisAntigo = frota[0].anoFabricacao;
    int maisNovo = frota[0].anoFabricacao;
    char placaAntigo[10], placaNovo[10];

    // Inicializa com o primeiro veículo da frota
    strcpy(placaAntigo, frota[0].placa);
    strcpy(placaNovo, frota[0].placa);

    // Percorre todos os veículos para coletar os dados
    for (int i = 0; i < totalVeiculos; i++) {
        somaKm += frota[i].quilometragem; // Soma total da quilometragem

        // Verifica o veículo mais antigo
        if (frota[i].anoFabricacao < maisAntigo) {
            maisAntigo = frota[i].anoFabricacao;
            strcpy(placaAntigo, frota[i].placa);
        }

        // Verifica o mais novo
        if (frota[i].anoFabricacao > maisNovo) {
            maisNovo = frota[i].anoFabricacao;
            strcpy(placaNovo, frota[i].placa);
        }
    }

    // Exibe os resultados do relatório
    printf("\nRELATÓRIO DA FROTA\n");
    printf("Total de veículos cadastrados: %d\n", totalVeiculos);
    printf("Média de quilometragem: %.2f\n", somaKm / totalVeiculos);
    printf("Veículo mais antigo: Placa %s, Ano %d\n", placaAntigo, maisAntigo);
    printf("Veículo mais novo: Placa %s, Ano %d\n", placaNovo, maisNovo);
}

// Atualiza a quilometragem de um veículo específico
void atualizarQuilometragem(struct Veiculo frota[], int totalVeiculos, char placa[], float novaQuilometragem) {
    // Percorre a frota para encontrar o veículo
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(frota[i].placa, placa) == 0) {
            if (novaQuilometragem < 0) {
                printf("Quilometragem inválida!\n");
                return;
            }
            frota[i].quilometragem = novaQuilometragem; // Atualiza a quilometragem
            printf("Quilometragem atualizada com sucesso!\n");
            return;
        }
    }
    // Caso a placa não seja encontrada
    printf("Veículo não encontrado.\n");
}

// Função principal que controla o sistema
int main() {
    setlocale(LC_ALL, ""); // Ativa suporte a acentuação no terminal (Windows)

    struct Veiculo frota[TAMANHO_FROTA]; // Array que armazena todos os veículos
    int totalVeiculos = 0;               // Contador de veículos cadastrados
    int opcao;                           // Armazena a opção do menu
    char placaBusca[10];                // Armazena a placa digitada para consulta ou atualização
    float novaQuilometragem;            // Armazena nova quilometragem

    // Loop principal do sistema
    do {
        opcao = exibirMenu(); // Exibe menu e recebe opção

        switch (opcao) {
            case 1:
                cadastrarVeiculo(frota, &totalVeiculos);
                break;
            case 2:
                printf("Digite a placa do veículo: ");
                scanf("%s", placaBusca);
                consultarVeiculo(frota, totalVeiculos, placaBusca);
                break;
            case 3:
                gerarRelatorio(frota, totalVeiculos);
                break;
            case 4:
                printf("Digite a placa do veículo: ");
                scanf("%s", placaBusca);
                printf("Digite a nova quilometragem: ");
                scanf("%f", &novaQuilometragem);
                atualizarQuilometragem(frota, totalVeiculos, placaBusca, novaQuilometragem);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 5); // Continua até o usuário escolher sair

    return 0; // Finaliza o programa
}
