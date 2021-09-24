/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 19:51:44 by minskim2          #+#    #+#             */
/*   Updated: 2021/09/24 20:22:23 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_simul(t_simul *simul, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	simul->philo_num = ft_atoi(argv[1]);
	simul->time_die = ft_atoi(argv[2]);
	simul->time_eat = ft_atoi(argv[3]);
	simul->time_sleep = ft_atoi(argv[4]);
	if (simul->philo_num < 1 || simul->time_die < 1 || simul->time_eat < 1 || simul->time_sleep < 1)
		return (0);
	if (argc == 6)
	{
		simul->time_opt = ft_atoi(argv[5]);
		if (simul->time_opt < 1)
			return (0);
	}
	else
		simul->time_opt = 0;
	simul->thread = (pthread_t *)malloc(sizeof(pthread_t) * simul->philo_num);
	simul->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * simul->philo_num);
	simul->philo = (t_philo *)malloc(sizeof(t_philo) * simul->philo_num);
	if (!simul->thread || !simul->mutex || !simul->philo)
		return (0);
	return (1);
}

void	init_philo(t_simul *simul)
{
	int	i;

	i = 0;
	while (i < simul->philo_num)
	{
		simul->philo[i].life = simul->time_die;
		simul->philo[i].fork = 0;
		simul->philo[i].status = THINK;
		i++;
	}
}

int	init_pthread_mutex(t_simul *simul)
{
	int	i;
	int	status;

	i = 0;
	while (i < 10)
	{
		status = pthread_create(&simul->thread[i], NULL, philo_survive, (void *)simul);
		if (status < 0 || pthread_mutex_init(&simul->mutex[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
