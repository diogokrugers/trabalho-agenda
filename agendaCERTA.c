#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 31

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

void Adicionar(void **buffer, int *i, int *op, int *numChars, int *numTempChars, int *tamanhoStringTemp, char *tempNome, char *nome, char *stringTemp2){

    for(*i = 0; *i < 3; (*i)++){
        
        switch(*i){
            case 0:
                printf("Digite o nome: (máx 30 caract.): ");
                gets(tempNome);
                    if(strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome)){
                        printf("Não dá pra adicionar essa pessoa, ela já está na agenda...\n");
                        return; 
                    } 
                break;
        
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

void RemoverPessoa(void **buffer, int *i, int *op, int *numChars, int *numTempChars, int *tamanhoStringTemp, char *tempNome, char *nome, char *stringTemp2){
    if(*numChars == 0){
        printf("A agenda está vazia, impossível remover alguém.\n");
        return;
    }

    printf("Quem desejas remover: (buscar pelo nome) (máx 30 caract.): ");
    gets(tempNome);
    *numTempChars = 0;
    *op = 0;

    if(strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome)){
        printf("%s está na agenda e será removido junto com suas informações!\n", tempNome);

        nome = strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome);

        for(*i = 0; *i <3; (*i)++){
            *numTempChars += strlen(nome) + 1;
            nome += (sizeof(char) * (strlen(nome) + 1));
        }
        
        for(*i = (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *tamanhoStringTemp){
        //       ints iniciais      nome temporario              |  enquanto o i < ints iniciais, o nome temporario, o num de chars                     | i pula pro proximo blocão de chars
            if(strcmp(nome, stringTemp2) == 0){
                break;
            }

            *tamanhoStringTemp += strlen(stringTemp2) + 1;
            stringTemp2 += (sizeof(char)) * (strlen(stringTemp2) + 1);
        }
        
        for(*i = (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) * (sizeof(char) * (int)*tamanhoStringTemp); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *op){
            *op += strlen(nome) + 1;
            nome += (sizeof(char) * (strlen(nome) + 1));
        }

        tempNome = strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome);
        memmove(tempNome, nome, sizeof(char) * *op);

        *buffer = (void*) realloc(*buffer, (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + ((sizeof(char) * *numChars) - (sizeof(char) * *numTempChars)));
        
        ArrumarOsPonteiros(buffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2); 
        *numChars = *numChars - *numTempChars;

        printf("Removido!\n");
    }
    else{
        printf("%s não está na agenda, não dá para removê-lo...\n", tempNome);
    }
}

void BuscaPessoa(void **buffer, int *numChars, int *numTempChars, char *tempNome, char *nome){
    if(*numChars == 0){
        printf("A agenda está vazia, não há como buscar ninguém.\n");
        return;
    }
    printf("Quem desejas buscar: (buscar pelo nome) (máx 30 caract.): ");
    gets(tempNome);
    *numTempChars = 0;

    if(strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome)){
        printf("%s está na agenda!\n", tempNome);

        nome = strstr(*buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2), tempNome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));
        printf("Suas outras informações são: \n");

        printf("\tIdade: %s\n", nome);
        *numTempChars += strlen(nome) + 1;
        nome += (sizeof(char) * (strlen(nome) + 1));

        printf("\tEmail: %s\n", nome);
    }
    else{
        printf("%s não está na agenda...\n", tempNome);
    }
}

void ListaTodos(void **buffer, int *i, int *op, int *numChars, int *numTempChars, char *nome){
    if(*numChars == 0){
        printf("A agenda está vazia, não há ninguém para mostrar.\n");
        return;
    }
    *numTempChars = 0;
    *op = 0;

    nome = *buffer + (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2);

    printf("Todas as pessoas na agenda até agora:\n");
    for(*i = (sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2); *i < (int)((sizeof(int) * 5) + (sizeof(char) * TAM_MAX * 2) + (sizeof(char) * *numChars)); *i = *i + *numTempChars){
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
                case 3: BuscaPessoa(&pBuffer, numChars, numTempChars, tempNome, nome);
                        ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
                        break;
                case 4: ListaTodos(&pBuffer, i, op, numChars, numTempChars, nome);
                        ArrumarOsPonteiros(&pBuffer, &i, &op, &numChars, &numTempChars, &tamanhoStringTemp, &tempNome, &stringTemp2);
                        break;
                case 5: printf("Ok, tchau!\n"); 
                        break;
                default: printf("Número inválido! Tente um número de 1-5.\n");
            }
    }while(*op != 5);

    printf("%d", *numChars);
    
    free(pBuffer);

    return 0;
}