#include "roucas_io.h"
#include <stdio.h>

/*
** Usage: 
** - ./roucas_cli 			-> charge data/stock.csv
** - ./roucas_cli path.csv 	-> charge path.csv
**
** Retour:
** - 0 si OK
** - 1 si erreur (load_products a echoue)
*/

int	main(int ac, char **av)
{
	const char	*path;
	t_product	*products;

	path = "data/stock.csv";
	if (ac == 2)
		path = av[1];
	else if (ac > 2)
	{
		fprintf(stderr, "usage: %s [path_to_csv]\n", av[0]);
		return (1);
	}
	products = NULL;
	if (load_products(path, &products) != 0)
		return (1);
	free_products(products);
	return (0);
}
