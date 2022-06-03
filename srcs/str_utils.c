/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:49:37 by rmamison          #+#    #+#             */
/*   Updated: 2022/06/03 09:12:42 by rmamison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!*s1 || !*s2)
		return (0);
	while (n-- > 0)
	{
		if (*s1 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return (*s1 - *s2);
	}
	return (0);	
}

int	ft_strlen(const char *s)
{
	size_t	ret;

	if (!*s)
		return (0);
	ret = 0;
	while (*s++)
		ret++;
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	len_all;
	char	*str;
	int	j;
	
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (s2);
	else if (!s2)
		return (s1);

	len_all = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len_all + 1));
	j = 0;
	while (*s1)
		str[j++] = *s1++;
	while (*s2)
		str[j++] = *s2++;
	str[j] = '\0';
	return (str);
}
