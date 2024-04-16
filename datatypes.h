#pragma once

#include <cmath>
#include <vector>
#include <iostream>

struct Point2D { float x, y; };
struct Point3D { float x, y, z; };
struct Vertex { unsigned short start, end; };

typedef std::vector<std::vector<float>> matrix;