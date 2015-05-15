/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GrowBlock.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:47:46 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GrowBlock.hpp"
#include "Game.hpp"
#include "Snake.hpp"

GrowBlock::GrowBlock(void)
	: ABlock(ABlock::GROW), _eaten(false)
{
}

GrowBlock::~GrowBlock(void)
{
}

void					GrowBlock::active(Game &game)
{
	_eaten = true;
	game.getSnake().grow();
	game.addScore(10);
	game.spawn(new GrowBlock());
}

bool					GrowBlock::shouldDestroy(void) const
{
	return (_eaten);
}
