/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_functions3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaryjan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 00:00:50 by mmaryjan          #+#    #+#             */
/*   Updated: 2021/06/29 00:01:09 by mmaryjan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	atoi;
	int	k;

	k = 1;
	atoi = 0;
	while ((*str == ' ') || (*str == '\f') || (*str == '\r')
		   || (*str == '\t') || (*str == '\v') || (*str == '\n'))
		str++;
	if ((*str == '+') || (*str == '-'))
	{
		if (*str == '-')
			k = -k;
		str++;
	}
	while ((*str >= '0') && (*str <= '9') && atoi <= 2147483647)
	{
		atoi = atoi * 10 + (*str - 48);
		str++;
	}
	if (atoi > 2147483647 && k == -1)
		return (53);
	if (atoi > 2147483647 && k == 1)
		return (-1);
	return (atoi * k);
}

size_t	ft_strlen(const char *str)
{
	int	k;

	k = 0;
	while (*str)
	{
		k++;
		str++;
	}
	return (k);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*src2;
	char		*dst2;

	dst2 = (char *)dst;
	src2 = (const char *)src;
	if (!n || dst == src)
		return (dst);
	while (n--)
	{
		*dst2++ = *src2++;
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * (len));
	if (!s2)
		return (NULL);
	s2 = ft_memcpy(s2, s1, len);
	return (s2);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*dest;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_retlen(n);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest = ft_filldest(dest, n, len);
	return (dest);
}
