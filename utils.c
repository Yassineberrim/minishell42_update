/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:25:45 by slazar            #+#    #+#             */
/*   Updated: 2023/09/25 17:40:19 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *ft_strdup_2(char *str,int start,int finish)
{
	int i;
	char *dup;
	i = 0;
	while (str && str[start + i] && (start +i)<= finish)
		i++;
	dup = malloc(sizeof(char)*(i + 1));
	dup[i] = '\0';
	i = 0;
	while (str && str[start +i] && start +i <= finish)
	{
		dup[i] = str[start+i];
		i++;
	}
	return(dup);
}

int ft_strcmp(char *s1,char *s2)
{
	while (s1 && s2 && *s1 && *s2)
	{
		if(*s1 - *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
int if_token(char c)
{
	if (( c == '\'' || c == '\"' || c == '\\' 
	|| c == '$' || c == '|' || c == '>' || c == '<' || c == ' '  || c == '\t'))
		return (0);
	return 1;
}
int is_digits(char c)
{
	if (c >= '0' && c <= '9')
		return 0;
	return(1);
}