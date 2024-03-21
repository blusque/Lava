#include "Random.h"

std::mt19937 Random::m_Random = std::mt19937(std::random_device{}());