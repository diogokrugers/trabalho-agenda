#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddPessoa(char*** ptr){
    for (int i = atoi((*ptr)[2]); i < atoi((*ptr)[2])+3; i++) {
    sprintf((*ptr)[1], "%d", atoi((*ptr)[1])+1); //aumenta em 1 o tamanho da alocação

    *ptr = (char**) realloc((*ptr), sizeof(char*) * atoi((*ptr)[1])); //aloca mais um ponteiro pra char na aloc.
        if((*ptr) == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }

    if(i == atoi((*ptr)[2])){
        printf("Digite o nome (max 30 caract.): ");     //pede input do usuário
        gets((*ptr)[3]);                         //pede input do usuário guardando no TEMPORÁRIO
    }
    else if(i == atoi((*ptr)[2])+1){
        printf("Digite a idade (max 30 caract.): ");    //pede input do usuário
        gets((*ptr)[3]);                         //pede input do usuário guardando no TEMPORÁRIO
    }
    else if(i == atoi((*ptr)[2])+2){
        printf("Digite o e-mail (max 30 caract.): ");    //pede input do usuário
        gets((*ptr)[3]);                         //pede input do usuário guardando no TEMPORÁRIO
    }

    (*ptr)[i] = (char*) malloc(sizeof(char) * strlen((*ptr)[3]) + sizeof(char)); //aloca pra guardar o nome em si
        if((*ptr)[i] == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }
    strcpy((*ptr)[i], (*ptr)[3]); //tira do temporário e guarda direito
    }
    printf("Ok! Adicionado.\n");
    strcpy((*ptr)[2], (*ptr)[1]); //faz a quantidade temporária virar a normal que foi aumentada agora
}

void RemoverPessoa(char** ptr){
    if (strcmp(ptr[1], "4") == 0){
        printf("A agenda está vazia, não há como remover ninguém.\n");
        return;
    }
    printf("Quem você deseja remover (procure pelo nome): ");
    gets(ptr[3]);

    for(int i = 4; i < atoi(ptr[1]); i++){
        if(ptr[i] != NULL){
            if (strcmp(ptr[i], ptr[3]) == 0) {
            free(ptr[i]); free(ptr[i+1]); free(ptr[i+2]);   // libera a memória dessa pessoa e suas informações
            ptr[i] = NULL; ptr[i+1] = NULL; ptr[i+2] = NULL;// coloca as informações dela como nulo por segurança
            printf("Ok! %s, juntamente com sua idade e e-mail foram removidos(as).\n", ptr[3]);
            break;
            }
        }
        if(i == atoi(ptr[1])-1){
          printf("Impossível remover, %s não está na agenda...\n", ptr[3]);
        }
    }
}

void BuscaPessoa(char** ptr){
    if(strcmp(ptr[1], "4") == 0){
        printf("A agenda está vazia, não há como buscar ninguém.\n");
        return;
    }

    printf("Quem você deseja procurar (nome): ");
    gets(ptr[3]);

    for(int i = 4; i < atoi(ptr[1]); i++){
      if(ptr[i] != NULL){
        if (strcmp(ptr[i], ptr[3]) == 0) {
        printf("%s está na agenda! A idade de %s é %s e seu e-mail é %s.\n", ptr[i], ptr[i], ptr[i+1], ptr[i+2]);
        break;
        }
      }
      if(i == atoi(ptr[1])-1){
        printf("%s não está na agenda...\n", ptr[3]);
      }
    }
}

void ListaTodos(char** ptr){
    if(strcmp(ptr[1], "4") == 0){
        printf("A agenda está vazia, não há ninguém para mostrar.\n");
        return;
    }

    printf("Todas as pessoas na agenda até agora:\n");
    strcpy(ptr[0], "0");    // usa o número reservado para operações para contar o número de pessoas
    for(int i = 4; i < atoi(ptr[1]); i = i+3){
        sprintf(ptr[0], "%d", atoi(ptr[0])+1); // soma 1 ao número de pessoas
        if(i > atoi(ptr[1])){
            break;
        }
        if (ptr[i] != NULL) {
        printf("Pessoa %d: Nome: %s\t| Idade: %s\t| E-mail: %s\n", atoi(ptr[0]), ptr[i], ptr[i+1], ptr[i+2]);
        }
    }
}

int main() {
    char **pBuffer = (char**) malloc(sizeof(char*) * 4);    // ALOCA 4 PONTEIROS PARA CHARS, OS DE BAIXO
        if(pBuffer == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }

    pBuffer[0] = (char*) malloc(sizeof(char) * 5);          // NÚMERO RESERVADO PARA OPERAÇÕES
        if(pBuffer[0] == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }

    pBuffer[1] = (char*) malloc(sizeof(char) * 5);          // QUANTIDADE DE ELEMENTOS
        if(pBuffer[1] == NULL){
                printf("Não tem memória o suficiente!\n");
                exit(0);
            }
    strcpy(pBuffer[1], "4");  //só 3 elementos até agora

    pBuffer[2] = (char*) malloc(sizeof(char) * 5);          // QUANTIDADE TEMPORÁRIA DE ELEMENTOS
        if(pBuffer[2] == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }
        strcpy(pBuffer[2], "4");  //só 3 elementos até agora

    pBuffer[3] = (char*) malloc(sizeof(char) * 30);         // NOME TEMPORÁRIO DO ELEMENTO
        if(pBuffer[3] == NULL){
            printf("Não tem memória o suficiente!\n");
            exit(0);
        }

        do{
        printf("--- AGENDA --------------------------------\n1 - Adicionar Pessoa (Nome, Idade e E-Mail)\n2 - Remover Pessoa\n3 - Buscar Pessoa\n4 - Listar Todos\n5 - Sair\n-------------------------------------------\n=>");
        gets(pBuffer[0]);    
            switch(atoi(pBuffer[0])) {
                case 1: AddPessoa(&pBuffer); break;
                case 2: RemoverPessoa(pBuffer); break;
                case 3: BuscaPessoa(pBuffer); break;
                case 4: ListaTodos(pBuffer); break;
                case 5: printf("Ok, tchau!"); break;
                default: printf("Número inválido! Tente um número de 1-5.\n");
            }
        }while(atoi(pBuffer[0]) != 5);

///////////////////////////////////////////////// FREE  
    for (int i = 0; i < atoi(pBuffer[1]); i++) {
        free(pBuffer[i]);
    }
        free(pBuffer);
///////////////////////////////////////////////// FREE 
    return 0;
}