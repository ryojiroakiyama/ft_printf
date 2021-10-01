#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define INIT -1
# define INVALID -2
# define DOT_ONLY -3

enum e_flag
{
	NON,
	HYPHEN,
	ZERO,
	FLAG_NUM
};

enum e_spec
{
	SPEC_C,
	SPEC_S,
	SPEC_P,
	SPEC_D,
	SPEC_I,
	SPEC_U,
	SPEC_SX,
	SPEC_LX,
	SPEC_PER,
	SPEC_NUM
};

typedef struct s_store
{
	int		flag;
	int		width;
	int		prec;
	int		spec;
	int		body;
	int		zero;
	int		blank;
	char	*prefix;
	char	*basestr;
	int		base;
	int		putnum;
}	t_store;

// start.c
void	put_arg(t_store *store, va_list *ap);
void	setstore_width(t_store *store, const char *fmt, size_t *i, va_list *ap);
void	setstore_precision(t_store *store, const char *fmt, size_t *i, va_list *ap);
int		percent_appeared(const char *fmt, size_t *i, va_list *ap);
int		ft_printf(const char *fmt, ...);

// pretreate_to_put.c
void	route_char(t_store *store, va_list *ap, void (*put[])(t_store *, char));
void	route_str(t_store *store, va_list *ap, void (*put[])(t_store *, char));
void	route_num(t_store *store, va_list *ap, void (*put[])(t_store *, char));

// put.c
void	put_flag_hyphen(t_store *store, char c);
void	put_flag_zero(t_store *store, char c);
void	put_flag_non(t_store *store, char c);

// utils.c
void	initialize_store(t_store *t);
int		is_specifier(char c);
int		cnt_digit(unsigned long long n, unsigned long long div);
int		ft_strnlen(const char *s, int n);

#endif