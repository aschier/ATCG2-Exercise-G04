#include <Eigen/Eigen>
#include <iostream>

Eigen::Vector3d from_barycentric_coordinates(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3, Eigen::Vector3d bary) {
	assert(abs(1.0 - bary.sum()) < 1e-6);
	// TODO: implement
	// ////////////////////////////////////////////////Example solution
	return v1 * bary[0] + v2 * bary[1] + v3 * bary[2];
}

Eigen::Vector3d circumcenter(Eigen::Vector3d v1, Eigen::Vector3d v2, Eigen::Vector3d v3) {
	// TODO: implement
	Eigen::Vector3d bary;
	// ////////////////////////////////////////////////Example solution
	double a = (v2 - v3).norm();
	double b = (v3 - v1).norm();
	double c = (v1 - v2).norm();
	bary[0] = a*a * (b*b + c*c - a*a);
	bary[1] = b*b * (c*c + a*a - b*b);
	bary[2] = c*c * (a*a + b*b - c*c);
	bary /= bary.sum();
	// ////////////////////////////////////////////////
	return from_barycentric_coordinates(v1, v2, v3, bary);
}

int main(int argc, char **argv) {
	Eigen::Vector3d v1, v2, v3, bary;
	std::cout << "v1: ";
	std::cin >> v1[0] >> v1[1] >> v1[2];
	std::cout << "v2: ";
	std::cin >> v2[0] >> v2[1] >> v2[2];
	std::cout << "v3: ";
	std::cin >> v3[0] >> v3[1] >> v3[2];

	std::cout << "barycentric coordinates: ";
	std::cin >> bary[0] >> bary[1] >> bary[2];
	std::cout << "Coordinate: " << from_barycentric_coordinates(v1, v2, v3, bary).transpose() << std::endl;

	std::cout << "Circumcenter of the triangle: " << circumcenter(v1, v2, v3).transpose() << std::endl;
	return 0;
}
