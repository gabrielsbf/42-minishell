#include "../../includes/minishell.h"

void	add_other_str(char *text, char* substr,  int i)
{
	int	len;
	char *text_past;

	text_past = ft_strdup(text);
	free(text);
	len = 0;
	text = (char *)malloc(sizeof(char) * (i + ft_strlen(substr) + 2));
	if (!text)
		return ;
	while (text_past[len] != '\0')
	{
		text[len] = text_past[len];
		len++;
	}
	i = 0;
	while (substr[i] != '\0')
	{
		text[len] = substr[i];
		len++;
		i++;
	}
	text[len] = '\0';
}

int main (int argc, char *argv[])
{
	char *text;
	int		i;

	i = 0;
	text = (char *)malloc(sizeof(char) * (ft_strlen(argv[1] + 1)));

	while (argv[1][i] != '\0')
	{
		text[i] = argv[1][i];
		i++;
	}
	printf("substr before : %s\n", text);
	add_other_str(text, argv[2], i);
	printf("substr 1 : %s, substr 2 : %s, result is: %s\n",argv[1], argv[2], text );
}
