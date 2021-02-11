/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleem <jleem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:05:07 by jleem             #+#    #+#             */
/*   Updated: 2021/02/11 18:57:22 by jleem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>
#include "thread.h"

color	ray_color(const ray &r, const hittable &world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		auto a = dot(rec.normal, vec3(-1, 1, 1).unit());
		return (color(1, 1, 1) * a);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(0.784, 0.635, 0.784) + t * color(0.784, 0.635, 0.784);
}

int		main(void)
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int ssaa_multiplier = 4;
	const int samples_per_pixel = ssaa_multiplier * ssaa_multiplier;

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	// world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera
	camera cam;

	// Render
	std::cout << "P3\n"
			  << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			c_runner runner(samples_per_pixel, ray_color);
			for (int s = 0; s < samples_per_pixel; ++s)
			{
				auto ssaa_i = s / ssaa_multiplier;
				auto ssaa_j = s - ssaa_i * ssaa_multiplier;
				auto u = (i + ((double)ssaa_i / ssaa_multiplier)) / (image_width - 1);
				auto v = (j + ((double)ssaa_j / ssaa_multiplier)) / (image_height - 1);
				// auto u = (i + random_double()) / (image_width-1);
				// auto v = (j + random_double()) / (image_height-1);
				ray r = cam.get_ray(u, v);
				runner.create(r, world);
			}
			write_color(std::cout, runner.join(), samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
	return (0);
}
