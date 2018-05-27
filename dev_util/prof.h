#ifndef DEV_UTIL_PROF_H
#define DEV_UTIL_PROF_H

//PAPI performance API
//http://icl.cs.utk.edu/papi/software/index.html
#include <sstream>
#include <iostream>
#include <functional>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

struct Prof
{
    static void profile(const std::string& name,std::function<void()> body) {
        std::string filename = name.find(".data") == std::string::npos ? (name + ".data") : name;

  	//Lauch profiler      
        pid_t pid;
        std::stringstream s;
        s << getpid();
        pid = fork();
        if (pid == 0) {
            auto fd=open("/dev/null",O_RDWR);
            dup2(fd,1);
            dup2(fd,2);
            exit(execl("/usr/bin/perf","perf","record","-o",filename.c_str(),"-p",s.str().c_str(),nullptr));
        }

        //Run body
        body();

        //Kill profiler
        kill(pid,SIGINT);
        waitpid(pid,nullptr,0);
    }

    static void profile(std::function<void()> body) {
        profile("perf.data",body);
    }
};
//perf report -i loading.data
#endif
