# The Evolution of Trust - C++ Simulation
Remaking the game in https://ncase.me/trust/ in C++. Furthermore, new strategies have been included inside for exploration.
## Installation
Make sure that you have already installed C++ compilers (preferred gcc) before running this program.
Download the zip folder of the source code and unzip it. Open your command prompt and locate the prompt to the unzipped folder. Then, compile the code to become an executable file.
### Single Match between 2 Players
`g++ -c singleGame.cpp singleGameManual.cpp`

`g++ -o manual.exe singleGame.o singleGameManual.o`

To run the program, simply type `.\manual.exe` in your command prompt.
### Tournaments between multiple players
`g++ -c singleGame.cpp main.cpp`

`g++ -o main.exe singleGame.o main.o`

To run the program, simply type `.\main.exe` in your command prompt.
