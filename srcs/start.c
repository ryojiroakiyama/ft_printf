#include "ft_printf.h"

void	put_arg(t_store *store, va_list *ap)
{
	void	(*route[SPEC_NUM])(t_store *, va_list *, void (*put[])(t_store *, char));
	void	(*put[FLAG_NUM])(t_store *, char);

	route[SPEC_C] = route_char;
	route[SPEC_S] = route_str;
	route[SPEC_P] = route_num;
	route[SPEC_D] = route_num;
	route[SPEC_I] = route_num;
	route[SPEC_U] = route_num;
	route[SPEC_SX] = route_num;
	route[SPEC_LX] = route_num;
	route[SPEC_PER] = route_char;
	put[NON] = put_flag_non;
	put[HYPHEN] = put_flag_hyphen;
	put[ZERO] = put_flag_zero;
	route[store->spec](store, ap, put);
}

void	setstore_width(t_store *store, const char *fmt, size_t *i, va_list *ap)
{
	int	nb;

	nb = 0;
	if (fmt[*i] == '*')
	{
		nb = (int)va_arg(*ap, int);
		if (nb < 0)
		{
			store->flag = HYPHEN;
			nb *= -1;
		}
		store->width = nb;
		(*i)++;
	}
	else if ('1' <= fmt[*i] && fmt[*i] <= '9')
	{
		while ('0' <= fmt[*i] && fmt[*i] <= '9')
		{
			nb = nb * 10 + (fmt[*i] - '0');
			(*i)++;
		}
		store->width = nb;
	}
}

void	setstore_precision(t_store *store, const char *fmt, size_t *i, va_list *ap)
{
	int	nb;

	nb = 0;
	if (fmt[*i] != '.')
		return ;
	(*i)++;
	if (fmt[*i] == '*')
	{
		nb = (int)va_arg(*ap, int);
		if (nb < 0)
			nb = INVALID;
		(*i)++;
		store->prec = nb;
	}
	else if ('0' <= fmt[*i] && fmt[*i] <= '9')
	{
		while ('0' <= fmt[*i] && fmt[*i] <= '9')
		{
			nb = nb * 10 + (fmt[*i] - '0');
			(*i)++;
		}
		store->prec = nb;
	}
	else
		store->prec = DOT_ONLY;
}

int	percent_appeared(const char *fmt, size_t *i, va_list *ap)
{
	t_store	store;

	initialize_store(&store);
	(*i)++;
	while (fmt[*i] == '0')
	{
		store.flag = ZERO;
		(*i)++;
	}
	while (fmt[*i] == '-' || fmt[*i] == '0')
	{
		store.flag = HYPHEN;
		(*i)++;
	}
	setstore_width(&store, fmt, i, ap);
	setstore_precision(&store, fmt, i, ap);
	store.spec = is_specifier(fmt[*i]);
	if (store.spec == -1)
		return (-1);
	put_arg(&store, ap);
	return (store.putnum);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	size_t		i;
	int			put_num;
	int			ret;

	i = 0;
	put_num = 0;
	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
			ret = percent_appeared(fmt, &i, &ap);
		else
			ret = write(1, &fmt[i], 1);
		if (ret == -1)
			break ;
		put_num += ret;
		i++;
	}
	va_end(ap);
	if (ret == -1)
		return (-1);
	return (put_num);
}
