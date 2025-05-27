/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:58:06 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 19:00:41 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	len_n;

	i = 0;
	j = 0;
	len_n = ft_strlen((char *)needle);
	if (!len_n)
		return ((char *)haystack);
	while (haystack[i] != '\0' && len_n <= len)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
			j = 0;
		}
		len--;
		i++;
	}
	return (NULL);
}
