/*
** free_opt.c for opt_parser in sources/free
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat Dec 03 14:30:37 2016 Benoit Hamon
** Last update Sun Dec 04 13:09:46 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stdlib.h>
#include "tools/tools.h"
#include "opt.h"

static void	free_list_name(t_opt_name *name)
{
  if (name)
  {
    free_list_name(name->next);
    free(name->str);
    free(name);
  }
}

void		*free_opt(t_opt *opt)
{
  free_list_name(opt->name);
  free(opt);
  return (NULL);
}
