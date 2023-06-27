#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE_PLACA 8
#define MAX_SIZE_OBS 100
#define MAX_VEICULOS 100

struct Veiculo
{
    char placa[MAX_SIZE_PLACA];
    char marca[50];
    char modelo[50];
    int ano;
    float preco;
    char tipo[10];
    char observacao[MAX_SIZE_OBS];
};

void excluirVeiculo()
{
    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int quantidade;
    fscanf(arquivo, "%d\n", &quantidade);

    char placaPesquisa[MAX_SIZE_PLACA];
    printf("Digite a placa do veiculo a ser excluido: ");
    scanf("%7s", placaPesquisa);

    struct Veiculo veiculos[MAX_VEICULOS];

    int encontrado = 0;

    for (int i = 0; i < quantidade; i++)
    {
        fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%[^;];%[^\n]\n",
               veiculos[i].placa, veiculos[i].marca, veiculos[i].modelo, &(veiculos[i].ano),
               &(veiculos[i].preco), veiculos[i].tipo, veiculos[i].observacao);

        if (strcmp(veiculos[i].placa, placaPesquisa) == 0)
        {
            printf("Veiculo encontrado:\n");
            printf("Placa: %s\n", veiculos[i].placa);
            printf("Marca: %s\n", veiculos[i].marca);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Ano: %d\n", veiculos[i].ano);
            printf("Preco: %.2f\n", veiculos[i].preco);
            printf("Tipo: %s\n", veiculos[i].tipo);
            printf("Observacao: %s\n", veiculos[i].observacao);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado)
    {
        printf("Veiculo nao encontrado.\n");
        return;
    }

    arquivo = fopen("carros.txt", "w");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo para exclusao.\n");
        return;
    }

    fprintf(arquivo, "%d\n", quantidade - 1);

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(veiculos[i].placa, placaPesquisa) != 0)
        {
            fprintf(arquivo, "%s;%s;%s;%d;%.2f;%s;%s\n", veiculos[i].placa, veiculos[i].marca,
                    veiculos[i].modelo, veiculos[i].ano, veiculos[i].preco, veiculos[i].tipo,
                    veiculos[i].observacao);
        }
    }

    fclose(arquivo);

    printf("Veiculo excluido com sucesso.\n");
}

void listarVeiculos()
{
    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int quantidade;
    fscanf(arquivo, "%d\n", &quantidade);

    printf("Total de veiculos cadastrados: %d\n", quantidade);

    struct Veiculo veiculo;

    for (int i = 0; i < quantidade; i++)
    {
        fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%[^;];%[^\n]\n", veiculo.placa, veiculo.marca, veiculo.modelo, &veiculo.ano, &veiculo.preco, veiculo.tipo, veiculo.observacao);

        printf("----------------------------\n");
        printf("Placa: %s\n", veiculo.placa);
        printf("Marca: %s\n", veiculo.marca);
        printf("Modelo: %s\n", veiculo.modelo);
        printf("Ano: %d\n", veiculo.ano);
        printf("Preco: %.2f\n", veiculo.preco);
        printf("Tipo: %s\n", veiculo.tipo);
        printf("Observacao: %s\n", veiculo.observacao);
    }

    fclose(arquivo);
}

void pesquisarVeiculo()
{
    FILE *arquivo = fopen("carros.txt", "r");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int quantidade;
    fscanf(arquivo, "%d\n", &quantidade);

    char placaPesquisa[MAX_SIZE_PLACA];
    printf("Digite a placa do veiculo a ser pesquisado: ");
    scanf("%7s", placaPesquisa);

    struct Veiculo veiculo;
    int encontrado = 0;

    for (int i = 0; i < quantidade; i++)
    {
        fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%[^;];%[^\n]\n", veiculo.placa, veiculo.marca, veiculo.modelo, &veiculo.ano, &veiculo.preco, veiculo.tipo, veiculo.observacao);

        if (strcmp(veiculo.placa, placaPesquisa) == 0)
        {
            printf("\n--------------------");
            printf("\nVeiculo encontrado:\n");
            printf("Placa: %s\n", veiculo.placa);
            printf("Marca: %s\n", veiculo.marca);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Ano: %d\n", veiculo.ano);
            printf("Preco: %.2f\n", veiculo.preco);
            printf("Tipo: %s\n", veiculo.tipo);
            printf("Observacao: %s\n", veiculo.observacao);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
    {
        printf("Veiculo nao encontrado.\n");
    }

    fclose(arquivo);
}

void cadastrarVeiculo()
{
    FILE *arquivo = fopen("carros.txt", "r+");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int quantidade;
    fscanf(arquivo, "%d\n", &quantidade);

    struct Veiculo veiculo;

    printf("Digite a placa do veiculo: ");
    scanf("%7s", veiculo.placa);

    // Verifica se a placa já existe
    struct Veiculo temp;
    int encontrado = 0;
    for (int i = 0; i < quantidade; i++)
    {
        fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%[^;];%[^\n]\n", temp.placa, temp.marca, temp.modelo, &temp.ano, &temp.preco, temp.tipo, temp.observacao);
        if (strcmp(temp.placa, veiculo.placa) == 0)
        {
            encontrado = 1;
            break;
        }
    }

    if (encontrado)
    {
        printf("Placa ja cadastrada. Nao e possivel cadastrar o veiculo.\n");
        fclose(arquivo);
        return;
    }

    printf("Digite a marca do veiculo: ");
    scanf("%99s", veiculo.marca);

    printf("Digite o modelo do veiculo: ");
    scanf("%99s", veiculo.modelo);

    printf("Digite o ano do veiculo: ");
    scanf("%d", &veiculo.ano);

    printf("Digite o preco do veiculo: ");
    scanf("%f", &veiculo.preco);

    printf("Digite o tipo do veiculo (Carro ou Moto): ");
    scanf("%99s", veiculo.tipo);

    printf("Digite uma observacao para o veiculo (opcional): ");
    scanf(" %[^\n]", veiculo.observacao);

    fprintf(arquivo, "%s;%s;%s;%d;%.2f;%s;%s\n", veiculo.placa, veiculo.marca, veiculo.modelo, veiculo.ano, veiculo.preco, veiculo.tipo, veiculo.observacao);

    // Atualiza a quantidade de veiculos
    rewind(arquivo);
    quantidade++;
    fprintf(arquivo, "%d\n", quantidade);

    printf("Veiculo cadastrado com sucesso.\n");

    fclose(arquivo);
}

void editarVeiculo()
{
    FILE *arquivo = fopen("carros.txt", "r+");
    if (arquivo == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int quantidade;
    fscanf(arquivo, "%d\n", &quantidade);

    char placaPesquisa[MAX_SIZE_PLACA];
    printf("Digite a placa do veiculo a ser editado: ");
    scanf("%7s", placaPesquisa);

    struct Veiculo veiculo;
    int encontrado = 0;
    long int posicao = ftell(arquivo);

    for (int i = 0; i < quantidade; i++)
    {
        fscanf(arquivo, "%[^;];%[^;];%[^;];%d;%f;%[^;];%[^\n]\n", veiculo.placa, veiculo.marca, veiculo.modelo, &veiculo.ano, &veiculo.preco, veiculo.tipo, veiculo.observacao);

        if (strcmp(veiculo.placa, placaPesquisa) == 0)
        {
            printf("Veiculo encontrado:\n");
            printf("Placa: %s\n", veiculo.placa);
            printf("Marca: %s\n", veiculo.marca);
            printf("Modelo: %s\n", veiculo.modelo);
            printf("Ano: %d\n", veiculo.ano);
            printf("Preco: %.2f\n", veiculo.preco);
            printf("Tipo: %s\n", veiculo.tipo);
            printf("Observacao: %s\n", veiculo.observacao);
            encontrado = 1;
            break;
        }

        posicao = ftell(arquivo);
    }

    if (!encontrado)
    {
        printf("Veiculo nao encontrado.\n");
        fclose(arquivo);
        return;
    }

    printf("Digite a nova marca do veiculo: ");
    scanf("%99s", veiculo.marca);

    printf("Digite o novo modelo do veiculo: ");
    scanf("%99s", veiculo.modelo);

    printf("Digite o novo ano do veiculo: ");
    scanf("%d", &veiculo.ano);

    printf("Digite o novo preco do veiculo: ");
    scanf("%f", &veiculo.preco);

    printf("Digite o novo tipo do veiculo (Carro ou Moto): ");
    scanf("%99s", veiculo.tipo);

    printf("Digite uma nova observacao para o veiculo (opcional): ");
    scanf(" %[^\n]", veiculo.observacao);

    // Move o ponteiro para a posicao correta
    fseek(arquivo, posicao, SEEK_SET);

    fprintf(arquivo, "%s;%s;%s;%d;%.2f;%s;%s\n", veiculo.placa, veiculo.marca, veiculo.modelo, veiculo.ano, veiculo.preco, veiculo.tipo, veiculo.observacao);

    printf("Veiculo atualizado com sucesso.\n");

    fclose(arquivo);
}

void sairPrograma()
{
    printf("Saindo do programa...\n");
    exit(0);
}

int menu()
{
    int escolha;
    do
    {
        printf("\n=========MENU=========\n");
        printf("1. Listar veiculos\n");
        printf("2. Pesquisar um veiculo\n");
        printf("3. Cadastrar um veiculo\n");
        printf("4. Editar um veiculo\n");
        printf("5. Excluir um veiculo\n");
        printf("6. Sair do programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > 6);

    return escolha;
}

int main()
{
    int opcao;
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            listarVeiculos();
            break;
        case 2:
            pesquisarVeiculo();
            break;
        case 3:
            cadastrarVeiculo();
            break;
        case 4:
            editarVeiculo();
            break;
        case 5:
            excluirVeiculo();
            break;
        case 6:
            sairPrograma();
            break;
        default:
            break;
        }
    } while (opcao != 6);

    return 0;
}
