/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:02:18 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 19:35:01 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		start;
	int		end;
	char	*temp;

	len = ft_strlen((char *)s1);
	start = 0;
	end = len - 1;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	temp = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &s1[start], (end - start + 2));
	return (temp);
}
