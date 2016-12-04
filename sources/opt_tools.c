/*
** opt_tools.c for PSU_2015_42sh in sources/opt
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 13:18:56 2016 Benoit Hamon
** Last update Wed Nov 30 17:57:59 2016
*/

#include "tools/tools.h"

t_status		the_opt_atoi(char const *str, int *nbr)
{
  t_status		ok;
  int			neg;
  int			i;

  *nbr = 0;
  neg = (*str == '-' ? -1 : 1);
  i = (*str == '-' ? 1 : 0);
  ok = FAILURE;
  while (str[i] >= '0' && str[i] <= '9')
  {
    *nbr = *nbr * 10 + (str[i] - '0') * neg;
    ++i;
    ok = SUCCESS;
  }
  return (!str[i] ? ok : FAILURE);
}
