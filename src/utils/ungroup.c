/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ungroup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:02:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 22:21:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	update_quote(char *quote, int value)
{
	if (value == '\'' || value == '"')
	{
		if (*quote == 0)
			*quote = value;
		else if (*quote == value)
			*quote = 0;
	}
}

static void	rewrite(char *str, int read_pos, int write_pos)
{
	int		depth;
	char	quote;

	depth = 0;
	quote = 0;
	while (str[read_pos] != '\0')
	{
		update_quote(&quote, str[read_pos]);
		if (str[read_pos] == '(' && quote == 0)
		{
			if (depth != 0)
				str[write_pos++] = str[read_pos];
			depth++;
		}
		else if (str[read_pos] == ')' && quote == 0)
		{
			depth--;
			if (depth != 0)
				str[write_pos++] = str[read_pos];
		}
		else
			str[write_pos++] = str[read_pos];
		read_pos++;
	}
	str[write_pos] = '\0';
}

/**
 * Remove a `()` pair which is outside of quote pair.
 */
void	ungroup(char *str)
{
	rewrite(str, 0, 0);
}
