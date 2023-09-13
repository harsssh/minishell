#include "exec_internal.h"
#include <unistd.h>
#include <stdlib.h>

// for child process
static void configure_io(t_pipe *left, t_pipe *right)
{
    if (left != NULL)
    {
        dup2(left->fd_out, STDIN_FILENO);
        close(left->fd_in);
        close(left->fd_out);
    }
    if (right != NULL)
    {
        dup2(right->fd_in, STDOUT_FILENO);
        close(right->fd_in);
        close(right->fd_out);
    }
}

static int child_routine(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe)
{
    configure_io(left_pipe, right_pipe);
}

int handle_command(t_context *ctx, t_ast_node *ast, t_pipe *left_pipe, t_pipe *right_pipe) 
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        child_routine(ctx, ast, left_pipe, right_pipe);
        exit(EXIT_FAILURE);
    }
}