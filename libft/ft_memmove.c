/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:31:15 by zrebhi            #+#    #+#             */
/*   Updated: 2022/11/18 15:56:13 by zrebhi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*destcpy;
	char	*srccpy;
	int		overlap;

	if (dst == 0 && src == 0)
		return (0);
	destcpy = (char *)dst;
	srccpy = (char *)src;
	overlap = 0;
	i = -1;
	while (++i < len)
		if (&src[i] == &dst[0])
			overlap = 1;
	i = 0;
	while (i < len)
	{
		if (overlap == 1)
			destcpy[len - 1 - i] = srccpy[len - 1 - i];
		else
			destcpy[i] = srccpy[i];
		i++;
	}
	return (dst);
}
