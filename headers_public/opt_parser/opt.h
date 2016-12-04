/*
** opt.h for opt_parser in headers_public/opt_parser
**
** Made by Benoit Hamon
** Login   <hamon_e@epitech.net>
**
** Started on  Sun Dec 04 13:12:46 2016 Benoit Hamon
** Last update Sun Dec 04 13:12:58 2016 Benoit Hamon
*/

#ifndef HEADERS_PUBLIC_OPT_PARSER_OPT_H_
# define HEADERS_PUBLIC_OPT_PARSER_OPT_H_

typedef enum		e_opt_type
{
  OPT_TYPE_STRING,
  OPT_TYPE_NBR
}			t_opt_type;

typedef struct		s_opt_dico
{
  unsigned int		bit;
  char			c;
  char const		*str;
  bool			data;
  size_t		offset;
  t_opt_type		type;
}			t_opt_dico;

typedef struct		s_opt_name
{
  char			*str;
  struct s_opt_name	*next;
}			t_opt_name;

typedef struct		s_opt
{
  int			bit;
  void			*data;
  t_opt_name		*name;
}			t_opt;

t_opt			*opt_init(int argc,
				  char const *argv[],
				  size_t size,
				  t_opt_dico const dico[]);

#endif /* end of include guard: HEADERS_PUBLIC_OPT_PARSER_OPT_H_ */
