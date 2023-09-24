/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:43:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/24 22:40:24 by yberrim          ###   ########.fr       */
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
    if (cmd[0] == '/' && ft_strlen(cmd) > 1)
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    if(cmd[0] == '.' && cmd[1] == '/')
    {
        if (access(cmd, F_OK) == 0)
            return cmd;
        return NULL;
    }
    while (path_arr[i])
    {
        char* fwd_slash = ft_strjoin(path_arr[i], "/");
        char* abs_path = ft_strjoin(fwd_slash, cmd);
        if (access(abs_path, F_OK) == 0) {
            // free(fwd_slash);
            free(path_arr);
            printf("found abs path: %s\n", abs_path);
            return abs_path;
        }
        // free(fwd_slash);
        free(abs_path);
        i++;
    }
    printf("command not found\n");
    return NULL;
}

void check_redirections(t_cmd* cmd) 
{
    int pipefd[2];
    // >
    if (cmd->out_redir_type == WRITEOUT) 
    {
        cmd->fd_out = open(cmd->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        printf("out redir fd: %i\n", cmd->fd_out);
        if(cmd->fd_out == -1)
            printf("error opening file\n");
    }
    // >>
    if (cmd->out_redir_type == APPENDOUT) {
        cmd->fd_out = open(cmd->out_file, O_WRONLY | O_APPEND, 0644);
        if(cmd->fd_out == -1)
            printf("error opening file\n");
    }
    // <
    if (cmd->in_redir_type == READIN) 
    {
        cmd->fd_in = open(cmd->in_file, O_RDONLY);
        if(cmd->fd_in == -1)
            printf("error opening file\n");
    }
    // <<
    if (cmd->in_redir_type == HEREDOC) 
    {
        pipe(pipefd);
        write(pipefd[1], cmd->in_file, ft_strlen(cmd->in_file));
        close(pipefd[1]);
        cmd->fd_in = pipefd[0];
    }
}


int execution_proto(t_cmd *cmd, char** env) 
{
    int exit_status = 0;
    int pipe_fd[2];

   while (cmd)
   {
        char* cmd_abs_path = find_abs_path(cmd->cmd[0]);

        if (cmd->next) 
        {
            printf("has pipe set to true\n");
            pipe(pipe_fd);
            cmd->fd_out = pipe_fd[1];
            cmd->next->fd_in = pipe_fd[0];
        }
        if (!cmd_abs_path) 
        {
            printf("minishell: %s: command not found\n", cmd->cmd[0]); // print f stderro later
            exit_status = 127;
            close(cmd->fd_out);
            cmd = cmd->next;
            continue;
        }
        check_redirections(cmd);
        cmd->cmd[0] = cmd_abs_path;
        int child_pid = fork();
        if(child_pid == 0)
        {
            if (cmd->fd_out != 1)
            {
                dup2(cmd->fd_out, 1);
                close(cmd->fd_out);
            }
            if (cmd->fd_in != 0)
            {
                dup2(cmd->fd_in, 0);
                close(cmd->fd_in); 
            }
            execve(cmd->cmd[0], cmd->cmd, env);
            exit(1);
        }
        else if (child_pid == -1)
        {
            printf("error forking\n");
            exit(1);
        }
        if (cmd->fd_out != 1)
            close(cmd->fd_out);
        if (cmd->fd_in != 0)
            close(cmd->fd_in);
        cmd = cmd->next;
   }
   while (wait(&exit_status) > 0);
   return WEXITSTATUS(exit_status);
}


