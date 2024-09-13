/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 14:23:47 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

int		ft_token_is_op(char *input);
void	ft_token_free(t_shell *shell);
int		ft_token_realloc(t_shell *shell);
int		ft_token_categorize(
			t_shell *shell,
			char *input,
			char *start);
void	ft_token_print(t_shell *shell);
int		tokenize(t_shell *shell, char *line);

#endif