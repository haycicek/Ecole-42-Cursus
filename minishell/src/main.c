/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:33:36 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:33:36 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../libft/libft.h"

static char	*get_prompt(void)
{
	char	*prompt;
	char	*pwd;
	int		i;

	i = 0;
	prompt = NULL;
	pwd = getcwd(NULL, 0);
	while (pwd[i] != '\0')
		i++;
	while (pwd[i - 1] != '/')
		i--;
	prompt = ft_strdup(YELLOW"minishell@"RESET);
	prompt = ft_strjoin(prompt, pwd + i,
			ft_strlen(pwd + i) + ft_strlen(prompt) + 1);
	prompt = ft_strjoin(prompt, " $ ", ft_strlen(prompt) + 4);
	free(pwd);
	return (prompt);
}

static void	start_minishell(char *input, t_data *data)
{
	int		error_state;
	char	**lexered_input;

	if (!ft_control(input))
		return ;
	if (!ft_quote_check(input))
		return ;
	lexered_input = ft_lexer(input, 0);
	if (lexered_input == NULL)
	{
		free_array(lexered_input);
		return ;
	}
	data->exped = ft_expander(lexered_input, 0, 0, data);
	free_array(lexered_input);
	data->exped = ft_parser(data->exped);
	error_state = check_strange_chars(data->exped);
	if (error_state != 0)
	{
		free_exp(data->exped);
		ft_error(error_state, 0);
		return ;
	}
	load_cmd(data->exped, data, 0, 0);
	free_exp_and_pipe(data);
}

static void	minishell(t_data *data)
{
	char	*input;

	while (1)
	{
		ft_signal(1, data);
		data->prompt = get_prompt();
		input = readline(data->prompt);
		if (!input)
		{
			free_string(data->prompt);
			free_string(input);
			ft_signal(2, data);
		}
		else if (input && data->prompt)
		{
			start_minishell(input, data);
			if (is_space(input))
				add_history(input);
		}
		free_string(data->prompt);
		free_string(input);
	}
}

static char	**ft_copy_matrix(char **matrix)
{
	int		i;
	char	**new_matrix;

	i = 0;
	while (matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		if (!new_matrix[i])
			return (NULL);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (ac != 1 || av[1])
		exit((printf("! Too many arguments.\n"), 1));
	ft_entry();
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	data->var.env = NULL;
	data->var.str = NULL;
	data->environmental = NULL;
	data->export = NULL;
	data->env = ft_copy_matrix(env);
	data->exit_status = 0;
	ft_load(env, 0, data);
	ft_load(env, 1, data);
	minishell(data);
	return (0);
}
