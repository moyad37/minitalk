#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H

#include "libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct s_save_cahr
{
	unsigned int	bin[32];
	int	c;
	int	counter;
	int resived;
	int pid;
}		t_save_char;

void		init_data(t_save_char *g_my);
int		convert_bin_to_char(unsigned int *bin);
void	handle_code(int seg);
void    check_resived(int n);

#endif