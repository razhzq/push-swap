/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:10:45 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 18:14:25 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;

	ptr = (const unsigned char *)s;
	while (n != 0)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
