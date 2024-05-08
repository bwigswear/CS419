#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <dlfcn.h>

// Name: Ben Wiggins
// netID: bcw62
// RUID: 202007696
// your code for time() goes here

typedef time_t (*oldtime_t)(time_t*);

time_t time( time_t *second ){
    static int count = 0;

    if(count == 0){
        count++;

        const char *date_string = "2022-01-02";
        struct tm date_struct;
        
        strptime(date_string, "%Y-%m-%d", &date_struct);

        time_t return_time = mktime(&date_struct);
        
        *second = return_time;

        return return_time;

    }else{

        void* libc = dlopen("libc.so.6", RTLD_NOW);
        oldtime_t oldtime = (oldtime_t)dlsym(libc, "time");
        
        time_t return_time = oldtime(NULL);

        *second = return_time;

        dlclose(libc);
        return return_time;

    }


}