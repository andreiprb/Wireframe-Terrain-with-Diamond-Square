#include "Renderer3D.h"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3D>& _points, std::vector<Vertex>& _vertices)
{
	SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
	renderer = _renderer;
	points = _points;
	vertices = _vertices;
}

void Renderer3D::render(const float& count)
{
	auto time1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration(0);

	Yrotation += 0.5 * DeltaTime;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for (auto& vertex : vertices)
	{
		Point3D rotatedStartPoint = rotateX(rotateY(points[vertex.start]));
		Point3D rotatedEndPoint = rotateX(rotateY(points[vertex.end]));

		Point2D start = projection(rotatedStartPoint, count);
		Point2D end = projection(rotatedEndPoint, count);

		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}

	SDL_RenderPresent(renderer);

	auto time2 = std::chrono::high_resolution_clock::now();
	duration = time2 - time1;
	DeltaTime = duration.count();
	time1 = time2;
}

Point3D Renderer3D::rotateX(Point3D point)
{
	Point3D returnPoint{};

	returnPoint.x = point.x;
	returnPoint.y = cos(Xrotation) * point.y - sin(Xrotation) * point.z;
	returnPoint.z = sin(Xrotation) * point.y + cos(Xrotation) * point.z;

	return returnPoint;
}

Point3D Renderer3D::rotateY(Point3D point)
{
	Point3D returnPoint{};

	returnPoint.x = cos(Yrotation) * point.x - sin(Yrotation) * point.z;
	returnPoint.y = point.y;
	returnPoint.z = sin(Yrotation) * point.x + cos(Yrotation) * point.z;

	return returnPoint;
}

Point2D Renderer3D::projection(Point3D point, const float& count)
{
	return Point2D{ WindowSizeX / 2 + (FOV * point.x) / (FOV + point.z) * (float)WindowSizeY / count, WindowSizeY / 2 + (FOV * point.y) / (FOV + point.z) * (float)WindowSizeY / count };
}

void startRender(std::vector<Point3D>& points, std::vector<Vertex>& vertices)
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Diamond Square Terrain Generation Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;

	float count = sqrt(points.size());

	Renderer3D DSqTerrainRender(window, renderer, points, vertices);

	while (running)
	{
		if (SDL_QuitRequested())
		{
			running = false;
			break;
		}

		DSqTerrainRender.render(count);
	}

	return;
}
