/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 15:15:41 by ngoguey           #+#    #+#             */
/*   Updated: 2015/05/01 19:58:13 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "nibbler.h"
#include "IUI.hpp"
#include "Game.hpp"

int main(void)
{
	Game			game;

	try
	{
		game.changeUI("lib/OpenGL.so");
	}
	catch (std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	game.start();
	return (0);
}
