// Definindo a struct de tarefas
typedef struct {
  int prioridade;
  char categoria[100];
  char descricao[300];
  char estado[13];
} Tarefa; // Nomeando este tipo de struct como: Tarefa

// Definindo a struct que conterá as structs Tarefa
typedef struct {
  Tarefa tarefas[100];
  int qtd;
} ListaDeTarefas; // Nomeando este tipo de struct como: ListaDeTarefas

// Função para cadastrar tarefas, que recebe um ponteiro de ListaDeTarefas como
// parâmetro e retorna um inteiro
int cadastrarTarefa(ListaDeTarefas *lt);

// Função para adicionar/modificar o estado da tarefa, que recebe um
// ponteiro de ListaDeTarefas como parâmetro e retorna um inteiro
int estadoTarefa(ListaDeTarefas *lt, int num_tarefa);

// Função para alterar algum dado da tarefa, que recebe um
// ponteiro de ListaDeTarefas como parâmetro e retorna um inteiro
int alterarTarefa(ListaDeTarefas *lt);

// Função para deletar tarefas, que recebe um ponteiro de ListaDeTarefas como
// parâmetro e retorna um inteiro
int deletarTarefa(ListaDeTarefas *lt);

// Função para deletar tarefas, que recebe uma struct ListaDeTarefas como
// parâmetro e retorna um inteiro
int listarTarefas(ListaDeTarefas lt);

// Função para imprimir o menu, sem parâmetros e sem retorno
void printMenu();

// Função para salvar tarefas em um arquivo binário, que recebe um ponteiro de
// ListaDeTarefas como parâmetro e retorna um inteiro
int salvarTarefas(ListaDeTarefas *lt);

// Função para salvar tarefas lidas de um arquivo binário, que recebe um
// ponteiro de ListaDeTarefas como parâmetro e retorna um inteiro
int carregarTarefas(ListaDeTarefas *lt);
