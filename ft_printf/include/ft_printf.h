/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademarti <ademarti@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:07:02 by ademarti          #+#    #+#             */
/*   Updated: 2024/01/10 14:53:45 by ademarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		data_type_check(const char *s, va_list args_copy);
int		writeformat(const char *s, va_list args_copy);
int		ft_printf(const char *format, ...);
int		ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_string(char *str);
int		ft_putnbr_fd_un(unsigned int n, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_hexa_lowercase(unsigned int c);
int		ft_hexa_uppercase(unsigned int c);
int		ft_print_ptr(void *ptr);
int		ft_put_ptr(unsigned long long num);

#endif
