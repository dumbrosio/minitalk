/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vd-ambro <vd-ambro@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:32:34 by vd-ambro          #+#    #+#             */
/*   Updated: 2023/07/12 14:52:27 by vd-ambro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_message(int sig_no, siginfo_t *info, void *context)
{
	static unsigned char	ch;
	static int				bit;
	static unsigned char	message[4096];

	(void)context;
	if (sig_no == SIGUSR1)
		ch |= (1 << bit % 8);
	if (bit++ == 0)
		ft_printf("Message from client @%d: ", info->si_pid);
	if (bit % 8 == 0)
	{
		if (ch == '\0')
		{
			write(1, message, bit / 8);
			write(1, "\n", 1);
			ft_bzero(message, bit / 8);
			bit = 0;
			kill(info->si_pid, SIGUSR2);
		}
		else
		{
			message[bit / 8 - 1] = ch;
			ch = '\0';
		}
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	pid = getpid();
	if (pid == -1)
	{
		ft_printf("Error starting server.\n");
		exit(EXIT_FAILURE);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_message;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Hello from server. Send me a message @%d!\n", pid);
	while (1)
		pause();
	return (0);
}
