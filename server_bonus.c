#include "server_bonus.h"

t_save_char	g_my;

void	init_data(t_save_char *g_my)
{
	int	i;
	i = 0;
	g_my->counter = 0;
	g_my->c= 0;
	while (i < 32)
	{
		g_my->bin[i] = 0;
		i++;
	}
}

int	convert_bin_to_char(unsigned int *bin)
{
	int		i;
	int		dec;
	int		base;
	char	ascii;

	base = 1;
	dec = 0;
	i = 0;
	while (i < 32)
	{
		if (bin[i] != 0 && bin[i] != 1)
			return (-1);
		i++;
	}
	i = 31;
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
	if (seg != SIGUSR1 && seg != SIGUSR2)
		return ;
	else
	{
		if (seg == SIGUSR1)
		{
			g_my.bin[g_my.counter] = 0;
			g_my.counter++;
			usleep(200);
		}
		else if (seg == SIGUSR2)
		{
			g_my.bin[g_my.counter] = 1;
			g_my.counter++;
			usleep(200);
		}
		if (g_my.counter == 32)
		{
			g_my.c = convert_bin_to_char(g_my.bin);
			write(1, &g_my.c, 1);
			g_my.counter = 0;
		}
	}
}

int	main(void)
{
	init_data(&g_my);
	write(1, "id= ", 4);
	g_my.pid = getpid();
	ft_putnbr_fd(g_my.pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handle_code);
	signal(SIGUSR2, handle_code);
	while (1)
	{
		pause();
	}
	return (0);
}
