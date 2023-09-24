/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:00:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/24 04:11:47 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

//◦ exit with no options

int is_strdigits(char* str) {
    int i = 0;
    while (str[i]) {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_exit(t_cmd* cmd)
{
    int i;
    char** argv = cmd->cmd;
    i = 0;
    while (argv[i])
        i++;
    if (i == 1)
        exit(0);
    else if (i == 2)
    {
        if (is_strdigits(argv[1]))
            exit(ft_atoi(argv[1]));
        else
        {
            printf("minishell: exit: %s: numeric argument required\n", argv[1]);
            exit(255);
        }
    }
    else
    {
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    return (0);
}