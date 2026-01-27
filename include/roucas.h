#ifndef ROUCAS_H
# define ROUCAS_H

typedef struct s_product
{
	char				*id;
	char				*name;
	char				*category;
	double				buy_price;
	double				sell_price;
	int					stock;
	int					low_threshold;
	struct s_product	*next;
}						t_product;

t_product				*create_product(const char *id, const char *name,
							const char *category, double buy_price,
							double sell_price, int stock, int low_threshold);

#endif
