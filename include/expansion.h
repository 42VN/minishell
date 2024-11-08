/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:34:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 15:37:01 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

int		exp_valid_dollar_var(char c);

void	exp_dollar(
			t_shell *shell,
			char **res,
			char *cmd);
void	expansion(t_shell *shell);

#endif