#include "roucas_io.h"
#include <stdio.h>

/*
** print_usage
**
** Rôle:
** - Afficher l'aide minimale et retourner un code d'erreur (1).
*/
static int	print_usage(const char *prog)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "  %s list [path_to_csv]\n", prog);
	return (1);
}

/*
** main
**
** Rôle:
** - Point d'entrée CLI.
** - Implémente la commande 'list' (v1).
*/
int	main(int argc, char **argv)
{
	const char	*path;
	t_product	*products;

	if (argc < 2)
		return (print_usage(argv[0]));
	path = "data/stock.csv";
	if (argc >= 3)
		path = argv[2];
	if (argc > 3)
		return (print_usage(argv[0]));
	if (argv[1][0] != 'l' || argv[1][1] != 'i' || argv[1][2] != 's'
		|| argv[1][3] != 't' || argv[1][4] != '\0')
		return (print_usage(argv[0]));
	products = NULL;
	if (load_products(path, &products) != 0)
		return (1);
	print_products(products);
	free_products(products);
	return (0);
}
