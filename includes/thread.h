/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:37:18 by jleem             #+#    #+#             */
/*   Updated: 2021/02/11 18:56:46 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <thread>
# include "vec3.h"
# include "hittable_list.h"

class c_runner
{
public:
	c_runner(int samples_per_pixel, color (*ray_color)(const ray &, const hittable &))
		: t_idx(0), t_count(samples_per_pixel), f(ray_color)
	{
		threads = new std::thread[samples_per_pixel];
	}
	~c_runner(void)
	{
		delete[] threads;
	}

	void	create(const ray &r, const hittable_list &world)
	{
		threads[t_idx++] = std::thread(
			[this, &r, &world]()
			{
				std::cerr << "thread: " << t_idx << std::endl;
				pixel_color += f(r, world);
			}
		);
	}

	color	join(void)
	{
		for (size_t i = 0; i < t_count; i++)
			threads[i].join();
		return (pixel_color);
	}

private:
	std::thread	*threads;
	size_t		t_idx;
	size_t		t_count;
	color		pixel_color;
	color		(*f)(const ray &, const hittable &);
};

#endif
