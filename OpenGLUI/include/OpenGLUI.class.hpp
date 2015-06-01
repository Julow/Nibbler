// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OpenGLUI.class.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/22 14:51:58 by ngoguey           #+#    #+#             //
//   Updated: 2015/06/01 13:44:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPENGLUI_CLASS_HPP
# define OPENGLUI_CLASS_HPP

# include <utility>
# include <iostream>
# include <stdexcept>
# include <queue>
# include <tuple>
# include <deque>
# include <map>

# include <GLFW/glfw3.h>
# include <FTGL/ftgl.h>

# include "nibbler.h"
# include "IBlock.hpp"
# include "IUI.hpp"
# include "IGame.hpp"
# include "ISnake.hpp"
# include "OpenGLLib.h"
# include "AngledSnakePoints.class.hpp"
# include "ftconstexpr/Vertex.hpp"
# include "ftconstexpr/VtsColor.hpp"

typedef std::tuple<float, float, float>	t_color;
typedef decltype(GLFW_KEY_DOWN)			t_glfwevent;
typedef unsigned char					t_byte;

class OpenGLUI : public IUI
{
	OpenGLUI() = delete;
	OpenGLUI(OpenGLUI const &src) = delete;
	OpenGLUI						&operator=(OpenGLUI const &rhs) = delete;
public:
	// * STATICS ******************** //
	static std::queue<EventType>								pendingEvents;
	static std::map<t_glfwevent, EventType> const				eventsMap;
	static std::map<IBlock::Type, std::array<t_byte, 9> > const	blocksSchemes;

	// * CTORS / DTORS ************** //
	OpenGLUI(std::pair<int, int> gridSize);
	virtual ~OpenGLUI();

	// * MEMBER FUNCTIONS / METHODS * //
	EventType					getEvent(void);
	void						draw(IGame const &game);
	bool						windowShouldClose(void) const;
	void                    	init(void);

private:
	// * DRAW MEMBER FUNCTIONS ****** //
	void							_put_grid(void) const;
	void							_put_block(std::pair<int, int> const &pos,
											   IBlock::Type type) const;
	void							_put_head(
		std::pair<int, int> const &selfPos,
		std::pair<int, int> const &prevPos,
		float phase, float ratio) const;
	void							_putSnakeChunk(
		std::pair<int, int> const &selfPos,
		std::pair<int, int> const &prevPos,
		std::pair<int, int> const &nextPos,
		float phase, float frontThickness = 1.f, float rearThickness = 1.f
		) const;
	void							_putGround(void) const;
	void							_putBackground(void) const;
	void							_putTexts(IGame const &game);

	// * NESTED OBJECTS ************* //
	typedef std::tuple<float, float, float, float>				t_colorDeltas;
	typedef std::tuple<float, float, t_color, t_colorDeltas>	t_groundData;
	typedef std::vector<std::vector<t_groundData>>				t_groundDatas;
	typedef ftce::VtsColor<3u, float, 2u>						bg_point;
	typedef std::vector<bg_point>								bg_points;

	// * PRECALC MEMBER FUNCTIONS *** //
	t_groundDatas					_buildGroundDatas(void) const;
	bg_points						_buildBgDatas(void) const;
	
	// * ATTRIBUTES ***************** //
	GLFWwindow						*_win;			// Window PTR
	FTGLPixmapFont					_font;
	std::pair<int, int> const		_tmpGridSize;	// Grid size (Ctor)

	std::pair<int, int> const		_winSize;		// Pixels size
	std::pair<float, float> const	_topLeftCell;	// Top left cell coords

	float							_lastTime;		// Last render time
	float							_phase;			// Current phase at the tail
	float							_deathTime;
	float							_lastMoveRatio;	// Used to smooth undulations.
	t_groundDatas const				_groundDatas;	// Ground colors/vertices
	bg_points const					_bgDatas;		// Background colors/vertices

	// * STATICS ******************** //
#define TEMPLATE_SIZE(S) S[0], S[1], S[2], S[3], S[4], S[5]
	static constexpr ftce::Array<size_t, 6>							sinSize
		{AngledSnakePoints::calcPointsArraySize(true)};
	static constexpr ftce::Array<
		CornerPoints<TEMPLATE_SIZE(sinSize)>, NUM_PRECALC_POINTS>	sinPoints
		{AngledSnakePoints::buildPointsArray<TEMPLATE_SIZE(sinSize)>(true)};
	static constexpr ftce::Array<size_t, 6>							dexSize
		{AngledSnakePoints::calcPointsArraySize(false)};
	static constexpr ftce::Array<
		CornerPoints<TEMPLATE_SIZE(dexSize)>, NUM_PRECALC_POINTS>	dexPoints
		{AngledSnakePoints::buildPointsArray<TEMPLATE_SIZE(dexSize)>(false)};
#undef TEMPLATE_SIZE
};

/*
Todo:
fmod on straight snake chunk to greatly reduce holes in snake
Narrow Z in neck's angle
Tongue
Obstacles
plane lean
apple's color
plane thickness
texts
overlays pause/death
*/
#endif // ************************************************** OPENGLUI_CLASS_HPP //
