#include "DiamondSquareAlgorithm.h"
#include "Renderer3D.h"

int main(int argc, char** argv)
{
	srand(time(NULL));

	int size, height;
	float roughnessIndex;

	getInput(size, height, roughnessIndex);
	Terrain t(size, height, roughnessIndex);
	
	std::vector<Point3D> points = t.getPoints();
	std::vector<Vertex> vertices = t.getVertices();

	startRender(points, vertices);

	return 0;
}