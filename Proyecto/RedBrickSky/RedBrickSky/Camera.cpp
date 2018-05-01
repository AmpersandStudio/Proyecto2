#include "Game.h"
#include "Camera.h"

Camera Camera::s_pCamera;

Camera::Camera() : m_pTarget(0), m_position(0, 0)
{
}

Camera::~Camera()
{
	//if (m_pTarget != nullptr)
	//	delete m_pTarget;
}

const Vector2D Camera::getPosition() const
{
	if (m_pTarget != 0)
	{
		Vector2D pos(m_pTarget->getX() - (TheGame::Instance()->getWinWidth() / 2), 
			         m_pTarget->getY() - (TheGame::Instance()->getWinHeight() / 2));

		if (pos.getX() < 0)
		{
			pos.setX(0);
		}
		if (pos.getX() > mapWidth - TheGame::Instance()->getWinWidth())
		{
			pos.setX(mapWidth - TheGame::Instance()->getWinWidth());
		}

		if (pos.getY() < 0)
		{
			pos.setY(0);
		}
		if (pos.getY() > mapHeight - TheGame::Instance()->getWinHeight())
		{
			pos.setY(mapHeight - TheGame::Instance()->getWinHeight());
		}

		return pos;
	}

	return m_position;
}

void Camera::update(Vector2D velocity)
{
/*	m_position = m_position + velocity;

	if (m_position.getX() < 0)
	{
		m_position.setX(0);
	}*/	
}
