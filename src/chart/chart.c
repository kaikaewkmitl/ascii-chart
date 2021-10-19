#include "chart.h"

#define N_COLUMNS 3
#define GROWTH_FACTOR 2
#define BAR "█"
#define STDOUT_FILENO 1

typedef struct Key
{
    char keyname[CHAR_LIMIT];
    int count;
    int countDigit;
    float percentage;
} Key;

struct Chart
{
    int columnWidth[N_COLUMNS];

    // size as in keys max capacity,
    // len as in total no. of keys
    Key *keys;
    int size;
    int len;
};

static int screenWidth, screenHeight;

static char *COLUMNS[N_COLUMNS] = {"Keys", "Count", "Chart"};

void updateColumn1Width(Chart *ch);
void updateColumn2Width(Chart *ch);
void updateColumn3Width(Chart *ch);
int addKey(Chart *ch, char *keyname, int count);
void printHeader(Chart *ch);
void printFooter(Chart *ch);
void printKeys(Chart *ch);
void printNewRow(Chart *ch);
void printStrNTimes(char *str, int n);
int cmpAscending(const void *a, const void *b);
int cmpDescending(const void *a, const void *b);

Chart *newChart(void)
{
    Chart *ch = (Chart *)malloc(sizeof(Chart));
    if (ch == NULL)
    {
        PRINT_ERROR("failed to allocate a new Chart\n");
        return NULL;
    }

    ch->size++;
    ch->keys = (Key *)malloc(sizeof(Key));
    if (ch->keys == NULL)
    {
        PRINT_ERROR("failed to allocate a new Chart\n");
        return NULL;
    }

    for (int i = 0; i < N_COLUMNS; i++)
    {
        ch->columnWidth[i] = strlen(COLUMNS[i]);
    }

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    screenWidth = ws.ws_col;
    screenHeight = ws.ws_row;
    return ch;
}

int addKeys(Chart *ch, int *count)
{
    for (int i = 0; i < N_ASCII; i++)
    {
        if (count[i] > 0)
        {
            switch (i)
            {
            case '\n':
                if (addKey(ch, "\\n", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case ' ':
                if (addKey(ch, "space", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case '\t':
                if (addKey(ch, "\\t", count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            default:
            {
                char keyname[2] = {i, 0};
                if (addKey(ch, keyname, count[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
            }
            }
        }
    }

    return RETURN_SUCCESS;
}

void sortChart(Chart *ch, eOrder order)
{
    switch (order)
    {
    case Ascending:
        qsort(ch->keys, ch->len, sizeof(Key), cmpAscending);
        break;
    case Descending:
        qsort(ch->keys, ch->len, sizeof(Key), cmpDescending);
        break;
    }
}

void displayChart(Chart *ch)
{
    updateColumn1Width(ch);
    updateColumn2Width(ch);
    updateColumn3Width(ch);

    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);

    printf("\n %sGenerated successfully%s\n\n", COLOR_GREEN, COLOR_RESET);

    printHeader(ch);
    printKeys(ch);
    printFooter(ch);
}

void deleteChart(Chart *ch)
{
    if (ch)
    {
        free(ch->keys);
        free(ch);
    }
}

void updateColumn1Width(Chart *ch)
{
    for (int i = 0; i < ch->len; i++)
    {
        int len = strlen(ch->keys[i].keyname);
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

int addKey(Chart *ch, char *keyname, int count)
{
    if (ch->len == ch->size)
    {
        ch->size *= GROWTH_FACTOR;
        ch->keys = (Key *)realloc(ch->keys, ch->size * sizeof(Key));
        if (ch->keys == NULL)
        {
            PRINT_ERROR("failed to allocate a new key\n");
            return RETURN_FAILURE;
        }
    }

    strcpy(ch->keys[ch->len].keyname, keyname);

    ch->keys[ch->len].count = count;
    int digit = 0;
    while (count != 0)
    {
        count /= 10;
        digit++;
    }

    ch->keys[ch->len].countDigit = digit;
    ch->len++;
    return RETURN_SUCCESS;
}

void printHeader(Chart *ch)
{
    printf(" %s%s%s ", COLOR_YELLOW, COLUMNS[0], COLOR_RESET);
    int padding = ch->columnWidth[0] - strlen(COLUMNS[0]);
    printStrNTimes(" ", padding);

    printf("| %s%s%s ", COLOR_YELLOW, COLUMNS[1], COLOR_RESET);
    padding = ch->columnWidth[1] - strlen(COLUMNS[1]);
    printStrNTimes(" ", padding);

    printf("| %s%s%s \n", COLOR_YELLOW, COLUMNS[2], COLOR_RESET);

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
        printf(" %s%s%s ", COLOR_YELLOW, ch->keys[i].keyname, COLOR_RESET);
        int padding = ch->columnWidth[0] - strlen(ch->keys[i].keyname);
        printStrNTimes(" ", padding);

        printf("| %s%d%s ", COLOR_YELLOW, ch->keys[i].count, COLOR_RESET);
        padding = ch->columnWidth[1] - ch->keys[i].countDigit;
        printStrNTimes(" ", padding);

        printf("| %s", COLOR_YELLOW);
        printStrNTimes(BAR, ch->keys[i].count);
        printf("%s\n", COLOR_RESET);
    }
}

void printNewRow(Chart *ch)
{
    for (int i = 0; i < N_COLUMNS; i++)
    {
        printStrNTimes("-", ch->columnWidth[i] + 2);
        if (i != N_COLUMNS - 1)
        {
            printf("+");
        }
    }

    printf("\n");
}

void printStrNTimes(char *str, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s", str);
    }
}

int cmpAscending(const void *a, const void *b)
{
    Key *k1 = (Key *)a, *k2 = (Key *)b;
    return k1->count - k2->count;
}

int cmpDescending(const void *a, const void *b)
{
    Key *k1 = (Key *)a, *k2 = (Key *)b;
    return k2->count - k1->count;
}