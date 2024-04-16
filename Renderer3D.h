#pragma once

#include <SDL.h>
#include <chrono>
#include "datatypes.h"

class Renderer3D
{
public:
	Renderer3D(SDL_Window* window, SDL_Renderer* renderer, std::vector<Point3D>& points, std::vector<Vertex>& vertices);
	void render(const float& count);
private:
	Point3D rotateX(Point3D point);
	Point3D rotateY(Point3D point);
	Point2D projection(Point3D point, const float& count);

	float Xrotation = -75.0f;
	float Yrotation = 0.0f;

	float FOV = 90.0;
	float DeltaTime = 0.0f;

	int WindowSizeX;
	int WindowSizeY;
	SDL_Renderer* renderer;

	std::vector<Point3D> points;
	std::vector<Vertex> vertices;
};

void startRender(std::vector<Point3D>& points, std::vector<Vertex>& vertices);