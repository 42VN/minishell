/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:34:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 13:17:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

void	exp_strip_quotes(char *str);

int		exp_valid_dollar_var(char c);
void	exp_tiddle_front(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_tiddle(char **res, char *cmd, size_t *i);
void	exp_dollar(t_shell *shell, char **res, char *cmd, size_t *i);
void	exp_normal(char **res, char *cmd, size_t *i);
void	exp_single_quote(char **res, char *cmd, size_t *i);
void	exp_double_quote(char **res, char *cmd, size_t *i);
void	expansion(t_shell *shell);

#endif