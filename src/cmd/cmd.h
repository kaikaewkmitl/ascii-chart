#ifndef CMD_H
#define CMD_H

#include "../macros.h"
#include "../fileHandler/fileHandler.h"
#include "../chart/chart.h"

typedef enum eMode
{
    DefaultMode,
    WithFilesMode,
    HelpMode,
    UnknownCmd,
} eMode;

// parse flags given as argument when calling program
eMode parseFlags(int argc, char **argv);

// default mode of the program - user
// did not provide any argument
int runDefaultMode();

// user provided -f as an argument
int runWithFilesMode(int argc, char **argv);

// user provided -h as an argument
void runHelpMode(char **argv);

// user provided an invalid argument
void runUnknownCmd(int argc, char **argv);

#endif