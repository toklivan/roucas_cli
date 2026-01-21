#include "roucas_io.h"
#include <stdio.h>
#include <string.h>

static int	split_csv_7(char *line, char *fields[7])
{
	int	i;

	if (!line)
		return (1);
	fields[0] = line;
	i = 1;
	while (*line && i < 7)
	{
		if (*line == ',')
		{
			*line = '\0';
			fields[i] = line + 1;
			i++;
		}
		line++;
	}
	if (i != 7)
		return (1);
	while (*line)
	{
		if (*line == ',')
			return (1);
		line++;
	}
	return (0);
}

int	load_products(const char *path, t_product **products)
{
	FILE	*fp;
	char	buffer[1024];
	char	*fields[7];
	int		line_no;

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
	if (strcmp(buffer,
			"id,name,category,buy_price,sell_price,stock,low_threshold") != 0)
	{
		fprintf(stderr, "roucas_cli: invalid CSV header\n");
		fclose(fp);
		return (1);
	}
	line_no = 2;
	while (fgets(buffer, sizeof(buffer), fp))
	{
		buffer[strcspn(buffer, "\n")] = '\0';
		if (buffer[0] == '\0')
		{
			line_no++;
			continue ;
		}
		if (split_csv_7(buffer, fields) != 0)
		{
			fprintf(stderr, "roucas_cli: invalid CSV line format at line %d\n",
				line_no);
			fclose(fp);
			return (1);
		}
		printf("Line %d fields:\n", line_no);
		printf("  id            = '%s'\n", fields[0]);
		printf("  name          = '%s'\n", fields[1]);
		printf("  category      = '%s'\n", fields[2]);
		printf("  buy_price     = '%s'\n", fields[3]);
		printf("  sell_price    = '%s'\n", fields[4]);
		printf("  stock         = '%s'\n", fields[5]);
		printf("  low_threshold = '%s'\n", fields[6]);
		line_no++;
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

