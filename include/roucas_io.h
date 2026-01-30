#ifndef ROUCAS_IO_H
# define ROUCAS_IO_H

# include "roucas.h"

int			load_products(const char *path, t_product **products);
int			save_products(const char *path, t_product *products);
void		free_products(t_product *products);
t_product	*find_product_by_id(t_product *products, const char *id);
void        print_products(t_product *products);
void        print_stats(t_product *products);

#endif
