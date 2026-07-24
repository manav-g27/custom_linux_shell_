#ifndef JOBS_H
#define JOBS_H

#include <string>
#include <vector>
#include <sys/types.h>

struct Job {
    pid_t pid;
    std::string command;
    bool running;
};

extern std::vector<Job> jobList;

void addJob(pid_t pid, const std::string &cmd);
void listJobs();

#endif // JOBS_H