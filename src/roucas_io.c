#include "roucas_io.h"
#include <stdio.h>
#include <string.h>

int	load_products(const char *path, t_product **products)
{
	FILE	*fp;
	char	buffer[1024];

	if (!path || !products)
		return (1);
	*products = NULL;
	fp = fopen(path, "r");
	if (!fp)
	{
		perror("roucas_cli: fopen");
		return (1);
	}
	if (!fgets(buffer, sizeof(buffer), fp))
	{
		fprintf(stderr, "roucas_cli: empty or unreadable CSV file\n");
		fclose(fp);
		return (1);
	}
	buffer[strcspn(buffer, "\n")] = '\0';
	if (strcmp(buffer, "id,name,category,buy_price,sell_price,stock,low_threshold") != 0)
	{
		fprintf(stderr, "roucas_cli: invalid CSV header\n");
		fclose(fp);
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
