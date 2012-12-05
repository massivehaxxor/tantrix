#include <wchar.h>
#include <wctype.h>

#include "tantrix_thread.h" /* tansleep */
wchar_t *wcslwr(wchar_t * str)
{
  int i = 0;
  int n = wcslen(str);

  for (i = 0; i < n; i++)
    str[i] = towlower(str[i]);
}

void usleep(long val)
{
  tansleep(val);
}
