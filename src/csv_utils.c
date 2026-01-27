#include <stddef.h>

/* split_csv_7: decoupe line en 7 champs (modifie line en place). */
int	split_csv_7(char *line, char *fields[7])
{
	int	i;

	if (!line)
		return (1);
	fields[0] = line;
	i = 1;
	while (*line && i < 7)
	{
		if (*line == ',')
		{
			*line = '\0';
			fields[i] = line + 1;
			i++;
		}
		line++;
	}
	if (i != 7)
		return (1);
	while (*line)
	{
		if (*line == ',')
			return (1);
		line++;
	}
	return (0);
}

/* trim_inplace: supprime espaces/tabs debut+fin, renvoie le nouveau debut. */
char	*trim_inplace(char *s)
{
	char	*end;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
		return (s);
	end = s;
	while (*end)
		end++;
	end--;
	while (end > s && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}
	return (s);
}

/* has_space: 1 si s contient espace/tab, sinon 0. */
int	has_space(const char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ' ' || *s == '\t')
			return (1);
		s++;
	}
	return (0);
}
