// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Window.draw.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/30 08:24:36 by ngoguey           #+#    #+#             //
//   Updated: 2015/05/15 16:22:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

//#include <iostream>
#include "Window.class.hpp"
#include <cmath>

// * MEMBER FUNCTIONS / METHODS ********************************************* //

static void					rotateChunk(
	std::pair<int, int> const &prevDelta, std::pair<int, int> const &nextDelta)
{
	(void)nextDelta;
	if (prevDelta.first != 0)
	{
		//x changes
		if (prevDelta.first > 0)
		{
			glRotatef(-90.f, 0, 0, 1);
			glTranslatef(-CHUNK_SIZE, 0.f, 0.f);
		}
		else
		{
			glRotatef(90.f, 0, 0, 1);
			glTranslatef(0.f, -CHUNK_SIZE, 0.f);
		}
	}
	else
	{
		//ychanges
		if (prevDelta.second > 0)
			return ;
		else
		{
			glRotatef(180.f, 0, 0, 1);
			glTranslatef(0.f, -CHUNK_SIZE, 0.f);
			glTranslatef(-CHUNK_SIZE, 0.f, 0.f);
		}
	}
	return ;
}

void						Window::_putSnakeChunk(
	std::pair<int, int> selfPos,
	std::pair<int, int> prevPos,
	std::pair<int, int> nextPos,
	float phase,
	std::tuple<float, float, float> color1,
	std::tuple<float, float, float> color2) const
{
	std::pair<int, int> prevDelta =
		std::make_pair<int, int>(selfPos.first - prevPos.first,
								 selfPos.second - prevPos.second);
	std::pair<int, int> nextDelta =
		std::make_pair<int, int>(nextPos.first - selfPos.first,
								 nextPos.second - selfPos.second);
	if (prevDelta.first > 1)
		prevDelta.first = -1;
	else if (prevDelta.first < -1)
		prevDelta.first = 1;
	if (prevDelta.second > 1)
		prevDelta.second = -1;
	else if (prevDelta.second < -1)
		prevDelta.second = 1;
	if (nextDelta.first > 1)
		nextDelta.first = -1;
	else if (nextDelta.first < -1)
		nextDelta.first = 1;
	if (nextDelta.second > 1)
		nextDelta.second = -1;
	else if (nextDelta.second < -1)
		nextDelta.second = 1;

	std::pair<float, float> const	topLeft(
		_topLeftCell.first + CHUNK_SIZEF * selfPos.first,
		_topLeftCell.second + CHUNK_SIZEF * selfPos.second);
	float ratio = fmod(glfwGetTime(), 5.f) / 5.f; //debug
	(void)ratio;
	(void)color1;
	(void)color2;
	
	glLoadIdentity();
	glTranslatef(topLeft.first, topLeft.second, -0.0f);
	rotateChunk(prevDelta, nextDelta);
	
	// glRotatef(ratio * 360.f, 0, 1, 0);
	// glRotatef(0.f, 0, 1, 0);	

	float curphase = phase;

	// float r, g, b;
	float r = 0.f, g = 0.33f, b = .66f;
		
	float z = 20.f;
	float x, y = 0.f;
	
	if ((prevDelta.first != 0) != (nextDelta.first != 0))
	{
		if ((prevDelta.second > 0 && nextDelta.first > 0) ||
			(prevDelta.second < 0 && nextDelta.first < 0) ||
			(prevDelta.first > 0 && nextDelta.second < 0) ||
			(prevDelta.first < 0 && nextDelta.second > 0)) //sinistro
		{
			auto const	&points = Window::sinPoints[
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f))];
#define PUTCOLOR								\
			if (v.z < 0.5f)						\
				glColor3f(.7f, 0.f, 0.0f);		\
			else								\
				glColor3f(.0f, 0.5f, 0.0f);
			
#define PUTCOLOR2								\
			if (v.z < 0.5f)						\
				glColor3f(fmod(r += 0.33f, 1.f), fmod(g += 0.33f, 1.f), fmod(b += 0.33f, 1.f));	\
			else								\
				glColor3f(.0f, 0.5f, 0.0f);
			
			glBegin(GL_TRIANGLE_STRIP);
			// glColor3f(.5f, 0.0f, 0.0f);
			
			for (auto const &v : points.leftStrip1)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.0f, 0.5f, 0.0f);				
			for (auto const &v : points.leftFan)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 0.0f, 0.5f);				
			for (auto const &v : points.leftStrip2)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();

			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.5f, 0.0f);				
			for (auto const &v : points.rightStrip1)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.5f, 0.0f, 0.0f);				
			for (auto const &v : points.rightFan)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 5.0f, 0.f);				
			for (auto const &v : points.rightStrip2)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
		else
		{
			auto const	&points = Window::dexPoints[
				static_cast<int>(std::round(phase * NUM_PRECALC_POINTSF - 0.5f))];

			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.0f, 0.0f);
			for (auto const &v : points.leftStrip1)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.0f, 0.5f, 0.0f);
			for (auto const &v : points.leftFan)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 0.0f, 0.5f);
			for (auto const &v : points.leftStrip2)
			{
				PUTCOLOR;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.5f, 0.5f, 0.0f);
			for (auto const &v : points.rightStrip1)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(.5f, 0.0f, 0.0f);
			for (auto const &v : points.rightFan)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(.0f, 5.0f, 0.f);
			for (auto const &v : points.rightStrip2)
			{
				PUTCOLOR2;
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	}
	else
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;
				
			// LOL
			// glColor3f(fmod(r, 1.f), fmod(g, 1.f), fmod(b, 1.f));
			glColor3f(fmod(r += 0.33f, 1.f), fmod(g += 0.33f, 1.f), fmod(b += 0.33f, 1.f));
			
			glVertex3f(x * CHUNK_SIZE, y, 0.f);
			glColor3f(.0f, 0.5f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH_HALF) * CHUNK_SIZE, y, z);

			y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
		}
		glEnd();
	
		glBegin(GL_TRIANGLE_STRIP);
		curphase = phase;	
		y = 0.f;
		for (int i = 0; i <= POINTS_PER_SIDE; i++)
		{
			x = (cosf((0.5f + curphase) * M_PI * 2.f) + 1.f) / 2.f * SNAKE_WIDTH_INV;
		
			glColor3f(.7f, 0.f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH) * CHUNK_SIZE, y, 0.f);
			glColor3f(.0f, 0.5f, 0.0f);
			glVertex3f((x + SNAKE_WIDTH_HALF) * CHUNK_SIZE, y, z);
				
			y += TRIANGLES_DISTANCE;
			curphase += PHASE_PER_TRIANGLE;
		}	
		glEnd();
	}
	return ;
}

void                        Window::_put_block(std::pair<int, int> const &topLeft,
											   std::tuple<float, float, float> c) const
{
	glLoadIdentity();
	glTranslatef(topLeft.first * CHUNK_SIZEF + 10
				 , topLeft.second * CHUNK_SIZEF + 10
				 , -0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(std::get<0>(c) * 1.f, std::get<1>(c) * 1.f, std::get<2>(c) * 1.f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 0.8f, std::get<1>(c) * 0.8f, std::get<2>(c) * 0.8f);
	glVertex3f(0.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 0.6f, std::get<1>(c) * 0.6f, std::get<2>(c) * 0.6f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.5f * CHUNK_SIZEF, CHUNK_SIZEF);
	glColor3f(std::get<0>(c) * 0.4f, std::get<1>(c) * 0.4f, std::get<2>(c) * 0.4f);
	glVertex3f(1.f * CHUNK_SIZEF, 1.f * CHUNK_SIZEF, 0.f);
	glColor3f(std::get<0>(c) * 1.f, std::get<1>(c) * 1.f, std::get<2>(c) * 1.f);
	glVertex3f(0.5f * CHUNK_SIZEF, 0.f * CHUNK_SIZEF, 0.f);
	glEnd();
	return ;
}
