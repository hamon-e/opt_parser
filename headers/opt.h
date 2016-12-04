/*
** opt.h for opt_parser in headers
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Dec 04 13:07:59 2016 Benoit Hamon
** Last update Sun Dec 04 13:36:43 2016 Benoit Hamon
*/

#ifndef HEADERS_OPT_H_
# define HEADERS_OPT_H_

# include "opt_parser/opt.h"

typedef struct		s_controller
{
  int			i;
  char const		**argv;
}			t_controller;

t_status		opt_get_data_simple(void *data,
					    t_controller *ctrl,
					    t_opt_dico const *dico,
					    int *i);
t_status		opt_get_data_double(void *data,
					    t_controller *ctrl,
					    t_opt_dico const *dico);

t_status		the_opt_atoi(char const *str, int *nbr);

#endif /* end of include guard: HEADERS_OPT_H_ */
