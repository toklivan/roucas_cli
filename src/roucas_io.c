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

static int	has_space(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			return (1);
		s++;
	}
	return (0);
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

static char	*dup_str(const char *s)
{
	size_t	len;
	char	*copy;

	if (!s)
		return (NULL);
	len = strlen(s);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	memcpy(copy, s, len);
	copy[len] = '\0';
	return (copy);
}

static void	free_one_product(t_product *p)
{
	if (!p)
		return ;
	free(p->id);
	free(p->name);
	free(p->category);
	free(p);
}

static t_product	*create_product(const char *id, const char *name,
		const char *category, double buy_price, double sell_price, int stock,
		int low_threshold)
{
	t_product	*p;

	p = (t_product *)malloc(sizeof(t_product));
	if (!p)
		return (NULL);
	p->id = NULL;
	p->name = NULL;
	p->category = NULL;
	p->next = NULL;
	p->id = dup_str(id);
	p->name = dup_str(name);
	p->category = dup_str(category);
	if (!p->id || !p->name || !p->category)
	{
		free_one_product(p);
		return (NULL);
	}
	p->buy_price = buy_price;
	p->sell_price = sell_price;
	p->stock = stock;
	p->low_threshold = low_threshold;
	return (p);
}

int	load_products(const char *path, t_product **products)
{
	FILE		*fp;
	char		buffer[1024];
	char		*fields[7];
	int			line_no;
	t_product	*head;
	t_product	*tail;
		double buy_price;
		double sell_price;
		int stock;
		int low_threshold;
		t_product *newp;

	if (!path || !products)
		return (1);
	head = NULL;
	tail = NULL;
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
			free_products(head);
			fclose(fp);
			return (1);
		}
		fields[0] = trim_inplace(fields[0]);
		fields[1] = trim_inplace(fields[1]);
		fields[2] = trim_inplace(fields[2]);
		fields[3] = trim_inplace(fields[3]);
		fields[4] = trim_inplace(fields[4]);
		fields[5] = trim_inplace(fields[5]);
		fields[6] = trim_inplace(fields[6]);
		if (fields[0][0] == '\0' || fields[1][0] == '\0'
			|| fields[2][0] == '\0')
		{
			fprintf(stderr, "roucas_cli: empty text field at line %d\n",
				line_no);
			free_products(head);
			fclose(fp);
			return (1);
		}
		if (has_space(fields[0]))
		{
			fprintf(stderr,
				"roucas_cli: invalid id (space not allowed) at line %d\n", line_no);
			free_products(head);
			fclose(fp);
			return (1);
		}
		if (parse_double_strict(fields[3], &buy_price) != 0
			|| parse_double_strict(fields[4], &sell_price) != 0
			|| parse_int_strict_nonneg(fields[5], &stock) != 0
			|| parse_int_strict_nonneg(fields[6], &low_threshold) != 0)
		{
			fprintf(stderr, "roucas_cli: invalid numeric field at line %d\n",
				line_no);
			free_products(head);
			fclose(fp);
			return (1);
		}
		if (find_product_by_id(head, fields[0]) != NULL)
		{
			fprintf(stderr, "roucas_cli: duplicate id '%s' at line %d\n",
				fields[0], line_no);
			free_products(head);
			fclose(fp);
			return (1);
		}
		newp = create_product(fields[0], fields[1], fields[2], buy_price,
				sell_price, stock, low_threshold);
		if (!newp)
		{
			fprintf(stderr, "roucas_cli: allocation failed at line %d\n",
				line_no);
			free_products(head);
			fclose(fp);
			return (1);
		}
		if (!head)
		{
			head = newp;
			tail = newp;
		}
		else
		{
			tail->next = newp;
			tail = newp;
		}
		line_no++;
	}
	fclose(fp);
	*products = head;
	return (0);
}

int	save_products(const char *path, t_product *products)
{
	(void)path;
	(void)products;
	fprintf(stderr, "save_products: not implemented yet\n");
	return (1);
}
