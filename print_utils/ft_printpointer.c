/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:36:00 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints a long unsigned integer as a hexadecimal string.
 *
 * @param addr The long unsigned integer to print.
 * @return The total number of characters printed.
 */
static int	print_long_as_hex(long unsigned addr)
{
	char	c;
	int		total;

	total = 0;
	if (addr >= 16)
	{
		total += print_long_as_hex(addr / 16);
		total += print_long_as_hex(addr % 16);
	}
	else
	{
		c = (addr % 16) + '0';
		if ((addr % 16) > 9)
			c = ((addr % 16) + 87);
		write(1, &c, 1);
		total++;
	}
	return (total);
}

/**
 * @brief Calculates the size of a hexadecimal representation
 * of a long unsigned integer.
 *
 * @param addr The long unsigned integer.
 * @return The size of the hexadecimal representation.
 */
static int	get_hex_size(long unsigned addr)
{
	int	total;

	total = 0;
	if (addr >= 16)
	{
		total += get_hex_size(addr / 16);
		total += get_hex_size(addr % 16);
	}
	else
		total++;
	return (total);
}

/**
 * @brief Prints a pointer address as a hexadecimal string with options.
 *
 * @param ptr The pointer to print.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
int	ft_printpointer(void *ptr, t_opt opt)
{
	long	addr;
	int		total;
	int		len;

	addr = (long unsigned)ptr;
	total = 0;
	if (ptr == NULL)
	{
		total += print_str("(nil)");
		return (total);
	}
	len = get_hex_size(addr) + 2;
	while (len + total < opt.min_width)
		total += print_char(' ');
	total += print_str("0x");
	total += print_long_as_hex(addr);
	while (total < opt.offset)
		total += print_char(' ');
	return (total);
}
