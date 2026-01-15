#include "roucas_io.h"
#include <stdio.h>

int	load_products(const char *path, t_product **products)
{
	FILE	*fp;

	if (!path || !products)
		return (1);
	*products = NULL;
	fp = fopen(path, "r");
	if (!fp)
	{
		perror("roucas_cli: fopen");
		return (1);
	}
	fclose(fp);
	return (0);
}

int	save_products(const char *path, t_product *products)
{
	(void)path;
	(void)products;
	fprintf(stderr, "save_products: not implemented yet\n");
	return (1);
}
