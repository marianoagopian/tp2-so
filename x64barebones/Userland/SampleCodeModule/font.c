#include <commands.h>
#include <syscalls.h>
#include <functions.h>

static char * noArgument = "For this function argument is necessary\n";


int strToNum(char *str){
  int result;
  int sign;

  result = 0;
  sign = 1;
  while (('-' == (*str)) || ((*str) == '+'))
  {
      if (*str == '-')
        sign = sign * -1; // cambiamos el signo si es negativo
      str++;
  }
  while ((*str >= '0') && (*str <= '9'))
  {
      result = (result * 10) + ((*str) - '0');
      str++;
  }
  return (result * sign);
}

void changefontsize(char *par){
  if(*par == 0) {
    print(noArgument, strlen(noArgument));
    return;
  }
  int level = strToNum(par);
  if(level < 1 || level > 3){
    printf("The parameter must be a number between 1 and 3\n");
    return;
  }
  if(level == sys_get_level()){
    printf("Enter a different font size number to change from the current one\n");
    return;
  }
  sys_set_level(level);
}
