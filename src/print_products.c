#include <stdio.h>
#include "roucas_io.h"

/*
** print_products
** 
** Role:
** - Afficher une liste de produits sous forme de tableau simple.
**
** Notes:
** - N'alloue rien, ne modifie pas la liste>
** - Si products == NULL, affiche uniquement l'en tete.
*/
void    print_products(t_product *products)
{
    printf("ID\t\tNAME\t\tCATEGORY\tBUY\tSELL\tSTOCK\tLOW\n");
    while (products)
    {
        printf("%s\t%s\t%s\t%.2f\t%.2f\t%d\t%d\n",
            products->id,
            products->name,
            products->category,
            products->buy_price,
            products->sell_price,
            products->stock,
            products->low_threshold);
        products = products->next;
    }
}
