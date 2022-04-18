/* Containes functions for HW4.c file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "queue.h"


job create_job(char *command, int job_id)
{
    job job_details;
    job_details.job_id = job_id;
    job_details.command = malloc(sizeof(char) * strlen(command));
    strcpy(job_details.command, remove_null(command));
    job_details.stat = "waiting";
    job_details.exit_stat = -1;
    job_details.start = NULL;
    job_details.stop = NULL;
    sprintf(job_details.output_file, "%d.out", job_details.job_id);
    sprintf(job_details.err_file, "%d.err", job_details.job_id);
    return job_details;
}

char *get_command(char *line){
    const char s[2] = " ";
    char *token, *temp, *x;
    temp = malloc(sizeof(char) * strlen(s));
    x = malloc(sizeof(char) * strlen(line));
    strcpy(x, line);

    token = strtok(x, s);
    token = strtok(NULL, s);
    while ((temp=strtok(NULL, s))!=NULL){
        sprintf(token, "%s %s", token, temp);
    }
    return token;
}

void show_jobs(job *jobs, int n)
{
    int i;
    if (jobs != NULL && n != 0)
    {
        printf("%-3s %-10s %10s\n", "Job ID", "Command", "Status");
        for (i = 0; i < n; ++i)
        {
            if (strcmp(jobs[i].stat, "complete") != 0)
                printf("%-3d   %-10s %10s\n", jobs[i].job_id, jobs[i].command, jobs[i].stat);
        }
    }
}

void submit_history(job *jobs, int n)
{
    int i;
    if (jobs != NULL && n != 0)
    {
        printf("%s   |   %*s  |  %*s  |  %*s  |  %*s\n", "Job ID", -12, "Command", -20, "Start Time", -20, "Stop Time", -6, "Status");
        for (i = 0; i < n; ++i)
        {
            if (strcmp(jobs[i].stat, "complete") == 0)
                printf("%*d   |   %*s  |  %*s |  %*s  |  %*d\n", 3,  jobs[i].job_id, -3, jobs[i].command, 3, jobs[i].start, 3, jobs[i].stop, -6, jobs[i].exit_stat);
        }
    }
}


queue *queue_init(int n)
{
    queue *job_queue = malloc(sizeof(queue));
    job_queue->size = n;
    job_queue->buffer = malloc(sizeof(job *) * n);
    job_queue->start = 0;
    job_queue->end = 0;
    job_queue->count = 0;

    return job_queue;
}

int queue_insert(queue *job_queue, job *current_jobs)
{
    if ((job_queue == NULL) || (job_queue->count == job_queue->size))
        return -1;

    job_queue->buffer[job_queue->end % job_queue->size] = current_jobs;
    job_queue->end = (job_queue->end + 1) % job_queue->size;
    ++job_queue->count;

    return job_queue->count;
}
