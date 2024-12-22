/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:34:05 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Prints a number in a specified base.
 *
 * @param nbr The number to print.
 * @param base The base to use for printing.
 * @return The total number of characters printed.
 */
static int	print_number_base(int nbr, char *base)
{
	unsigned int	base_len;
	unsigned int	nbrl;
	int				total;

	total = 0;
	nbrl = nbr;
	base_len = ft_strlen(base);
	if (nbrl >= base_len)
	{
		total += print_number_base(nbrl / base_len, base);
		total += print_number_base(nbrl % base_len, base);
	}
	else
	{
		total += print_char(base[nbrl]);
	}
	return (total);
}

/**
 * @brief Calculates the size of a hexadecimal representation of an integer.
 *
 * @param nbr The integer.
 * @return The size of the hexadecimal representation.
 */
static int	get_hex_size(int nbr)
{
	int				total;
	unsigned int	nbrl;

	total = 0;
	nbrl = nbr;
	if (nbrl >= 16)
	{
		total += get_hex_size(nbrl / 16);
		total += get_hex_size(nbrl % 16);
	}
	else
		total++;
	return (total);
}

/**
 * @brief Gets the values for printing the number in a specified base.
 *
 * @param prefix Pointer to the prefix character.
 * @param len_prec Pointer to the length of the prefix.
 * @param opt Pointer to the options structure.
 * @param nbr The number.
 * @return The length of the number.
 */
static int	get_values(char	*prefix, int *len_prec, t_opt *opt, int nbr)
{
	int		len;

	len = get_hex_size(nbr);
	*len_prec = len;
	if (opt->precision > len)
		*len_prec = opt->precision;
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
 * @brief Prints a number in hexadecimal format with options.
 *
 * @param is_maj Flag indicating if the hexadecimal should be uppercase.
 * @param len The length of the number.
 * @param nbr The number.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
static int	print_x(int is_maj, int len, int nbr, t_opt opt)
{
	int	total;

	total = 0;
	if (nbr == 0 && opt.min_width && opt.min_width < len)
		total += print_char(' ');
	else if (nbr == 0 && opt.dot && !opt.precision && opt.min_width >= len)
		total += print_char(' ');
	else if (!(nbr == 0 && opt.dot && !opt.precision))
	{
		if (is_maj)
			total += print_number_base(nbr, "0123456789ABCDEF");
		else
			total += print_number_base(nbr, "0123456789abcdef");
	}
	return (total);
}

/**
 * @brief Prints a number in binary format with options.
 *
 * @param nbr The number to print.
 * @param is_maj Flag indicating if the hexadecimal should be uppercase.
 * @param opt The options structure.
 * @return The total number of characters printed.
 */
int	ft_printbnum(int nbr, int is_maj, t_opt opt)
{
	int		total;
	int		len;
	char	prefix;
	int		len_prec;

	total = 0;
	len = get_values(&prefix, &len_prec, &opt, nbr);
	while (len_prec + total < opt.min_width)
		total += print_char(prefix);
	while (len + total < opt.min_width)
		total += print_char('0');
	if (opt.sharp && nbr != 0)
	{
		if (is_maj)
			total += print_str("0X");
		else
			total += print_str("0x");
	}
	total += print_x(is_maj, len, nbr, opt);
	while (total < opt.offset)
		total += print_char(' ');
	return (total);
}
