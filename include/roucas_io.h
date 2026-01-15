#ifndef ROUCAS_IO_H
# define ROUCAS_IO_H

# include "roucas.h"

int			load_products(const char *path, t_product **products);
int			save_products(const char *path, t_product *products);
void		free_products(t_product *products);
t_product	*find_product_by_id(const char *id, t_product *products);

#endif
