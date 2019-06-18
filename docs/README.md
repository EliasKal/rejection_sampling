# Rejection sampling

Rejection sampling is a simple method from sampling from an arbitrary probability distribution, when we know the probability density function.

In these notes, we will create a small project for rejection sampling in C++. We will not use any external library, only the standard STL library, available with any C++ compiler. We will note here only the functions we create and some example usages. You can find the complete project files in the repository.

## Sample from uniform distribution

Sampling means drawing random numbers from a probability distribution. All randomness in our code comes from using the `rand()` C++ function, available in the `<cstdlib>` header.

The `rand()` function returns a random integer between `0` and `RAND_MAX`. The number `RAND_MAX` is a very large integer that may differ in different computers, but it is so large that this is not a problem, as we will see. In my computer, `RAND_MAX` is `2147483647` The integer that `rand()` returns is selected uniformly, i.e. all numbers in the range have the same chance to be returned.

As an example, running `rand()` a few times can be done as follows.

```c++
int a = rand();
int b = rand();
int c = rand();
cout << a << ", " << b << ", " << c << endl;

// Output (in my computer; it may differ in yours):
// 1804289383, 846930886, 1681692777
```

We will use the `rand()` function to create our first very useful sampling function: a function to sample from the uniform distribution, with arbitrary limits. Sampling from the standard uniform distribution means drawing a random real number in range $[a, b]$. When `a = 0` and `b = 1`, the uniform distribution is called the *standard uniform distribution*.

So let's create this function. We will first create a function `runif()` to draw from the standard uniform distribution.

```c++
// Samples from a uniform distribution in [0, 1].
double runif()
{
    return rand() / (double)RAND_MAX;
}
```

This function just calls `rand()` and divides the returned number by `RAND_MAX` in order to limit the result in the range `[0, 1]`. The necessary type conversion to `double` is made, so that a real number is returned.

Calling this function a few times can be done like this:

```c++
double a = runif();
double c = runif();
double b = runif();
cout << a << ", " << b << ", " << c << endl;

// 0.840188, 0.783099, 0.394383
```

To make it more general, we can add two arguments in our function, so that we can sample from a uniform distribution in the arbitrary range `[a, b]`, instead of the range `[0, 1]`. To do so, we first take a number in the range `[0, 1]`. Then, we scale it by `(b - a)`, so that the resulting number is in the range `[0, b - a]`. Finally, we add `a`, so that the resulting number is in the range `[a, b]`.

```c++
// Samples from a uniform distribution in [a, b].
double runif(double a, double b)
{
    return (rand() / (double)RAND_MAX) * (b - a) + a;
}
```

As an example:

```c++
double a = runif(3, 5);
double c = runif(3, 5);
double b = runif(3, 5);
cout << a << ", " << b << ", " << c << endl;

// 4.68038, 4.5662, 3.78877
```

We will usually want a lot of samples drawn from a distribution, so we will usually create an array of samples. For arrays, we will use the STL `vector` template, available in the `<vector>` header.

```c++
int n = 100;
vector<double> samples(n);
for (int i = 0; i < n; i++) {
    samples[i] = runif(3, 5);
}
for (int i = 0; i < n; i++) {
    cout << samples[i] << endl;
}

// 4.68038
// 3.78877
// 4.5662
// ...
// 4.62953
// 4.36844
// 4.82194
```

Sampling from an arbitrary uniform distribution is very useful and will be used as a component in more complex sampling functions.


## Plotting a distribution

In order to see visually the distribution of the samples we draw, we can create a histogram. A histogram is a bar chart, where the height of each bar is the number of samples that are between a small range of values, called a *bin*. The domain of the sample values is first split into a desired number of consecutive bins and then the samples that fall in each bin are counted.

We will use the following function for drawing a histogram.

```c++
// Plots a histogram of the elements of x.
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
```

As an example, we can use this function to plot the distribution of several uniform samples.

```c++
int n = 100;
vector<double> samples(n);
for (int i = 0; i < n; i++) {
    samples[i] = runif(3, 5);
}
printHist(samples, 10, 16);

// 3.03 *********
// 3.23 ********
// 3.43 ***********
// 3.62 *************
// 3.82 ******
// 4.02 ***********
// 4.21 *************
// 4.41 **********
// 4.60 *************
// 4.80 ****************
```

The more samples we take, the more the histogram will resemble the true distribution of the samples. In the uniform distribution, the probability density function is just a constant value.

```c++
int n = 1000;
vector<double> samples(n);
for (int i = 0; i < n; i++) {
    samples[i] = runif(3, 5);
}
printHist(samples, 10, 16);

// 3.00 ***********
// 3.20 *************
// 3.40 ************
// 3.60 ************
// 3.80 ***********
// 4.00 ************
// 4.20 ****************
// 4.40 ************
// 4.60 *************
// 4.80 ************
```

```c++
int n = 10000;
vector<double> samples(n);
for (int i = 0; i < n; i++) {
    samples[i] = runif(3, 5);
}
printHist(samples, 10, 16);

// 3.00 ***************
// 3.20 ***************
// 3.40 ***************
// 3.60 ***************
// 3.80 ***************
// 4.00 ****************
// 4.20 ***************
// 4.40 ***************
// 4.60 ***************
// 4.80 ***************
```
