#pragma once

#include "Vector2D.h"
#include "checkML.h"
class Camera
{
public:
	~Camera();
	static Camera* Instance()
	{
		return &s_pCamera;
	}

	void update(Vector2D velocity);

	void setTarget(Vector2D* target) { m_pTarget = target; }
	void setPosition(const Vector2D& position) { m_position = position; }

	const Vector2D getPosition() const;

	void setMapDims(int w, int h) { mapWidth = w; mapHeight = h ; }

private:
	Camera();

	// the camera's target
	Vector2D* m_pTarget;

	// the camera's position
	Vector2D m_position;

	int mapWidth;
	int mapHeight;

	int cameraWidth_;
	int cameraHeight_;
	int scaleDownFactor_;

	static Camera s_pCamera;

};

typedef Camera TheCamera;

