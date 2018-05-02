# Statistics-of-Extremes
Codes, data files etc. related to Bachelor's thesis.

This repository contains files associated with my Bachelor's thesis project. The title of the thesis is "ON THE STATISTICS OF EXTREMES IN SELF-DRIVEN PARTICLES", and it aims to model certain "active" particles and to study certain rare behaviours in them.
In particular we try to mathematically model an experimental setup that was used to verify certain fluctuation relations involving entropy production (and consumption).

## Files included:
1) C++ source file (2dActiveBrownianMotion-multiple-tau.cpp), written in C++11. This program simulates the active Browninan process. To compile type
> g++ -std=c++11 2dActiveBrownianMotion-multiple-tau.cpp

Before running make sure to create two subdirectories in your present directory Output and Output/LDF/. Run the code using
>./a.out

The code gives has two options: No potential and Periodic potential. The switch has to be made in the function called V(x,y) in the source code. Once changed, the code has to be recompiled.

2) Python script (plot_ldf-multiple-tau-D-F.py) written in python 2.7. Dependencies: matplotlib and numpy. This script is used to calculate the large deviation function from the output files of 2dActiveBrownianMotion-multiple-tau.cpp and plots it. 

3) Output/ (readme inside)
