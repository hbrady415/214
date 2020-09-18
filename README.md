This project is designed as an introduction to multithreading and multiprocessing. Goal is to find a tradeoff of when threads are more efficient than processes and vice versa.

The executable, in this case searchtest.c searches for a specific value in an array of size N and returns the result. a driver was needed for this project as well but needed to 
be a little more thorough to ensure uniform testing for both multiprocessing and multithreading since they are both loaded as different executables. 

The driver needed to first fill in an array of a specific size with values from 1 to n(where n is the size of the array) and then jumble at least 3/4ths of them. 
This was accomplished by using the rand() function on its own modded by the max array size. We used the regular rand() function because it kept the randomizer the same for both 
executables where seeding it first would lead to very different arrays across both executables. 

In the end we found threads work best for larger arrays(in the high thousands) and processes work best for arrays of smaller sizes.
