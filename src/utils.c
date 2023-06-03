/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:24:33 by macarval          #+#    #+#             */
/*   Updated: 2023/06/03 18:53:30 by macarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*strchr_mod(const char *str, int c)
{
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
			{
				str++;
				return ((char *)str);
			}
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (0);
}

char	*strchr_rev(const char *str, int c)
{
	int			i;
	const char	*temp;

	i = 0;
	temp = str;
	if (str != NULL)
	{
		while (*str != '\0')
		{
			if (*str == (char) c)
				return ((char *)ft_substr(temp, 0, i));
			i++;
			str++;
		}
		if ((char) c == '\0' && *str == '\0')
			return ((char *)str);
	}
	return (0);
}

int	strcmp_mod(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	if (s1 && s2)
	{
		i = 0;
		len = ft_strlen(s1);
		if (len != ft_strlen(s2))
			return (1);
		while (i < len)
		{
			if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
			{
				return ((unsigned char) s1[i] - (unsigned char) s2[i]);
			}
			i++;
		}
		return (0);
	}
	return (1);
}

int	strcmp_order(const char *s1, const char *s2)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (s1[i] != s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (0);
}

int	isalnum_mod(char *c)
{
	int	r;
	int	i;

	i = 0;
	r = 0;
	while (c[++i] && r == 0)
	{
		if (!ft_isalnum(c[i]) && c[i] != '=')
			r = 1;
	}
	return (r);
}
