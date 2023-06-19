#include "client_bonus.h"

char	*convert_char_to_binary(char c)
{
	int		dec;
	int		i;
	char	*binary;
	int		bit;

	i = 31;
	dec = (int)c;
	binary = (char *)malloc(sizeof(char) * 33);
	if (!binary)
		return NULL;
	while (i >= 0)
	{
		bit = (dec >> i) & 1;
		binary[31 - i] = bit + '0';
		i--;
	}
    binary[32] = 0;
	return (binary);
}

void	send_binary(char *binary, pid_t pid)
{
	int	i;

	i = 0;
	while (i <= 31)
	{
		if (binary[i] == '0')
		{
			kill(pid, SIGUSR1);
			usleep(200);
			//signal(SIGUSR1, get_recived);
		}
		else if (binary[i] == '1')
		{
			kill(pid, SIGUSR2);
			usleep(200);
			//signal(SIGUSR1, get_recived);
		}
		usleep(200);
        i++;
	}
	usleep(200);
}

void	send_end(pid_t pid)
{
	int	i;

	i = 0;
	while (i != 32)
	{
		kill(pid, SIGUSR1);
		i++;
		usleep(200);
	}
	usleep(200);
	return ;
}

void	handle_av(const char *av, pid_t pid)
{
	int		i;
	char	*binary;

	i = 0;
	while (av[i] != '\0')
	{
		binary = convert_char_to_binary(av[i]);
		usleep(650);
		send_binary(binary, pid);
		usleep(650);
		free(binary);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(2, "ERROR\n", 6);
		return (0);
	}
	else
	{
		if (!*av[2])
			return (0);
		else
		{
			handle_av(av[2], ft_atoi(av[1]));
			usleep(200);
			send_end(ft_atoi(av[1]));
			usleep(200);
		}
	}
	return (0);
}
