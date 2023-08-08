/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 06:16:35 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 06:19:46 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_her_doc_c_core_01(char *line, int *i, int j)
{
	char	*var;
	int		le;

	if (line[*i + j] && ft_is_delimiter(line[*i + j]) != SPACES
		&& ft_isalnum(line[*i + j]))
	{
		while (line[*i + j] && ft_is_delimiter(line[*i + j]) != SPACES
			&& ft_isalnum(line[*i + j]))
			j++;
		var = ft_substr(line, *i + 1, j - 1, 1);
		le = ft_strlen(ft_expand(var));
		line = ft_replace_str(line, ft_expand(var), *i, *i + j - 1);
		*i += le;
		return (1);
	}
	return (0);
}

void	ft_pre_her_doc_c(t_variables *var, int heredoc, char *dlm)
{
	var->line = readline("herdoc> ");
	if (!var->line)
		ft_err_line(var->line, heredoc);
	if (!ft_strcmp(var->line, dlm))
		ft_err_line(var->line, heredoc);
	var->i = 0;
}

void	ft_post_her_doc_c(t_variables *var)
{
	var->var = ft_substr(var->line, var->i + 1, var->j - 1, 1);
	var->le = ft_strlen(ft_expand(var->var));
	var->line = ft_replace_str(var->line, ft_expand(var->var), var->i,
			var->i + var->j - 1);
	var->i += var->le;
}

void	ft_postpost_herdoc(t_variables *var, int heredoc)
{
	ft_putendl_fd(var->line, heredoc);
	free(var->line);
}
