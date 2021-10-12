#include "chart.h"

#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_RESET "\033[0m"
#define CHAR_LIMIT 25
#define N_COLUMNS 3
#define GROWTH_FACTOR 2

typedef struct Key
{
    char keyName[CHAR_LIMIT];
    int count;
    int countDigit;
    float percentage;
} Key;

struct Chart
{
    char title[CHAR_LIMIT];
    int columnWidth[N_COLUMNS];

    // size as in keys max capacity,
    // len as in total no. of keys
    Key *keys;
    int size;
    int len;
};

char *COLUMNS[N_COLUMNS] = {"Keys", "Count", "Chart"};

Chart *newChart(char *title)
{
    Chart *ch = (Chart *)malloc(sizeof(Chart));
    if (ch == NULL)
    {
        fprintf(stderr, "failed to allocate a new Chart\n");
        return ch;
    }

    ch->size++;
    ch->keys = (Key *)malloc(sizeof(Key));
    if (ch->keys == NULL)
    {
        fprintf(stderr, "failed to allocate a new Chart\n");
        return ch;
    }

    strcpy(ch->title, title);

    for (int i = 0; i < N_COLUMNS; i++)
    {
        ch->columnWidth[i] = strlen(COLUMNS[i]);
    }

    return ch;
}

void addKey(Chart *ch, char *keyName, int count)
{
    if (ch->len == ch->size)
    {
        ch->size *= GROWTH_FACTOR;
        ch->keys = (Key *)realloc(ch->keys, ch->size * sizeof(Key));
        if (ch->keys == NULL)
        {
            fprintf(stderr, "failed to allocate new keys\n");
            return;
        }
    }

    strcpy(ch->keys[ch->len].keyName, keyName);

    ch->keys[ch->len].count = count;
    int digit = 0;
    while (count != 0)
    {
        count /= 10;
        digit++;
    }

    ch->keys[ch->len].countDigit = digit;
    ch->len++;
}

void printCharNTimes(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

void printNewRow(Chart *ch)
{
    printf("%s", COLOR_WHITE);
    for (int i = 0; i < N_COLUMNS; i++)
    {
        printCharNTimes('-', ch->columnWidth[i] + 2);
        if (i != N_COLUMNS - 1)
        {
            printf("+");
        }
    }

    printf("%s\n", COLOR_RESET);
}

void printHeader(Chart *ch)
{
    printf(" %sKeys%s ", COLOR_GREEN, COLOR_RESET);
    int padding = ch->columnWidth[0] - strlen(COLUMNS[0]);
    printCharNTimes(' ', padding);

    printf("%s| %sCount%s ", COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
    padding = ch->columnWidth[1] - strlen(COLUMNS[1]);
    printCharNTimes(' ', padding);

    printf("%s| %sChart%s \n", COLOR_WHITE, COLOR_YELLOW, COLOR_RESET);

    printNewRow(ch);
}

void printFooter(Chart *ch)
{
    printNewRow(ch);
    printf("\n");
}

void printKeys(Chart *ch)
{
    for (int i = 0; i < ch->len; i++)
    {
        printf(" %s%s%s ", COLOR_GREEN, ch->keys[i].keyName, COLOR_RESET);
        int padding = ch->columnWidth[0] - strlen(ch->keys[i].keyName);
        printCharNTimes(' ', padding);

        printf("%s| %s%d%s ", COLOR_WHITE, COLOR_CYAN, ch->keys[i].count, COLOR_RESET);
        padding = ch->columnWidth[1] - ch->keys[i].countDigit;
        printCharNTimes(' ', padding);

        printf("%s| %s", COLOR_WHITE, COLOR_YELLOW);
        printCharNTimes('#', ch->keys[i].count);
        printf("%s\n", COLOR_RESET);
    }
}

void updateColumn1Width(Chart *ch)
{
    for (int i = 0; i < ch->len; i++)
    {
        int len = strlen(ch->keys[i].keyName);
        if (ch->columnWidth[0] < len)
        {
            ch->columnWidth[0] = len;
        }
    }
}

void updateColumn2Width(Chart *ch)
{
    for (int i = 0; i < ch->len; i++)
    {
        if (ch->columnWidth[1] < ch->keys[i].countDigit)
        {
            ch->columnWidth[1] = ch->keys[i].countDigit;
        }
    }
}

void updateColumn3Width(Chart *ch)
{
    for (int i = 0; i < ch->len; i++)
    {
        if (ch->columnWidth[2] < ch->keys[i].count)
        {
            ch->columnWidth[2] = ch->keys[i].count;
        }
    }
}

void display(Chart *ch)
{
    updateColumn1Width(ch);
    updateColumn2Width(ch);
    updateColumn3Width(ch);

    printf("\n %s%s\n\n", COLOR_WHITE, ch->title);

    printHeader(ch);
    printKeys(ch);
    printFooter(ch);

    printf("%s", COLOR_RESET);
}
