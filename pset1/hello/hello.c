#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); //Enter your name
    printf("hello, %s\n", name); //Greet the user with input name provided
}