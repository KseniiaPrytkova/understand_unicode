/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprytkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 16:57:53 by kprytkov          #+#    #+#             */
/*   Updated: 2018/08/27 16:57:54 by kprytkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNICODE_H
# define UNICODE_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define TWO_BYTES_F			192
#define THREE_BYTES_F		224 
#define FOUR_BYTES_F		240
#define REST_BYTES			128

#define SIX_UNITS			63
#define TWELVE_UNITS		4095

#define SIX_U_HEAD_FOUR_B	258048
#define SIX_U_MID_FOUR_B	4032

typedef struct 	s_box
{
	int 		c_uni;
	int 		bits_amt;

	int			char_1;
	int			char_2;
	int			char_3;
	int			char_4;

	int 		ret;
	
}				t_box;

void	ft_putchar(char c);
void	print_bits(unsigned char octet, t_box *box);
int		count_active_bits(int c_uni, t_box *box);
void	print_bytes(int c_uni, t_box *box);
int		decide_about_bytes(int bits_amount);


void	if_2_bytes(t_box *box);
void	if_3_bytes(t_box *box);
void	if_4_bytes(t_box *box);

#endif