#ifndef CLIENT_BONUS_H
# define CLIENT_BONUS_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

char	*convert_char_to_binary(char c);
void	send_binary(char *binary, int pid);
void	send_end(pid_t pid);
void	handle_av(const char *av, pid_t pid);
void	get_recived(int s);
#endif