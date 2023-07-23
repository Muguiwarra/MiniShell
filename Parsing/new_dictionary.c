/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dictionary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:02:25 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/23 02:15:39 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dic	*ft_new_dic(char *input)
{
	int		i;
	int		j;
	t_dic	*dic;

	i = 0;
	g_glob.open = 0;
	dic = NULL;
	while(input[i] && ft_is_delimiter(input[i]) == SPACE)
		i++;
	if (!input[i])
		return (NULL);
	if (ft_nb_quotes(input) == 1)
	{
		g_glob.exit_status = SYNTAX_ERROR;
		return (NULL);
	}
	while (input[i])
	{
		j = 0;
		if (input[i + j] && g_glob.open == 1)
		{

		}
	}
}

char	*ft_del_char(char *input, char c)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i++] == c)
			continue ;
		j++;
	}
	output = ft_malloc(j + 1);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] ==  c)
		{
			i++;
			continue ;
		}
		output[j++] = input[i++];
	}
	output[j] = '\0';
	return (output);
}

int		ft_nb_quotes(char *input)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (input[i])
	{
		if (input[i] == '\"')
		{
			q++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				q++;
		}
		else if (input[i] == '\'')
		{
			q++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
				q++;
		}
		i++;
	}
	return (q % 2);
}

char	*ft_new_expanded_input(char *input)
{
	char	*output;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			j++;
			while (input[i] && input[i] != '\'')
			{
				j++;
				i++;
			}
			j++;
		}
		else
		{
			if (input[i] && ft_is_dollar(input[i]))
			{
				i++;
				while (input[i] && )
			}
		}
	}
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (SPACE);
	else if (c == '<')
		return (LESSER);
	else if (c == '>')
		return (GREATER);
	else if (c == '|')
		return (PIPE);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	return (0);
}

int	ft_is_dollar(char c)
{
	if (c == '$')
		return (DOLLAR);
	return (0);
}