// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/27 14:11:16 by ngoguey           #+#    #+#             //
//   Updated: 2015/04/29 07:11:23 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <GLFW/glfw3.h>
# include <utility>
//# include <string>
# include <iostream>
# include <stdexcept>

class Window
{
public:
	Window(std::pair<int, int> gridSize, float cellSize);
	virtual ~Window();

	void						draw(void) const;
	bool						windowShouldClose(void) const;
	
protected:
private:
	Window();
	Window(Window const &src);
	Window						&operator=(Window const &rhs);

	void						_put_grid(void) const;
	
	
	GLFWwindow					*_win;
	std::pair<int, int> const	_tmpGridSize;		// Grid size (Ctor)
	float const					_cellSize;			// Cell size (Ctor)
	
	std::pair<int, int> const	_winSize;			// Window size
	std::pair<float, float> const	_topLeftCell;	// Top left cell coords
	std::pair<float, float> const	_cellPadding;	// Padding between cells
	
	
};
//std::ostream					&operator<<(std::ostream &o, Window const &rhs);

#endif // ******************************************************** WINDOW_HPP //
