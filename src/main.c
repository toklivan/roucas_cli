#include <stdio.h>
#include "roucas_io.h"

/*
** is_cmd
**
** Rôle :
** - Comparer argv[1] avec une commande attendue ("list" ou "stats").
**
** Pourquoi ne pas utiliser strcmp ?
** - Ici on fait simple et explicite, sans dépendances.
*/
static int is_cmd(const char *s, const char *cmd)
{
    int i;

    if (!s || !cmd)
        return (0);
    i = 0;
    while (s[i] && cmd[i] && s[i] == cmd[i])
        i++;
    return (s[i] == '\0' && cmd[i] == '\0');
}

/*
** print_usage
**
** Rôle :
** - Afficher l'usage minimal.
*/
static int print_usage(const char *prog)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  %s list [path_to_csv]\n", prog);
    fprintf(stderr, "  %s stats [path_to_csv]\n", prog);
    return (1);
}

int main(int argc, char **argv)
{
    const char  *path;
    t_product   *products;

    /* 1) Vérification arguments */
    if (argc < 2 || argc > 3)
        return (print_usage(argv[0]));

    /* 2) Chemin CSV (par défaut ou fourni) */
    path = "data/stock.csv";
    if (argc == 3)
        path = argv[2];

    /* 3) Charger les produits */
    products = NULL;
    if (load_products(path, &products) != 0)
        return (1);

    /* 4) Exécuter la commande */
    if (is_cmd(argv[1], "list"))
        print_products(products);
    else if (is_cmd(argv[1], "stats"))
        print_stats(products);
    else
    {
        free_products(products);
        return (print_usage(argv[0]));
    }

    /* 5) Toujours libérer */
    free_products(products);
    return (0);
}
