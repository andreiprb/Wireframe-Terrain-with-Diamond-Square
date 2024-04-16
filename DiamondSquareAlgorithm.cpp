 #include "DiamondSquareAlgorithm.h"

void Terrain::diamondStep(const int& chunkSize, const int& height)
{
    int heightMapSize = this->m_heightMap.size();

    for (int i = 0; i < heightMapSize; i += chunkSize / 2)
        for (int j = (i + chunkSize / 2) % chunkSize; j < heightMapSize; j += chunkSize)
        {
            int count = 0;

            this->m_heightMap[i][j] = 0;

            if (i - chunkSize / 2 >= 0)
            {
                this->m_heightMap[i][j] += this->m_heightMap[i - chunkSize / 2][j];
                ++count;
            }

            if (i + chunkSize / 2 <= heightMapSize - 1)
            {
                this->m_heightMap[i][j] += this->m_heightMap[i + chunkSize / 2][j];
                ++count;
            }

            if (j - chunkSize / 2 >= 0)
            {
                this->m_heightMap[i][j] += this->m_heightMap[i][j - chunkSize / 2];
                ++count;
            }

            if (j + chunkSize / 2 <= heightMapSize - 1)
            {
                this->m_heightMap[i][j] += this->m_heightMap[i][j + chunkSize / 2];
                ++count;
            }

            this->m_heightMap[i][j] /= count;
            this->m_heightMap[i][j] += getRandomHeight(height);

            if (this->m_min > this->m_heightMap[i][j])
                this->m_min = this->m_heightMap[i][j];

            if (this->m_max < this->m_heightMap[i][j])
                this->m_max = this->m_heightMap[i][j];
        }
}

void Terrain::squareStep(const int& chunkSize, const int& height)
{
    int heightMapSize = this->m_heightMap.size();

    for (int i = 0; i < heightMapSize - 1; i += chunkSize)
        for (int j = 0; j < heightMapSize - 1; j += chunkSize)
        {
            this->m_heightMap[i + chunkSize / 2][j + chunkSize / 2] = (this->m_heightMap[i][j] + 
                this->m_heightMap[i][j + chunkSize] +
                this->m_heightMap[i + chunkSize][j] +
                this->m_heightMap[i + chunkSize][j + chunkSize]) * 0.25f +
                getRandomHeight(height);

            if (this->m_min > this->m_heightMap[i + chunkSize / 2][j + chunkSize / 2])
                this->m_min = this->m_heightMap[i + chunkSize / 2][j + chunkSize / 2];

            if (this->m_max < this->m_heightMap[i + chunkSize / 2][j + chunkSize / 2])
                this->m_max = this->m_heightMap[i + chunkSize / 2][j + chunkSize / 2];
        }
}

Terrain::Terrain(int& size, int& height, float& roughnessIndex)
{
    int heightMapSize = pow(2, size) + 1;

    this->m_heightMap.resize(heightMapSize);
    for (int i = 0; i < heightMapSize; ++i)
        this->m_heightMap[i].resize(heightMapSize);

    int chunkSize = heightMapSize - 1;

    this->m_heightMap[0][0] = getRandomHeight(height);
    this->m_heightMap[0][chunkSize] = getRandomHeight(height);
    this->m_heightMap[chunkSize][0] = getRandomHeight(height);
    this->m_heightMap[chunkSize][chunkSize] = getRandomHeight(height);

    while (chunkSize > 1)
    {
        this->squareStep(chunkSize, height);
        this->diamondStep(chunkSize, height);

        chunkSize /= 2;
        height *= roughnessIndex;
    }
}

std::vector<Point3D>& Terrain::getPoints()
{
    if (this->m_points.size())
        return this->m_points;

    int heightMapSize = this->m_heightMap.size();
    int avgHeight = (this->m_min + this->m_max) / 2, difference = abs(this->m_min) + abs(this->m_max);

    for (int i = 0; i < heightMapSize; ++i)
        for (int j = 0; j < heightMapSize; ++j)
        {
            Point3D point;

            point.x = j - heightMapSize / 2;
            point.y = (this->m_heightMap[i][j] - avgHeight) * (((float)difference - avgHeight) / difference);
            point.z = i - heightMapSize / 2;

            this->m_points.push_back(point);
        }

    return this->m_points;
}

std::vector<Vertex>& Terrain::getVertices()
{
    if (this->m_vertices.size())
        return this->m_vertices;

    int heightMapSize = this->m_heightMap.size();

    for (int i = 0; i < heightMapSize; ++i)
        for (int j = 0; j < heightMapSize; ++j)
        {
            Vertex vertex;

            if (j > 0)
            {
                vertex.start = i * heightMapSize + j;
                vertex.end = i * heightMapSize + (j - 1);

                this->m_vertices.push_back(vertex);
            }

            if (j > 0 && i < heightMapSize - 1)
            {
                vertex.start = i * heightMapSize + j;
                vertex.end = (i + 1) * heightMapSize + (j - 1);

                this->m_vertices.push_back(vertex);
            }

            if (i < heightMapSize - 1)
            {
                vertex.start = i * heightMapSize + j;
                vertex.end = (i + 1) * heightMapSize + j;

                this->m_vertices.push_back(vertex);
            }
        }

    return this->m_vertices;
}

void getInput(int& size, int& height, float& roughnessIndex)
{
    std::cout << "Introduceti indexul de dimensiune al hartii: ";
    std::cin >> size;
    while (size <= 0 || size >= 8)
    {
        std::cout << "\nIndexul de dimensiune al hartii trebuie sa fie un numar pozitiv mai mic decat 8.\n\n";
        std::cout << "Introduceti indexul de dimensiune al hartii: ";
        std::cin >> size;
    }

    std::cout << "\nIntroduceti inaltimea maxima de inceput: ";
    std::cin >> height;
    while (height <= 0)
    {
        std::cout << "\nInaltimea maxima de inceput trenuie sa fie un numar pozitiv.\n\n";
        std::cout << "Introduceti inaltimea maxima de inceput: ";
        std::cin >> height;
    }

    std::cout << "\nIntroduceti indexul de rugozitate pentru generare: ";
    std::cin >> roughnessIndex;
    while (roughnessIndex <= 0 || roughnessIndex >= 1)
    {
        std::cout << "\nIndexul de rugozitate pentru generare trebuie sa fie un numar pozitiv subunitar.\n\n";
        std::cout << "Introduceti indexul de rugozitate pentru generare: ";
        std::cin >> roughnessIndex;
    }
}

int getRandomHeight(const int& max)
{
    return max ? rand() % (2 * max + 1) - max : 0;
}