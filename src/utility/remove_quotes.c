/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:27:42 by hitran            #+#    #+#             */
/*   Updated: 2024/12/19 11:01:09 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_quotes_from_string(char *str)
{
    int i = 0, j = 0;
    char quote = 0;

    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            if (quote == 0)
                quote = str[i];
            else if (quote == str[i]) 
                quote = 0;
            i++;
        }
        else
        {
            str[j++] = str[i++];
        }
    }
    str[j] = '\0';
}

void remove_quotes_array(char **split_cmd)
{
    int i = 0;

    while (split_cmd[i])
    {
        remove_quotes_from_string(split_cmd[i]);
        i++;
    }
}

int remove_quotes(t_token *tokens, int size)
{
    int index = 0;

    while (index < size)
    {
        if (tokens[index].type == CMD)
        {
            if (tokens[index].split_cmd)
            {
                remove_quotes_array(tokens[index].split_cmd);
            }
        }
        index++;
    }
    return (EXIT_SUCCESS);
}
