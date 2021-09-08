/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:31:12 by minskim2          #+#    #+#             */
/*   Updated: 2021/09/08 20:41:53 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	test(t_inform *inform)
{
	int	i;

	i = 0;
	while (i < inform->size_a)
	{
		printf("%d ", inform->stack_a[i]);
		i++;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	t_inform	inform;

	if (argc < 2)
		return (0);
	init_stack(&inform, argc, argv);
	test(&inform);
	quick_a(&inform, inform.size_a);
	test(&inform);
	return (0);
}

