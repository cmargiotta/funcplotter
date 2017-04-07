# funcplotter
A simple function plotter, with (animated) support for parametric function and convolution of limited in time functions.

# Install
```sh
$ sudo sh -c "cmake -DINSTALL=ON CMakeLists.txt && make && make install"
```
Will install plotter in /usr/local/bin, allowing it to be executed with `plotter` from terminal, and a .desktop file in /usr/share/applications.

```
$ cmake -DINSTALL=OFF CMakeLists.txt
$ make
```
Will compile plotter and put it in the local bin folder.

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
