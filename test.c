#include "./libft/includes/libft.h"

int	cmp(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b));
}

void	print(t_list *l)
{
	ft_printf("%s\n", (char *)(l->content));
}

int main (int ac, char **av)

{
	t_list *lst = 0;
	t_list *new;

	while (ac > 1)
	{
		new = ft_lstnew((void *)av[ac - 1], ft_strlen(av[ac - 1]) + 1);
		ft_lstins(&lst, new, *cmp);
		ac--;
	}

	ft_printf("Size = %d\n", ft_lstsize(lst));
//return 0;

	ft_lstiter(lst, print);
	return (0);


}
