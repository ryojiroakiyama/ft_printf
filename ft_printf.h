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

void	ft_storenew_init(t_store *t);
int		ft_isspec(char c);
int		cnt_digit(unsigned long long n, unsigned long long div);
int		ft_strnlen(const char *s, int n);
void	setstore_various(t_store *store, unsigned long long nb);
void	put_flag_h(t_store *store, char c);
void	put_flag_z(t_store *store, char c);
void	put_flag_n(t_store *store, char c);
void	route_num2(unsigned long long nb, t_store *store,
			void (*g[])(t_store *, char));
void	route_c(t_store *store, va_list *ap, void (*g[])(t_store *, char));
void	route_s(t_store *store, va_list *ap, void (*g[])(t_store *, char));
void	route_num1(t_store *store, va_list *ap, void (*g[])(t_store *, char));
void	put_arg(t_store *store, va_list *ap);
void	setstore_width(t_store *store, const char *fmt, size_t *i, va_list *ap);
void	setstore_prec(t_store *store, const char *fmt, size_t *i, va_list *ap);
int		per_section(const char *fmt, size_t *i, va_list *ap);
int		ft_printf(const char *fmt, ...);

#endif