#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <dirent.h>

int word_count(char *str)
{
    int num_of_words = 0;
    char *buf;
    //printf("%s\n", buf);
    while (buf = strtok_r(str, " ", &str))
    {
        num_of_words++;
    }
    return num_of_words;
}
int string_divide(char* input, char **input_div);

int main()
{
    char Input[255];
    pid_t child_pid;
    pid_t new_child_pid;
    int statval;
    int exec_err;
    char **input_div;
    int scan_res;
    int j = 0;
    int num_of_words;
    char currpath[255];


    printf("Welcome to terminal!\n");
    while(1)
    {
        printf(">>");
        //считываем команду
        gets(Input);
        //printf("%s\n", Input);
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
        //считаем кол-во слов в строке
        num_of_words = word_count(Input);
        //создаем копию входной строки
        char input_2[255];
        strcpy(input_2, Input);

        // printf("%d\n", num_of_words);  
        //выделяем память для слов
        input_div = (char**)malloc(sizeof(char*)*num_of_words);

        //делим строку
        num_of_words = 0;
        char *buf = strtok(input_2, " ");
        //char * buf2 = strtok(input, " ");
        while (buf != NULL)
        {   
            //выделяем память под отдельное слово
            input_div[num_of_words] = (char*)malloc(sizeof(char)*(strlen(buf)+1));
            strcpy(input_div[num_of_words], buf);
            num_of_words++;
            //printf("%d\n", num_of_words);  
            buf = strtok(NULL, " ");
            //printf("%s\n", input_div[num_of_words-1]);
        }
        if(child_pid == 0)
        {
            //мы в дочернем процессe
            //for(int i = 0; i < num_of_words; i++)
            //{
            //    printf("%s\n", input_div[i]);
            //}          
            //заменяем процесс на новый
            exec_err = execvp(input_div[0], input_div, 0);
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
            //освобождаем память выделенную под слова
            for(int i = 0; i < num_of_words; i++)
            {
                free(input_div[i]);
            }
            free(input_div);                 
        }

    }
    return 0;
}


int string_divide(char* input, char **input_div)
{
    int num_of_words;
    //создаем копию входной строки
    char input_2[255];
    strcpy(input_2, input);
    //считаем кол-во слов в строке
    num_of_words = word_count(input);
    // printf("%d\n", num_of_words);  
    //выделяем память для слов
    input_div = (char**)malloc(sizeof(char*)*num_of_words);

    //делим строку
    num_of_words = 0;
    char *buf = strtok(input_2, " ");
    //char * buf2 = strtok(input, " ");
    while (buf != NULL)
    {
        //выделяем память под отдельное слово
        input_div[num_of_words] = (char*)malloc(sizeof(char)*(strlen(buf)+1));
        strcpy(input_div[num_of_words], buf);
        num_of_words++;
        //printf("%d\n", num_of_words);  
        buf = strtok(NULL, " ");
        //printf("%s\n", input_div[num_of_words-1]);
    }
    //printf("2%d\n", num_of_words);  
    return num_of_words;
}