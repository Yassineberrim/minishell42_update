/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:43:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/30 18:57:10 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_status(int status)
{
    return WEXITSTATUS(status);
}
/*create Get_env*/
char* find_abs_path(char* cmd)
{

    char* raw_path = getenv("PATH");
    char** path_arr = ft_split(raw_path, ':');
    int i = 0;
    if ( cmd && cmd[0] == '/' && ft_strlen(cmd) > 1 )
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    if( cmd && cmd[0] == '.' && cmd[1] == '/' && ft_strlen(cmd) > 2 )
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    while (path_arr[i])
    {
        char* fwd_slash = ft_strjoin(path_arr[i], "/");
        char* abs_path = ft_strjoin(fwd_slash, cmd);
        if (access(abs_path, F_OK) == 0)
        {
            // free(fwd_slash);
            free(path_arr);
            return abs_path;
        }
        // free(fwd_slash);
        free(abs_path);
        i++;
    }
    return NULL;
}

void check_redirections(t_cmd* cmd) 
{
    int pipefd[2]; 
    // > 
    if (cmd->out_redir_type == WRITEOUT) 
    {
        cmd->fd_out = open(cmd->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if(cmd->fd_out == -1)
            ft_putstr_fd("error opening file\n", 2);
    }
    // >>
    if (cmd->out_redir_type == APPENDOUT)
    {
        cmd->fd_out = open(cmd->out_file, O_WRONLY | O_APPEND, 0644);
        if(cmd->fd_out == -1)
            ft_putstr_fd("error opening file\n", 2);
    }
    // <
    if (cmd->in_redir_type == READIN) 
    {
        cmd->fd_in = open(cmd->in_file, O_RDONLY);
        printf("fd_in: %d\n", cmd->fd_in);
        if(cmd->fd_in == -1)
            ft_putstr_fd("error opening file\n", 2);
        // close(cmd->fd_in);
    }
    // <<
    /*mouchkil f herdoc mkhadamch*/
    if (cmd->in_redir_type == HEREDOC) 
    {
        pipe(pipefd);
        cmd->fd_in = pipefd[0];
        cmd->fd_out = pipefd[1];
        char *line;
        while (1) 
        {
            line = readline("> ");
            if (ft_strcmp(line, cmd->in_file) == 0)
            {
                free(line);
                break;
            }
            write(pipefd[1], line, ft_strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
        close(pipefd[1]);
    }
}


int execution_proto(t_cmd *cmd, char** env) 
{
    int pipe_fd[2];
   while (cmd)
   {
        char* cmd_abs_path = find_abs_path(cmd->cmd[0]);
        if (cmd->next) 
        {
            pipe(pipe_fd);
            cmd->fd_out = pipe_fd[1];
            cmd->next->fd_in = pipe_fd[0];
        }
        else if(is_buildin(cmd))
        {
            execution_builtin(cmd,0);
            return g_exit_status;
        }
        else if (!cmd_abs_path)
        {
            return g_exit_status = 127;
            ft_putstr_fd("minishell: command not found\n", 2);
            if(!cmd->next)
            {
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                return g_exit_status;
            }
            return g_exit_status;
        }
        check_redirections(cmd);
        int child_pid = fork();
        if (child_pid == 0) 
        {
            if (cmd->fd_out != 1)
            {
                dup2(cmd->fd_out, 1);
            }
            if (cmd->fd_in != 0)
            {
                dup2(cmd->fd_in, 0);
            } 
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            execve(cmd_abs_path, cmd->cmd, env);
            return g_exit_status = 127;
        }
        if (cmd->fd_out != 1)
            close(cmd->fd_out);
        if (cmd->fd_in != 0)
            close(cmd->fd_in);
        cmd = cmd->next;
   }
    while (wait(&g_exit_status) > 0);
    return g_exit_status;
}