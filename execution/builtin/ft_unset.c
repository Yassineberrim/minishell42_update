/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:09:26 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/25 23:28:42 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void ft_clear_env(t_env **env, t_env *prev)
{
    if (prev)
        prev->next = (*env)->next;
    t_env *tmp = *env;
    *env = (*env)->next;    
    free(tmp->name);
    free(tmp->value);
    free(tmp);
}

int ft_unset(t_cmd *cmd)
{
    char **argv = cmd->cmd;
    t_env *env = cmd->env;
    t_env *prev;
    int i = 0;

    prev = 0;
    while (env)
    {
        i = 0;
        while (argv[i])
        {
            if (ft_strcmp(env->name, argv[i]) == 0)
            {
                ft_clear_env(&env, prev);
                i = -1;
                break;
            }
            i++;
        }
        if (i != -1)
        {
            prev = env;
            env = env->next;
        }
    }
    return (0);
}
