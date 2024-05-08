#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>

// Name: Ben Wiggins
// netID: bcw62
// RUID: 202007696
// your code for readdir goes here

typedef struct dirent *(*oldreaddir_t)(DIR *);

struct dirent *readdir(DIR *dirp){
    char *hidden = getenv("HIDDEN");
    void *libc = dlopen("libc.so.6", RTLD_NOW);
    oldreaddir_t oldreaddir = (oldreaddir_t)dlsym(libc, "readdir");
    
    if(!hidden){return oldreaddir(dirp);}

    char *hidden_dupe = strdup(hidden);
    char* current_name = strtok(hidden_dupe, ":");

    struct dirent *file = oldreaddir(dirp);

    if(!file){free(hidden_dupe); return file;}

    while(current_name != NULL){
        //printf("%s and %s\n", current_name, file->d_name);

        if(strcmp(current_name, file->d_name) == 0){
            free(hidden_dupe);
            return oldreaddir(dirp);
        }

        current_name = strtok(NULL, ":");
    }

    free(hidden_dupe);
    return file;

}