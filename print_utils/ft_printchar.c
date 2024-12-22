/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:33:01 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints a single character to the standard output.
 *
 * @param c The character to print.
 * @return Always returns 1.
 */
int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

/**
 * @brief Prints a character with padding options.
 *
 * @param c The character to print.
 * @param opt The options structure containing padding information.
 * @return The total number of characters printed.
 */
int	ft_printchar(char c, t_opt opt)
{
	int	cur;

	cur = 0;
	while (cur + 1 < opt.min_width)
		cur += print_char(' ');
	cur += print_char(c);
	while (cur < opt.offset)
		cur += print_char(' ');
	return (cur);
}
