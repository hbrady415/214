Assignment 1: 

The goal of this project was to create our own C function for memory allocation to be used instead of the malloc function which would store the data globally to be accessed later.
We start with a char array with a default size of 4096 and return a void pointer to the user for each malloc call which would indicate the size of the data held so that we can
jump past it in order to store or locate the next piece of data we call malloc on.  We also had to construct a series of test cases which would test the correctness of our malloc
function.  

Extra credit: minimize the number of bytes your header takes up.  We managed to accomplish this with 2 bytes

Assignment 2:

This project is designed as an introduction to multithreading and multiprocessing. Goal is to find a tradeoff of when threads are more efficient than processes and vice versa.

The executable, in this case searchtest.c searches for a specific value in an array of size N and returns the result. a driver was needed for this project as well but needed to 
be a little more thorough to ensure uniform testing for both multiprocessing and multithreading since they are both loaded as different executables. 

The driver needed to first fill in an array of a specific size with values from 1 to n(where n is the size of the array) and then jumble at least 3/4ths of them. 
This was accomplished by using the rand() function on its own modded by the max array size. We used the regular rand() function because it kept the randomizer the same for both 
executables where seeding it first would lead to very different arrays across both executables. 

In the end we found threads work best for larger arrays(in the high thousands) and processes work best for arrays of smaller sizes.

Assignment 3:

This project asked us to create both a client and a server, specifically a client and server capable of handling a simplified version of a email service.  The client was in charge of making sure the user
sent valid commands to the server as well as sending correct commands to the server.  

The server needed to be able to create message boxes with names, delete them, open them , close them, and put messages into the boxes.  Multiple boxes could not be opened by multiple users simultaneously.  Since this was a simplified client/server
project, boxes could not be created within each other and any messages put into the boxes were stored in a queue and deleted upon being sent from the server to the client.
