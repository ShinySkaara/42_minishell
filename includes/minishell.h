/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alalonzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 12:43:04 by alalonzo          #+#    #+#             */
/*   Updated: 2019/02/26 12:26:41 by alalonzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SH_ER_NO_DIR "not a directory"
# define SH_ER_MANY_ARGS "too many arguments"
# define SH_ER_NO_FILE_DIR "no such file or directory"
# define SH_ER_NO_ACCESS "permission denied"
# define SH_ER_NO_CMD "command not found"
# define SH_ER_NO_FORK "fork failed"
# define SH_ER_NO_EXEC "execve failed"
# define SH_ER_BAD_KEY "key bad format"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

enum	e_builtins
{
	EXIT,
	ECHO,
	CD,
	ENV,
	SETENV,
	UNSETENV,
	HELP,
	BUILTIN_COUNT
};

typedef struct	s_env
{
	int			loop;
	char		**env;
	char		*builtin[BUILTIN_COUNT];
	void		(*fun[BUILTIN_COUNT])();
}				t_env;

void			sh_exit(char **row, t_env *env);
void			sh_echo(char **row, t_env *env);
void			sh_cd(char **row, t_env *env);
void			sh_env(char **row, t_env *env);
void			sh_setenv(char **row, t_env *env);
void			sh_unsetenv(char **row, t_env *env);
void			sh_help(char **row, t_env *env);

int				sh_isbuiltin(char **row, t_env *env);
int				sh_iscmd(char **row, t_env *env);
int				sh_ispath(char **row, t_env *env);

void			sh_error(char *a, char *b, char *c);
int				sh_stat(char *path, char *cmd, int mode);
int				sh_access(char *path, char *cmd);
int				sh_find_env_key(char *str, t_env *env, int mode);

int				sh_array_count(char **row);
char			**sh_array_new(int size);
char			**sh_array_dup(char **row);
char			**sh_array_realloc(char **row, int count);
char			**sh_array_del(char **row);

#endif
