/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:00:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:01:09 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = -1;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (++i < n && (s1[i] || s2[i]))
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

char	*ft_filldest(char *dest, int n, size_t len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		dest[0] = '-';
		n = -n;
	}
	if (n == 0)
		dest[0] = '0';
	while (n)
	{
		dest[len - i - 1] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	dest[len] = '\0';
	return (dest);
}

size_t	ft_retlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 0 || n == 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

int	ft_isnumber(char *str)
{
	char	*str1;

	str1 = str;
	while (*str1)
	{
		if (48 > *str1 || *str1 > 57)
			return (0);
		str1++;
	}
	return (1);
}

int	ft_checkargs(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i++]))
		{
			write(2, "The argument should be a number\n", 32);
			return (0);
		}
	}
	if (ft_atoi(argv[1]) < 1)
		return (0);
	return (1);
}
