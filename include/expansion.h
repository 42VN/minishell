/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:34:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/18 13:59:20 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

int		exp_strip_quotes(char *str, char c, int start);
void	exp_split_cmd_remove_quotes(char **split_str, size_t str_len);
char	*exp_split_cmd_join(char **split_str);
int		exp_split_cmd_push_back(t_shell *shell, char ***split_cmd, char *str);
int		exp_remove_quotes(char **res, int i);

void	ft_join_quote(char **res, char *quote);
void	cleanup_split_cmd(char **split_cmd);

int		exp_process(t_shell *shell, char **res, char *cmd);
int		exp_logic_str(t_shell *shell, char **str);
int		exp_logic_split_str(t_shell *shell, char **str, char ***split_cmd);

int		exp_valid_dollar_var(char c);
void	exp_tiddle_front(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_tiddle(char **res, char *cmd, size_t *i);
void	exp_dollar(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_dollar_in_quote(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_normal(char **res, char *cmd, size_t *i);
void	exp_single_quote(char **res, char *cmd, size_t *i);
void	exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i);

int		expansion(t_shell *shell);
int		expansion_heredoc(t_shell *shell);

#endif