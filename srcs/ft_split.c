#include "pipex.h"

static	int	count_sep(const char *s, char sep)
{
	int 	ret;
	int	times;

	ret = 0;
	times = 0;
	while (*s)
	{
		if (*s != sep && times == 0)
		{
			ret++;
			times = 1;
		}
		else if (*s == sep)
			times = 0;
		s++;
	}
	return (ret);
}

static	int	len_word(const char	*s, char sep, int i)
{
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

static char	*word_send(const char *s, char sep, int	*pos, int size)
{
	char	*word;
	int	j;

	j = -1;
	word = malloc(sizeof(char) * size + 1);
	if (!word)
		return (NULL);
	while (s[*pos] && s[*pos] != sep)
		word[++j] = s[(*pos)++];
	word[j + 1] = '\0';
	return (word);
}

char	**ft_split(const char *s, char sep)
{
	char	**tab;
	int	i;
	int	j;
	int	size;

	tab = (char **)malloc(sizeof(char *) * (count_sep(s, sep) + 1));
	if (!tab)
		return NULL;
	j = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] != sep)
		{
			size = len_word(s, sep, i);
			tab[++j] = word_send(s, sep, &i, size);
		}
		else if (s[i] == sep)
			i++;
	}
	tab[j + 1] = NULL;
	return (tab);	
}
