/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 15:38:18 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/11 17:36:40 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <exception>
# include <list>
# include "nibbler.h"
# include "IGame.hpp"
# include "Snake.hpp"

class	Game : public IGame
{
public:
	Game(void);
	virtual ~Game(void);

// Shared
	virtual int							getGameWidth(void) const;
	virtual int							getGameHeight(void) const;

	virtual int							getScore(void) const;
	virtual int							getFPS(void) const;
	virtual bool						isPaused(void) const;

	virtual bool						isBlock(int x, int y) const;

	virtual std::list<IBlock*> const	&getBlocks(void) const;
	virtual Snake const					&getSnake(void) const;
// -

	void								start(void);

	void								setPaused(bool paused);

	void								changeUI(char const *lib) throw(std::exception);

	Snake								&getSnake(void);

	void								spawn(ABlock *block);

protected:

	void								*_uiLib;
	IUI									*_ui;

	int									_gameWidth;
	int									_gameHeight;

	int									_score;
	bool								_paused;
	int									_fps;

	std::list<IBlock*>					_blocks;

	Snake								_snake;

	void								_update(std::chrono::steady_clock::duration t);

private:
	Game(Game const &src);
	Game								&operator=(Game const &rhs);
};

#endif
