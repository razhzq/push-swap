/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:28:30 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/05 18:29:38 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}
