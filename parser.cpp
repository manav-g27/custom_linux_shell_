#include "parser.h"
#include <sstream>

//[cite: 4]
Command parseCommand(const std::string &input) {
    Command cmd;
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> currentCmd;

    while (ss >> token) {
        if (token == "|") {
            if (!currentCmd.empty()) cmd.pipeline.push_back(currentCmd);
            currentCmd.clear();
        } else if (token == "<") {
            ss >> cmd.inputFile;
        } else if (token == ">") {
            cmd.appendOutput = false;
            ss >> cmd.outputFile;
        } else if (token == ">>") {
            cmd.appendOutput = true;
            ss >> cmd.outputFile;
        } else if (token == "&") {
            cmd.background = true;
        } else {
            currentCmd.push_back(token);
        }
    }

    if (!currentCmd.empty()) cmd.pipeline.push_back(currentCmd);
    return cmd;
}