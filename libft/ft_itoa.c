/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:03:43 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/05 19:19:29 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calculate_num(int n)
{
	int				len;
	unsigned int	num;

	num = n;
	if (n < 0)
		num = -n;
	len = 0;
	if (n <= 0)
		len++;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	unsigned int	num;

	num = n;
	if (n < 0)
		num = -n;
	i = calculate_num(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		str[0] = '-';
	while (num != 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
