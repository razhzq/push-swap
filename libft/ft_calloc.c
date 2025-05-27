/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:55:10 by muabdul-          #+#    #+#             */
/*   Updated: 2025/01/03 19:33:17 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	size_allo;
	void	*temp;

	size_allo = count * size;
	if (count && size && count > UINT_MAX / size)
		return (NULL);
	temp = malloc(size_allo);
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, size_allo);
	return (temp);
}
