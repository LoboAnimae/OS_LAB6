# Lab #6
## Development Environment
Developed in Windows 10 with a WSL 2 compiler.
***
## Requirements
Must have a linux machine compiler to take a look at the "bitácoras". In case this is not possible, the Makefiles can be modified to not include the last instruction of ```./main > bitacora.txt``` and, instead, just make it ```./main```. 
***
## How to run
Go into any of the two semaphore folders above and run the ```main``` program. This can be done in any Unix system with ```$ ./main``` or by running ```$ make``` inside the directory, because the Makefile includes the both of them. 
***
## How to Set Parameters
Go into ```semaphore.h``` and change the parameters in there. 

**The program works best when the amount of threads is bigger than the amount of resources.
Parameter | Description | Default
-|-|-
PTHREAD_NUMBER | How many threads are going to be generated in the program | 11
PTHREAD_ITERATIONS | How many iterations there will be per thread | 4
MAX_AVAILABLE_RESOURCES | How many resources will be available in the program | 10

***
## METADATA
Exercise | Description
------------ | -------------
Semaphore | Code where every program takes exactly one resource and gives it back after one time unit.
Semaphore_2 | Code where every program takes a variable amount of resources and give them back after one time unit.