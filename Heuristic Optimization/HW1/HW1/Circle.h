#pragma once
class Circle {
	public:
	Circle() {
		radius = 1.f;
	}
	Circle(float r) {
		radius = r;
	}

	float radius{ 1.f };
	int	  roomNo{ 0 };

	bool operator==(const Circle rhs) const {
		return radius == rhs.radius;
	}

};

