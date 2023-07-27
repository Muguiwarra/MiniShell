#include "exec.h"

void	increment_pid(t_vars *vars)
{
	vars->pid++;
}

void	update_value(t_env *env, char *key, char *value)
{
	while(env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	t_vars	vars;
	t_env	*env;

	env = NULL;
	env_add_back(&env, env_new("hello", "world"));
	env_add_back(&env, env_new("foo", "bar"));
	env_print(env);
	update_value(env, "foo", "baz");
	env_print(env);
	vars.pid = 0;
	increment_pid(&vars);
	increment_pid(&vars);
	printf("vars.pid = %d\n", vars.pid);
}