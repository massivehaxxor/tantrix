#include <termios.h>

void termios_init()
{
  struct termios t1;

  tcgetattr(0, &t1);

  t1.c_lflag &= ~ICANON;
  t1.c_lflag &= ~ECHO;
  t1.c_lflag &= ~ISIG;
  t1.c_cc[VMIN] = 0;
  t1.c_cc[VTIME] = 0;

  tcsetattr(0, TCSANOW, &t1);

}
