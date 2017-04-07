# funcplotter
A simple function plotter, with (animated) support for parametric function and convolution of limited in time functions.

# Install
```sh
$ cmake CMakeLists.txt
$ make
```

# Functions
rect(): rectangular impulse<br>
sinc(): sinc function (sin(arg)/arg)<br>
delta(): Dirac delta<br>
tri(b, arg): a triangular impulse, with a base of b<br>
sin(): sine<br>
cos(): cosine<br>
abs(): module<br>
sqrt(): square root<br>
log(): natural logarithm<br>
<br>
Supported operators are: +, -, *, /, ^.<br>
Other: e = Euler's number; x = unknown; a = parameter  
