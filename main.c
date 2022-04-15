#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    char Input[255];
    pid_t child_pid;
    pid_t new_child_pid;
    int statval;
    int exec_err;
    char input_div[10][255];
    int scan_res;
    int j = 0;


    printf("Welcome to terminal!\n");
    while(1)
    {
        printf(">>");
        //считываем команду
        scanf("%s", Input);
        //выход из терминала
        if(strncmp(Input, "kill", 5) == 0)
            break;
        //запускаем дочерний процесс
        child_pid = fork();
	
        if(child_pid == -1)
        {
            printf("Can't start new process\n");
            return 1;
        }

        if(child_pid == 0)
        {
            //мы в дочернем процессе
            //заменяем его на новый
            exec_err = execvp(Input, Input, 0);
            if(exec_err == -1)
            {
                printf("Process didn't launch");
                return 2;
            }
        }
        else 
        {
            //мы в родительском процессе
            //ждем завершения дочернего процесса
            new_child_pid = wait(&statval);            
            printf("parent\n");
        }

    }
    return 0;
}
