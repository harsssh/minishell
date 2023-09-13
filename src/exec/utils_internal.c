#include "exec_internal.h"
#include <unistd.h>

void new_pipe(t_pipe *p)
{
    int fd[2];

    pipe(fd);
    p->fd_in = fd[1];
    p->fd_out = fd[0];
}