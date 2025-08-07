# Project name: Fully-connected-neural-networks

This project is a simulation of an artificial neural network.

## Main concept

An artificial neural network is a simplified model of the human brain. Neurons are a description of a mathematical formula:

$$ f(u) = f(\sum_{i=0}^m w_i x_j + b) $$

$\ where: \$

$\ f(u) - activation \\ function \$

$\ u - output \\ value \$

$\ m - amound \\ of \\ input \\ data \$

$\ w_{i} - i-th \\ weight \$

$\ x_{i} - i-th \\ input \\ value \$

$\ b - bias \$

## Avaliable activation function:
- Unipolar sigmoidal function

## Graphical environment for drawing diagrams

According to the website root.cern :

After installing all required dependencies(https://root.cern/install/dependencies), ROOT can be compiled with these commands on most UNIX-like systems: 

# The latest stable branch gets updated automatically on each release.
# You may update your local copy by issuing a `git pull` command from within `root_src/`.
$ git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src
$ mkdir root_build root_install && cd root_build
$ cmake -DCMAKE_INSTALL_PREFIX=../root_install ../root_src # && check cmake configuration output for warnings or errors
$ cmake --build . -- install -j4 # if you have 4 cores available for compilation
$ source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}

And similarly, on Windows, inside a x86 Native Tools Command Prompt for VS 2019, ROOT can be compiled with these commands:

rem The `latest-stable` branch gets updated automatically on each release.
rem You may update your local copy by issuing a `git pull` command from within `root_src`.
C:\Users\username>git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src
C:\Users\username>mkdir root_build root_install && cd root_build
C:\Users\username>cmake -G"Visual Studio 16 2019" -A Win32 -Thost=x64 -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_INSTALL_PREFIX=../root_install ../root_src
C:\Users\username>cmake --build . --config Release --target install
C:\Users\username>..\root_install\bin\thisroot.bat

If running on Windows from Powershell (the default on Visual Studio Code), call instead thisroot.ps1.
