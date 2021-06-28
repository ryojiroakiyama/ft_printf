#include "ft_printf.h"

void	route_c(t_store *store, va_list *ap, void (*g[])(t_store *, char))
{
	unsigned char	c;

	if (store->spec == SPEC_C)
		c = (unsigned char)va_arg(*ap, int);
	if (store->spec == SPEC_PER)
		c = '%';
	store->body = 1;
	if (store->body < store->width)
		store->blank = store->width - store->body;
	g[store->flag](store, c);
}

void	route_s(t_store *store, va_list *ap, void (*g[])(t_store *, char))
{
	char	*str;

	str = (char *)va_arg(*ap, char *);
	if (!str)
		str = "(null)";
	if (store->prec == DOT_ONLY)
		store->prec = 0;
	store->body = ft_strnlen(str, store->prec);
	if (store->body < store->width)
		store->blank = store->width - store->body;
	if (store->body == 0)
		g[store->flag](store, 0);
	while (store->body)
	{
		g[store->flag](store, *str);
		str++;
	}
}

void	route_num2(unsigned long long nb,
			t_store *store, void (*g[])(t_store *, char))
{
	if (nb >= (unsigned long long)store->base)
	{
		route_num2(nb / store->base, store, g);
		route_num2(nb % store->base, store, g);
	}
	else
		g[store->flag](store, store->basestr[nb]);
}

void	setstore_various(t_store *store, unsigned long long nb)
{
	if (store->spec == SPEC_D || store->spec == SPEC_I || store->spec == SPEC_U)
	{
		store->basestr = "0123456789";
		store->base = 10;
	}
	if (store->spec == SPEC_SX || store->spec == SPEC_P)
		store->basestr = "0123456789abcdef";
	if (store->spec == SPEC_LX)
		store->basestr = "0123456789ABCDEF";
	if (store->spec == SPEC_SX || store->spec == SPEC_LX || store->spec == SPEC_P)
		store->base = 16;
	if ((store->prec == 0 || store->prec == DOT_ONLY) && nb == 0)
		store->body = 0;
	else
		store->body = cnt_digit(nb, store->base);
	if (!(store->prec == INIT || store->prec == INVALID) && store->flag == ZERO)
		store->flag = NON;
	if (store->spec == SPEC_P)
		store->prefix = "0x";
}

void	route_num1(t_store *store, va_list *ap, void (*g[])(t_store *, char))
{
	unsigned long long	nb;
	long				tmp_nb;
	int					tmp_len;

	if (store->spec == SPEC_D || store->spec == SPEC_I)
	{
		tmp_nb = (int)va_arg(*ap, int);
		if (tmp_nb < 0)
		{
			store->prefix = "-";
			tmp_nb *= -1;
		}
		nb = tmp_nb;
	}
	if (store->spec == SPEC_SX || store->spec == SPEC_LX || store->spec == SPEC_U)
		nb = (unsigned int)va_arg(*ap, unsigned int);
	if (store->spec == SPEC_P)
		nb = (unsigned long long)va_arg(*ap, unsigned long long);
	setstore_various(store, nb);
	if (store->body < store->prec)
		store->zero = store->prec - store->body;
	tmp_len = ft_strnlen(store->prefix, -1) + store->body + store->zero;
	if (tmp_len < store->width)
		store->blank = store->width - (tmp_len);
	route_num2(nb, store, g);
}
