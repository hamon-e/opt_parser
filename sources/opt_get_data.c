/*
** opt_get_data.c for PSU_2015_42sh in sources/opt
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sat May 28 13:19:35 2016 Benoit Hamon
** Last update Sun Dec 04 13:09:06 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <string.h>
#include "tools/tools.h"
#include "opt.h"

static t_status		opt_get_data(void *data,
				     t_controller *ctrl,
				     t_opt_dico const *dico,
				     char const *str)
{
  int			nbr;
  char			*string;

  if (!str || !*str)
    return (FAILURE);
  if (dico->type == OPT_TYPE_NBR)
  {
    if (!!the_opt_atoi(str, &nbr))
      return (FAILURE);
    else
      memcpy((void *)data + dico->offset, &nbr, sizeof(int));
  }
  if (dico->type == OPT_TYPE_STRING)
  {
    if (!(string = strdup(str)))
      return (FAILURE);
    else
      memcpy((void *)data + dico->offset, &string, sizeof(char *));
  }
  ++ctrl->i;
  return (SUCCESS);
}

t_status		opt_get_data_simple(void *data,
					    t_controller *ctrl,
					    t_opt_dico const *dico,
					    int *i)
{
  if (!dico->data)
    return (SUCCESS);
  if (!ctrl->argv[ctrl->i][*i])
  {
    ++ctrl->i;
    *i = -1;
    return (opt_get_data(data, ctrl, dico, ctrl->argv[ctrl->i]));
  }
  return (opt_get_data(data, ctrl, dico, &ctrl->argv[ctrl->i][*i]));
}

t_status		opt_get_data_double(void *data,
					    t_controller *ctrl,
					    t_opt_dico const *dico)
{
  int			n;

  n = strlen(dico->str) + 2;
  if (!dico->data)
  {
    if (!ctrl->argv[ctrl->i][n])
    {
      ++ctrl->i;
      return (SUCCESS);
    }
    return (FAILURE);
  }
  if (!ctrl->argv[ctrl->i][n])
  {
    ++ctrl->i;
    return (opt_get_data(data, ctrl, dico, ctrl->argv[ctrl->i]));
  }
  if (ctrl->argv[ctrl->i][n] != '=')
    return (FAILURE);
  return (opt_get_data(data, ctrl, dico, &ctrl->argv[ctrl->i][n + 1]));
}
