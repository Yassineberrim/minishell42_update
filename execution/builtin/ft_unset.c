/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:09:26 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/23 15:38:03 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void ft_clear_env(t_env **env)
{
    t_env *tmp;
    tmp = *env;
    *env = (*env)->next;
    free(tmp->name);
    free(tmp);
}

int ft_unset(t_cmd *cmd)
{
    char **var = cmd->cmd;
    t_env *env = cmd->env;
    t_env *tmp;
    
    while(env)
    {
        if (ft_strcmp(env->name, var[1]) == 0)
        {
            tmp->next = env->next;
            free(env->value);
            free(env->name);
            free(env);
        }
        tmp = env;
        env = env->next;
    }
    return (0);
}
