/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:27:26 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 18:38:57 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_sub_string(char *s, char c)
{
	unsigned int	count;
	int				i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

int	count_string_len(char *s, char c, int startIndex)
{
	int	len;

	len = 0;
	while (s[startIndex] != '\0' && s[startIndex] != c)
	{
		len++;
		startIndex++;
	}
	return (len);
}

char	*allo_string(char *s, char c, int startIndex)
{
	int		len;
	int		i;
	char	*temp;

	i = 0;
	len = count_string_len(s, c, startIndex);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (temp == NULL)
		return (NULL);
	while (i < len)
	{
		temp[i] = s[startIndex + i];
		i++;
	}
	temp[len] = '\0';
	return (temp);
}

int	fill_arr(char **arr, char *s, char c)
{
	int	i;
	int	arr_count;

	i = 0;
	arr_count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			arr[arr_count] = allo_string(s, c, i);
			if (arr[arr_count] == NULL)
				return (1);
			arr_count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	count;
	char			**temp;

	if (s == NULL)
		return (NULL);
	count = count_sub_string((char *)s, c);
	temp = (char **)malloc(sizeof(char *) * (count + 1));
	if (temp == NULL)
		return (NULL);
	if (fill_arr(temp, (char *)s, c) == 1)
	{
		free(temp);
		return (NULL);
	}
	temp[count] = NULL;
	return (temp);
}
