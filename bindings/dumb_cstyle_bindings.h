void my_function(arg1, arg2, arg3);

void my_function_in_their_interface(arg1, arg2, arg3, arg4)
{
my_function(arg1, arg2, arg3);
}

or

void my_function(arg1, arg2, arg3, arg4);

void my_function_in_their_interface(arg1, arg2, arg3)
{
my_function(arg1, arg2, arg3, my_arg4);
}
