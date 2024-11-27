/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:34:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/27 12:30:35 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

int		exp_strip_quotes(char *str, char quote);
void	ft_join_quote(char **res, char *quote);
void	cleanup_split_cmd(char **split_cmd);

int		exp_valid_dollar_var(char c);
void	exp_tiddle_front(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_tiddle(char **res, char *cmd, size_t *i);
void	exp_dollar(t_shell *shell, char **res, char *cmd, size_t *i);
void 	exp_dollar_in_quote(
			t_shell *shell,
			char **res,
			char *cmd,
			size_t *i);
void	exp_normal(char **res, char *cmd, size_t *i);
void	exp_single_quote(char **res, char *cmd, size_t *i);
void	exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i);
void	expansion(t_shell *shell);

#endif