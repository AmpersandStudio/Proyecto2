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
		Vector2D pos(m_pTarget->getX() - (TheGame::Instance()->getWinWidth() / (2 * Game::Instance()->getScaleFact())),
			         m_pTarget->getY() - (TheGame::Instance()->getWinHeight() / (2 * Game::Instance()->getScaleFact())));

		if (pos.getX() < 0)
		{
			pos.setX(0);
		}
		if (pos.getX() > mapWidth - TheGame::Instance()->getWinWidth() / Game::Instance()->getScaleFact())
		{
			pos.setX(mapWidth - TheGame::Instance()->getWinWidth() / Game::Instance()->getScaleFact());
		}

		if (pos.getY() < 0)
		{
			pos.setY(0);
		}
		if (pos.getY() > mapHeight - TheGame::Instance()->getWinHeight() / Game::Instance()->getScaleFact())
		{
			pos.setY(mapHeight - TheGame::Instance()->getWinHeight() / Game::Instance()->getScaleFact());
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
