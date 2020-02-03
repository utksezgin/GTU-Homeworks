// HW1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include "CirclePacker.h"
#include "Circle.h"
#include <time.h>
#include <chrono>



int main()
{
	int ITERATION_COUNT = 5;

																					//---CIRCLE INSTANCES---//
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	//5
	std::vector<Circle> instance1 { 36, 18, 3, 22, 47 };
	//10
	std::vector<Circle> instance2 { 36, 74, 38, 29, 44, 75, 37, 87, 83, 76 };
	//50
	std::vector<Circle> instance3 { 35, 11, 65, 90, 41, 56, 38, 53, 24, 27, 23, 60, 92, 91, 86, 51, 82, 23, 80, 22, 99, 48, 15, 61, 34, 58, 57, 20, 52, 83, 58, 54,
									99, 87, 77, 38, 54, 12, 92, 47, 51, 53, 29, 42, 18, 80, 55, 12, 7, 59 };
	//100
	std::vector<Circle> instance4 { 93, 81, 63, 44, 51, 69, 51, 98, 87, 90, 95, 40, 23, 77, 51, 16, 56, 75, 68, 24, 84, 11, 9, 72, 51, 93, 95, 10, 44, 31, 62, 86, 68,
									79, 42, 96, 80, 19, 84, 43, 9, 53, 18, 66, 17, 83, 22, 72, 56, 20, 37, 9, 56, 48, 50, 35, 62, 72, 22, 70, 84, 70, 71, 68, 43, 18,
									78, 63, 24, 78, 67, 54,10, 19, 68, 84, 34, 30, 93, 15, 64, 22, 72, 66, 97, 21, 45, 69, 73, 64, 87, 98, 11, 97, 8, 19, 96, 94, 18, 40 };
	//200
	std::vector<Circle> instance5 { 30, 46, 62, 6, 18, 85, 81, 87, 59, 71, 64, 34, 29, 18, 51, 64, 52, 39, 32, 75, 16, 82, 19, 6, 50, 8, 97, 15, 29, 23, 92, 52, 15, 47, 63,
									66, 59, 91, 44, 89, 65, 45, 85, 11, 76, 37, 98, 54, 67, 86, 66, 92, 60, 59, 8, 6, 98, 69, 33, 30, 74, 22, 59, 84, 99, 37, 54, 51, 46, 48,
									97, 25, 11, 77, 88, 69, 30, 33,	46, 9, 66, 41, 38, 84, 38, 59, 48, 85, 26, 15, 9, 5, 20, 80, 95, 28, 63, 52, 44, 27, 17, 33, 46, 88, 97,
									38, 18, 74, 55, 96, 40, 28, 72, 94, 10, 5, 71, 39, 39, 89, 49, 84, 81, 50, 59, 17, 89, 57, 52, 36, 38, 56, 70, 41, 75, 49, 63, 55, 62,
									82, 96, 78, 94, 77, 85, 34, 51, 40, 40, 67, 65, 16, 14, 32, 69, 84, 59, 77, 98, 38, 47, 14, 77,	37, 81, 48, 50, 45, 34, 82, 49, 77, 35,
									44, 17, 10, 39, 23, 86, 81, 78, 79, 72, 23, 29, 79, 8, 57, 29, 66, 65, 82, 97, 99, 48, 65, 41, 28, 18, 63 };
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	float tempLength;
	float minimumLength = std::numeric_limits<float>::max();
	float maximumLength = std::numeric_limits<float>::min();
	float sum = 0;
	float timeSum = 0.f;
	std::vector<Circle> testCircles;
	CirclePacker cp = CirclePacker();

	// Initialize random circles.
	/*srand(time(NULL));	
	int circleCount = 200;
	std::cout << "Number of Circles: " << circleCount << std::endl;
	testCircles.reserve(circleCount);
	for (int i = 0; i < circleCount; ++i) {
		testCircles.push_back(Circle(rand() % 95 + 5));
	}
	std::cout << "Circle Pool: \n{";
	
	for (int i = 0; i < testCircles.size()-1; ++i) {
		std::cout << testCircles[i].radius << ", ";
	}
	std::cout << testCircles.back().radius <<"}";*/

	//-------------------------------------------//

	tempLength;
	minimumLength = std::numeric_limits<float>::max();
	maximumLength = std::numeric_limits<float>::min();
	sum = 0;
	timeSum = 0.f;
	testCircles = instance5; //Change Instance here.
	for (int i = 0; i < ITERATION_COUNT; ++i) {
		begin = std::chrono::steady_clock::now();
		std::vector<Circle> minLengthLine = cp.geneticAlgorithm(testCircles); //Change function here for other methods!
		end = std::chrono::steady_clock::now();
		tempLength = cp.calculateLineLenght(minLengthLine);
		sum+= tempLength;
		if(tempLength < minimumLength)
			minimumLength = tempLength;
		if(tempLength > maximumLength)
			maximumLength = tempLength;
		timeSum += (double)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	}
	std::cout << "Best: " << minimumLength << std::endl;
	std::cout << "Avg: " << sum/(double)ITERATION_COUNT << std::endl;
	std::cout << "Worst: " << maximumLength << std::endl;
	std::cout << "Avg Time Elapsed: " << timeSum/(double)ITERATION_COUNT << "ms";

	//-------------------------------------------//
}