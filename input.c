#include "ft_printf.h"

void	put_arg(t_store *store, va_list *ap)
{
	void	(*f[SPEC_NUM])(t_store *, va_list *, void (*g[])(t_store *, char));
	void	(*g[FLAG_NUM])(t_store *, char);

	f[SPEC_C] = route_c;
	f[SPEC_S] = route_s;
	f[SPEC_P] = route_num1;
	f[SPEC_D] = route_num1;
	f[SPEC_I] = route_num1;
	f[SPEC_U] = route_num1;
	f[SPEC_SX] = route_num1;
	f[SPEC_LX] = route_num1;
	f[SPEC_PER] = route_c;
	g[NON] = put_flag_n;
	g[HYPHEN] = put_flag_h;
	g[ZERO] = put_flag_z;
	f[store->spec](store, ap, g);
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

void	setstore_prec(t_store *store, const char *fmt, size_t *i, va_list *ap)
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

int	per_section(const char *fmt, size_t *i, va_list *ap)
{
	t_store	store;

	ft_storenew_init(&store);
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
	setstore_prec(&store, fmt, i, ap);
	store.spec = ft_isspec(fmt[*i]);
	if (store.spec == -1)
		return (-1);
	put_arg(&store, ap);
	return (store.putnum);
}	

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	size_t		i;
	int			sum;
	int			ret;

	i = 0;
	sum = 0;
	va_start(ap, fmt);
	while (fmt[i])
	{
		if (fmt[i] == '%')
			ret = per_section(fmt, &i, &ap);
		else
			ret = write(1, &fmt[i], 1);
		if (ret == -1)
			break ;
		sum += ret;
		i++;
	}
	va_end(ap);
	if (ret == -1)
		return (-1);
	return (sum);
}
