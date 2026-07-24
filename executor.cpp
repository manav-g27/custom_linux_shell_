#include "executor.h"
#include "jobs.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <signal.h>

//[cite: 1]
void executeCommand(const Command &cmd, const std::string &cmdLine) {
    if (cmd.pipeline.empty()) return;
    int numPipes = static_cast<int>(cmd.pipeline.size()) - 1;
    std::vector<int> pipes(2 * std::max(0, numPipes));

    for (int i = 0; i < numPipes; ++i)
        if (pipe(&pipes[2 * i]) == -1) {
            perror("pipe failed");
            return;
        }

    for (int i = 0; i < (int)cmd.pipeline.size(); ++i) {
        pid_t pid = fork();

        if (pid == 0) { 
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);

            if (i == 0 && !cmd.inputFile.empty()) {
                int fd = open(cmd.inputFile.c_str(), O_RDONLY);
                if (fd < 0) perror("open input failed");
                else {
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
            }

            if (i == (int)cmd.pipeline.size() - 1 && !cmd.outputFile.empty()) {
                int flags = O_WRONLY | O_CREAT | (cmd.appendOutput ? O_APPEND : O_TRUNC);
                int fd = open(cmd.outputFile.c_str(), flags, 0644);
                if (fd < 0) perror("open output failed");
                else {
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }
            }

            if (i > 0) {
                dup2(pipes[2 * (i - 1)], STDIN_FILENO);
            }
            if (i < numPipes) {
                dup2(pipes[2 * i + 1], STDOUT_FILENO);
            }

            for (int fd : pipes) if (fd) close(fd);

            std::vector<char*> args;
            for (auto &a : cmd.pipeline[i]) args.push_back(const_cast<char*>(a.c_str()));
            args.push_back(nullptr);

            execvp(args[0], args.data());
            perror("execvp failed");
            _exit(127);
        } else if (pid < 0) {
            perror("fork failed");
            for (int fd : pipes) if (fd) close(fd);
            return;
        } else {
            if (cmd.background) addJob(pid, cmdLine);
        }
    }

    for (int fd : pipes) if (fd) close(fd);

    if (!cmd.background) {
        for (size_t i = 0; i < cmd.pipeline.size(); ++i) {
            int status;
            wait(&status);
        }
    } else {
        std::cout << "[Running in background]" << std::endl;
    }
}