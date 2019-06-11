#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

#define BUFFER_LENGHT 100

static char tarefa[BUFFER_LENGHT];

int main()
{
    int abrir_arquivo, escrever_arquivo, numero_atividades,printar, cont = 0;

    abrir_arquivo = open("/dev/lista_tarefas", O_RDWR);
    
    if(abrir_arquivo < 0)
    {
        perror("Failed to open the device.");
        return errno;
    }
    char escolha[3];
    while(1)
    {
        printf("\tMODULO KERNEL PARA LISTA DE TAREFAS USANDO LIST.H\t\n");
        printf("OPÇÕES:\n");
        printf("1 - INSERIR ATIVIDADES NA LISTA\n");
        printf("2 - IMPRIMIR ATIVIDADES NA LISTA\n");
        printf("0 - SAIR\n");
        printf("DIGITE UMA OPÇÃO:\n");
        scanf(" %[^\n]s",&escolha);

        switch (escolha[0])
        {
            case '1':
                printf("INSIRA O NUMERO DE ATIVIDADES QUE DESEJA INSERIR NA LISTA\n");
                scanf("%d",&numero_atividades);
                while(cont != numero_atividades)
                {
                    printf("INSIRA A DESCRIÇÃO DA ATIVIDADE %d:\n",cont++);
                    scanf(" %[^\n]s",tarefa);
                    escrever_arquivo = write(abrir_arquivo,tarefa,strlen(tarefa));
                    printf("AAAAAAA\n");
                    if(escrever_arquivo > 0)
                    {
                        perror("Failed to write the message to the device.");
                        return errno;
                    }
                    cont++;
                }
                cont = 0;
                break;
            case '2':
                printar = read(abrir_arquivo,tarefa,strlen(tarefa));
                break;
			/*
            case '3':
                print_list();
                int tarefa_removida;
                printf("INSIRA A ATIVIDADE QUE DESEJA REMOVER DA LISTA:\n");
                scanf("%d",&tarefa_removida);
                delete_list(tarefa_removida);
                break;
                * 
                * */

            case '0':
                return 0;

        default:
            printf("Opcao invalida, digite a opcao novamente:\n ");break;
            break;
        }
    }
}
