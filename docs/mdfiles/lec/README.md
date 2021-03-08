# Julia tutorial

1. [Think Julia](https://benlauwens.github.io/ThinkJulia.jl/latest/book.html)
2. [From zero to Julia](https://techytok.com/from-zero-to-julia/)
3. [Julia cheat sheet](https://juliadocs.github.io/Julia-Cheat-Sheet/) if you are familiar with Python and/or MATLAB.
4. [Official Julia Manual](https://docs.julialang.org/) for the API.
5. [Julia for Pythonistas](https://colab.research.google.com/github/ageron/julia_notebooks/blob/master/Julia_for_Pythonistas.ipynb)
6. [Learn Julia](https://julialang.org/learning/) from the official website.

# Why Julia?

[John F. Gibson's talk](https://github.com/johnfgibson/whyjulia/blob/master/1-whyjulia.ipynb)

- Python/MATLAB-like syntax + natural math presentation
- C-like speed (!) + built-in parallelism
- Composable and extensible (e.g. DiffEq + ANN)
- Right tool for this course to solve differential equations and stochastic simulations

## Why not Julia?

- Time to first plot (TTFF). Code needs to be compiled first so it feels less responsive than Python. [Somebody just gave up](https://www.zverovich.net/2016/05/13/giving-up-on-julia.html).
- Less libraries in some domains. (e.g. metabolic networks)
- [Arrays start at one](https://i.imgur.com/VRSkSGd.jpg)

# Install and run Julia

[Download Julia](https://julialang.org/downloads/) and install. You could give version `1.6-rc1` a try because it loads much fater than previous versions.

## REPL workflow

Run the julia REPL (terminal) and start typing.

## Jupyter workflow

This workflow suits demonstration

Open the Julia terminal and enter the following commands to install IJulia, the Julia kernel for Jupyter notebooks.

```julia
using Pkg

pkg"add IJulia"
```

And then run Jupyter Lab either from the Julia terminal.

```julia
using IJulia

# It will prompt you to install jupyter lab, enter y to proceed
# Will open at ${HOME}, thatby default it is "C:\Users\yourname\" in Windows systems.
IJulia.jupyterlab()
```

Or from Anaconda's Jupyter lab interface if you have installed Anaconda.

## VS Code workflow

[VS Code](https://code.visualstudio.com/) with [Julia extension](https://www.julia-vscode.org/) works better for structured code. See this [Youtube video](https://www.youtube.com/watch?v=IdhnP00Y1Ks).

!> Juno, the original IDE for Julia, is [in maintenance mode](https://www.youtube.com/watch?v=rQ7D1lXt3GM).

## My computer cannot run Julia

### Google collab

Open this [Julia for Pythonistas](https://colab.research.google.com/github/ageron/julia_notebooks/blob/master/Julia_for_Pythonistas.ipynb) notebook, save a copy to your Google drive, and run it.

### Nextjournal

[Nextjournal](https://nextjournal.com/) provides a notebook-like UI for reproducible research.

You could use [Tmy template for Julia 1.6 + Differential Equations](https://nextjournal.com/bebi5009/julia-template). 
