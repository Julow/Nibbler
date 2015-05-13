/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SfmlUI.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/12 17:49:37 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/12 20:08:14 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFMLUI_HPP
# define SFMLUI_HPP

# include <utility>
# include <SFML/Graphics.hpp>
# include "nibbler.h"
# include "IBlock.hpp"
# include "IUI.hpp"

# define CHUNK_SIZE		64

# define GRID_COLOR		150, 250, 0

class	SfmlUI : public sf::RenderWindow, public IUI
{
public:
	SfmlUI(std::pair<int, int> gameSize);
	virtual ~SfmlUI(void);

	virtual EventType			getEvent(void);

	virtual void				draw(IGame const &game);

	virtual bool				windowShouldClose(void) const;

protected:

	std::pair<int, int>			_gameSize;

	std::map<int, EventType>	_events;

	sf::VertexArray				_line;

	sf::Color					_chunkColor(IBlock::Type type);
	void						_drawGrid(void);
	void						_drawWallBlock(int x, int y);
	void						_drawChunk(int x, int y, sf::Color color);

private:
	SfmlUI(void);
	SfmlUI(SfmlUI const &src);
	SfmlUI			&operator=(SfmlUI const &rhs);
};

#endif