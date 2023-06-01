/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/06/01 14:03:14 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_save_char	g_my;

void	init_data(t_save_char g_my)
{
	//printf("hy from init\n");

	int	i;
	i = 0;
	g_my.counter = 6;
	g_my.c= 0;
	while (i < 8)
	{
		g_my.bin[i] = 5;
		i++;
	}
}

// void	get_fill(t_signal g_my_data)
// {
// 	int	i;

// 	i = 0;
// 	g_my_data.dec = 0;
// 	g_my_data.count = 0;
// 	while (i < 8)
// 	{
// 		g_my_data.bit[i] = '0';
// 		i++;
// 	}
// }

int	convert_bin_to_char(int *bin)
{
	//printf("hy from handle_convert_bin_to_char\n");

	int		i;
	int		dec;
	int		base;
	char	ascii;

	base = 1;
	dec = 0;
	i = 0;
	while (i < 8)
	{
		if (bin[i] != 0 && bin[i] != 1)
			return (-1);
		i++;
	}
	i = 7;
	while (i >= 0)
	{
		if (bin[i] == 1)
			dec += base;
		base *= 2;
		i--;
	}
	ascii = (char)dec;
	return (ascii);
}

void	handle_code(int seg)
{
	//printf("hy from handle_code\n");
	if (seg != SIGUSR1 && seg != SIGUSR2)
		return ;
	else
	{
		if (seg == SIGUSR1)
		{
			//printf("here SIG 1\n");
			g_my.bin[g_my.counter] = 0;
			g_my.counter++;
			usleep(200);
		}
		else if (seg == SIGUSR2)
		{
			//printf("here SIG 2\n");

			g_my.bin[g_my.counter] = 1;
			g_my.counter++;
			usleep(200);
		}
		if (g_my.counter == 8)
		{
			char c;
			g_my.c = convert_bin_to_char(g_my.bin);
			/*
			for(int i = 0; i < 8; i++)
			{
				printf("%d",g_my.bin[i]);
			}
			printf("c ==== %c\n", c);
			*/
			//printf("\n");
			c = g_my.c;
			write(1, &c, 1);
			g_my.counter = 0;
			//init(g_my);
		}
	}
}

int	main(void)
{
	init_data(g_my);
	write(1, "id= ", 4);
	//printf("my.counter = %d\n",g_my.counter);
	// for(int i = 0; i<8; i++)
	// {
	// 	printf("my.bin[%d] = %d\n", i, g_my.bin[i]);
	// }
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	//write(1, ft_itoa(getpid()), 9);
	signal(SIGUSR1, handle_code);
	signal(SIGUSR2, handle_code);
	while (1)
		pause();
	return (0);
}
