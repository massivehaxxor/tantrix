#include <ctype.h>
#include <string.h>
#include "tantrix_thread.h" /* tansleep */
char *strlwr(char *str)
{
  int i = 0;
  int n = strlen(str);

  for (i = 0; i < n; i++)
    str[i] = tolower(str[i]);
  return str;
}

void usleep(long val)
{
  tansleep(val);
}
