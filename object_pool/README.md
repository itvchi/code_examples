Examples of allocation objects with performance comparasion
- main_malloc - objects are returned for the user with dynamic memory allocation mechanism
- main_object_pool - objects are returned form statically allocated object pool

Performace test involves allocation then free of random number of elements in one iteration of loop, 
then the loop is repeated until specified number of elements were allocated and freed after all loop iterations.
Total number of allocated elements and maximum elements allocated in one loop iteration is the same for each example
to have similar test condition for each implementation.

--- TEST #1 ---
Test results (10^8 elements, up to 10^2 elements per loop):
- main_malloc - 1,2s
- main_object_pool - 5,82s

Test results (10^7 elements, up to 10^3 elements per loop):
- main_malloc - 0,13s
- main_object_pool - 4,8s

Above tests shows that current object pool implementation is much worse than dynamic allocation of the memory
for storing objects. The main reason of that behaviour is take() function implementation which traverse all object_pool
to get free object, it takes a lot of time to trverse the loop what can be seen with second test where there were more
elements get for each loop iteration.

--- TEST #2 ---
Test results (10^8 elements, up to 10^2 elements per loop):
- main_malloc - 1,26s
- main_object_pool - 0,93s

Test results (10^7 elements, up to 10^3 elements per loop):
- main_malloc - 0,13s
- main_object_pool - 0,09s

Using different method of traversing object pool for checkinf for free object significantly reduced execution time.
Now object pool implementation has an advantage over dynamic allocation of the objects.

--- TEST #3 ---
Test results (10^8 elements, up to 10^2 elements per loop):
- main_malloc - 2,38s
- main_object_pool - 0,81s

Test results (10^7 elements, up to 10^3 elements per loop):
- main_malloc - 1,03s
- main_object_pool - 0,08s

Increasing size of the object caused regression in performance of dynamic allocation example. The were no significant
changes in object pool example performace.