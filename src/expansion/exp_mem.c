/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 00:03:39 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 11:17:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_split_cmd_init_len(
	size_t *cmd_len,
	size_t *str_len,
	char ***split_cmd,
	char **split_str)
{
	while ((*split_cmd)[*cmd_len])
		(*cmd_len)++;
	while (split_str[*str_len])
		(*str_len)++;
}

static char	**exp_split_cmd_init_res(
	size_t cmd_len,
	size_t str_len,
	char **split_str)
{
	char	**res;

	res = (char **)ft_calloc(cmd_len + str_len + 1, sizeof(char *));
	if (!res)
	{
		ft_multi_free_null(&split_str);
		return (NULL);
	}
	return (res);
}

static void	exp_split_cmd_cpy(char **res, char ***src, size_t start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		res[i + start] = (*src)[i];
		(*src)[i] = NULL;
		++i;
	}
}
// static void	print_arr(char **tab)
// {
// 	unsigned int i = 0;
// 	while (tab && tab[i])
// 	{
// 		printf("%s, ", tab[i]);
// 		++i;
// 	}
// 	printf("\n");
// }

int	exp_split_cmd_push_back(t_shell *shell, char ***split_cmd, char *str)
{
	char	**res;
	char	**split_str;
	size_t	cmd_len;
	size_t	str_len;

	cmd_len = 0;
	str_len = 0;
	if (!split_cmd || !*split_cmd)
		return (0);
	split_str = ft_split_quote_wc(str);
	if (!split_str)
		return (0);
	exp_split_cmd_init_len(&cmd_len, &str_len, split_cmd, split_str);
	res = exp_split_cmd_init_res(cmd_len, str_len, split_str);
	if (!res)
		return (ft_error_ret("exp_split_cmd_push_back: ft_calloc",
				shell, ERR_MALLOC, 0));
	exp_split_cmd_cpy(res, split_cmd, 0, cmd_len);
	exp_split_cmd_cpy(res, &split_str, cmd_len, str_len);
	ft_multi_free_null(split_cmd);
	ft_multi_free_null(&split_str);
	*split_cmd = res;
	return (1);
}
