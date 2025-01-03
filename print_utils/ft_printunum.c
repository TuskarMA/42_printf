/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:29:46 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints an unsigned number to the standard output.
 *
 * @param nl The unsigned number to print.
 * @return The total number of characters printed.
 */
int	print_unumber(unsigned long nl)
{
	int				total;
	unsigned long	num;

	total = 0;
	num = nl;
	if (num > 100)
		total += print_unumber(num / 10);
	else if (num == 100)
		total += print_str("10");
	else if ((num / 10) > 0)
		total += print_char((num / 10) + '0');
	total += print_char((num % 10) + '0');
	return (total);
}

/**
 * @brief Calculates the number of digits in an unsigned number.
 *
 * @param num The unsigned number.
 * @return The number of digits in the number.
 */
static int	number_of_digit(unsigned long num)
{
	int	cur;

	cur = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 10;
		cur++;
	}
	return (cur);
}

/**
 * @brief Gets the values for printing an unsigned number with options.
 *
 * @param prefix Pointer to the prefix character.
 * @param lp Pointer to the length of the prefix.
 * @param opt Pointer to the options structure.
 * @param num The unsigned number.
 * @return The length of the number.
 */
static int	get_values(char	*prefix, int *lp, t_opt *opt, unsigned long num)
{
	int	len;

	len = number_of_digit(num);
	*lp = len;
	if (opt->precision > len)
		*lp = opt->precision;
	*prefix = '0';
	if (opt->zero && opt->dot && opt->zero_offset > opt->precision)
		*prefix = ' ';
	if (!opt->zero)
		*prefix = ' ';
	if (opt->zero)
		opt->min_width = opt->zero_offset;
	if (opt->precision > opt->min_width)
		opt->min_width = opt->precision;
	return (len);
}

/**
 * @brief Prints an unsigned number with options.
 *
 * @param len The length of the number.
 * @param num The unsigned number.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
static int	print_u(int len, unsigned long num, t_opt opt)
{
	int	total;

	total = 0;
	if (num == 0 && opt.min_width && opt.min_width < len)
		total += print_char(' ');
	else if (num == 0 && opt.dot && !opt.precision && opt.min_width >= len)
		total += print_char(' ');
	else if (!(num == 0 && opt.dot && !opt.precision))
		total += print_unumber(num);
	return (total);
}

/**
 * @brief Prints an unsigned number with options.
 *
 * @param num The unsigned number.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
int	ft_printunum(unsigned long num, t_opt opt)
{
	int		total;
	int		len;
	int		len_prec;
	char	prefix;

	total = 0;
	len = get_values(&prefix, &len_prec, &opt, num);
	while (len_prec + total < opt.min_width)
		total += print_char(prefix);
	while (len + total < opt.min_width)
		total += print_char('0');
	total += print_u(len, num, opt);
	while (total < opt.offset)
		total += print_char(' ');
	return (total);
}
