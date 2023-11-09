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

  // Lendo a descrição da tarefa
  printf("Digite a descricao da tarefa: ");
  scanf(" %[^\n]", lt->tarefas[lt->qtd].descricao);

  // Lendo a categoria da tarefa
  printf("Digite a categoria da tarefa: ");
  scanf(" %[^\n]", lt->tarefas[lt->qtd].categoria);

  controle = estadoTarefa(lt);
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
int estadoTarefa(ListaDeTarefas *lt) {

  char escolha;

  printf("\nEscolha o estado da tarefa:\n1 - Nao iniciada;\n2 - Em "
         "andamento;\n3 - Completa;\n");
  do {
    scanf(" %c", &escolha);
    // limpar buffer
    getchar();

    switch (escolha) {
    case '1':
      strcpy(lt->tarefas[lt->qtd].estado, "Nao iniciado");
      break;

    case '2':
      strcpy(lt->tarefas[lt->qtd].estado, "Em andamento");
      break;

    case '3':
      strcpy(lt->tarefas[lt->qtd].estado, "Completa");
      break;

    default:
      printf("\nDigite uma opcao valida!\n");
      escolha = '0';
      break;
    }

  } while (escolha == '0');

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------

// Função de delete
int deletarTarefa(ListaDeTarefas *lt) {

  // Variáveis para: o controle do retorno da função - verificar se a tarefa foi
  // encontrada - ler o número da tarefa a ser deletada
  int controle, verifica = 1, num_tarefa;

  // Verificando se existe alguma tarefa cadastrada
  if (lt->qtd == 0) {
    printf("\nNao existem tarefas cadastradas.\n");
  } else {
    // Listando as tarefas e verificando o retorno da função
    controle = listarTarefas(*lt);
    if (controle != 0) {
      printf("\nErro ao tentar executar a funcao :(\n");
    }

    // Opção 0 para cancelar o delete
    printf("\n0 - Cancelar.\n");

    // Lendo o número da tarefa ou o 0
    printf(
        "\nDigite o numero da tarefa que deseja apagarn ou 0 para cancelar: ");
    scanf("%d", &num_tarefa);

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
  }
  // Caso exista
  else {
    // Mostrando a quantidade de tarefas cadastradas
    printf("Quantidade de tarefas: %d\n", lt.qtd);

    // Printando todas as tarefas
    for (int i = 0; i < lt.qtd; i++) {

      printf("\nTarefa %d:\n", i + 1); // Número
      printf("Prioridade da tarefa: %d\n",
             lt.tarefas[i].prioridade); // Prioridade
      printf("Descricao da tarefa: %s\n", lt.tarefas[i].descricao); // Descrição
      printf("Categoria da tarefa: %s\n", lt.tarefas[i].categoria); // Categoria
      printf("Estado da tarefa: %s\n", lt.tarefas[i].estado);    // Estado
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
    // Caso não seja possível abrir ou escrever o arquivo, retorna 1 encerrando
    // a função
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
