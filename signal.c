/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:51:05 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/28 15:53:50 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int du_working(int affeect)
{
    if (affeect == 0)
        return (0);
    return (1);
}
int sig_handler(int sig)
{
    if(sig == SIGINT)
    {
        if(!du_working(0))
            ft_putstr_fd("\nminishell$ ", 1);
        else
            ft_putstr_fd("\n", 1);
    }
}
int	init_sigaction(void)
{
	if (signal(SIGINT, sig_handler) != 0)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) != 0)
		return (0);
	return (1);
}