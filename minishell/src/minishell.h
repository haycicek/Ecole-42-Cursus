/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haycicek <haycicek/mminga>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 02:34:20 by haycicek          #+#    #+#             */
/*   Updated: 2023/12/06 02:34:20 by haycicek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define YELLOW "\033[38;5;226m"
# define GREEN "\033[38;5;46m"
# define BLUE "\033[38;5;39m"
# define PURPLE "\033[38;5;129m"
# define RESET "\x1b[0m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define EXIT "\033[48;5;150m\033[38;5;214m"
# define CLEAR "\033[2J\033[H"

typedef struct s_var
{
	char	*str;
	char	*env;
}					t_var;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_expand
{
	char			*str;
	struct s_expand	*next;
}					t_expand;

typedef struct s_cmd
{
	char	*cmd_name;
	char	**args;
	int		infile;
	int		outfile;
}			t_cmd;

typedef struct s_data
{
	t_env		*environmental;
	t_env		*export;
	t_expand	*exped;
	t_var		var;
	int			exit_status;
	char		**env;
	int			**fd_pipe;
	int			fd_heredoc[2];
	int			cmd_cnt;
	char		*prompt;
}				t_data;

extern int	g_sin;
t_expand	*ft_add_back_expander(t_expand *head, char *str);
t_expand	*ft_expander(char **line, int i, int j, t_data *data);
t_expand	*ft_parser(t_expand *expander);
int			ft_is_valid_env(char *str, int choose, t_data *data);
int			ft_cd(t_cmd *cmd, t_data *data);
int			ft_echo(t_cmd *cmd);
int			ft_env(t_data *data);
int			ft_exit_cmd(t_cmd *cmd, int i, t_data *data);
int			ft_export(t_cmd *cmd, t_data *data);
int			ft_pwd(void);
int			ft_unset(t_cmd *cmd, t_data *data);
int			exec_ft(t_cmd *cmd, int i, t_data *data);
int			ft_get_path(t_cmd *cmd, char **path, t_data *data);
int			is_question_mark(char c, char x);
int			is_sinquote(char *str, int indx);
int			handle_redir(t_cmd *cmd, t_expand **exped, t_data *data);
int			ft_get_cmd(t_expand **exped, t_cmd *cmd_cmds, int indx,
				t_data *data);
int			load_cmd(t_expand *exped, t_data *data, int count, int i);
int			ft_arg_size(t_expand *exped);
int			ft_count_pipe(t_expand *exped);
int			ft_is_redir(char *str);
int			ft_is_pipe(char *str);
int			ft_error(char type, t_cmd *cmd);
int			find_len_util(char *str, int idx, char quote);
int			ft_get_word_len(char *str);
int			ft_is_delimiter(char c);
int			ft_is_quote(char c);
int			ft_quote_check(char *input);
int			check_strange_chars(t_expand *exped);
int			ft_control(char *input);
int			is_space(char *str);
int			extra_func(t_data *data);
int			chck(t_expand *exped);
char		*trim_env(char *line, int *k);
char		**ft_env_to_matrix(t_data *data);
char		*ft_search_env(char *splitted_input, t_data *data);
char		**ft_load_args(t_expand **exped, t_cmd *cmd, int arg_cnt,
				t_data *data);
char		*ft_trim_quotes(char *str, int i, int len);
char		**ft_lexer(char *str, int idx);
char		*ft_strsub(char *str, int start, int end);
char		*ft_strstr(char *big, char *little);
void		ft_delete_env(char *str, t_data *data);
void		ft_delete_export(char *str, t_data	*data);
void		ft_change_env(char *str, char *new_value, int choose,
				t_data *data);
void		ft_new_env(char *str, int choose, t_data *data);
void		ft_redir_error(t_cmd *cmd, char *str, char *filename);
void		ft_get_heredoc_lines(char *delim, int fd, t_data *data);
void		handle_heredoc_file(t_cmd *cmd, char *delim, t_data *data);
void		free_pipes(int **pipefd, int count);
void		free_string(char *str);
void		free_array(char **str);
void		free_cmds(t_cmd *cmds);
void		free_exp(t_expand *exped);
void		ft_entry(void);
void		free_env_node(t_env *env);
void		free_env(t_env *env);
void		ft_exit(char *str, t_data *data);
void		sig_int(int sig);
void		ft_signal(int flag, t_data *data);
void		ft_add_back(t_env *new, t_env **head);
void		ft_load(char **env, int choose, t_data *data);
void		free_exp_and_pipe(t_data *data);

#endif
