/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:32:31 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints a minus sign and adjusts the number and length.
 *
 * @param nl Pointer to the number.
 * @param len Pointer to the length of the number.
 * @param opt The options structure.
 * @return Always returns 1.
 */
static int	print_minus(long *nl, int *len, t_opt opt)
{
	print_char('-');
	(*nl) = (*nl) * -1;
	(*len)--;
	if (opt.dot)
		(*len)--;
	return (1);
}

/**
 * @brief Calculates the number of digits in a number.
 *
 * @param num The number to calculate the digits for.
 * @return The number of digits.
 */
static int	number_of_digit(long num)
{
	int	cur;

	cur = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		cur++;
	while (num != 0)
	{
		num = num / 10;
		cur++;
	}
	return (cur);
}

/**
 * @brief Gets the values for printing the number.
 *
 * @param prefix Pointer to the prefix character.
 * @param len_prec Pointer to the length of the prefix.
 * @param opt Pointer to the options structure.
 * @param nl The number.
 * @return The length of the number.
 */
static int	get_values(char	*prefix, int *len_prec, t_opt *opt, long nl)
{
	int		len;

	len = number_of_digit(nl);
	*len_prec = len;
	if (opt->precision > len)
		*len_prec = opt->precision;
	if (nl < 0 && opt->zero_offset > len && opt->precision > len)
		(*len_prec)++;
	if (nl < 0 && opt->dot && opt->precision < opt->zero_offset)
		len++;
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
 * @brief Prints a number with options.
 *
 * @param len The length of the number.
 * @param nl The number.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
static int	print_di(int len, long nl, t_opt opt)
{
	int	total;

	total = 0;
	if (nl == 0 && opt.min_width && opt.min_width < len)
		total += print_char(' ');
	else if (nl == 0 && opt.dot && !opt.precision && opt.min_width >= len)
		total += print_char(' ');
	else if (!(nl == 0 && opt.dot && !opt.precision))
		total += print_number(nl);
	return (total);
}

/**
 * @brief Prints a number with options.
 *
 * @param nl The number.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
int	ft_printnum(long nl, t_opt opt)
{
	int		total;
	int		len;
	char	prefix;
	int		len_prec;

	total = 0;
	len = get_values(&prefix, &len_prec, &opt, nl);
	while (prefix == ' ' && len_prec + total < opt.min_width)
		total += print_char(' ');
	if (nl < 0)
		total += print_minus(&nl, &len, opt);
	else if (opt.space && nl >= 0 && !opt.plus && !opt.dot)
		total += print_char(' ');
	else if (opt.plus && nl >= 0 && !opt.dot)
		total += print_char('+');
	while (len + total < opt.min_width)
		total += print_char('0');
	total += print_di(len, nl, opt);
	while (total < opt.offset)
		total += print_char(' ');
	return (total);
}
