/* Driver program to test the queue implementation */
/* Use the Makefile provided or compile using: gcc queue.c HW4.c -lpthread */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "queue.h"

#define MAXJOBLEN 1000
#define JOBQLEN 100

int max_job;
int curr_work_num_jobs;
job total_jobs[MAXJOBLEN];
queue *waiting_jobs;

void *curr_job_complete(void *arg);
void *all_jobs_complete(void *arg);
void queue_handler();


int main(int argc, char **argv)
{
    if ((argc != 2) || (atoi(argv[1])%2!=0))
    {
        printf("Usage: %s Number of (Even)Jobs to run at a single time\n", argv[0]);
        exit(-1);
    }
    
    char *err_file;
    pthread_t tid;

    max_job = atoi(argv[1]);
    if (max_job < 1)
        max_job = 1;
    else if (max_job > 8)
        max_job = 8;

    printf("Maximum Jobs to be run at any given time : %d\n\n", max_job);

    err_file = malloc(sizeof(char) * (strlen(argv[0]) + 5));
    sprintf(err_file, "%s.err", argv[0]);
    dup2(file_open(err_file), STDERR_FILENO);

    waiting_jobs = queue_init(JOBQLEN);
    pthread_create(&tid, NULL, all_jobs_complete, NULL);
    queue_handler();

    exit(-1);
}

void queue_handler()
{
    int i;
    char *line = NULL, *temp = NULL;
    char *argument, *command;
    const char s[2] = " ";
    size_t len = 0;
    temp = malloc(sizeof(char) * strlen(s));
    i = 0;
    
    printf("> ");
    while (getline(&line, &len, stdin) != -1)
    {
        strcpy(temp, line);
        if ((argument = strtok(temp, s)) != NULL)
        {
            if (strcmp(argument, "submit") == 0)
            {
                if (i >= MAXJOBLEN)
                    printf("Job history full; restart the program to schedule more\n");
                else if (waiting_jobs->count >= waiting_jobs->size)
                    printf("Job queue full; try again after more jobs complete\n");
                else
                {
                    command = get_command(line);
                    total_jobs[i] = create_job(command, i);
                    queue_insert(waiting_jobs, total_jobs + i);
                    printf("Job %d added to the queue\n", i++);
                }
            }
            
            else if (strcmp(argument, "showjobs\n") == 0)
                show_jobs(total_jobs, i);
            else if (strcmp(argument, "submithistory\n") == 0)
                submit_history(total_jobs, i);
        }
        printf("> ");
    }
    kill(0, SIGINT);
}
