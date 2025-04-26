#include <stdlib.h>
#include <iostream>
#include <Eigen/Dense>

#include <matplotlibcpp.h>
#include <cmath>
#include <vector>

namespace plt = matplotlibcpp;

int main() {
    std::cout <<  "Hello World" << std::endl;

    Eigen::Matrix2d mat;
    mat << 1, 2,
           3, 4;

    std::cout << "Matrix:\n" << mat << std::endl;

    std::vector<double> x, y;

    // Generate x and y data
    for (double i = 0; i < 2 * M_PI; i += 0.1) {
        x.push_back(i);
        y.push_back(sin(i));
    }

    // Plot
    plt::plot(x, y);
    plt::title("Sine Wave");
    plt::xlabel("x");
    plt::ylabel("sin(x)");
    plt::grid(true);
    plt::show();


}   



