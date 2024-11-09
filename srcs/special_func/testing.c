#include <unistd.h>
#include <stdlib.h>
void	free_pointer(char **text)
{
	free(*text);
}

int		main()
{
	char *text;
	char **text2;

	text = (char *)malloc(sizeof(char) * 2);

	free_pointer(&text);
	(void)text2;
	return (0);
}
