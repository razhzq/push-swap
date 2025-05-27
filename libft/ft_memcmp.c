/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:14:46 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 18:16:20 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr = (const unsigned char *)s1;
	const unsigned char	*ptr2 = (const unsigned char *)s2;

	while (n > 0)
	{
		if (*ptr != *ptr2)
			return (*ptr - *ptr2);
		ptr++;
		ptr2++;
		n--;
	}
	return (0);
}
