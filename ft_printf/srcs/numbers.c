/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:51:28 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/06 14:47:29 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putnbr_fd_(int n, int fd)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += write(fd, "-2147483648", 11);
		return (count);
	}
	if (n < 0)
	{
		count += ft_putchar_fd_('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_putnbr_fd_(n / 10, fd);
	}
	count += ft_putchar_fd_(n % 10 + '0', fd);
	return (count);
}

int	ft_putnbr_fd_un(unsigned int n, int fd)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putnbr_fd_(n / 10, fd);
	}
	count += ft_putchar_fd_(n % 10 + '0', fd);
	return (count);
}

int	ft_hexa_lowercase(unsigned int c)
{
	int	count;

	count = 0;
	if (c >= 16)
	{
		count += ft_hexa_lowercase(c / 16);
		count += ft_hexa_lowercase(c % 16);
	}
	else
	{
		if (c <= 9)
			count += ft_putchar_fd_((c + '0'), 1);
		else if (c == 0)
		{
			count += write(1, "0", 1);
			return (count);
		}
		else
		{
			count += ft_putchar_fd_((c - 10 + 'a'), 1);
		}
	}
	return (count);
}

int	ft_hexa_uppercase(unsigned int c)
{
	int	count;

	count = 0;
	if (c >= 16)
	{
		count += ft_hexa_uppercase(c / 16);
		count += ft_hexa_uppercase(c % 16);
	}
	else
	{
		if (c <= 9)
			count += ft_putchar_fd_((c + '0'), 1);
		else if (c == 0)
		{
			count += write(1, "0", 1);
			return (count);
		}
		else
		{
			count += ft_putchar_fd_((c - 10 + 'A'), 1);
		}
	}
	return (count);
}
