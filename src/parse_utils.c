#include <stdlib.h>

/* parse_double_strict: OK si s est un double strict (pas de junk). */
int	parse_double_strict(const char *s, double *out)
{
	char	*endptr;
	double	val;

	if (!s || *s == '\0')
		return (1);
	val = strtod(s, &endptr);
	if (endptr == s)
		return (1);
	if (*endptr != '\0')
		return (1);
	if (out)
		*out = val;
	return (0);
}

/* parse_int_strict_nonneg: OK si s est int >= 0 (strict + pas overflow int). */
int	parse_int_strict_nonneg(const char *s, int *out)
{
	char	*endptr;
	long	val;

	if (!s || *s == '\0')
		return (1);
	val = strtol(s, &endptr, 10);
	if (endptr == s)
		return (1);
	if (*endptr != '\0')
		return (1);
	if (val < 0)
		return (1);
	if (val > 2147483647L)
		return (1);
	if (out)
		*out = (int)val;
	return (0);
}
