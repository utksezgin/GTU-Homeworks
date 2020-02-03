#include "CirclePacker.h"
#include <iostream>
#include <time.h>
#include <queue>
#include <random>
#include <set>

//FIX ME.
//Problem: This calculation is wrong for cases where the first circle's radius is much smaller than the following ones.
float CirclePacker::calculateLineLenght(const std::vector<Circle>& circleLine) const {
	float length{ 0.f };
	if (circleLine.size() == 0)
		return 0;
	else if (circleLine.size() == 1)
		return circleLine[0].radius;

	length += circleLine[0].radius;
	unsigned int i = 0;
	for (; i < circleLine.size() - 1; ++i) {
		length += getLength(circleLine[i], circleLine[i + 1]);
	}
	length += circleLine[circleLine.size() - 1].radius;
	return length;
}

//Brute-force
std::vector<Circle> CirclePacker::bruteForce(std::vector<Circle> circles) const {

	std::vector<Circle> currMinLine = std::vector<Circle>();
	currMinLine.reserve(circles.size());
	std::vector<Circle> tempLine;
	tempLine.reserve(circles.size());

	constexpr float currMinLineLength = std::numeric_limits<float>::max();
	float tempLength{ 0.f };
	int tries{ 0 };
	return bruteHelper(circles, circles.size(), tempLine);

}

//Brute-force Helper
std::vector<Circle> CirclePacker::bruteHelper(std::vector<Circle> circles, size_t circleCount, std::vector<Circle> currentLine) const {
	std::vector<Circle> currMinLine;
	currMinLine.reserve(circleCount);
	std::vector<Circle> tempLine;
	tempLine.reserve(circleCount);
	float tempLength;
	float currMinLength = std::numeric_limits<float>::max();

	if (currentLine.size() == circleCount)
		return currentLine;
	else {
		for (unsigned int i = 0; i < circles.size(); ++i) {
			currentLine.push_back(circles[i]);
			std::vector<Circle> temp = std::vector<Circle>(circles);
			temp.erase(temp.begin() + i);
			tempLine = bruteHelper(temp, circleCount, currentLine);
			tempLength = calculateLineLenght(tempLine);
			if (tempLength < currMinLength) {
				currMinLine = tempLine;
				currMinLength = tempLength;
			}
			currentLine.pop_back();
			tempLine.clear();

		}
	}
	return currMinLine;
}


//Greedy Method
std::vector<Circle> CirclePacker::greedy(const std::vector<Circle> circles) const {
	std::vector<Circle> circlePool(circles);
	std::vector<Circle> currMinLine;
	unsigned int currMinIndex = 0;
	currMinLine.reserve(circles.size());

	float tempLength;
	float currMinLength = std::numeric_limits<float>::max();

	for (int i = 0; i < circles.size(); ++i) {
		for (unsigned int j = 0; j < circlePool.size(); ++j) {
			currMinLine.push_back(circlePool[j]);
			tempLength = calculateLineLenght(currMinLine);
			if (tempLength < currMinLength) {
				currMinLength = tempLength;
				currMinIndex = j;
			}
			currMinLine.pop_back();
		}
		currMinLine.push_back(circlePool[currMinIndex]);
		circlePool.erase(circlePool.begin() + currMinIndex);
		currMinLength = std::numeric_limits<float>::max();
	}

	return currMinLine;

}

//Iterative local search
std::vector<Circle> CirclePacker::iterativeLocalSearch(const std::vector<Circle> circles) const {
	int MAX_ITERATION_COUNT = 25;

	std::vector<Circle> currentBestSolution;
	std::vector<Circle> tempLine;

	currentBestSolution.reserve(circles.size());
	tempLine.reserve(circles.size());

	currentBestSolution = greedy(circles);

	float tempLength;
	float currentMinLength = calculateLineLenght(currentBestSolution);

	int iterationCount = 0;
	int noChange = 0;

	while (true) {
		std::vector<std::vector<Circle>> neighborhood = generateNeighborhood(currentBestSolution);
		tempLine = localSearch(currentBestSolution, neighborhood);
		tempLength = calculateLineLenght(tempLine);

		if (tempLength < currentMinLength) {
			currentMinLength = tempLength;
			currentBestSolution = tempLine;
			noChange = 0;
		}
		if (noChange == MAX_ITERATION_COUNT)
			break;
		else
			++noChange;
	}
	return currentBestSolution;
}

//Local Search
std::vector<Circle> CirclePacker::localSearch(std::vector<Circle> initialSolution, std::vector<std::vector<Circle>> neighborhood) const {
	unsigned int currMinIndex = 0;
	float currMinLength = calculateLineLenght(initialSolution);
	float tempLength;

	for (unsigned int i = 0; i < neighborhood.size(); ++i) {
		tempLength = calculateLineLenght(neighborhood[i]);
		if (tempLength < currMinLength) {
			currMinIndex = i;
			currMinLength = tempLength;
		}
	}
	return neighborhood[currMinIndex];

}

//VNDS Variable Neighborhood Decomposition Search
std::vector<Circle> CirclePacker::variableNeighborhoodSearch(const std::vector<Circle> circles) const {
	srand(time(nullptr));
	int MAX_NEIGHBORHOOD = 5;
	int MIN_NEIGHBORHOOD = 1;
	int DELTA_NEIGHBORHOOD = 1;
	std::vector<Circle> currentBestSolution;
	std::vector<Circle> tempLine;

	currentBestSolution.reserve(circles.size());
	tempLine.reserve(circles.size());

	float tempLength;
	float currentMinLength = calculateLineLenght(currentBestSolution);

	currentBestSolution = greedy(circles);
	currentMinLength = calculateLineLenght(currentBestSolution);

	int currentNeighborhood = 0;
	std::vector<std::vector<std::vector<Circle>>> neighborhoods(MAX_NEIGHBORHOOD);
	for (int i = MIN_NEIGHBORHOOD; i < MAX_NEIGHBORHOOD; i += DELTA_NEIGHBORHOOD) {
		neighborhoods[i] = generateNeighborhoodKRandoms(currentBestSolution, i);
	}

	int k = MIN_NEIGHBORHOOD;
	while (k != MAX_NEIGHBORHOOD) {
		tempLine = neighborhoods[k][rand() % neighborhoods[k].size()];
		tempLine = iterativeLocalSearch(tempLine);
		tempLength = calculateLineLenght(tempLine);
		if (tempLength < currentMinLength) {
			k = MIN_NEIGHBORHOOD;
			currentMinLength = tempLength;
			currentBestSolution = tempLine;
			//Generate new neighborhood structure for the new solution.
			for (int i = MIN_NEIGHBORHOOD; i < MAX_NEIGHBORHOOD; i += DELTA_NEIGHBORHOOD) {
				neighborhoods[i] = generateNeighborhoodKRandoms(currentBestSolution, i);
			}
		}
		else {
			k += DELTA_NEIGHBORHOOD;
		}
	}
	return currentBestSolution;
}

//Neighborhood generator
std::vector<std::vector<Circle>> CirclePacker::generateNeighborhood(std::vector<Circle> line) const {
	std::vector<std::vector<Circle>> neighborhood;
	neighborhood.reserve(line.size());
	srand(time(nullptr));
	for (int i = line.size() - 1; i >= 0; --i) {
		neighborhood.push_back(line);
		int r = rand() % (i + 1);
		neighborhood[line.size() - i - 1][i] = line[r];
		neighborhood[line.size() - i - 1][r] = line[i];
	}
	return neighborhood;
}

//Generates Neighborhood with k swaps.
std::vector<std::vector<Circle>> CirclePacker::generateNeighborhoodKRandoms(std::vector<Circle> line, int k) const {
	Circle temp;
	std::vector<std::vector<Circle>> neighborhood;
	neighborhood.reserve(line.size());
	srand(time(nullptr));
	for (int i = line.size() - 1; i >= 0; --i) {
		//REFACTOR HERE
		neighborhood.push_back(line);
		for (int j = 0; j < k; ++j) {
			int r1 = rand() % (i + 1);
			int r2 = rand() % (i + 1);
			temp = neighborhood[line.size() - i - 1][i];
			neighborhood[line.size() - i - 1][i] = neighborhood[line.size() - i - 1][r1];
			neighborhood[line.size() - i - 1][r1] = temp;
		}
	}
	return neighborhood;
}


std::vector<Circle> CirclePacker::simulatedAnnealing(const std::vector<Circle> circles) const {
	float TEMP_MIN{ 0.000001f };
	float TEMP_DEC{ 0.9f }; //Temperature decrease -> T *= TEMP_DEC
	int NEIGHBORHOOD_SWAP_COUNT{ 2 };	

	std::vector<Circle> currentBestSolution;
	std::vector<Circle> tempLine;
	int tries{ 0 };
	float temp{ 1.f };

	currentBestSolution.reserve(circles.size());
	tempLine.reserve(circles.size());
	currentBestSolution = greedy(circles);

	float tempLength;
	float currentMinLength = calculateLineLenght(currentBestSolution);
	std::vector<std::vector<Circle>> neighborhood = generateNeighborhoodKRandoms(currentBestSolution, NEIGHBORHOOD_SWAP_COUNT);

	while (temp > TEMP_MIN) {
		for (int i = 0; i < neighborhood.size(); ++i) {
			tempLength = calculateLineLenght(neighborhood[i]);
			if (tempLength < currentMinLength) {
				currentBestSolution = neighborhood[i];
				currentMinLength = tempLength;
				//New neighborhood for the new candidate.
				neighborhood = generateNeighborhoodKRandoms(currentBestSolution, NEIGHBORHOOD_SWAP_COUNT);
				break;
			}
			else if ((double)rand() / ((double)RAND_MAX + 1) < temp) {
				currentBestSolution = neighborhood[i];
				currentMinLength = tempLength;
				//New neighborhood for the new candidate.
				neighborhood = generateNeighborhoodKRandoms(currentBestSolution, NEIGHBORHOOD_SWAP_COUNT);
				break;
			}

		}
		temp *= powf(TEMP_DEC, (double)tries);
		++tries;
	}

	return currentBestSolution;
}


//Branch and Bound
std::vector<Circle> CirclePacker::branchAndBound(std::vector<Circle> circles) const {
	std::vector<Circle> currMinLine = std::vector<Circle>();
	currMinLine.reserve(circles.size());
	std::vector<Circle> tempLine;
	tempLine.reserve(circles.size());

	constexpr float currMinLineLength = std::numeric_limits<float>::max();
	float tempLength{ 0.f };
	int tries{ 0 };
	return branchAndBoundHelper(circles, circles.size(), tempLine, calculateLineLenght(greedy(circles)));

}

//Branch and Bound Helper
std::vector<Circle> CirclePacker::branchAndBoundHelper(std::vector<Circle> circles, size_t circleCount, std::vector<Circle> currentLine, int greedy) const {
	std::vector<Circle> currMinLine;
	currMinLine.reserve(circleCount);
	std::vector<Circle> tempLine;
	tempLine.reserve(circleCount);
	float tempLength;
	float currMinLength = (float)greedy * 99.0f;

	//If the current line is already longer than greedy one, no need to look further.
	if (currentLine.size() == circleCount) {
		return currentLine;
	}
	if (calculateLineLenght(currentLine) > greedy) {
		return currentLine;
	}
	for (unsigned int i = 0; i < circles.size(); ++i) {
		currentLine.push_back(circles[i]);
		std::vector<Circle> temp = std::vector<Circle>(circles);
		temp.erase(temp.begin() + i);
		tempLine = branchAndBoundHelper(temp, circleCount, currentLine, greedy);
		tempLength = calculateLineLenght(tempLine);
		if (tempLength < currMinLength) {
			currMinLine = tempLine;
			currMinLength = tempLength;
		}
		currentLine.pop_back();
		tempLine.clear();

	}
	return currMinLine;
}


//********************************* PART 2 *********************************

std::vector<Circle> CirclePacker::geneticAlgorithm(std::vector<Circle> circles) const {
	int POPULATION_SIZE{ 12 };
	int MAX_ITERATION{ 10 };
	int PARENT_COUNT{ 8 };
	float currMinLength = std::numeric_limits<float>::max();
	float tempLength{ 0.f };

	std::vector<Circle> currMinLine;
	std::vector<Circle> tempLine;
	std::vector<std::vector<int>> population;

	srand(time(nullptr));

	for (int i = 0; i < circles.size(); ++i) {
		circles[i].roomNo = i;
		currMinLine.push_back(circles[i]);
	}

	//Generate random lines as initial population
	auto temp = currMinLine;
	auto rng = std::default_random_engine{};
	for (int i = 0; i < POPULATION_SIZE; ++i) {
		std::shuffle(temp.begin(), temp.end(), rng);
		population.push_back(realToChromosome(circles, temp));
	}

	std::vector<std::vector<int>> parents;
	std::vector<std::vector<int>> offsprings;

	int iterationWithNoChanges = 0;
	while (iterationWithNoChanges != MAX_ITERATION) {
		std::sort(population.begin(), population.end(), [&](const std::vector<int>& lhs, const std::vector<int>& rhs)
		{
			std::vector<Circle> temp1(lhs.size());
			std::vector<Circle> temp2(rhs.size());
			for (int i = 0; i < lhs.size(); ++i) {
				temp1[i] = circles[lhs[i]];
				temp2[i] = circles[rhs[i]];
			}

			return calculateLineLenght((temp1)) > calculateLineLenght(temp2);
		});

		parents = std::vector<std::vector<int>>(population.begin(), population.begin() + PARENT_COUNT);
		offsprings = createOffsprings(parents);
		std::copy_n(offsprings.begin(), offsprings.size(), parents.begin()); //Replace offsprings with worst ones.


		tempLine = getMinOfPopulation(circles, population);
		tempLength = calculateLineLenght(tempLine);
		if (tempLength < currMinLength) {
			currMinLine = tempLine;
			currMinLength = tempLength;
			iterationWithNoChanges = 0;
		}
		else
			++iterationWithNoChanges;
	}

	return currMinLine;
}


std::vector<std::vector<int>> CirclePacker::createOffsprings(std::vector<std::vector<int>> parents) const {
	std::vector<std::vector<int>> offsprings;
	float chanceToMutate{ 0.6f };

	for (int i = 0; i < parents.size(); i += 2) {
		offsprings.push_back(crossover(parents[i], parents[i + 1]));
	}
	for (auto offspring : offsprings) {
		if (((double)rand() / (RAND_MAX)) < chanceToMutate) {
			offspring = swapMutation(offspring);
		}
	}

	return offsprings;
}


std::vector<int> CirclePacker::swapMutation(std::vector<int>& line) const {
	srand(time(nullptr));
	int index1 = rand() % line.size();
	int index2 = rand() % line.size();
	int temp = line[index1];
	line[index1] = line[index2];
	line[index2] = temp;

	return line;
}


std::vector<int> CirclePacker::crossover(std::vector<int> parent1, std::vector<int> parent2) const {
	std::vector<int> offspring(parent1.size());
	int index1 = rand() % parent1.size();
	int index2 = rand() % parent1.size();
	while (index1 == index2)
		index2 = rand() % parent1.size();
	if (index1 > index2) {
		int temp = index1;
		index1 = index2;
		index2 = temp;
	}

	for (int i = index1; i <= index2; ++i) {
		offspring[i] = parent1[i];
	}
	int j = index2 + 1;
	j %= parent2.size();
	for (int i = index2 + 1; i != index2; ++i) {
		if (i == parent2.size())
			i = 0;

		if (!(std::find(offspring.begin(), offspring.end(), parent2[i]) != offspring.end())) {
			offspring[j] = parent2[i];
			++j;
			j %= parent2.size();
		}
	}

	return offspring;
}

std::vector<Circle> CirclePacker::getMinOfPopulation(const std::vector<Circle>& circles, std::vector<std::vector<int>> population) const {
	std::vector<int> currMinLine;
	float currMinLenght = std::numeric_limits<float>::max();
	float tempLength;
	for (int i = 0; i < population.size(); ++i) {
		tempLength = calculateLineLenght(chromosomeToReal(circles, population[i]));
		if (tempLength < currMinLenght) {
			currMinLenght = tempLength;
			currMinLine = population[i];
		}
	}

	return chromosomeToReal(circles, currMinLine);
}

std::vector<Circle> CirclePacker::chromosomeToReal(const std::vector<Circle>& circles, const std::vector<int> chromosome) const {
	std::vector<Circle> temp(chromosome.size());
	for (int i = 0; i < chromosome.size(); ++i) {
		temp[i] = circles[chromosome[i]];
	}
	return temp;
}

std::vector<int> CirclePacker::realToChromosome(const std::vector<Circle>& circles, const std::vector<Circle> real) const {
	std::vector<int> temp(real.size());
	for (int i = 0; i < real.size(); ++i) {
		temp[i] = real[i].roomNo;
	}
	return temp;
}


std::vector<Circle> CirclePacker::tabuSearch(std::vector<Circle> circles) const {
	int MAX_TRIES				 { 15 };
	int NEIGHBORHOOD_SWAP_AMOUNT { 2 };
	int TABU_SIZE				 { 20 };
	int tries					 { 0 };

	std::vector<Circle> localBestSolution = greedy(circles);
	std::vector<Circle> globalBestSolution = localBestSolution;
	std::vector<std::vector<Circle>> solutionSpace;
	std::set<float> tabuList;
	
	float solutionLength;
	float currentMinLength = calculateLineLenght(localBestSolution);

	while(tries != MAX_TRIES) {
		solutionSpace = generateNeighborhoodKRandoms(localBestSolution, NEIGHBORHOOD_SWAP_AMOUNT);

		for (auto solution : solutionSpace) {
			solutionLength = calculateLineLenght(solution);
			if (tabuList.find(calculateLineLenght(solution)) == tabuList.end() && solutionLength < currentMinLength){
				localBestSolution = solution;
				tabuList.insert(calculateLineLenght(localBestSolution));
				currentMinLength = calculateLineLenght(localBestSolution);
			}
		}
		if (calculateLineLenght(localBestSolution) < calculateLineLenght(globalBestSolution)) {
			globalBestSolution = localBestSolution;
			tries = 0;
		}
		else
			++tries;

		tabuList.insert(calculateLineLenght(localBestSolution));
		

		if(tabuList.size() == TABU_SIZE )
			tabuList.erase(tabuList.begin());
		else if(tabuList.size() == TABU_SIZE/2)
			++NEIGHBORHOOD_SWAP_AMOUNT;
	}

	return globalBestSolution;
}