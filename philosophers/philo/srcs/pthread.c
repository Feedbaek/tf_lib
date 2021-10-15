/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minskim2 <minskim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:07:09 by minskim2          #+#    #+#             */
/*   Updated: 2021/10/16 03:23:15 by minskim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static t_philo	*running_start(void *p, int *idx)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	*idx = philo->num - 1;
	philo->change = 1;
	while (1)
	{
		usleep(50);
		if (*philo->start_point)
			break ;
	}
	return (philo);
}

static void	running_think(t_philo *philo, int idx)
{
	philo->status = THINK;
	usleep(300);
	if (idx % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex[idx]);
		philo->status = FORK;
		philo->change = 1;
		pthread_mutex_lock(&philo->mutex[(idx + 1) % philo->philo_num]);
	}
	else
	{
		usleep(100);
		pthread_mutex_lock(&philo->mutex[(idx + 1) % philo->philo_num]);
		philo->status = FORK;
		philo->change = 1;
		pthread_mutex_lock(&philo->mutex[idx]);
	}
}

void	*running_pthread(void *p)
{
	t_philo			*philo;
	int				idx;

	philo = running_start(p, &idx);
	while (1)
	{
		running_think(philo, idx);
		philo->status = EAT;
		philo->change = 1;
		usleep(philo->time_eat * 1000);
		pthread_mutex_unlock(&philo->mutex[idx]);
		pthread_mutex_unlock(&philo->mutex[(idx + 1) % philo->philo_num]);
		philo->num_eat += 1;
		if (philo->time_opt && philo->num_eat >= philo->time_opt)
			philo->end_eat = 1;
		philo->status = SLEEP;
		philo->change = 1;
		usleep(philo->time_sleep * 1000);
		philo->change = 1;
	}
	return (p);
}

int	end_mutex(t_simul *simul)
{
	int	i;

	i = 0;
	while (i < simul->philo_num)
	{
		pthread_detach(simul->thread[i]);
		pthread_mutex_unlock(&simul->mutex[i]);
		pthread_mutex_destroy(&simul->mutex[i]);
		i++;
	}
	return (1);
}

int	wait_pthread(t_simul *simul)
{
	int	status;

	status = pthread_create(&simul->thread[simul->philo_num], \
	NULL, mornitor_pthread, (void *)simul);
	if (status < 0)
		return (0);
	pthread_join(simul->thread[simul->philo_num], NULL);
	return (1);
}
