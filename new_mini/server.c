// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <signal.h>
// #include <string.h>
// #include "libft/libft.h"

// typedef struct s_save_char
// {
//     int bin[8];
//     int c;
//     int counter;
//     char *message;
//     int message_size;
// } t_save_char;

// t_save_char g_my;

// void init_data(t_save_char *g_my)
// {
//     int i;
//     g_my->counter = 0;
//     g_my->c = 0;
//     g_my->message = NULL;
//     g_my->message_size = 0;
//     for (i = 0; i < 8; i++)
//     {
//         g_my->bin[i] = 0;
//     }
// }

// int convert_bin_to_char(int *bin)
// {
//     int i;
//     int dec;
//     int base;
//     char ascii;

//     base = 1;
//     dec = 0;
//     for (i = 7; i >= 0; i--)
//     {
//         if (bin[i] != 0 && bin[i] != 1)
//             return -1;
//         if (bin[i] == 1)
//             dec += base;
//         base *= 2;
//     }
//     ascii = (char)dec;
//     return ascii;
// }

// void handle_code(int seg)
// {
//     if (seg != SIGUSR1 && seg != SIGUSR2)
//         return;

//     if (seg == SIGUSR1)
//     {
//         g_my.bin[g_my.counter] = 0;
//         g_my.counter++;
//         usleep(200);
//     }
//     else if (seg == SIGUSR2)
//     {
//         g_my.bin[g_my.counter] = 1;
//         g_my.counter++;
//         usleep(200);
//     }

//     if (g_my.counter == 8)
//     {
//         char c;
//         g_my.c = convert_bin_to_char(g_my.bin);
//         c = g_my.c;
        
//         g_my.message_size++;
//         g_my.message = realloc(g_my.message, g_my.message_size);
//         g_my.message[g_my.message_size - 1] = c;
        
//         g_my.counter = 0;
//     }
// }

// int main(void)
// {
//     struct sigaction sa;
//     init_data(&g_my);
//     write(1, "id= ", 4);
//     ft_putnbr_fd(getpid(), 1);
//     write(1, "\n", 1);

//     sa.sa_handler = handle_code;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGUSR1, &sa, NULL);
//     sigaction(SIGUSR2, &sa, NULL);

//     while (1)
//         pause();

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "libft/libft.h"
typedef struct s_save_char
{
    int bin[8];
    int c;
    int counter;
    char *message;
    size_t message_size;
    size_t message_capacity;
} t_save_char;

t_save_char g_my;

void init_data(t_save_char *g_my)
{
    int i;
    g_my->counter = 0;
    g_my->c = 0;
    g_my->message_size = 0;
    g_my->message_capacity = 0;
    g_my->message = NULL;
    for (i = 0; i < 8; i++)
    {
        g_my->bin[i] = 0;
    }
}

int convert_bin_to_char(int *bin)
{
    int i;
    int dec;
    int base;
    char ascii;

    base = 1;
    dec = 0;
    for (i = 7; i >= 0; i--)
    {
        if (bin[i] != 0 && bin[i] != 1)
            return -1;
        if (bin[i] == 1)
            dec += base;
        base *= 2;
    }
    ascii = (char)dec;
    return ascii;
}

void handle_code(int seg)
{
    if (seg != SIGUSR1 && seg != SIGUSR2)
        return;

    if (seg == SIGUSR1)
    {
        g_my.bin[g_my.counter] = 0;
        g_my.counter++;
        usleep(100);
    }
    else if (seg == SIGUSR2)
    {
        g_my.bin[g_my.counter] = 1;
        g_my.counter++;
        usleep(100);
    }

    if (g_my.counter == 8)
    {
        char c;
        g_my.c = convert_bin_to_char(g_my.bin);
        c = g_my.c;

        if (g_my.message_size >= g_my.message_capacity)
        {
            g_my.message_capacity = g_my.message_size + 1;
            char *new_message = realloc(g_my.message, g_my.message_capacity);
            if (new_message == NULL)
            {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                exit(1);
            }
            g_my.message = new_message;
        }

        g_my.message[g_my.message_size] = c;
        g_my.message_size++;

        g_my.counter = 0;

        if (c == '\0')
        {
            printf("Received message: %s\n", g_my.message);
            fflush(stdout);
            g_my.message_size = 0;
            g_my.message_capacity = 0;
            free(g_my.message);
            g_my.message = NULL;
        }
    }
}

int main(void)
{
    struct sigaction sa;
    init_data(&g_my);
    write(1, "id= ", 4);
    ft_putnbr_fd(getpid(), 1);
    write(1, "\n", 1);

    sa.sa_handler = handle_code;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();

    return 0;
}

