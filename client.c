/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by mmanssou          #+#    #+#             */
/*   Updated: 2023/06/01 14:03:05 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char	*convert_char_to_binary(char c)
{
	int		dec;
	int		i;
	char	*binary;
	int		bit;

	i = 7;
	dec = (int)c;
	binary = (char *)malloc(sizeof(char) * 9);
	if (!binary)
		return NULL;
	while (i >= 0)
	{
		bit = (dec >> i) & 1;
		binary[7 - i] = bit + '0';
		i--;
	}
    binary[8] = 0;
	return (binary);
}

void	send_binary(char *binary, pid_t pid)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (binary[i] == '0')
		{
			kill(pid, SIGUSR1);
			usleep(200);
		}
		else if (binary[i] == '1')
		{
			kill(pid, SIGUSR2);
			usleep(200);
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
	while (i != 8)
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
		usleep(200);
		send_binary(binary, pid);
		usleep(200);
		free(binary);
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		write(2, "ERORR\n", 1);
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