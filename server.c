/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/05/31 14:27:00 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_save_char	g_my;

int	init(t_save_char g_my)
{
	//printf("hy from init\n");

	int	i;
	(void)g_my;
	g_my.counter = 6;
	i = 0;
	while (i < 8)
	{
		g_my.bin[i] = 5;
		i++;
	}
	return (0);
}

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
		}
		else if (seg == SIGUSR2)
		{
			//printf("here SIG 2\n");

			g_my.bin[g_my.counter] = 1;
			g_my.counter++;
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
	if(init(g_my) != 0)
	{
		write(2, "fehler", 6);
		return (0);
	}
	write(1, "id= ", 4);
		printf("my.counter = %d\n",g_my.counter);
	for(int i = 0; i<8; i++)
	{
		printf("my.bin[%d] = %d\n", i, g_my.bin[i]);
	}
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	//write(1, ft_itoa(getpid()), 9);
	signal(SIGUSR1, handle_code);
	signal(SIGUSR2, handle_code);
	//while (1)
	//	pause();
	return (0);
}
