/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:51:05 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/30 20:27:34 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int du_working(int affeect)
// {
//     if (affeect == 0)
//         return (0);
//     return (1);
// }
// int sig_handler(int sig)
// {
//     if(sig == SIGINT)
//     {
//         ft_putstr_fd("\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//         g_exit_status = 1;
//     }
//     return (1);
// }
// int	init_sigaction(void)
// {
// 	if (signal(SIGINT, sig_handler) != 0)
// 		return (0);
// 	if (signal(SIGQUIT, SIG_IGN) != 0)
// 		return (0);
// 	return (1);
// }