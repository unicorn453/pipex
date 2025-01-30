/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:20:18 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/30 16:39:49 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_command(t_parser *parser)
{
	while (parser->command[parser->i] != '\0')
	{
		parser->c = parser->command[parser->i];
		process_char(parser);
		if (handle_space(parser->c, parser->checks) && parser->token_index > 0)
		{
			add_token_to_args(parser->args, parser->token, &parser->arg_index,
				&parser->token_index);
		}
		parser->i++;
	}
	if (parser->token_index > 0)
	{
		add_token_to_args(parser->args, parser->token, &parser->arg_index,
			&parser->token_index);
	}
	parser->args[parser->arg_index] = NULL;
}

bool	*process_char(t_parser *parser)
{
	char	c;

	c = parser->command[parser->i];
	if (handle_escape(parser) || handle_quotes(c, parser->checks)
		|| handle_space(c, parser->checks))
		return (parser->checks);
	parser->token[parser->token_index++] = c;
	parser->checks[2] = false;
	return (parser->checks);
}

bool	handle_space(char c, bool *checks)
{
	if (c == ' ' && !checks[0] && !checks[1] && !checks[2])
		return (true);
	return (false);
}

bool	handle_quotes(char c, bool *checks)
{
	if ((c == '\'' || c == '"') && checks[2])
	{
		checks[2] = false;
		return (true);
	}
	if (c == '\'' && !checks[1] && !checks[2])
	{
		checks[0] = !checks[0];
		return (true);
	}
	if (c == '"' && !checks[0] && !checks[2])
	{
		checks[1] = !checks[1];
		return (true);
	}
	return (false);
}
