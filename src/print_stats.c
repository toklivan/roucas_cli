#include <stdio.h>
#include "roucas_io.h"

/*
** print_stats
**
** Role : 
** - Calculer et afficher des statistiques simples sur la liste de produits.
**
** Calculs
** - products_count : nombre de produits
** - total_stock    : somme des stocks
** - buy_value      : somme(stock * buy_price)
** - sell_value     : somme(stock * sell_price)
** - profit         : sell_value - buy_value
**
** Notes : 
** - Ne modifie pas la liste.
** - Pas d'allocation memoire.
*/
void    print_stats(t_product *products)
{
    int     count;
    int     total_stock;
    double  buy_value;
    double  sell_value;

    count = 0;
    total_stock = 0;
    buy_value = 0.0;
    sell_value = 0.0;

    while (products)
    {
        count++;
        total_stock += products->stock;
        buy_value += (double)products->stock * products->buy_price;
        sell_value += (double)products->stock * products->sell_price;
        products = products->next;
    }
    printf("Products: %d\n", count);
    printf("Total stock: %d\n", total_stock);
    printf("Buy value: %.2f\n", buy_value);
    printf("Sell value: %.2f\n", sell_value);
    printf("Potential profit: %.2f\n", sell_value - buy_value);
}
