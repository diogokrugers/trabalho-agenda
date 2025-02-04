#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 31
/*
====================
ArrumarOsPonteiros
  Pega todos os ponteiros usados no código
  e faz eles serem apontados para os seus
  devidos lugares na memória alocada.
====================
*/
void ArrumarOsPonteiros(void **buffer, int **i, int **op, int **numChars, int **numTempChars, int **tamanhoStringTemp, char **tempNome, char **stringTemp2){
    *i                   = *buffer;
    *op                  = *buffer + sizeof(int);
    *numChars            = *buffer + (sizeof(int) * 2);
    *numTempChars        = *buffer + (sizeof(int) * 3);
    *tamanhoStringTemp   = *buffer + (sizeof(int) * 4);
    *tempNome            = *buffer + (sizeof(int) * 5);
    *stringTemp2         = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX);
    return;
}

/*
====================
Adicionar
  Adiciona uma pessoa, juntamente com
  as suas informações, como idade e
  email, à agenda.
====================
*/
void Adicionar(void **buffer, int *i, int *op, int *numChars, int *numTempChars, int *tamanhoStringTemp, char *tempNome, char *nome, char *stringTemp2){
    *numTempChars = 0;
    *op = 0;
    nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2);
    for(*i = 0; *i < 3; (*i)++){
        
        switch(*i){
            case 0:
                printf("Digite o nome: (máx 30 caract.): ");
                gets(tempNome);
                //   op sendo usado como i
                //   op = ints iniciais     +  chars iniciais             |  op < ints iniciais           + chars iniciais               +  numero de chars           |  op = próxima string
                for( *op = (sizeof(int) * 5 ) + (sizeof(char) * TAM_MAX * 2); *op < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *op = *op + *numTempChars){
                    if( strcmp(nome, tempNome) == 0 ){
                        printf("Não dá pra adicionar essa pessoa, ela já está na agenda...\n");
                        return; //ESSA PESSOA JÁ EXISTE, SAI DA FUNÇÃO
                    }
                    *numTempChars += strlen(nome) + 1; // numTempChars SOMA-SE COM TAMANHO DO NOME
                    nome += (sizeof(char) * (strlen(nome) + 1)); // NOME PASSA PRO PRÓX. NOME
                }  //PROCURA PELA MEMORIA ATÉ ACHAR A PESSOA, SE ACHAR, SAI                                    
                break; //SE CHEGAR AQUI, O NOME NÃO EXISTE NA MEMÓRIA   
        
            case 1:
                printf("Digite a idade: (máx 30 caract.): ");
                gets(tempNome);
                break;

            case 2:
                printf("Digite o email: (máx 30 caract.): ");
                gets(tempNome); 
                break;
        }   
        
        *buffer = (void*) realloc(*buffer, (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars) + (sizeof(char) * (strlen(tempNome) + 1)));
        ArrumarOsPonteiros(&*buffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2); 

        nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars);
        *numChars = *numChars + strlen(tempNome) + 1;  

        strcpy(nome, tempNome);
        nome[strlen(tempNome)] = '\0'; 
    }
    printf("Adicionado!\n");
}

/*
====================
RemoverPessoa
  Remove uma pessoa da agenda
  junto com todas as suas informações,
  movendo toda a memória na frente dessa
  pessoa para onde essa pessoa ficava.
====================
*/
void RemoverPessoa(void **buffer, int *i, int *op, int *numChars, int *numTempChars, int *tamanhoStringTemp, char *tempNome, char *nome, char *stringTemp2){
    if( *numChars == 0 ){
        printf("A agenda está vazia, impossível remover alguém.\n");
        return;
    }

    printf("Quem desejas remover: (buscar pelo nome) (máx 30 caract.): ");
    gets(tempNome);
    *numTempChars = 0;
    *op = 0;

nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2);

//   i =  ints iniciais       chars iniciais             |  i < tamanho total da memoria                                                            |  i passa pra próxima string
for(*i = (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *numTempChars){
    if( strcmp(nome, tempNome) == 0 ){
        printf("%s está na agenda e será removido junto com suas informações!\n", tempNome); //ACHOU!!!

        *tamanhoStringTemp = *numTempChars;
        *numTempChars = 0;
        for( *op = 0; (*op < 3); (*op)++ ){
            *numTempChars += strlen(nome) + 1; // numTempChars SOMA-SE COM O TAMANHO DO NOME
            nome += (sizeof(char) * (strlen(nome) + 1)); // PASSA PRO PRÓXIMO NOME
        } //numTempChars COMEÇA A TER O TAMANHO A SER TIRADO

            stringTemp2 = tempNome; //stringTemp2 vira o nome, para calcular o tamanho a ser movido

            //    op = ints iniciais        chars iniciais                 tempNome                           |  op < ints iniciais             chars iniciais                  quantidade de chars total |    op pula pra proxima string
            for( *op = (sizeof(int) * 5 ) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *tamanhoStringTemp); *op < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); (*op) = *op + *tamanhoStringTemp){
                *tamanhoStringTemp += strlen(stringTemp2) + 1; //tamanhoStrinTemp2 se soma com o tamanho da string que ele está
                stringTemp2 += sizeof(char) * strlen(stringTemp2) + 1; //stringTemp2 passa pra próxima string
            } 
            *tamanhoStringTemp = *tamanhoStringTemp - *numTempChars;
            // tamanhoStringTemp COMEÇA A TER O TAMANHO A SER MOVIDO

            memmove(tempNome, nome, sizeof(char) * *tamanhoStringTemp);

        //                        pBuffer   ints iniciais    +  chars iniciais              + numChars - numTempChars               
        *buffer = (void*) realloc(*buffer, (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + ((sizeof(char) * *numChars) - (sizeof(char) * *numTempChars)));

        ArrumarOsPonteiros(buffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2); 
        *numChars = *numChars - *numTempChars;

        printf("Removido!\n");
        return; //ESSA PESSOA FOI REMOVIDA
    }
    //NOME FICA PULANDO PRO PRÓXIMO ATÉ ACHAR A PESSOA
    *numTempChars += strlen(nome) + 1; // numTempChars SOMA-SE COM TAMANHO DO NOME
    nome += (sizeof(char) * (strlen(nome) + 1)); // NOME PASSA PRO PRÓX. NOME

}  //PROCURA PELA MEMORIA ATÉ ACHAR A PESSOA                                

printf("%s não está na agenda...\n", tempNome);
}

/*
====================
BuscaPessoa
  Baseado na escolha do usuário,
  busca uma pessoa, mostrando se
  ela está ou não na agenda, caso 
  estiver, mostra também suas informações.
====================
*/
void BuscaPessoa(void **buffer, int *i, int *numChars, int *numTempChars, char *tempNome, char *nome){
    if( *numChars == 0 ){
        printf("A agenda está vazia, não há como buscar ninguém.\n");
        return;
    }

    printf("Quem desejas buscar: (buscar pelo nome) (máx 30 caract.): ");
    gets(tempNome);
    *numTempChars = 0;
    nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2);

for(*i = (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *numTempChars){
    if( strcmp(nome, tempNome) == 0 ){
        printf("%s está na agenda!\n", tempNome); //ACHOU!!!

        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));
        printf("Suas outras informações são: \n");

        printf("\tIdade: %s\n", nome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));

        printf("\tEmail: %s\n", nome);
        return; //ESSA PESSOA EXISTE
    }

    *numTempChars += strlen(nome) + 1; // numTempChars SOMA-SE COM TAMANHO DO NOME
    nome += (sizeof(char) * (strlen(nome) + 1)); // NOME PASSA PRO PRÓX. NOME

}  //PROCURA PELA MEMORIA ATÉ ACHAR A PESSOA                                

printf("%s não está na agenda...\n", tempNome);       
}

/*
====================
ListaTodos
  Lista todas as pessoas presentes
  até o momento na agenda, junto com
  todas as suas informações.
====================
*/
void ListaTodos(void **buffer, int *i, int *op, int *numChars, int *numTempChars, char *nome){
    if( *numChars == 0 ){
        printf("A agenda está vazia, não há ninguém para mostrar.\n");
        return;
    }
    *numTempChars = 0;
    *op = 0;

    nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2);

    printf("Todas as pessoas na agenda até agora:\n");

    //   i = ints iniciais     +  chars iniciais             |  i < ints iniciais           + chars iniciais               +  numero de chars           |  i = próxima string
    for( *i = (sizeof(int) * 5 ) + (sizeof(char) * TAM_MAX * 2); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *numTempChars){
        (*op)++; 
        printf("Pessoa %d: \n", *op);

        printf("\tNome: %s\n", nome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));

        printf("\tIdade: %s\n", nome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));

        printf("\tEmail: %s\n", nome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));
    }
}

/*
====================
main
  Onde ocorre a alocação da memória principal,
  o usuário escolhe as operações que ele deseja
  fazer em questão à agenda, e onde a memória é liberada. 
====================
*/
int main() {
  void *pBuffer = (void*) malloc((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2));
  
  int *i, *op, *numChars, *numTempChars, *tamanhoStringTemp;           
  char *tempNome, *nome, *stringTemp2;
  
  ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
  nome = NULL;
  *numChars = 0;
  *numTempChars = 0;
  
  do{
      printf("--- AGENDA --------------------------------\n1 - Adicionar Pessoa (Nome, Idade e E-Mail)\n2 - Remover Pessoa\n3 - Buscar Pessoa\n4 - Listar Todos\n5 - Sair\n-------------------------------------------\n=>");
      scanf("%d", op);
      getchar();
          switch(*op){
              case 1: Adicionar(&pBuffer, i, op, numChars, numTempChars, tamanhoStringTemp, tempNome, nome, stringTemp2);
                      ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2); 
                      break;
              case 2: RemoverPessoa(&pBuffer, i, op, numChars, numTempChars, tamanhoStringTemp, tempNome, nome, stringTemp2);
                      ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
                      break;
              case 3: BuscaPessoa(&pBuffer, i, numChars, numTempChars, tempNome, nome);
                      ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
                      break;
              case 4: ListaTodos(&pBuffer, i, op, numChars, numTempChars, nome);
                      ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
                      break;
              case 5: printf("Ok, tchau!\n"); 
                      break;
              default: printf("Número inválido! Tente um número de 1-5.\n");
          }
  }while( *op != 5 );

  free(pBuffer);

  return 0;
}