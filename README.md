# CString

### *INFO*

`cstring.h` is a basic library to make easier the use and
management of strings in c. All the functions provided by
this header file are inspired from the Java's String class.

`darray.h` is a library that allows to create
dynamic arrays and provide standard functions to work
with them. **HEAVILY USED INSIDE** `cstring.h`

>*NOTE: For debugging, error corrections and some features ideas,
[SPECTREv333](https://github.com/SPECTREv333) helped me a lot. Go check his profile!*

### *USAGE*

`darray.h`:

The DArray struct is not only a dynamic array, but it is a collection of nodes.
The array it wraps (of type _void**_), allows you to insert practically everything you
want. This type of grouping, technically, permits you to create a not homogeneous data structure, but
if you do so, you need something to keep track of the type of each node. Maybe in the future I will 
refactor this library to make it possible without writing other management code outside the header file.
Inside the DArray struct there is an enum representing a primitive type, probably it isn't
required, but I wanted something to keep track of the type of the structure.
The header does not provide any sorting algorithm because the type of the node is _void*_, 
so it's impossible to determine how it should be sorted. I leave you the fun of implementing any sorting 
algorithm, and maybe you will write a brand-new type of sorting that will replace all the old ones!
Here's a little tutorial.

To define a dynamic array, the first thing that you need to
do is to import the library.

    1   #include "your/path/to/headers/darray.h"

To create a new DArray array, you only need to declare a
variable of the relative struct and initialize it with the
function *init_*.

    2   DArray array;
    3   init_(&array, CHAR);
    
Inside the library is present an enum, like I said into the introduction, to easily
manage the primitive types.

Now if you want to manipulate the array you can call the 
*add_* or *delete_* functions.

    4   char a = 'a';
    5   add_(&array, &a);
    6   delete_(&array, 0); // there is a safe checking

To retrieve the content of the array, there is a function named *get_*.

    7   char elmnt = *get_(array, 0, char);
    
Because the array contains, by default, elements of type *void**,
you need to cast them into the correct type manually.
For this reason there are some macros that do this for you,
one per type.

In addition, in this library is also present a shortcut
to empty the array, it calls *free_* and then again *init_*.

    8   reset_(&array);

If you don't need to work anymore with a DArray variable,
you can *free_* the memory by destroying it.

    9   free_(&array);

___

`cstring.h`:

The String struct is a wrapper for a DArray of type CHAR. With the methods provided,
you're more or less capable of manipulating strings like other languages do.
Here's a little tutorial.

>This library heavily uses the DArray struct, for this reason,
>if you decide to import `cstring.h` you don't need to import
>`darray.h`.

The first step is to include the library.

    1   #include "path/to/headers/cstring.h"

To create and initialize a new string, you only need to declare a variable of
the relative struct and defining it with the *create* function.

    2   String string = create("");

Remember always to deallocate the memory occupied by the
struct calling the function named *destroy*.

    3   destroy(&string);

Here a list of the functions provided by this library:

- create
- destroy
- str_size
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

>***You can find all the examples inside `src/main.c`***
>>*NOTE: feel free to fork the project and modify this code.
>> For any idea you can present a pull request on this repository.*

