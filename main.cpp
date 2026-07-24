#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include "parser.h"
#include "executor.h"
#include "jobs.h"

bool executeBuiltin(const Command &cmd, std::vector<std::string> &history) {
    if (cmd.pipeline.empty() || cmd.pipeline[0].empty()) return false;
    const std::string &name = cmd.pipeline[0][0];

    if (name == "exit") {
        std::cout << "Exiting shell...\n";
        exit(0);
    }
    if (name == "cd") {
        std::string path = (cmd.pipeline[0].size() > 1) ? cmd.pipeline[0][1] : std::string(getenv("HOME"));
        if (chdir(path.c_str()) != 0) perror("cd failed");
        return true;
    }
    if (name == "pwd") {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr) std::cout << cwd << std::endl;
        else perror("pwd failed");
        return true;
    }
    if (name == "echo") {
        for (size_t i = 1; i < cmd.pipeline[0].size(); ++i) {
            std::cout << cmd.pipeline[0][i] << (i + 1 < cmd.pipeline[0].size() ? " " : "");
        }
        std::cout << std::endl;
        return true;
    }
    if (name == "history") {
        for (size_t i = 0; i < history.size(); ++i)
            std::cout << i + 1 << "  " << history[i] << std::endl;
        return true;
    }
    if (name == "jobs") {
        listJobs();
        return true;
    }
    return false;
}

//[cite: 3]
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