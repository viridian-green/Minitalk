/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:31 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/10 16:26:08 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	data_type_check(const char *s, va_list args_copy)
{
	int	i;

	i = 0;
	if (s[i] == 'c')
		return (ft_putchar_fd(va_arg(args_copy, int), 1));
	else if (s[i] == 's')
		return (ft_string(va_arg(args_copy, char *)));
	else if (s[i] == '%')
		return (write(1, "%", 1));
	else if (s[i] == 'd' || s[i] == 'i')
		return (ft_putnbr_fd(va_arg(args_copy, int), 1));
	else if (s[i] == 'u')
		return (ft_putnbr_fd_un(va_arg(args_copy, unsigned int), 1));
	else if (s[i] == 'x' )
		return (ft_hexa_lowercase(va_arg(args_copy, unsigned int)));
	else if (s[i] == 'X' )
		return (ft_hexa_uppercase(va_arg(args_copy, unsigned int)));
	else if (s[i] == 'p' )
		return (ft_print_ptr(va_arg(args_copy, void *)));
	return (-1);
}

int	writeformat(const char *s, va_list args_copy)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			size += data_type_check(&s[i], args_copy);
		}
		else
		{
			write(1, &s[i], 1);
			size++;
		}
		if (s[i] != '\0')
			i++;
	}
	va_end(args_copy);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	va_list	args_copy;
	int		len;

	va_start(args, format);
	va_copy(args_copy, args);
	len = writeformat(format, args_copy);
	va_end(args);
	return (len);
}
