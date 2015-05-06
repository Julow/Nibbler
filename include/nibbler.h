/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nibbler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 19:08:22 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 16:45:45 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIBBLER_H
# define NIBBLER_H

/*
** ========================================================================== **
** Prototypes
*/

class	Game;
class	Snake;
class	IUI;
class	Event;
class	IBonus;
class	GrowBonus;

/*
** ========================================================================== **
** Settings
*/

# define GAME_WIDTH			12
# define GAME_HEIGHT		20

# define UPDATE_INTERVAL	std::chrono::milliseconds(150)

/*
** ========================================================================== **
** Libs
*/

# define INIT_FUNCTION		init

# define UI_1				"lib/OpenGL.so"
# define UI_2				"lib/NcursesUI.so"

/*
** ========================================================================== **
** Utils
*/

# define STR_VALUE(s)		#s
# define STR(s)				STR_VALUE(s)

# define PRINT(msg)			std::cout << msg << std::endl;

# define DEBUG(msg)			PRINT("Debug: " << msg)

#endif
