//Pedro Henrique Correia de Oliveira 22.222.009-7
//Turma: 610
//Disciplina: CC2632

//Projeto 3

#include <stdio.h>
#include "projeto.h"

int main(void) {
  
  ListaDeTarefas ListaGeral;
  //Variaveis para ler o comando do usuario e verificar o retorno das funções
  int opcao, controle;

  //Lendo o arquivo e verificando o retorno da função
  controle = carregarTarefas(&ListaGeral);
  if (controle != 0){
        printf("\nErro ao tentar executar a funcao :(\n");
      }

  printf("Bem Vindo ao programa de gerenciamento de tarefas!!!\n\n");

  //Usando um laço de repetição para o Menu
  do {
    //Função de print do menu
    printMenu();

    //Lendo o número da opção desejada
    printf("Digite o numero da opcao desejada: "); 
    scanf("%d",&opcao);
    printf("\n----------------------------------\n\n");

    //Número 1 chama a função cadastrar
    if (opcao == 1){
     printf("Funcao 1 - Cadastrar\n");
      
      //Chamando a função de cadastro e verificando seu retorno
      controle = cadastrarTarefa(&ListaGeral);
      if (controle != 0){
        printf("\nErro ao tentar executar a funcao :(\n");
      }
    }
      
    //Número 2 chama a função deletar
    else if (opcao == 2){
      printf("Funcao 2 - Deletar\n");

      //Chamando a função de delete e verificando seu retorno
      controle = deletarTarefa(&ListaGeral);
      if (controle != 0){
        printf("\nErro ao tentar executar a funcao :(\n");
      }
    }
      
    //Número 3 chama a função listar
    else if (opcao == 3){
      printf("Funcao 3 - Listar\n");

      //Chamando a função de lista e verificando seu retorno
      controle = listarTarefas(ListaGeral);
      if (controle != 0){
        printf("\nErro ao tentar executar a funcao :(\n");
      }
    }
      
    // Número 4 chama a função alterar
    else if (opcao == 4) {
      printf("Funcao 4 - alterar\n");

      // Chamando a função de lista e verificando seu retorno
      controle = alterarTarefa(&ListaGeral);
      if (controle != 0) {
        printf("\nErro ao tentar executar a funcao alterar :(\n");
      }
    }
      
    //Qualquer outro digito além de 0, 1, 2 ou 3 informará ao usuário que a opção escolhida não é válida e repetirá o menu
    else if (opcao != 0){
      printf("Opcao invalida :(\n");
    }

    printf("\n----------------------------------\n\n");

  //Caso o usuário digite 0 o laço acabará
  } while (opcao != 0);
  
  //Mensagem de despedida
  printf("Ate mais :)");
  
  return 0;
}
