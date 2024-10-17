#include "../../includes/minishell.h"

// int main()
// {
// 	//usar open pra criar um pingResults.txt
// 	int fd = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
// 	if (fd == -1)
// 		return 2;
// 	//vc consegue printar o fd e ele aparece como um inteiro, rodando o programa você verá qual é
// 	printf("the fd of file %d\n", fd);
// 	//aqui q a magia acontece, usando "dup2" voce consegue trocar os fds do programa LITERALMENTE
// 	int file = dup2(fd, STDOUT_FILENO);
// 	//cat "pingResults.txt" e vc vai ver a magia kkk
// 	printf("the fd of file %d\n", file);
// 	close(fd);
// 	return 0;
// }

// int main(void)
// {
// 	int fd[2];
// 	int fd_2[2];
// 	int fd_temp;

// 	pipe(fd);
// 	int stdout = STDOUT_FILENO;
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		fd_temp = dup2(fd[1], STDOUT_FILENO);
// 		dup2(STDOUT_FILENO, fd_temp);
// 		printf("esse é o texto de saída %d\n", fd[1]);
// 		printf("mais um texto de saída %d\n" , fd_temp);
// 		exit(0);
// 	}
// 	close(fd[1]);
// 	close(fd[0]);
// 	pipe(fd_2);
// 	dup2(fd_2[0], fd[1]);
// 	printf("fd2 apareceu %d\n", fd[1]);
// 	printf("Agora sim apareceu %d\n", stdout);
// }

// int	main(void)
// {
// 	int fd[2];
// 	int	pid;
// 	int	i;
// 	char str1[100] = "echo laulau |";
// 	char str2[100] = "echo leuleu";

// 	i = 0;
// 	pipe(fd);
// 	pid = fork();
// 	while (i < 2)
// 	{
// 		if (pid == 0)
// 		{

// 		}
// 		i++;
// 	}

// }

