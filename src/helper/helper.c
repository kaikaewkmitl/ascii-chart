#include "helper.h"

int charCount(Chart *ch, int freq[])
{
    for (int i = 0; i < 128; i++)
    {
        if (freq[i] > 0)
        {
            switch (i)
            {
            case '\n':
                if (addKey(ch, "\\n", freq[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case ' ':
                if (addKey(ch, "space", freq[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            case '\t':
                if (addKey(ch, "\\t", freq[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
                break;
            default:
            {
                char c[2] = {i, 0};
                if (addKey(ch, c, freq[i]) == RETURN_FAILURE)
                {
                    return RETURN_FAILURE;
                }
            }
            }
        }
    }

    return RETURN_SUCCESS;
}