/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:39:27 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 18:41:03 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*temp;

	len = ft_strlen((char *)s1) + 1;
	temp = (char *)malloc(sizeof(char) * len);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, s1, len);
	return (temp);
}
