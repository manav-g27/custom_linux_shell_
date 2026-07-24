#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>
#include "parser.h"
#include "executor.h"
#include "jobs.h"

bool executeBuiltin(const Command &cmd, std::vector<std::string> &history) {
    if (cmd.pipeline.empty() || cmd.pipeline[0].empty()) return false;
    const std::string &name = cmd.pipeline[0][0];

    // Handle output redirection for built-ins (e.g., echo "text" > file.txt)
    int saved_stdout = -1;
    if (!cmd.outputFile.empty()) {
        saved_stdout = dup(STDOUT_FILENO);
        int flags = O_WRONLY | O_CREAT | (cmd.appendOutput ? O_APPEND : O_TRUNC);
        int fd = open(cmd.outputFile.c_str(), flags, 0644);
        if (fd < 0) {
            perror("open output failed");
        } else {
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }

    bool executed = true;
    if (name == "exit") {
        std::cout << "Exiting shell...\n";
        exit(0);
    } else if (name == "cd") {
        std::string path = (cmd.pipeline[0].size() > 1) ? cmd.pipeline[0][1] : std::string(getenv("HOME"));
        if (chdir(path.c_str()) != 0) perror("cd failed");
    } else if (name == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) std::cout << cwd << std::endl;
        else perror("pwd failed");
    } else if (name == "echo") {
        for (size_t i = 1; i < cmd.pipeline[0].size(); ++i) {
            std::cout << cmd.pipeline[0][i] << (i + 1 < cmd.pipeline[0].size() ? " " : "");
        }
        std::cout << std::endl;
    } else if (name == "history") {
        for (size_t i = 0; i < history.size(); ++i)
            std::cout << i + 1 << "  " << history[i] << std::endl;
    } else if (name == "jobs") {
        listJobs();
    } else {
        executed = false;
    }

    // Restore standard output if it was redirected
    if (saved_stdout != -1) {
        std::cout << std::flush;
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
    }

    return executed;
}

int main() {
    std::string line;
    std::vector<std::string> history;

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    while (true) {
        std::cout << "myshell> ";
        if (!std::getline(std::cin, line)) break;

        if (line.empty()) continue;

        history.push_back(line);

        Command cmd = parseCommand(line);
        if (!executeBuiltin(cmd, history)) {
            executeCommand(cmd, line);
        }
    }

    return 0;
}