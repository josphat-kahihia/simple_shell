#include "main.h"

/**
 * main - init, run and control the shell
 *
 * Description: The main function first initialises the variables 'centres'
 * required to run the shell, then checks the mode of execution, and handles
 * operation based on that mode. It should never get to its own return value.
 * That signifies an error that should be checked. However, because GCC-alx
 * requires it, we'll set it to return to zero. In the current state, it should
 * actually get to return.
 *
 * Return: 0 on success.
 */
int main(void)
{
	commands_centre *cmd_main;

	cmd_main = init_commands_centre();
	if (cmd_main == NULL)
		return (-1);
	return (0);
}
