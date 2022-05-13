#include "minishell.h"

void	echo(char **matrix)
{
	char	*temp;
	int		flag;
	int		i;

	flag = 0;
	i = 1;
	if (!matrix[1])
	{
		ft_putchar_fd("\n", 1);
		return ;
	}
	if (!ft_strncmp(matrix[1], "-n", 3))
	{
		flag = 1;
		i = 2;
	}
	while (matrix[i])
	{
		ft_putstr_fd(matrix[i], 1);
		if (matrix[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
}

// comportamento do echo
// echo printa o que tem depois do comando
// a opcao -n tira a quebra de linha
