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

eMode parseFlags(int argc, char **argv);

int runDefaultMode(int charCount[]);

int runWithFilesMode(int argc, char **argv, int charCount[]);

void runHelpMode(char **argv);

void runUnknownCmd(int argc, char **argv);

#endif