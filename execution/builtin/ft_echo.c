/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:52:08 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 17:22:51 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int ft_echo(t_cmd *cmd, int fd_out)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (cmd->cmd[i] && ft_strcmp(cmd->cmd[i], "-n") == 0)
    {
        n = 1;
        i++;
    }
    while (cmd->cmd[i])
    {
        ft_putstr_fd(cmd->cmd[i], fd_out);
        if (cmd->cmd[i + 1])
            ft_putstr_fd(" ", fd_out);
        i++;
    }
    if (n == 0)
        ft_putstr_fd("\n", fd_out);
    return (0);
}