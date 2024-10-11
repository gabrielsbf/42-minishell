#ifndef MINISHELL_H
#define MINISHELL_H

#include "pipe.h"
#include "server.h"
#include "maybe_libft.h"
#include "libft/includes/libft.h"
//readline lib
#include <readline/readline.h>
#include <readline/history.h>
//common libs
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
//system libs
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/wait.h>

#define FOLDER_BIN "/bin/"
#define FOLDER_BUILT_IN "./srcs/prompt_set/built_ins/"
#endif
