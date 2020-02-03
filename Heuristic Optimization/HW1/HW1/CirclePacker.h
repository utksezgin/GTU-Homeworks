#pragma once
#include <vector>
#include "Circle.h"

class CirclePacker {

	public:
	//CirclePacking methods
	std::vector<Circle> bruteForce(std::vector<Circle> circles) const;
	std::vector<Circle> branchAndBound(std::vector<Circle> circles) const;
	std::vector<Circle> greedy(const std::vector<Circle> circles) const;
	std::vector<Circle> iterativeLocalSearch(const std::vector<Circle> circles) const;
	std::vector<Circle> variableNeighborhoodSearch(const std::vector<Circle> circles) const;
	std::vector<Circle> simulatedAnnealing(const std::vector<Circle> circles) const;
	std::vector<Circle> geneticAlgorithm(std::vector<Circle> circles) const;
	std::vector<Circle> tabuSearch(std::vector<Circle> circles) const;

	float calculateLineLenght(const std::vector<Circle>& circleLine) const;

	private:

	std::vector<Circle> localSearch(std::vector<Circle> initialSolution, std::vector<std::vector<Circle>> neighborhood) const;
	std::vector<std::vector<Circle>> generateNeighborhood(std::vector<Circle> line) const;
	std::vector<std::vector<Circle>> generateNeighborhoodKRandoms(std::vector<Circle> line, int k) const;

	std::vector<Circle> bruteHelper(std::vector<Circle> circles, size_t circleCount, std::vector<Circle> currentLine) const;
	std::vector<Circle> branchAndBoundHelper(std::vector<Circle> circles, size_t circleCount, std::vector<Circle> currentLine, int greedy) const;

	//Genetic Algorithm helpers
	std::vector<std::vector<int>> createOffsprings(std::vector<std::vector<int>> population) const;
	std::vector<int> swapMutation(std::vector<int>& line) const;
	std::vector<int> crossover(std::vector<int> parent1, std::vector<int> parent2) const;
	std::vector<Circle> getMinOfPopulation(const std::vector<Circle>& circles, std::vector<std::vector<int>> population) const;

	std::vector<Circle> chromosomeToReal(const std::vector<Circle>& circles, const std::vector<int> chromosome) const;
	std::vector<int> realToChromosome(const std::vector<Circle>& circles, const std::vector<Circle> real) const;

	inline float getLength(Circle c1, Circle c2) const {
		return sqrtf(powf(c1.radius + c2.radius, 2.0f) - powf(c1.radius - c2.radius, 2.0f));
	}
};

