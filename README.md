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
```

In my computer, the above code produces the following output.

```
1804289383, 846930886, 1681692777
```

We will use the `rand()` function to create our first very useful sampling function: a function to sample from the uniform distribution, with arbitrary limits. Sampling from the standard uniform distribution means drawing a random real number in range `[a, b]`. When `a = 0` and `b = 1`, the uniform distribution is called the *standard uniform distribution*.

So let's create this function. We will first create a function `runif()` to draw from the standard uniform distribution.

```c++
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
```

Which outputs the following:

```
0.840188, 0.783099, 0.394383
```

To make it more general, we can add two arguments in our function, so that we can sample from a uniform distribution in the arbitrary range `[a, b]`, instead of the range `[0, 1]`. To do so, we first take a number in the range `[0, 1]`. Then, we scale it by `(b - a)`, so that the resulting number is in the range `[0, b - a]`. Finally, we add `a`, so that the resulting number is in the range `[a, b]`.

```c++
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
```

Which outputs:

```
4.68038, 4.5662, 3.78877
```

Sampling from an arbitrary uniform distribution is very useful and will be used as a component in more complex sampling functions.
