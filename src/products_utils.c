#include <stdlib.h>
#include <string.h>
#include "roucas_io.h"

t_product   *find_product_by_id(const char *id, t_product *products)
{
    if (!id)
        return NULL;
    while (products)
    {
        if (products->id && strcmp(products->id, id) == 0)
            return products;
        products = products->next;
    }
    return NULL;
}

void    free_products(t_product *products)
{
    t_product   *next;

    while (products)
    {
        next = products->next;
        free(products->id);
        free(products->name);
        free(products->category);
        free(products);
        products = next;
    }
}
