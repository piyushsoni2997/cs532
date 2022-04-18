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

