#include <iostream>
#include <cstdlib>

using namespace std;

double runif(double a, double b)
{
    return (rand() / (double)RAND_MAX) * (b - a) + a;
}

int main(int argc, char **argv)
{
    double a = runif(3, 5);
    double c = runif(3, 5);
    double b = runif(3, 5);
    cout << a << ", " << b << ", " << c << endl;

    return 0;
}
