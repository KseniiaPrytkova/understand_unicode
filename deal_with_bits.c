/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 17:04:48 by kprytkov          #+#    #+#             */
/*   Updated: 2018/08/27 17:04:49 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unicode.h"

void	print_bytes(int c_uni, t_box *box)
{
	int 	c_temp;

	c_temp = c_uni;
	if ((box->bits_amt <= 11) || (box->bits_amt > 11 && box->bits_amt <= 16))
	{
		while (c_uni)
		{
			c_uni = c_uni >> 8;
			print_bits(c_uni, box);

			c_uni = c_temp & 255;
			print_bits(c_uni, box);
			c_uni = c_uni >> 8;
		}
	}
	else if (box->bits_amt > 16)
	{
		c_uni = c_uni >> 16;
		print_bits(c_uni, box);

		c_uni = c_temp;
		c_uni = c_uni >> 8;
		print_bits(c_uni, box);
		c_uni = c_temp;
		c_uni = c_uni & 255;
		print_bits(c_uni, box);
	}
}

void	print_bits(unsigned char octet, t_box *box)
{
	int		oct;
	int		div;

	div = 128;
	oct = octet;
	while (div != 0)
	{
		if (div <= oct)
		{
			write(1, "1", 1);
			oct = oct % div;
		}
		else
			write(1, "0", 1);
		div = div / 2;
	}
	write(1, " ", 1);	
}

int		count_active_bits(int c_uni, t_box *box)
{
	int count_b;

	count_b = 0;
	while (c_uni)
	{
		c_uni = c_uni >> 1;
		count_b++;
	}
	return (count_b);
}

int		decide_about_bytes(int bits_amount)
{
	if (bits_amount <= 7)
		return (1);
	else if (bits_amount >7 && bits_amount <= 11)
		return (2);
	else if (bits_amount > 11 && bits_amount <= 16)
		return (3);
	else if (bits_amount > 16)
		return (4);
	else
		return (0);
}
