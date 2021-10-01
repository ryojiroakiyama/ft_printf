#include "ft_printf.h"

void	initialize_store(t_store *t)
{
	t->flag = NON;
	t->width = INIT;
	t->prec = INIT;
	t->spec = INIT;
	t->body = 0;
	t->zero = 0;
	t->blank = 0;
	t->putnum = 0;
	t->prefix = "";
}

int	is_specifier(char c)
{
	int		i;
	char	*specs;

	specs = "cspdiuxX%";
	i = 0;
	while (i < SPEC_NUM)
	{
		if (specs[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	cnt_digit(unsigned long long n, unsigned long long div)
{
	int		cnt;

	cnt = 1;
	while (n >= div)
	{
		n /= div;
		cnt++;
	}
	return (cnt);
}

int	ft_strnlen(const char *s, int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		while (s[i])
			i++;
	}
	else
	{
		while (s[i] && i < n)
			i++;
	}
	return (i);
}
