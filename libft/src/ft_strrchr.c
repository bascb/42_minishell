/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:31:18 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 05:10:26 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
Description:
	checks for the last instance of c in str.
Return Value:
	pointer to the last instance of c.
	NULL if non existent.
*/

char	*ft_strrchr(const char *str, int c)
{
	int	a;

	a = 0;
	while (*str)
	{		
		str++;
		a++;
	}
	while (a >= 0)
	{
		if (*str == (unsigned char) c)
			return ((char *)str);
		a--;
		str--;
	}
	return (0);
}
