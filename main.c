/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/09/26 18:17:32 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int only_sp_tab(char *line)
{
	while (*line && ( *line == ' ' || *line == '\t'))
		line++;
	return(*line ? 1 : 0);
}
int check_space(char *line)
{
	if(*line == '\0' || only_sp_tab(line) == 0)
		return(0);
	return(1);
}
void join_in_quote_and_word(t_lexer *lx)
{
	t_node *tmp;
	t_node *cur;
	
	cur = lx->head;
	while(cur)
	{
		if(cur->next && ((cur->type == QOUTE || cur->type == DOUBLE_QUOTE || cur->type == WORD ) && \
			(cur->next->type == QOUTE || cur->next->type == DOUBLE_QUOTE || cur->next->type == WORD)))
		{
			tmp = cur->next;
			cur->content = ft_strjoin(cur->content,tmp->content);
			cur->len = ft_strlen(cur->content);
			cur->next = tmp->next;
			if(tmp->next)
				tmp->next->prev = cur;
			free(tmp->content);
			free(tmp);
			lx->size -= 1;
			cur = lx->head;
		}
		cur = cur->next;
	}
}
int ft_count_cmd(t_lexer *lx)
{
	t_node *tmp;
	int count;
	
	count = 0;
	tmp = lx->head;
	while(tmp)
	{
		if(tmp->type == PIPE_LINE)
			count++;
		tmp = tmp->next;
	}
	return(count);
}
void init_cmd_struct(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->fd_in = 0;
	(*cmd)->fd_out = 1;
	(*cmd)->herdoc_fd = 0;
	(*cmd)->redir.in_file = NULL;
	(*cmd)->redir.out_file = NULL;
}

void	create_cmd(t_lexer *lx, t_cmd *cmd)
{
	t_node *cur;
	int i;
	int j;
	
	i = 0;
	j = 0;
	cur = lx->head;
	while(cur)
	{
		if(cur->type == PIPE_LINE)
		{
			cmd[i].cmd = malloc(sizeof(char *) * (j + 1));
			cmd[i].cmd[j] = NULL;
			i++;
			j = 0;
		}
		else
			j++;
		cur = cur->next;
	}
	cmd[i].cmd = malloc(sizeof(char *) * (j + 1));
	cmd[i].cmd[j] = NULL;
	cmd[i + 1].cmd = NULL;
}

t_cmd *commands(t_lexer *lx,t_cmd *cmd)
{
	t_node *cur;
	int i;
	int j;
	int max_i;
	
	i = 0;
	j = 0;
	cmd = malloc(sizeof(t_cmd) * (ft_count_cmd(lx) + 2));
	init_cmd_struct(&cmd);
	create_cmd(lx,cmd);
	cur = lx->head;
	while(cur)
	{
		if(cur->type == PIPE_LINE)
		{
			cmd[i].cmd[j] = NULL;
			i++;
			j = 0;
		}
		else
		{
			cmd[i].cmd[j] = ft_strdup(cur->content);
			j++;
		}
		cur = cur->next;
	}
	cmd[i].cmd[j] = NULL;
	max_i = i;
	i = 0;
	while (i < max_i)
	{
		cmd[i].next = &cmd[i + 1];
		i++;
	}
	cmd[i].next = NULL;
	return(cmd);
}


int main(int __unused ac,char **av,char **envirement)
{
	char *line;
    t_env *env;
	t_lexer lx;
	t_cmd *cmd;
	(void)cmd;
    (void) av;
    (void) ac;
	
    ft_variables(&env,envirement);

	while (1)
	{
		ft_initialisation(&lx);
		line = readline("minishell ");
		if (!line)
			return (1);
		else if (check_space(line) == 0)
			continue;
		else
		{
			add_history(line);
			if(lexer(line, &lx, env))
				continue;
			else
			{
				join_quotes(&lx);
				join_in_quote_and_word(&lx);
				delete_white_space(&lx);
				cmd = commands(&lx,cmd);
				cmd->env = env;
				if(is_buildin(cmd))
				{
					execution_builtin(cmd,0);
				}
				else
					execution_proto(cmd, envirement);
			}
		}
	}
	if(line)
		free(line);
}
