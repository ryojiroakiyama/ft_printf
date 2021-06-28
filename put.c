#include "ft_printf.h"

void	put_flag_h(t_store *store, char c)
{
	while (*(store->prefix))
	{
		store->putnum += write(1, store->prefix, 1);
		store->prefix++;
	}
	while (store->zero)
	{
		store->putnum += write(1, "0", 1);
		store->zero--;
	}
	if (store->body)
	{
		store->putnum += write(1, &c, 1);
		store->body--;
	}
	while (store->blank && store->body == 0)
	{
		store->putnum += write(1, " ", 1);
		store->blank--;
	}
}

void	put_flag_z(t_store *store, char c)
{
	while (*(store->prefix))
	{
		store->putnum += write(1, store->prefix, 1);
		store->prefix++;
	}
	while (store->blank)
	{
		store->putnum += write(1, "0", 1);
		store->blank--;
	}
	if (store->body)
	{
		store->putnum += write(1, &c, 1);
		store->body--;
	}
}

void	put_flag_n(t_store *store, char c)
{
	while (store->blank)
	{
		store->putnum += write(1, " ", 1);
		store->blank--;
	}
	while (*(store->prefix))
	{
		store->putnum += write(1, store->prefix, 1);
		store->prefix++;
	}
	while (store->zero)
	{
		store->putnum += write(1, "0", 1);
		store->zero--;
	}
	if (store->body)
	{
		store->putnum += write(1, &c, 1);
		store->body--;
	}
}
