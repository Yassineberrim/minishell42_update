/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:34 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/29 23:16:59 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void  add_new_var(t_env *env, char **var)
{
    t_env *new;
    t_env *head;
    new = malloc(sizeof(t_env));
    new->name = ft_strdup(var[0]);
    new->value = ft_strdup(var[1]);
    new->next = NULL;
    if (!env)
        env = new;
    else
    {
        head = env;
        while (head->next)
            head = head->next;
        head->next = new;
    }
}
int check_if_exist(t_cmd *cmd, char **var)
{
    t_env *env = cmd->env;
    while(env)
    {
        if (ft_strcmp(env->name, var[0]) == 0)
            return (1);
        env = env->next;
    }
    return (0);
}
char **check_invalid_var(char *str)
{
    if (str[0] && !ft_isalpha(str[0]) && str[0] != '_' )
    {
        ft_putstr_fd("bash: export: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (NULL);
    }
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i - 1] == '-')
    {
       ft_putstr_fd("bash: export: `", 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return (NULL);
    }
    return (ft_split(str, '='));
}
char update_env(t_env *env, char **str)
{
    while (env)
    {
       
        if (ft_strcmp(env->name, str[0]) == 0)
        {
            if (env->value && !str[1])
            {
                return 0;
            }
            free(env->value);
            env->value = ft_strdup(str[1]);
            return (1);
        }
        env = env->next;
    }
    return (0);
}
int ft_export(t_cmd *cmd )
{
        int i = 1;
        char **var;

        var = NULL;
        if (cmd->cmd[1] == NULL)
        {
            print_env(cmd->env, cmd->cmd[0]);
            return (0);            
        }
        while (cmd->cmd[i])
        {
            var = check_invalid_var(cmd->cmd[i]);
            if (var)
            {
                if (!check_if_exist(cmd, var)) 
                {
                    add_new_var(cmd->env, var);
                }
                if(check_if_exist(cmd, var))
                {
                    update_env(cmd->env, var);
                }
            }
            i++;
        }
        return (0);
}

