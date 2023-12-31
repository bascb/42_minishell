/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:23:08 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/27 00:31:52 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_dputstr(int fd, char *s)
{
	int	ret;

	ret = 0;
	if (!s)
		return (write(fd, "(null)", 6));
	while (*s)
	{
		ret += write(fd, &*s, 1);
		s++;
	}
	return (ret);
}

int	ft_dputdigit(int fd, long long int n, int base, char	*basestr)
{
	int		ret;

	ret = 0;
	if (n < 0 && base == 10)
	{
		ret += write(fd, "-", 1);
		n *= -1;
	}
	if (n >= base)
		ret += ft_dputdigit(fd, n / base, base, basestr);
	ret += write(fd, &basestr[n % base], 1);
	return (ret);
}

int	ft_dputpointer(int fd, unsigned long int n, int flag, char	*basestr)
{
	int		ret;

	ret = 0;
	if (!n)
		return (write(fd, "(nil)", 5));
	if (flag == 1)
		ret += write(fd, "0x", 2);
	if (n >= 16)
		ret += ft_dputpointer(fd, n / 16, 0, basestr);
	ret += write(fd, &basestr[n % 16], 1);
	return (ret);
}

int	conversions(int fd, const char *str, va_list p)
{
	int	ret;
	int	c;

	ret = 0;
	c = 0;
	if (*str == 'c')
	{
		c = va_arg(p, int);
		ret += write(fd, &c, 1);
	}
	else if (*str == 's')
		ret += ft_dputstr(fd, va_arg(p, char *));
	else if (*str == 'd' || *str == 'i')
		ret += ft_dputdigit(fd, va_arg(p, int), 10, DECIMAL);
	else if (*str == 'u')
		ret += ft_dputdigit(fd, va_arg(p, unsigned int), 10, DECIMAL);
	else if (*str == 'x')
		ret += ft_dputdigit(fd, va_arg(p, unsigned int), 16, HEXA);
	else if (*str == 'X')
		ret += ft_dputdigit(fd, va_arg(p, unsigned int), 16, HEXA2);
	else if (*str == 'p')
		ret += ft_dputpointer(fd, va_arg(p, unsigned long int), 1, HEXA);
	else if (*str == '%')
		ret += write(fd, "%%", 1);
	return (ret);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		ret;
	va_list	p;

	ret = 0;
	va_start(p, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ret += conversions(fd, &*str, p);
		}
		else
			ret += write(fd, &*str, 1);
		str++;
	}
	va_end(p);
	return (ret);
}
