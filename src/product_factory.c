#include "roucas.h"
#include <stdlib.h>
#include <string.h>

/*dup_str: copie s (malloc). */
char	*dup_str(const char *s)
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

/* free_one_product: libere un node (utile en cas d'echec partiel). */
void	free_one_product(t_product *p)
{
	if (!p)
		return ;
	free(p->id);
	free(p->name);
	free(p->category);
	free(p);
}

/* create_product: construit un t_product (malloc + copies strings). */
t_product	*create_product(const char *id, const char *name,
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
