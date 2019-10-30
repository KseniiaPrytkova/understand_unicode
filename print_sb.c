/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 21:12:37 by kprytkov          #+#    #+#             */
/*   Updated: 2018/08/27 21:12:38 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unicode.h"

void if_2_bytes(t_box *box)
{
	int c;
	/* we are starting from the most significant byte (the most LEFT one);
	we need to throw right byte away - let's use bit shift on 6 units right */
	c = box->c_uni;
	c = c >> 6;
	/* now we need to apply BITMASK for 2-bytes representation of sb for lead byte;
	using logical OR for this:*/
	c = c | TWO_BYTES_F;
	box->char_1 = c;
	printf("i am food for putchar now: %d\n", box->char_1);
	/* Now we need to apply the corresponding mask to the low-order byte;
	get the low byte using the properties of the logical AND (00111111 = 63)*/
	c = box->c_uni;
	c = c & SIX_UNITS;
	c = c | REST_BYTES;
	box->char_2 = c;
	box->ret++;
	printf("i am also food for putchar %d\n", box->char_2);
	write(1, &(box->char_1), 1);
	write(1, &(box->char_2), 1);
	printf("\n");
}

void if_3_bytes(t_box *box)
{
	int c;
	
	c = box->c_uni;
	c = c >> 12;
	c = c | THREE_BYTES_F;
	box->char_1 = c;

	c = box->c_uni;
	c = (c & TWELVE_UNITS) >> 6;
	c = c | REST_BYTES;
	box->char_2 = c;

	c = box->c_uni;
	c = c & SIX_UNITS;
	c = c | REST_BYTES;
	box->char_3 = c;
	box->ret++;
	write(1, &(box->char_1), 1);
	write(1, &(box->char_2), 1);
	write(1, &(box->char_3), 1);
	printf("\n");
}

void if_4_bytes(t_box *box)
{
	int c;
	
	c = box->c_uni;
	c = c >> 18;

	c = c | FOUR_BYTES_F;
	box->char_1 = c;

	c = box->c_uni;
	c = (c & SIX_U_HEAD_FOUR_B) >> 12;
	c = c | REST_BYTES;
	box->char_2 = c;

	c = box->c_uni;
	c = (c & SIX_U_MID_FOUR_B) >> 6;
	c = c | REST_BYTES;
	box->char_3 = c;

	c = box->c_uni;
	c = c & SIX_UNITS;
	c = c | REST_BYTES;
	box->char_4 = c;
	box->ret++;
	write(1, &(box->char_1), 1);
	write(1, &(box->char_2), 1);
	write(1, &(box->char_3), 1);
	write(1, &(box->char_4), 1);
	printf("\n");
}