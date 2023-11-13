#include "projeto.h"
#include <stdio.h>
#include <string.h>

// Função de cadastro
int cadastrarTarefa(ListaDeTarefas *lt) {

  // Variável para o controle do retorno das funções
  int controle;

  // Lendo a prioridade da tarefa
  printf("Digite a prioridade da tarefa: ");
  scanf("%d", &lt->tarefas[lt->qtd].prioridade);
  // limpar buffer
  getchar();

  // Lendo a descrição da tarefa
  printf("Digite a descricao da tarefa: ");
  scanf(" %[^\n]", lt->tarefas[lt->qtd].descricao);
  // limpar buffer
  getchar();

  // Lendo a categoria da tarefa
  printf("Digite a categoria da tarefa: ");
  scanf(" %[^\n]", lt->tarefas[lt->qtd].categoria);
  // limpar buffer
  getchar();

  controle = estadoTarefa(lt, lt->qtd);
  if (controle != 0) {
    printf("\nErro ao tentar executar a funcao 'estadoTarefa' :(\n");
  }

  // Aumentando a variável do número de structs
  lt->qtd++;

  // Guardando a nova struct em um arquivo binário e verificando retorno da
  // função
  controle = salvarTarefas(lt);
  if (controle != 0) {
    printf("\nErro ao tentar executar a funcao 'salvarTarefa' :(\n");
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função para mudar o estado da tarefa
int estadoTarefa(ListaDeTarefas *lt, int num_tarefa) {

  char escolha;

  printf("\n1 - Nao iniciada;\n2 - Em "
         "andamento;\n3 - Completa;\n\nEscolha o estado da tarefa: ");
  do {
    scanf("%c", &escolha);
    // limpar buffer
    getchar();

    switch (escolha) {
    case '1':
      strcpy(lt->tarefas[num_tarefa].estado, "Nao iniciado");
      break;

    case '2':
      strcpy(lt->tarefas[num_tarefa].estado, "Em andamento");
      break;

    case '3':
      strcpy(lt->tarefas[num_tarefa].estado, "Completa");
      break;

    default:
      printf("\nDigite uma opcao valida: ");
      escolha = '0';
      break;
    }

  } while (escolha == '0');

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função de alteração
int alterarTarefa(ListaDeTarefas *lt) {

  int controle, verifica = 1, escolha;

  // Listando as tarefas e verificando o retorno da função
  controle = listarTarefas(*lt);
  if (controle != 0) {
    printf("\nErro ao tentar executar a funcao listar :(\n");
  }

  // Opção 0 para cancelar a alteracao
  printf("\n0 - Cancelar.\n");

  printf(
      "\nDigite o numero da funcao que deseja alterar ou 0 para cancelar:\n");
  scanf(" %d", &escolha);
  // limpar buffer
  getchar();

  // Cancelando a alteração
  if (escolha == 0) {
    verifica = 0;
    printf("\n\nCancelado!\n");
  }

  // Iniciando a alteração
  else {

    // Percorrendo a ListaDeTarefas e comparando o número digitado com o
    // número da tarefa
    for (int i = 0; i < lt->qtd; i++) { // Laço 1
      if (i + 1 == escolha) {
        char campo;

        printf("\n\nCampos:\n1 - Prioridade;\n2 - Categoria;\n3 - "
               "Descricao;\n4 - Estado;\n");

        // Alterando a tarefa
        printf("\nDigite o numero do campo que deseja alterar: ");
        scanf(" %c", &campo);
        // limpar buffer
        getchar();

        switch (campo) {
        case '1':

          // prioridade
          printf("\nDigite a nova prioridade: ");
          scanf("%d", &lt->tarefas[i].prioridade);
          // limpar buffer
          getchar();
          printf("\n\nTarefa Alterada!\n");
          break;

        case '2':

          // categoria
          printf("\nDigite a nova categoria: ");
          scanf("%[^\n]", lt->tarefas[i].categoria);
          // limpar buffer
          getchar();
          printf("\n\nTarefa Alterada!\n");
          break;

        case '3':

          // descricao
          printf("\nDigite a nova descricao: ");
          scanf("%[^\n]", lt->tarefas[i].descricao);
          // limpar buffer
          getchar();
          printf("\n\nTarefa Alterada!\n");
          break;

        case '4':
          // estado
          controle = estadoTarefa(lt, i);
          if (controle != 0) {
            printf("\nErro ao tentar executar a funcao 'estadoTarefa' :(\n");
          }
          printf("\n\nTarefa Alterada!\n");
          break;

        default:
          printf("\nDigite uma opcao valida!\n");
          break;
        }

        // Atualizando a variável que verifica se a tarefa foi encontrada
        verifica = 0;
        // Saindo do laço 1
        break;
      }
    }
    // Caso a tarefa não seja encontrada
    if (verifica == 1) {
      printf("\n\nTarefa não encontrada\n");
    }

    // Guardando a nova struct em um arquivo binário e verificando retorno da
    // função
    controle = salvarTarefas(lt);
    if (controle != 0) {
      printf("\nErro ao tentar executar a funcao :(\n");
    }
  }
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função de delete
int deletarTarefa(ListaDeTarefas *lt) {

  // Variáveis para: o controle do retorno da função - verificar se a tarefa foi
  // encontrada - ler o número da tarefa a ser deletada
  int controle, verifica = 1, num_tarefa;

  // Listando as tarefas e verificando o retorno da função
  controle = listarTarefas(*lt);
  if (controle != 0) {
    printf("\nErro ao tentar executar a funcao :(\n");
  }

  // Opção 0 para cancelar o delete
  printf("\n0 - Cancelar.\n");

  // Lendo o número da tarefa ou o 0
  printf("\nDigite o numero da tarefa que deseja apagar ou 0 para cancelar: ");
  scanf("%d", &num_tarefa);
  // limpar buffer
  getchar();

  // Cancelando o delete
  if (num_tarefa == 0) {
    verifica = 0;
    printf("\n\nCancelado!\n");
  }

  // Iniciando o delete
  else {

    // Percorrendo a ListaDeTarefas e comparando o número digitado com o
    // número da tarefa
    for (int i = 0; i < lt->qtd; i++) { // Laço 1
      if (i + 1 == num_tarefa) {

        // Atualizando o resto da ListaDeTarefas pelo índice.
        // Adicionando o conteúdo da próxima struct Tarefa (próximo índice da
        // struct ListaDeTarefas) à atual struct Tarefa
        for (int j = i; j < lt->qtd - 1; j++) { // Laço 2
          lt->tarefas[j] = lt->tarefas[j + 1];
        }

        // Reduzindo o número de tarefas
        lt->qtd -= 1;
        printf("\n\nTarefa Apagada!\n");
        // Atualizando a variável que verifica se a tarefa foi encontrada
        verifica = 0;
        // Saindo do laço 1
        break;
      }
    }
  }
  // Caso a tarefa não seja encontrada
  if (verifica == 1) {
    printf("\n\nTarefa não encontrada\n");
  }

  // Guardando a nova struct em um arquivo binário e verificando retorno da
  // função
  controle = salvarTarefas(lt);
  if (controle != 0) {
    printf("\nErro ao tentar executar a funcao :(\n");
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função de lista
int listarTarefas(ListaDeTarefas lt) {

  // Verificando se existe alguma tarefa cadastrada
  if (lt.qtd == 0) {
    printf("\nNao existem tarefas cadastradas.\n");
    return 1;
  }
  // Caso exista
  else {

    int controle;
    char escolha;

    printf("\n1 - Sim;\n2 - Nao;\n\nDeseja filtrar as tarefas? ");
    scanf(" %c", &escolha);
    // limpar buffer
    getchar();

    if (escolha == '1') {

      char esc_filtro;

      printf("\n1 - Prioridade;\n2 - Estado;\n3 - Categoria;\n4 - Prioridade e "
             "Categoria;\n\nDigite qual filtro deseja: ");
      scanf(" %c", &esc_filtro);
      // limpar buffer
      getchar();

      switch (esc_filtro) {

      case '1':

        printf("\nPrioridade:\n");
        // Imprimindo as tarefas e verificando o retorno da função
        controle = filtrar_Prioridade(&lt);
        if (controle != 0) {
          printf("\nErro ao tentar executar a funcao :(\n");
        }

        break;
      case '2':
        printf("\nEstado:\n");
        // Imprimindo as tarefas e verificando o retorno da função
        controle = filtrar_Estado(&lt);
        if (controle != 0) {
          printf("\nErro ao tentar executar a funcao :(\n");
        }

        break;

      case '3':
        printf("\nCategoria:\n");
        // Imprimindo as tarefas e verificando o retorno da função
        controle = filtrar_Categoria(&lt);
        if (controle != 0) {
          printf("\nErro ao tentar executar a funcao :(\n");
        }
        break;

      case '4':
        printf("\n4 - Prioridade e Categoria;\n");
        break;

      default:
        printf("\nDigite uma opcao valida!\n");
        break;
      }
    }

    else if (escolha == '2') {

      // Mostrando a quantidade de tarefas cadastradas
      printf("Quantidade de tarefas: %d\n", lt.qtd);

      // Printando todas as tarefas
      for (int i = 0; i < lt.qtd; i++) {

        // Imprimindo as tarefas e verificando o retorno da função
        controle = imprimirTarefas(&lt, i);
        if (controle != 0) {
          printf("\nErro ao tentar executar a funcao :(\n");
        }
      }
    } else {
      printf("\nOpcao invalida!\n");
    }
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função para printar o menu
void printMenu() {

  // Printando o Menu
  printf("Menu:\n");
  printf("1 - Cadastrar tarefa.\n");
  printf("2 - Deletar tarefa.\n");
  printf("3 - Listar tarefas.\n");
  printf("4 - Alterar tarefas.\n");
  printf("0 - Sair.\n\n");
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função para salvar as structs em um arquivo binário
int salvarTarefas(ListaDeTarefas *lt) {

  // Abrindo o arquivo binário no modo de escrita
  FILE *f = fopen("arquivo.bin", "wb");

  // Verificando se foi possível abrir e escrever o arquivo
  if (f == NULL) {
    printf("Erro ao escrever o arquivo.\n");
    // Caso não seja possível abrir ou escrever o arquivo, retorna 1
    // encerrando a função
    return 1;
  }

  // Escrevendo a struct no arquivo
  fwrite(lt->tarefas, sizeof(Tarefa), lt->qtd, f);
  // Fechando o arquivo
  fclose(f);

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função para ler o arquivo binário e salvar as informações nas structs
int carregarTarefas(ListaDeTarefas *lt) {
  // Abrindo o arquivo binário no modo de leitura
  FILE *f = fopen("arquivo.bin", "rb");

  // Verificando se foi possível abrir e ler o arquivo
  if (f == NULL) {
    // Caso não seja possível abrir ou ler o arquivo, retorna 1 encerrando a
    // função
    return 1;
  }

  // Variável para descobrir o número de tarefas presentes no arquivo
  int i = 0;

  // Armazenando todas as tarefas do arquivo em structs Tarefas dentro da
  // struct ListaDeTarefas
  while (fread(&lt->tarefas[i], sizeof(Tarefa), 1, f) == 1) {
    // Iterando a quantidade de tarefas
    i++;
  }

  // Armazenando o número de tarefas
  lt->qtd = i;

  // Fechando o arquivo
  fclose(f);
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int imprimirTarefas(ListaDeTarefas *lt, int numTarefa) {

  printf("\nTarefa %d:\n", numTarefa + 1); // Número
  printf("Prioridade da tarefa: %d\n",
         lt->tarefas[numTarefa].prioridade); // Prioridade
  printf("Descricao da tarefa: %s\n",
         lt->tarefas[numTarefa].descricao); // Descrição
  printf("Categoria da tarefa: %s\n",
         lt->tarefas[numTarefa].categoria);                        // Categoria
  printf("Estado da tarefa: %s\n", lt->tarefas[numTarefa].estado); // Estado

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int filtrar_Prioridade(ListaDeTarefas *lt) {

  int prioridade, controle;

  printf("\nDigite qual prioridade deseja: ");
  scanf("%d", &prioridade);
  // limpar buffer
  getchar();

  for (int i = 0; i < lt->qtd; i++) {
    if (prioridade == lt->tarefas[i].prioridade) {

      // Imprimindo as tarefas e verificando o retorno da função
      controle = imprimirTarefas(lt, i);
      if (controle != 0) {
        printf("\nErro ao tentar executar a funcao :(\n");
      }
    }
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int filtrar_Estado(ListaDeTarefas *lt) {

  int esc_estado, controle;
  char estado[13];

  printf("\n1 - Nao iniciada;\n2 - Em "
         "andamento;\n3 - Completa;\n\nEscolha o estado da tarefa: ");
  scanf("%d", &esc_estado);
  // limpar buffer
  getchar();

  if (esc_estado == 1) {
    strcpy(estado, "Nao iniciado");
  } else if (esc_estado == 2) {
    strcpy(estado, "Em andamento");
  } else if (esc_estado == 3) {
    strcpy(estado, "Completa");
  } else {
    printf("\nOpcao invalida!\n");
  }

  for (int i = 0; i < lt->qtd; i++) {
    if (!strcmp(estado, lt->tarefas[i].estado)) {
      // Imprimindo as tarefas e verificando o retorno da função
      controle = imprimirTarefas(lt, i);
      if (controle != 0) {
        printf("\nErro ao tentar executar a funcao :(\n");
      }
    }
  }

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

int filtrar_Categoria(ListaDeTarefas *lt) {

  int controle, lista_prioridades[100], qtd_filtro = 0, aux, n;
  char categoria[100];

  // Lendo a categoria da tarefa
  printf("Digite a categoria da tarefa: ");
  scanf(" %[^\n]", categoria);
  // limpar buffer
  getchar();

  for (int i = 0; i < lt->qtd; i++) {
    if (!strcmp(categoria, lt->tarefas[i].categoria)) {

      lista_prioridades[qtd_filtro] = lt->tarefas[i].prioridade;
      qtd_filtro++;
    }
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {

      if (lista_prioridades[j] < lista_prioridades[j + 1]) {
        aux = lista_prioridades[j];
        lista_prioridades[j] = lista_prioridades[j + 1];
        lista_prioridades[j + 1] = aux;
      }
    }
  }


  for (int i = 0; i < qtd_filtro; i++) {

    if (lista_prioridades[i - 1] == lista_prioridades[i]) {
      lista_prioridades[i] = lista_prioridades[i + 1];
      qtd_filtro--;
    }
  }

  for (int i = 0; i < qtd_filtro; i++) {
    for (int j = 0; j < lt->qtd; j++) {
      if (lista_prioridades[i] == lt->tarefas[j].prioridade &&
          !strcmp(categoria, lt->tarefas[j].categoria)) {
        // Imprimindo as tarefas e verificando o retorno da função
        controle = imprimirTarefas(lt, j);
        if (controle != 0) {
          printf("\nErro ao tentar executar a funcao :(\n");
        }
      }
    }
  }

  return 0;
}
