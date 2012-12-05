#include <ctype.h>

#include "tantrix_thread.h" /* tansleep */
char *strlwr(char *str)
{
  int i = 0;
  int n = strlen(str);

  for (i = 0; i < n; i++)
    str[i] = tolower(str[i]);
}

void usleep(long val)
{
  tansleep(val);
}
