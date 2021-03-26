#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Enter your name
    string name = get_string("What is your name?\n");

    // Greet the user with input name provided
    printf("hello, %s\n", name);
}
