#include "exec_internal.h"
#include <unistd.h>
#include <stdlib.h>

static void set_io(int fd_in, int fd_out)
{
    if (fd_in != STDIN_FILENO)
    {
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }
    if (fd_out != STDOUT_FILENO)
    {
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }
}

static void child_routine(t_context *ctx, t_ast_node *ast, int fd_in, int fd_out)
{
}

int handle_command(t_context *ctx, t_ast_node *ast, int fd_in, int fd_out)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        child_routine(ctx, ast, fd_in, fd_out);
        exit(EXIT_FAILURE);
    }
}