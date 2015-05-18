/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BonusBlock.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:36:29 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 18:35:21 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BonusBlock.hpp"
#include "WallBlock.hpp"
#include "Game.hpp"
#include "Snake.hpp"

BonusBlock::BonusBlock(std::chrono::steady_clock::duration timeout)
	: ABlock(ABlock::BONUS), _eaten(false),
	_timeout(timeout)
{
}

BonusBlock::~BonusBlock(void)
{
}

void					BonusBlock::update(Game &game, std::chrono::steady_clock::duration t)
{
	_timeout -= t;
	if (_timeout <= std::chrono::seconds(0))
	{
		_eaten = true;
		if (game.getSettings().bonusToWall)
		{
			WallBlock *b = new WallBlock();
			b->setPos(_pos.first, _pos.second);
			game.getBlocks().push_back(b);
		}
	}
}

void					BonusBlock::active(Game &game)
{
	_eaten = true;
	game.getSnake().grow();
	game.addScore(65);
}

bool					BonusBlock::shouldDestroy(void) const
{
	return (_eaten);
}
