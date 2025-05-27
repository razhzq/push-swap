/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:43:06 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 19:34:17 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*temp;

	i = 0;
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	temp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	while (*s1 != '\0')
	{
		temp[i] = *s1;
		s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		temp[i] = *s2;
		s2++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
