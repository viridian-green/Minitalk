/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:55:08 by ademarti          #+#    #+#             */
/*   Updated: 2024/06/06 14:45:45 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_put_ptr(unsigned long long num)
{
	int	count;

	count = 0;
	if (num >= 16)
	{
		count += ft_put_ptr(num / 16);
		count += ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			count += ft_putchar_fd_((num + '0'), 1);
		else
		{
			count += ft_putchar_fd_((num - 10 + 'a'), 1);
		}
	}
	return (count);
}

int	ft_print_ptr(void *ptr)
{
	int					count;
	unsigned long long	un_ptr;

	un_ptr = (unsigned long long)ptr;
	count = 0;
	if (ptr == 0)
		count += write(1, "(nil)", 5);
	else
	{
		count += write(1, "0x", 2);
		count += ft_put_ptr(un_ptr);
	}
	return (count);
}
