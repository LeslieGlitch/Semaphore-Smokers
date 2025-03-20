# Semaphore Smokers

A variant of Suhas Patil's smoker problem. This program uses POSIX
threads and semaphores to allow a set of smokers to continually
smoke cigarrettes.  
The scene involves a set of 6 smokers who each need 3 ingredients
to make a cigarrette: tobacco, paper, and a match. Each smoker has
one of these ingredients ininfinite supply, but needs the other two
from an agent. Three agents sit at a table with the smokers, and
occasionally set out two of the ingredients on the table. The goal
is for one of the smokers who needs those ingredients to collect,
smoke a cigarrette for a bit, then return for more ingredients.  
This is accomplished through three pusher threads that are
activated once ingredients are set out and wakes up the correct
smoker. Without these pushers, we would be at risk of deadlock.  

In this example, we track the actions of each thread through
standard output.  

## Instructions for building
Open the terminal in the main directory and run `make run`  
To remove the compiled files, run `make clean`
