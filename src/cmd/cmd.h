#ifndef CMD_H
#define CMD_H

#include "../macros.h"
#include "../fileHandler/fileHandler.h"
#include "../chart/chart.h"

#define DEFAULT_MODE 0
#define WITH_FILES_MODE 1

int parseFlags(int argc);

int runDefaultMode(void);

int runWithFilesMode(void);

#endif