#include "roucas_io.h"
#include <stdio.h>
#include <stdlib.h>
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

static char	*trim_inplace(char *s)
{
	char	*end;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
		return (s);
	end = s;
	while (*end)
		end++;
	end--;
	while (end > s && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}
	return (s);
}

static int	parse_double_strict(const char *s, double *out)
{
	char	*endptr;
	double	val;

	if (!s || *s == '\0')
		return (1);
	val = strtod(s, &endptr);
	if (endptr == s)
		return (1);
	if (*endptr != '\0')
		return (1);
	if (out)
		*out = val;
	return (0);
}

static int	parse_int_strict_nonneg(const char *s, int *out)
{
	char	*endptr;
	long	val;

	if (!s || *s == '\0')
		return (1);
	val = strtol(s, &endptr, 10);
	if (endptr == s)
		return (1);
	if (*endptr != '\0')
		return (1);
	if (val < 0)
		return (1);
	if (val > 2147483647L)
		return (1);
	if (out)
		*out = (int)val;
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
		for (int i = 0; i < 7; i++)
			fields[i] = trim_inplace(fields[i]);
		if (fields[0][0] == '\0' || fields[1][0] == '\0'
			|| fields[2][0] == '\0')
		{
			fprintf(stderr, "roucas_cli: invalid id (spaces) at line %d\n",
				line_no);
			fclose(fp);
			return (1);
		}
		{
			double 	buy_price;
			double 	sell_price;
			int 	stock;
			int 	low_threshold;

			if (parse_double_strict(fields[3], &buy_price) != 0
					|| parse_double_strict(fields[4], &sell_price) != 0
					|| parse_int_strict_nonneg(fields[5], &stock) != 0
					|| parse_int_strict_nonneg(fields[6], &low_threshold) != 0)
			{
				fprintf(stderr, "roucas_cli: invalid numeric field at line %d\n",
					line_no);
				fclose(fp);
				return (1);
			}
		}
		printf("OK line %d | id='%s'\n", line_no, fields[0]);
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
