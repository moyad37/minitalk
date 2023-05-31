/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanssou <mmanssou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:01:15 by mmanssou          #+#    #+#             */
/*   Updated: 2023/05/31 13:45:26 by mmanssou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct s_save_cahr
{
	int	bin[8];
	int	c;
	int	counter;
}		t_save_char;

void	init(t_save_char my);
int		convert_bin_to_char(int *bin);
void	handle_code(int seg);

#endif