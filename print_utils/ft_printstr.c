/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:30:35 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints a string to the standard output.
 *
 * @param str Pointer to the string to print.
 * @return The total number of characters printed.
 */
int	print_str(char *str)
{
	int	cur;

	cur = 0;
	while (str[cur])
		write(1, &str[cur++], 1);
	return (cur);
}

/**
 * @brief Prints a string up to a specified size to the standard output.
 *
 * @param str Pointer to the string to print.
 * @param size The maximum number of characters to print.
 * @return The total number of characters printed.
 */
static int	print_str_size(char *str, int size)
{
	int	cur;

	if (size == -1)
		return (print_str(str));
	cur = 0;
	while (str[cur] && cur < size)
		write(1, &str[cur++], 1);
	return (cur);
}

/**
 * @brief Prints a string with options to the standard output.
 *
 * @param str Pointer to the string to print.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
int	ft_printstr(char *str, t_opt opt)
{
	int	cur;
	int	len;

	cur = 0;
	if (!str)
		len = 6;
	else
		len = ft_strlen(str);
	while (cur + len < opt.min_width)
		cur += print_char(' ');
	if (!opt.dot)
		opt.precision = -1;
	if (!str)
		cur += print_str_size("(null)", opt.precision);
	else
		cur += print_str_size(str, opt.precision);
	while (cur < opt.offset)
		cur += print_char(' ');
	return (cur);
}
