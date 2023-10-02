/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 22:04:19 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_writout(t_cmd *cmd)
{
	cmd->fd_out = open(cmd->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->fd_out == -1)
		return ;
}

void	check_appendout(t_cmd *cmd)
{
	cmd->fd_out = open(cmd->out_file, O_WRONLY | O_APPEND, 0644);
	if (cmd->fd_out == -1)
		return ;
}

void	check_readin(t_cmd *cmd)
{
	cmd->fd_in = open(cmd->in_file, O_RDONLY);
	if (cmd->fd_out == -1)
		return ;
}

// void	check_herdoc(t_cmd *cmd)
// {
// 	if(cmd->cmd[0] == REDIR_IN || cmd->cmd[0] == REDIR_OUT)
// 	{
// 		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
// 		return ;
// 	}
// 	cmd->fd_in = open(cmd->in_file, O_RDONLY);
// 	if (cmd->fd_out == -1)
// 	{
// 		ft_putstr_fd("error opening file\n", 2);
// 		return ;
// 	}
// }

void	check_redirections(t_cmd *cmd)
{
	if (cmd->out_redir_type == WRITEOUT)
		check_writout(cmd);
	if (cmd->out_redir_type == APPENDOUT)
		check_appendout(cmd);
	if (cmd->in_redir_type == READIN)
		check_readin(cmd);
	// if (cmd->in_redir_type == HEREDOC)
	// 	check_herdoc(cmd);
}
