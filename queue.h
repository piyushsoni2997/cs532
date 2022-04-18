//
//  helper.h
//  
//
//  Created by Piyush Soni on 4/16/22.
//
#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <pthread.h>

typedef struct job
{
    int job_id;
    pthread_t tid;
    char *command;
    char *stat;
    int exit_stat;
    char *start;
    char *stop;
    char output_file[10];
    char err_file[10];
} job;

typedef struct queue
{
    int size;
    job **buffer;
    int start;
    int end;
    int count;
} queue;


job create_job(char *command, int job_id);
void show_jobs(job *jobs, int n);
void submit_history(job *jobs, int n);
queue *queue_init(int n);
int queue_insert(queue *job_queue, job *jp);
job *queue_delete(queue *job_queue);
void queue_destroy(queue *job_queue);
char *current_time();
char **get_args(char *line);
int file_open(char *fn);
char *remove_null(char *s);
char *get_command(char *line);

#endif
