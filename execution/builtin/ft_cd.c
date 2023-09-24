/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 17:38:32 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// typedef enum {
//     OUT_NONE,
//     WRITEOUT,
//     APPENDOUT
// } out_redirs;

// typedef enum {
//     IN_NONE,
//     READIN,
//     HEREDOC
// } in_redirs;

// typedef struct c {
//     char** argv;
//     int in;
//     int out;
//     int has_pipe;
//     out_redirs out_redir_type;
//     in_redirs in_redir_type;
//     char* in_file;
//     char* out_file;
//     struct c* next;
//     // redirections l8r
// } cmd;

int ft_cd(t_cmd *cmd, int fd)
{
    char *old_pwd;
    
    if(cmd->cmd[1] == NULL)
    {
        if(chdir(getenv("HOME")) == -1)
        {
            ft_putstr_fd("cd: HOME not set\n", fd);
            return 1;
        }
    }
    else if(ft_strcmp(cmd->cmd[1], "-") == 0)
    {
        if((old_pwd = getenv("OLDPWD")) == NULL)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", fd);
            return 1;
        }
        if(chdir(old_pwd) == -1)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", fd);
            return 1;
        }
    }
    else
    {
        if(chdir(cmd->cmd[1]) == -1)
        {
            ft_putstr_fd("cd: No such file or directory\n", fd);
            return 1;
        }
    }
    return 0;
}