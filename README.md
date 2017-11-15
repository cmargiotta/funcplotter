# funcplotter
A simple function plotter, with (animated) support for parametric function and convolution of limited in time functions.

# Install

Make a build directory for out-of-source building.

```sh
$ mkdir build
$ cd build
$ cmake ..
```

Build and test locally.

```sh
$ make
$ bin/plotter
```

Install plotter in `/usr/local/bin`, allowing it to be executed with `plotter` from terminal, and a .desktop file in `/usr/local/share/applications`.

```sh
$ sudo make install
```

# Functions
|||
--------------|----------------------
`rect()`      | Rectangular impulse
`sinc()`      | Sinc function (`sin(arg)/arg`)
`delta()`     | Dirac delta
`tri(b, arg)` | A triangular impulse, with a base of b
`sin()`       | Sine
`cos()`       | Cosine
`abs()`       | Absolute value
`sqrt()`      | Square root
`log()`       | Natural logarithm

Supported operators are: `+`, `-`, `*`, `/`, `^`.  
Other: `e` = Euler's number; `x` = unknown; `a` = parameter  
