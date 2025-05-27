/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:54:15 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/05 18:03:33 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char *)b;
	while (len)
	{
		temp[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (temp);
}
