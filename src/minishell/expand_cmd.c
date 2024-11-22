/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 00:34:04 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/28 09:46:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "io.h"
#include "constants.h"

static int	handle_io_expansion(t_io *io, char buf[], t_minishell *minishell)
{
	t_list	*match_list;

	if (expand_dollar(&io->token, minishell) < 0)
		return (-1);
	if (*io->token == '\0' && io->redi_type != REDIR_HEREDOC)
		return (ft_fprintf(2, "minishell: %s: ambiguous redirect\n", buf), -1);
	match_list = expand_wildcard(io->token);
	if (match_list == NULL)
		return (-1);
	if (match_list->length > 1 && io->redi_type != REDIR_HEREDOC)
	{
		ft_list_clear(&match_list, free);
		ft_fprintf(2, "minishell: %s: ambiguous redirect\n", buf);
		return (-1);
	}
	if (match_list->length == 1)
	{
		free(io->token);
		io->token = (char *)match_list->head->data;
	}
	else if (io->redi_type != REDIR_HEREDOC)
		ft_remove_quote_pair(io->token);
	ft_list_clear(&match_list, NULL);
	return (0);
}

static int	expand_io_list(t_list *io_list, t_minishell *minishell)
{
	char	buffer[FILE_NAME_MAX];
	t_node	*node;

	node = io_list->head;
	while (node != NULL)
	{
		ft_strlcpy(buffer, ((t_io *)node->data)->token, FILE_NAME_MAX);
		if (handle_io_expansion(node->data, buffer, minishell) < 0)
			return (-1);
		node = node->next;
	}
	return (0);
}

static int	process_matches(char *argv, t_list *arg_list, t_list *match_list)
{
	char	*temp;

	if (*argv == '\0')
		return (0);
	if (match_list->length == 0)
	{
		ft_remove_quote_pair(argv);
		temp = ft_strdup(argv);
		if (temp == NULL)
			return (-1);
		if (ft_list_push(arg_list, temp) < 0)
			return (free(temp), -1);
		return (0);
	}
	if (
		ft_list_push_all(\
			arg_list, \
			match_list, \
			(void *(*)(void *))ft_strdup \
		) < 0 \
	)
		return (-1);
	return (0);
}

static t_list	*expand_argv(char **argv, t_minishell *minishell)
{
	t_list	*arg_list;
	t_list	*match_list;

	arg_list = ft_list(0);
	if (arg_list == NULL)
		return (NULL);
	while (*argv != NULL)
	{
		if (expand_dollar(argv, minishell) < 0)
			return (ft_list_clear(&arg_list, free), NULL);
		match_list = expand_wildcard(*argv);
		if (match_list == NULL)
			return (ft_list_clear(&arg_list, free), NULL);
		if (process_matches(*argv, arg_list, match_list) < 0)
		{
			ft_list_clear(&match_list, free);
			ft_list_clear(&arg_list, free);
			return (NULL);
		}
		ft_list_clear(&match_list, free);
		argv++;
	}
	return (arg_list);
}

int	expand_cmd(t_command *cmd, t_minishell *minishell)
{
	t_list	*arg_list;
	char	**new_argv;

	if (expand_io_list(cmd->io_list, minishell) < 0)
		return (-1);
	arg_list = expand_argv(cmd->argv, minishell);
	if (arg_list == NULL)
		return (-1);
	new_argv = (char **)ft_list_to_array(arg_list, sizeof(char *));
	if (new_argv == NULL)
		return (ft_list_clear(&arg_list, free), -1);
	ft_list_clear(&arg_list, NULL);
	ft_del_str_arr(&cmd->argv);
	cmd->argv = new_argv;
	return (0);
}
