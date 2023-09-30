/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/29 23:15:34 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int ft_cd(t_cmd *cmd, int fd)
{
    char *old_pwd;
    
    if(cmd->cmd[1] == NULL)
    {
        if(chdir(getenv("HOME")) == -1)
        {
            ft_putstr_fd("cd: HOME not set\n", fd);
            return g_exit_status = 1;
        }
    }
    else if(ft_strcmp(cmd->cmd[1], "-") == 0)
    {
        if((old_pwd = getenv("OLDPWD")) == NULL)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", fd);
            return g_exit_status = 1;
        }
        if(chdir(old_pwd) == -1)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", fd);
            return g_exit_status = 1;
        }
    }
    else
    {
        if(chdir(cmd->cmd[1]) == -1)
        {
            ft_putstr_fd("cd: No such file or directory\n", fd);
            return g_exit_status = 1;
        }
    }
    return 0;
}
