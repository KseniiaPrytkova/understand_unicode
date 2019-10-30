/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:56:31 by kprytkov          #+#    #+#             */
/*   Updated: 2018/08/27 16:56:32 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unicode.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	i_will_init_struct(t_box *box, int c)
{
	box->c_uni = c;
	box->bits_amt = 0;
	box->char_1 = 0;
    box->char_2 = 0;
    box->char_3 = 0;
    box->char_4 = 0;
    box->ret = 0;
}

int		main (void)
{
	t_box 	*box;
	int 	c_uni; /* type C in ft_printf */
	int 	*s_uni; /* type S in ft_printf */
	int 	how_much_bytes;
	int 	save_c;

	c_uni = 987;
	how_much_bytes = 0;
	save_c = 0;
	if (!(box = (t_box *)malloc(sizeof(t_box))))
    {
        printf("BAD MALLOC (structure)\n");
        return (-1);
    }
    i_will_init_struct(box, c_uni);
	/* 1. α(wchar_t) == 945(int); Let's look at this number in binary representation */
	box->bits_amt = count_active_bits(c_uni, box);
	printf("input nb %d = \n", c_uni);
	if (c_uni > 255)
	{
		print_bytes(c_uni, box);
		printf("\n");
	}
	else
		print_bits(c_uni, box);
	/* 2. Let's calculate the number of active bits */
	// bits_amount = count_active_bits(c_uni, box);
	printf("There are %d active bits in input number.\n", box->bits_amt);
	/* 3. Now we have to decide how many bytes we need to encode our concrete symbol; 
	if bits_amount <= 7 ONE byte will be enough; if bits_amount > 7 && bits_amount <= 11 we need 
	TWO bytes; if bits_amount > 11 && bits_amount <= 16 we need THREE bytes for encoding;
	and if bits_amount more then 16 we need 4 bytes */
	how_much_bytes = decide_about_bytes(box->bits_amt);
	printf("You need %d BYTES to incode your sb.\n", how_much_bytes);
	if (how_much_bytes == 1)
		ft_putchar((char)c_uni);
	else if (how_much_bytes == 2)
		if_2_bytes(box);
	else if (how_much_bytes == 3)
		if_3_bytes(box);
	else if (how_much_bytes == 4)
		if_4_bytes(box);
	free (box);
	// system("leaks -quiet a.out");
	return (0);
}