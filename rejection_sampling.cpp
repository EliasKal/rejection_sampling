#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

// Returns the minimum value of a vector.
template <typename T>
T min(const vector<T> &x)
{
    T m = x[0];
    for (int i = 1; i < x.size(); i++)
        m = x[i] < m ? x[i] : m;
    return m;
}

// Returns the maximum value of a vector.
template <typename T>
T max(const vector<T> &x)
{
    T m = x[0];
    for (int i = 1; i < x.size(); i++)
        m = x[i] > m ? x[i] : m;
    return m;
}

// Draws a histogram of the values in a vector x.
void printHist(const vector<double> &x, int nBins, int plotWidth)
{
    double minVal = min(x);
    double maxVal = max(x);
    double binSize = (maxVal - minVal) / nBins;
    // count bins
    vector<double> counts(nBins);
    for (int i = 0; i < x.size(); i++) {
        int binIdx = (int)((x[i] - minVal) / binSize);
        if (binIdx >= nBins)
            binIdx = nBins - 1;
        counts[binIdx]++;
    }
    // draw bins
    double maxCount = max(counts);
    for (int i = 0; i < nBins; i++) {
        printf("%5.2f ", minVal + i * binSize);
        for (int j = 0; j < (int)((counts[i] / maxCount) * plotWidth); j++)
            cout << "*";
        cout << endl;
    }
}

// Samples from a uniform distribution.
double runif(double a, double b)
{
    return (rand() / (double)RAND_MAX) * (b - a) + a;
}

int main(int argc, char **argv)
{
    int n = 100;
    vector<double> samples(n);
    for (int i = 0; i < n; i++) {
        samples[i] = runif(3, 5);
    }
    printHist(samples, 10, 16);

    return 0;
}
