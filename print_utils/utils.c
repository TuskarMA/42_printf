/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddivaev <ddivaev@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 07:43:24 by ddivaev           #+#    #+#             */
/*   Updated: 2024/12/22 14:28:21 by ddivaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/**
 * @brief Calculates the length of a string.
 *
 * @param str Pointer to the string.
 * @return The length of the string.
 */
int	ft_strlen(char *str)
{
	int	cur;

	cur = 0;
	if (!str)
		return (cur);
	while (str[cur])
		cur++;
	return (cur);
}

/**
 * @brief Converts a string to an integer.
 *
 * @param str Pointer to the string to convert.
 * @param o_cur Pointer to an integer to store the current position.
 * @return The converted integer.
 */
int	ft_atoi(const char *str, int *o_cur)
{
	int	cur;
	int	num;

	cur = 0;
	num = 0;
	while (str[cur] >= '0' && str[cur] <= '9')
	{
		num = num * 10 + str[cur] - '0';
		cur++;
		(*o_cur)++;
	}
	return (num);
}

/**
 * @brief Checks if a character is in a set of characters.
 *
 * @param c The character to check.
 * @param set Pointer to the set of characters.
 * @return 1 if the character is in the set, 0 otherwise.
 */
int	in_set(char c, char *set)
{
	int	cur;

	cur = -1;
	while (set[++cur])
		if (set[cur] == c)
			return (1);
	return (0);
}

/**
 * @brief Prints a number to the standard output.
 *
 * @param nl The number to print.
 * @return The total number of characters printed.
 */
int	print_number(long nl)
{
	int		total;
	long	num;

	total = 0;
	num = nl;
	if (nl < 0)
	{
		total += print_char('-');
		num = -nl;
	}
	if (num > 100)
		total += print_number(num / 10);
	else if (num == 100)
		total += print_str("10");
	else if ((num / 10) > 0)
		total += print_char((num / 10) + '0');
	total += print_char((num % 10) + '0');
	return (total);
}

/**
 * @brief Initializes the options structure with default values.
 *
 * @param opt Pointer to the options structure to initialize.
 */
void	init_opt(t_opt *opt)
{
	opt->sharp = 0;
	opt->space = 0;
	opt->plus = 0;
	opt->minus = 0;
	opt->min_width = 0;
	opt->dot = 0;
	opt->precision = 0;
	opt->zero = 0;
	opt->zero_offset = 0;
	opt->offset = 0;
}
