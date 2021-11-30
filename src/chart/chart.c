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

static int screenWidth = 168;

static char *COLUMNS[N_COLUMNS] = {"Keys", "Count", "Chart"};

void updateColumn1Width(Chart *ch);
void updateColumn2Width(Chart *ch);
void updateColumn3Width(Chart *ch);
int addKey(Chart *ch, char keyname[], int count);
void printHeader(Chart *ch);
void printFooter(Chart *ch);
void printKeys(Chart *ch, bool isUnicode);
void printNewRow(Chart *ch);
void printStrNTimes(char str[], int n);
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

    ch->len = 0;
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

    char *width = getenv("COLUMNS");
    if (width == NULL)
    {
        PRINT_ERROR("COLUMNS env variable is not defined, proceed to use default value for screen width (168) \n");
    }
    else
    {
        screenWidth = atoi(width);
    }

    return ch;
}

int addKeys(Chart *ch, int charCount[])
{
    for (int i = 0; i < N_ASCII; i++)
    {
        if (charCount[i] > 0)
        {
            switch (i)
            {
            case '\n':
                if (addKey(ch, "\\n", charCount[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case ' ':
                if (addKey(ch, "space", charCount[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case '\t':
                if (addKey(ch, "\\t", charCount[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            default:
            {
                char keyname[2] = {i, 0};
                if (addKey(ch, keyname, charCount[i]) == RETURN_FAILURE)
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

void displayChart(Chart *ch, bool isUnicode)
{
    updateColumn1Width(ch);
    updateColumn2Width(ch);
    updateColumn3Width(ch);

    printf("%s%s", CLEAR_SCREEN, CURSOR_HOME);

    printf("\n %s%sGenerated Successfully%s\n\n", COLOR_GREEN, BOLD_TEXT, COLOR_RESET);

    printHeader(ch);
    printKeys(ch, isUnicode);
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

int addKey(Chart *ch, char keyname[], int count)
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
    printf(" %s%s%s%s ", COLOR_YELLOW, BOLD_TEXT, COLUMNS[0], COLOR_RESET);
    int padding = ch->columnWidth[0] - strlen(COLUMNS[0]);
    printStrNTimes(" ", padding);

    printf("| %s%s%s%s ", COLOR_BLUE, BOLD_TEXT, COLUMNS[1], COLOR_RESET);
    padding = ch->columnWidth[1] - strlen(COLUMNS[1]);
    printStrNTimes(" ", padding);

    printf("| %s%s%s%s \n", COLOR_WHITE, BOLD_TEXT, COLUMNS[2], COLOR_RESET);

    printNewRow(ch);
}

void printFooter(Chart *ch)
{
    printNewRow(ch);
    printf("\n");
}

void printKeys(Chart *ch, bool isUnicode)
{
    for (int i = 0; i < ch->len; i++)
    {
        // - 7 comes from space paddings and
        // column dividers of the 3 columns below
        int limit = screenWidth - 7;

        // 2 paddings
        printf(" %s%s%s ", COLOR_YELLOW, ch->keys[i].keyname, COLOR_RESET);
        int n = strlen(ch->keys[i].keyname);
        int padding = ch->columnWidth[0] - n;
        limit -= padding + n;
        printStrNTimes(" ", padding);

        // 2 paddings + 1 column divider
        printf("| %s%d%s ", COLOR_BLUE, ch->keys[i].count, COLOR_RESET);
        n = ch->keys[i].countDigit;
        padding = ch->columnWidth[1] - n;
        limit -= padding + n;
        printStrNTimes(" ", padding);

        n = ch->keys[i].count;
        if (limit < n)
        {
            n = limit;
        }

        // 1 padding + 1 column divider
        printf("| %s%s", COLOR_BLACK, BOLD_TEXT);
        if (isUnicode)
        {
            printStrNTimes(BAR, n);
        }
        else
        {
            printStrNTimes("#", n);
        }
        printf("%s\n", COLOR_RESET);
    }
}

void printNewRow(Chart *ch)
{
    int limit = screenWidth;
    for (int i = 0; i < N_COLUMNS; i++)
    {
        // + 2 comes from space padding on both sides
        int n = ch->columnWidth[i] + 2;
        limit -= n;
        if (limit < 0)
        {
            n += limit;
        }

        printStrNTimes("-", n);
        if (i != N_COLUMNS - 1)
        {
            limit--;
            printf("+");
        }
    }

    printf("\n");
}

void printStrNTimes(char str[], int n)
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