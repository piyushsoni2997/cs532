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


