# CString

### *INFO*

`cstring.h` is a basic library to make easier the usage and
management of strings in c. All the functions provided by
this header file are inspired from the methods provided in
Java by the String class.

`darray.h` is a library function that allow to create
dynamical arrays and provide standard functions to work
with them. 

>**HEAVILY USED INSIDE** `cstring.h`

### *USAGE*

`darray.h`:

To define a dynamic array, the first thing that you need to
do is to define a constant *TYPE* and assign it the type of
array that you want.

    1   #define TYPE char //default -> int

If you don't define it, the header file will define it
automatically and assign to it the integer type.

To create a new DArray array, you only need to declare a
variable of the relative struct and initialize it with the
function *init_*.

    2   DArray array;
    3   init_(&array);

Now if you want to manipulate the array you can call the 
*add_* or *delete_* functions.

    4   add_(&array, 'a');
    5   delete_(&array, 0); // there is a safe checking

In addition, in this library is also present a shortcut
to empty the array, it calls *free_* and then *init_*.

    6   reset_(&array);

If you don't need to work anymore with a DArray variable,
you can *free_* the memory by destroying it.

    7   free_(&array);

<br>

>*At the moment you can only have one type of DArray per
program, but in future I will modify and correct it*

___

`cstring.h`:

To create a new string you only need to declare a variable of
the relative struct and defining it with the *create* function.

    1   String string = create("");

>This library heavily uses the DArray struct, for this reason,
>if you decide to import `cstring.h` you don't need to import
>also `darray.h`. 

Remember always to deallocate the memory occupied by the
struct. You can do it by calling the *destroy* function.

    2   destroy(&string);

Here a list of the functions provided by this library:

- create
- destroy
- set
- to_chars
- capitalize
- lower
- upper
- charAt
- compare
- compareIgnoreCase
- concat
- isEmpty
- indexOf
- lastIndexOf
- indexOfSubStr
- contains
- startsWith
- endsWith
- equals
- equalsIgnoreCase
- matches
- replace
- trim
- substring_begin
- substring_begin_end
- split

<br>

>***The examples of the usage of these functions are inside the file
>`src/main.c`***
> 
>>**NOTE:** inside `cstring.h` is already declared a *TYPE* 
>>constant and defined with *char*.

