/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_name_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:49:22 by hebatist          #+#    #+#             */
/*   Updated: 2025/03/17 18:21:46 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_strlen(const char *s)
{
	int	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ptr;
	int			i;
	int			len1;
	int			len2;

	i = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (ptr == NULL)
		return (NULL);
	while (++i < len1)
		ptr[i] = s1[i];
	i--;
	while (++i < len1 + len2)
		ptr[i] = s2[i - len1];
	ptr[i] = '\0';
	return (ptr);
}

int	get_n_len(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*alloc_str(int n, int *len)
{
	char	*str;

	if (n < 0)
		(*len)++;
	str = (char *)malloc(sizeof(char) * (*len + 1));
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = get_n_len(n);
	if (n == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = alloc_str(n, &len);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
