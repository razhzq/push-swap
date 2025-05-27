/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:09:02 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/05 18:51:25 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	unsigned int	sub_len;
	char			*temp;

	if (s == NULL)
		return (0);
	s_len = ft_strlen((char *)s);
	if (start > s_len)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	sub_len += 1;
	temp = (char *)malloc(sizeof(char) * (sub_len));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, (s + start), sub_len);
	return (temp);
}
