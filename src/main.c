#include "roucas_io.h"
#include <stdio.h>

int	main(void)
{
	t_product	*products;
	int			status;

	products = NULL;
	status = load_products("data/stock.csv", &products);
	if (status != 0)
	{
		fprintf(stderr, "roucas_cli: failed to load CSV\n");
		return (1);
	}
	printf("roucas_cli: CSV loaded successfully (WIP)\n");
	free_products(products);
	return (0);
}
