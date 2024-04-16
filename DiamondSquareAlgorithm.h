#pragma once

#include "datatypes.h"

class Terrain
{
	matrix m_heightMap;
	int m_min, m_max;
	std::vector<Point3D> m_points;
	std::vector<Vertex> m_vertices;

	void diamondStep(const int& chunkSize, const int& roughness);
	void squareStep(const int& chunkSize, const int& roughness);
public:
	Terrain(int& size, int& height, float& roughnessIndex);
	// generates Terrain using Diamond-Square algorithm

	std::vector<Point3D>& getPoints();
	std::vector<Vertex>& getVertices();
};

void getInput(int& size, int& height, float& roughnessIndex);
int getRandomHeight(const int& max);