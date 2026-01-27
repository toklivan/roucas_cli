#include "roucas_io.h"
#include <stdio.h>
#include <string.h>

/* Fonctions externes (defineies dans d'autres .c). */
int			split_csv_7(char *line, char *fields[7]);
char			*trim_inplace(char *s);
int			has_space(const char *s);
int			parse_double_strict(const char *s, double *out);
int			parse_int_strict_nonneg(const char *s, int *out);
t_product	*create_product(const char *id, const char *name,
						const char *category, double buy_price,
						double sell_price, int stock, int low_threshold);

/* check_header: lit+valide la 1ere ligne. */
int	check_header(FILE *fp, char *buffer, size_t n)
{
	if (!fgets(buffer, n, fp))
	{
		fprintf(stderr, "roucas_cli: empty CSV\n");
		return (1);
	}
	buffer[strcspn(buffer, "\n")] = '\0';
	if (strcmp(buffer,
			"id,name,category,buy_price,sell_price,stock,low_threshold") != 0)
	{
		fprintf(stderr, "roucas_cli: invalid CSV header\n");
		return (1);
	}
    return (0);
}

/* append_product: ajoute en fin  en 0(1) via tail. */
void	append_product(t_product **head, t_product **tail, t_product *newp)
{
	if (*head == NULL)
	{
		*head = newp;
		*tail = newp;
	}
	else
	{
		(*tail)->next = newp;
		*tail = newp;
	}
}

/* parse_line_product: split/trim/valide + cree un produit. */
t_product	*parse_line_product(char *buffer, int line_no,
		t_product *head)
{
	char	*fields[7];
	double	buy_price;
	double	sell_price;
	int		stock;
	int		low_threshold;

	buffer[strcspn(buffer, "\n")] = '\0';
	if (buffer[0] == '\0')
		return ((t_product *)1);
	if (split_csv_7(buffer, fields) != 0)
	{
		fprintf(stderr, "roucas_cli: bad format line %d\n", line_no);
		return (NULL);
	}
	fields[0] = trim_inplace(fields[0]);
	fields[1] = trim_inplace(fields[1]);
	fields[2] = trim_inplace(fields[2]);
	fields[3] = trim_inplace(fields[3]);
	fields[4] = trim_inplace(fields[4]);
	fields[5] = trim_inplace(fields[5]);
	fields[6] = trim_inplace(fields[6]);
	if (fields[0][0] == '\0' || fields[1][0] == '\0' || fields[2][0] == '\0')
	{
		fprintf(stderr, "roucas_cli: empty text field line %d\n", line_no);
		return (NULL);
	}
	if (has_space(fields[0]))
	{
		fprintf(stderr, "roucas_cli: invalid id (spaces) line %d\n", line_no);
		return (NULL);
	}
	if (parse_double_strict(fields[3], &buy_price) != 0
		|| parse_double_strict(fields[4], &sell_price) != 0
		|| parse_int_strict_nonneg(fields[5], &stock) != 0
		|| parse_int_strict_nonneg(fields[6], &low_threshold) != 0)
	{
		fprintf(stderr, "roucas_cli: bad number line %d\n", line_no);
		return (NULL);
	}
	if (find_product_by_id(head, fields[0]) != NULL)
	{
		fprintf(stderr, "roucas_cli: duplicate id '%s' line %d\n", fields[0],
			line_no);
		return (NULL);
	}
	return (create_product(fields[0], fields[1], fields[2], buy_price,
			sell_price, stock, low_threshold));
}

/* load_products: CSV -> liste chainee. */
int	load_products(const char *path, t_product **products)
{
	FILE		*fp;
	char		buffer[1024];
	int			line_no;
	t_product	*head;
	t_product	*tail;
	t_product	*newp;

	line_no = 2;
	head = NULL;
	tail = NULL;
	if (!path || !products)
		return (1);
	*products = NULL;
	fp = fopen(path, "r");
	if (!fp)
	{
		perror("roucas_cli: fopen");
		return (1);
	}
	if (check_header(fp, buffer, sizeof(buffer)))
	{
		fclose(fp);
		return (1);
	}
	while (fgets(buffer, sizeof(buffer), fp))
	{
		newp = parse_line_product(buffer, line_no++, head);
		if (newp == (t_product *)1)
			continue ;
		if (!newp)
		{
			free_products(head);
			fclose(fp);
			return (1);
		}
		append_product(&head, &tail, newp);
	}
	fclose(fp);
	*products = head;
	return (0);
}
