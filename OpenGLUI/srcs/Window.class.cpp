/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/30 10:55:52 by ngoguey           #+#    #+#             */
//   Updated: 2015/05/19 14:34:37 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "Window.class.hpp"
#include "IGame.hpp"
#include "ISnake.hpp"
#include "IBlock.hpp"

#define TMP_PADDING ((int)10)

// * STATICS **************************************************************** //
#define TEMPLATE_SIZE(S) S[0], S[1], S[2], S[3], S[4], S[5]

constexpr ftce::Array<size_t, 6>    Window::sinSize;
constexpr ftce::Array<CornerPoints<TEMPLATE_SIZE(Window::sinSize)>, NUM_PRECALC_POINTS>
Window::sinPoints;
constexpr ftce::Array<size_t, 6>    Window::dexSize;
constexpr ftce::Array<CornerPoints<TEMPLATE_SIZE(Window::dexSize)>, NUM_PRECALC_POINTS>
Window::dexPoints;

#undef TEMPLATE_SIZE
std::queue<EventType>				Window::pendingEvents;
// std::queue<EventType>				Window::pendingEvents{EventType::EVENT_NOPE};

// * CONSTRUCTORS *********************************************************** //
static void error_callback(int error, const char* description)
{
	std::cout << description << "(" << error << ")" << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int, int action, int)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_UP);
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_LEFT);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_RIGHT);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_DOWN);
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_R);
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		Window::pendingEvents.push(EventType::EVENT_SPACE);
}

Window::Window(std::pair<int, int> gridSize) :
	_tmpGridSize(gridSize),
	_winSize(
		std::make_pair(
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.first) *
								 CHUNK_SIZEF)) + TMP_PADDING * 2,
			static_cast<int>(std::ceilf(
								 static_cast<float>(gridSize.second) *
								 CHUNK_SIZEF)) + TMP_PADDING * 2
			)),
	_topLeftCell(std::make_pair(static_cast<float>(TMP_PADDING),
								static_cast<float>(TMP_PADDING))),
	_lastTime(glfwGetTime()),
	_phase(0.f),
	_deathTime(-1.f)
{
	// int	i = 0;

	if (CHUNK_SIZEF < 3.f || gridSize.first < 1 || gridSize.second < 1)
		throw std::invalid_argument("Grid attributes invalid");
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		throw std::runtime_error("Could not init glfw");
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	_win = glfwCreateWindow(_winSize.first, _winSize.second, "Nibbler",
							NULL, NULL);
	if (!_win)
	{
		glfwTerminate();
		throw std::runtime_error("Could not create glfw window");
	}
	// glfwMakeContextCurrent(_win); //useless?
	// glfwSwapInterval(1); //useless?

	// gluLookAt(3,3,3,0,0,0,0,0,1); // to test
	glfwSetKeyCallback(_win, key_callback);


	glEnable(GL_DEPTH_TEST);

	glEnable( GL_MULTISAMPLE );
	
	glMatrixMode(GL_MODELVIEW);
	return ;
}

// * DESTRUCTORS ************************************************************ //
Window::~Window()
{
	glfwDestroyWindow(_win);
	glfwTerminate();
	std::cout << "[Window]() Dtor called" << std::endl;
	return ;
}

// * OPERATORS ************************************************************** //
// * GETTERS **************************************************************** //
// * SETTERS **************************************************************** //
// * MEMBER FUNCTIONS / METHODS ********************************************* //

EventType					Window::getEvent(void)
{
	auto ev = EventType::EVENT_NOPE;

	if (!Window::pendingEvents.empty())
	{
		ev = Window::pendingEvents.front();
		Window::pendingEvents.pop();
	}
	return (ev);
}

void						Window::_put_grid(void) const
{
	int		i;

	glBegin(GL_LINES);
	glColor3f(0.f, .3f, 0.f);
	i = 0;
	for (float y = _topLeftCell.second; i <= _tmpGridSize.second;
		 i++, y += CHUNK_SIZEF)
	{
		glVertex3f(_topLeftCell.first, y, 0.f);
		glVertex3f(_winSize.first - _topLeftCell.first, y, 0.f);
	}
	i = 0;
	for (float x = _topLeftCell.first; i <= _tmpGridSize.first;
		 i++, x += CHUNK_SIZEF)
	{
		glVertex3f(x, _topLeftCell.second, 0.f);
		glVertex3f(x, _winSize.second - _topLeftCell.second, 0.f);		
	}	
	glEnd();
	return ;
}

float				getPhase(float fullTime = 3.f, float selfDelta = 0.f)
{
	float randRange = fmod(glfwGetTime() + selfDelta, fullTime) /
		(fullTime / 2.f);

	if (randRange < 1.f)
		return (randRange - 0.5f);
	return (1.f - randRange + 0.5f);
}

float				getPhaseLoop(float fullTime = 10.f, float selfDelta = 0.f)
{
	return (fmod(glfwGetTime() + selfDelta, fullTime) / fullTime);
}


std::deque<std::pair<int, int>>	customSnake(void)
{
	
	std::deque<std::pair<int, int>>		q;

	q.push_front(std::make_pair(3, 0)); //tail
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	
	
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));

	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));

	q.push_front(std::make_pair(q.front().first, q.front().second - 1));
	q.push_front(std::make_pair(q.front().first, q.front().second - 1));
	q.push_front(std::make_pair(q.front().first, q.front().second - 1));

	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
		
	q.push_front(std::make_pair(q.front().first, q.front().second - 1));
	q.push_front(std::make_pair(q.front().first, q.front().second - 1));

	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));
	q.push_front(std::make_pair(q.front().first + 1, q.front().second));

	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));
	q.push_front(std::make_pair(q.front().first, q.front().second + 1));

	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));
	q.push_front(std::make_pair(q.front().first - 1, q.front().second));

	
	return (q);
}

void						Window::draw(IGame const &game)
{
	ISnake const		&snake = game.getSnake();
	float const			elapsed = glfwGetTime() - this->_lastTime;


	if (!snake.isDie())
	{
		_phase -= elapsed / (snake.getSpeed() / 1000.f) * PHASE_PER_CHUNK;
		_phase = std::fmod(_phase + 1.f, 1.f);
		this->_deathTime = -1.f;
	}
	else
	{
		if (this->_deathTime < 0.f)
			this->_deathTime = glfwGetTime();		
	}	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(.0f, static_cast<float>(_winSize.first),
			static_cast<float>(_winSize.second), .0f,
			-CHUNK_SIZEF * 1000.f, CHUNK_SIZEF * 1000.f);
	if (snake.isDie())
	{
		float const		rateScale = 1.f /
			std::pow(glfwGetTime() - this->_deathTime + 1.f, 3.f);
		float const		rateTranslation = ((1.f - rateScale) / 2.f);

		glTranslatef(
			rateTranslation * static_cast<float>(_winSize.first),
			rateTranslation * static_cast<float>(_winSize.second), 0.f);
		glScalef(rateScale, rateScale, rateScale);
	}
	// glRotatef(25.f , 0.f, 1.f, 0.f);
	// glRotatef(getPhaseLoop(3.f) * 75.f + .35f
	// , 1.f, 0.f, 0.f);
	glRotatef(25.f, 1.f, 0.f, 0.f);
	// glRotatef(-3.f, 0.f, 0.f, 1.f);

	// glTranslatef(-25.f
	// , 130.f
	// , -80.f
	// );
	
	glMatrixMode(GL_MODELVIEW); //useless?
	glLoadIdentity();
	this->_put_grid();
	glLoadIdentity();
	

	for (auto const *v : game.getBlocks())
	{
		if (v->getType() == IBlock::GROW)
			this->_put_block(std::make_pair(v->getX(), v->getY()),
							 std::make_tuple(1.f, 0.5f, 0.f));
		else if (v->getType() == IBlock::BONUS)
			this->_put_block(std::make_pair(v->getX(), v->getY()),
							 std::make_tuple(0.5f, 0.5f, 0.99f));
		else
			this->_put_block(std::make_pair(v->getX(), v->getY()),
							 std::make_tuple(0.f, 0.5f, 0.f));
	}

/*
	std::cout <<
		"elapsed(SEC):" << elapsed <<
		"   sec per chunk:" << (snake.getSpeed() / 1000.f) <<
		"   fraction of chunk:" << elapsed / (snake.getSpeed() / 1000.f) <<

		"   PHASE_PER_CHUNK:" << PHASE_PER_CHUNK 

						<< std::endl;
*/	
	auto const &q = snake.getChunks();
	// auto const &q = customSnake();

	float curPhase = _phase;

	
	for (auto it = ++q.rbegin(), ite = --(--q.rend());
		 it != ite;
		 ++it)
	{
		_putSnakeChunk(
			*(it), *(it - 1), *(it + 1), curPhase);
		curPhase = std::fmod(curPhase + PHASE_PER_CHUNK + 1.f, 1.f);
	}
	_putSnakeChunk(
		*(++(q.begin())), *(++(++q.begin())), *(q.begin()), curPhase, true);
	curPhase = std::fmod(curPhase + PHASE_PER_CHUNK + 1.f, 1.f);
	this->_put_head(*q.begin(), *++q.begin(), curPhase,
					snake.getMoveRatio());

	
	glFlush(); //remove ?
	glfwSwapBuffers(_win);
	glfwPollEvents();
	this->_lastTime += elapsed;
	return ;
}
bool						Window::windowShouldClose(void) const
{
	return (glfwWindowShouldClose(_win));
}

// * NESTED_CLASSES ********************************************************* //
