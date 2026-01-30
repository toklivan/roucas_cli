#include "roucas_io.h"
#include <stdio.h>

/*
** print_products
**
** Role:
**
	- Afficher la liste des produits sous forme de tableau simple sous forme de tableau aligne.
**
** Notes:
** - Largeurs fixes pour un affichage lisible en terminal.
** - Ne modifie pas la liste, n'alloue rien.
*/
void	print_products(t_product *products)
{
	/* En-tete */
	printf("%-10s  %-15s  %-15s  %7s  %7s  %7s  %5s\n", "ID", "NAME",
		"CATEGORY", "BUY", "SELL", "STOCK", "LOW");
	/* Ligne de separation */
	printf("-------------------------------------------------------------------------------\n");
	/* Lignes produits */
	while (products)
	{
		printf("%-10s  %-15s  %-15s  %7.2f  %7.2f  %7d  %5d\n", products->id,
			products->name, products->category, products->buy_price,
			products->sell_price, products->stock, products->low_threshold);
		products = products->next;
	}
}
