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


void toLowerCase(char *);

int validationCarType(char *);

void formartValidation(const char *, void *);

int verificarPlacaExistente(struct Veiculo [], int, char []);

int exibirMenu();

int validarPlaca(char placa[]);

void cadastrarVeiculo(struct Veiculo frota[], int* totalVeiculos);

void consultarVeiculo(struct Veiculo frota[], int totalVeiculos, char placa[]);

void gerarRelatorio(struct Veiculo frota[], int totalVeiculos);

void atualizarQuilometragem(struct Veiculo frota[], int totalVeiculos, char placa[], float novaQuilometragem);


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
                printf("Digite a placa do veiculo: ");
                scanf("%s", placaBusca);
                consultarVeiculo(frota, totalVeiculos, placaBusca);
                break;
            case 3:
                gerarRelatorio(frota, totalVeiculos);
                break;
            case 4:
                printf("Digite a placa do veiculo: ");
                scanf("%s", placaBusca);
                printf("Digite a nova quilometragem: ");
                scanf("%f", &novaQuilometragem);
                atualizarQuilometragem(frota, totalVeiculos, placaBusca, novaQuilometragem);
                break;
            case 5:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao inválida!\n");
        }

    } while (opcao != 5); // Continua até o usuário escolher sair

    return 0; // Finaliza o programa
}


// Exibe o menu principal do sistema e retorna a opção escolhida pelo usuário
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
        printf("Limite de veiculos atingido.\n");
        return;
    }

    struct Veiculo v; // Cria uma variável temporária do tipo Veiculo

    // Valida placa e entra com o valor da placa
    do {
        printf("Digite a placa do veiculo (formato ABC-1234): ");
        formartValidation("%s", v.placa);

        if (verificarPlacaExistente(frota, *totalVeiculos, v.placa)) {
            printf("Placa ja cadastrada! Nao e possível cadastrar o veiculo novamente.\n");
        }

        if (!validarPlaca(v.placa)) {
            printf("Placa invalida! Use o formato ABC-1234.\n");
        }
    } while (!validarPlaca(v.placa) || verificarPlacaExistente(frota, *totalVeiculos, v.placa));

    // Solicita o tipo do veículo

    do {
        printf("Digite o tipo do veiculo (Carro, Moto, Caminhao): ");
        formartValidation("%s", v.tipo);
        if (validationCarType(v.tipo) == 1) {
            printf("Tipo de veiculo invalido!\n");
        }
    }while (validationCarType(v.tipo) == 1);


    do {
        // Solicita o ano de fabricação e valida o intervalo
        printf("Digite o ano de fabricacao (1980 a 2025): ");

        formartValidation("%d", &v.anoFabricacao);

        if (v.anoFabricacao < 1980 || v.anoFabricacao > 2025) {
            printf("Ano invalido!\n");
        }
    }while (v.anoFabricacao < 1980 || v.anoFabricacao > 2025);



    // Solicita a quilometragem atual e valida se é não negativa

    printf("Digite a quilometragem atual: ");
    formartValidation("%f", &v.quilometragem);

    if (v.quilometragem < 0) {
        printf("Quilometragem invalida!\n");
        return;
    }

    // Adiciona o veículo no array da frota
    frota[*totalVeiculos] = v;
    (*totalVeiculos)++; // Atualiza o total de veículos cadastrados

    printf("Veiculo cadastrado com sucesso!\n");
}

// Consulta um veículo pela placa
void consultarVeiculo(struct Veiculo frota[], int totalVeiculos, char placa[]) {
    // Percorre todos os veículos cadastrados
    for (int i = 0; i < totalVeiculos; i++) {
        // Compara as placas para encontrar o veículo
        if (strcmp(frota[i].placa, placa) == 0) {
            // Exibe os dados do veículo encontrado
            printf("\nDADOS DO VEICULO:\n");
            printf("Placa: %s\n", frota[i].placa);
            printf("Tipo: %s\n", frota[i].tipo);
            printf("Ano de Fabricacao: %d\n", frota[i].anoFabricacao);
            printf("Quilometragem: %.2f\n", frota[i].quilometragem);
            return;
        }
    }
    // Se não encontrar
    printf("Veiculo não encontrado.\n");
}

// Gera e exibe o relatório da frota
void gerarRelatorio(struct Veiculo frota[], int totalVeiculos) {
    // Verifica se há veículos cadastrados
    if (totalVeiculos == 0) {
        printf("Nenhum veiculo cadastrado.\n");
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
    printf("Total de veiculos cadastrados: %d\n", totalVeiculos);
    printf("Media de quilometragem: %.2f\n", somaKm / totalVeiculos);
    printf("Veiculo mais antigo: Placa %s, Ano %d\n", placaAntigo, maisAntigo);
    printf("Veiculo mais novo: Placa %s, Ano %d\n", placaNovo, maisNovo);
}

// Atualiza a quilometragem de um veículo específico
void atualizarQuilometragem(struct Veiculo frota[], int totalVeiculos, char placa[], float novaQuilometragem) {
    // Percorre a frota para encontrar o veículo
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(frota[i].placa, placa) == 0) {
            if (novaQuilometragem < 0) {
                printf("Quilometragem invalida!\n");
                return;
            }
            frota[i].quilometragem = novaQuilometragem; // Atualiza a quilometragem
            printf("Quilometragem atualizada com sucesso!\n");
            return;
        }
    }
    // Caso a placa não seja encontrada
    printf("Veiculo nao encontrado.\n");
}



void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

int validationCarType(char *tipo) {

    toLowerCase(tipo);

    if (strcasecmp(tipo, "carro") == 0 || strcasecmp(tipo, "moto") == 0 || strcasecmp(tipo, "caminhao") == 0) {
        return 0; // Válido
    } else {
        return 1; // Inválido
    }


}


void formartValidation(const char *formato, void *variavel) {
    int sucesso;
    do {
        sucesso = scanf(formato, variavel);  // Lê o valor e armazena na variável
        if (sucesso != 1) {
            printf("Entrada invalida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
    } while (sucesso != 1);  // Repete até uma entrada válida ser dada
}


int verificarPlacaExistente(struct Veiculo frota[], int totalVeiculos, char placa[]) {
    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(frota[i].placa, placa) == 0) {
            return 1; // Placa já cadastrada
        }
    }
    return 0; // Placa não encontrada
}
