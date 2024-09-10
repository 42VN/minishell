/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 21:34:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

void	ft_token_free(t_shell *shell);
int		ft_token_realloc(t_shell *shell);
void	*tokenize(t_shell *shell, char *input);

#endif