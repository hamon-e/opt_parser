/*
** test.c for Opt_parser in sources
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Mon May 02 00:35:02 2016 Benoit Hamon
** Last update Sun Dec 04 13:09:15 2016 Benoit Hamon
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "tools/tools.h"
#include "opt.h"

int			opt_parse_simple(void *data,
					 t_controller *ctrl,
					 t_opt_dico const dico[])
{
  int			bit;
  int			i;
  int			j;

  i = 1;
  bit = 0;
  while (i > 0 && ctrl->argv[ctrl->i] && ctrl->argv[ctrl->i][i])
  {
    j = 0;
    while (dico[j].bit && dico[j].c != ctrl->argv[ctrl->i][i])
      ++j;
    if (!dico[j].bit)
      return (FAILURE);
    bit |= dico[j].bit;
    ++i;
    if (!!opt_get_data_simple(data, ctrl, &dico[j], &i))
      return (FAILURE);
  }
  if (i > 0 && ctrl->argv[ctrl->i])
    ++ctrl->i;
  return (bit);
}

int			opt_parse_double(void *data,
					 t_controller *ctrl,
					 t_opt_dico const dico[])
{
  int			bit;
  int			i;

  bit = 0;
  i = 0;
  while (dico[i].bit
	 && strncmp(dico[i].str,
		    ctrl->argv[ctrl->i] + 2,
		    strlen(dico[i].str)))
    ++i;
  if (!dico[i].bit)
    return (FAILURE);
  bit |= dico[i].bit;
  return (!!opt_get_data_double(data, ctrl, &dico[i]) ? FAILURE : bit);
}

t_status		opt_parse_name(t_opt_name **name,
				       t_controller *ctrl)
{
  t_opt_name		*elem;

  if (!(elem = malloc(sizeof(t_opt_name)))
      || !(elem->str = strdup(ctrl->argv[ctrl->i])))
    return (FAILURE);
  elem->next = NULL;
  ++ctrl->i;
  the_pushback((void **)name, elem, offsetof(t_opt_name, next));
  return (SUCCESS);
}

int			opt_parse(t_opt *opt,
				  t_controller *ctrl,
				  t_opt_dico const dico[])
{
  int			bit;
  int			tmp;

  bit = 0;
  while (ctrl->argv[ctrl->i])
  {
    if (ctrl->argv[ctrl->i][0] == '-' && ctrl->argv[ctrl->i][1] == '-'
	&& ctrl->argv[ctrl->i][2])
    {
      if ((tmp = opt_parse_double(opt->data, ctrl, dico)) == FAILURE)
	return (FAILURE);
    }
    else if (ctrl->argv[ctrl->i][0] == '-' && ctrl->argv[ctrl->i][1] != '-'
	     && ctrl->argv[ctrl->i][1])
    {
      if ((tmp = opt_parse_simple(opt->data, ctrl, dico)) == FAILURE)
	return (FAILURE);
    }
    else if ((tmp = opt_parse_name(&opt->name, ctrl)) == FAILURE)
      return (FAILURE);
    bit |= tmp;
  }
  return (bit);
}

t_opt			*opt_init(int __attribute__((unused))argc,
				  char const *argv[],
				  size_t size,
				  t_opt_dico const dico[])
{
  t_controller		ctrl;
  t_opt			*opt;

  ctrl.argv = argv;
  ctrl.i = 0;
  if (!(opt = malloc(sizeof(t_opt))))
    return (NULL);
  memset(opt, 0, sizeof(t_opt));
  if (!(opt->data = malloc(size)))
    return (the_free(1, FREE_OPT, opt));
  memset(opt->data, 0, size);
  if ((opt->bit = opt_parse(opt, &ctrl, dico)) == FAILURE)
    return (the_free(2, FREE_STR, opt->data, FREE_OPT, opt));
  return (opt);
}
