/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:21:58 by bkwamme           #+#    #+#             */
/*   Updated: 2023/11/16 15:24:24 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_free_arr(char **arr, size_t word)
{
	while (word > 0)
	{
		free(arr[word]);
		word--;
	}
	free(arr);
	return (0);
}

static size_t	ft_putword(char **arr, char const *s, char c, size_t word)
{
	size_t	i;
	size_t	word_len;

	word_len = 0;
	i = 0;
	while (s[word_len] != c && s[word_len] != '\0')
		word_len++;
	arr[word] = (char *) malloc (sizeof(char) * (word_len + 1));
	if (!arr[word])
		return (ft_free_arr(arr, word));
	while (i < word_len)
	{
		arr[word][i] = s[i];
		i++;
	}
	arr[word][i] = '\0';
	return (word_len);
}

static int	ft_word_count(char const *s, char c)
{
	size_t	word;
	size_t	i;

	i = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			word++;
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	size_t	i;
	char	**arr;

	if (!s)
		return (NULL);
	i = 0;
	word = 0;
	arr = (char **) ft_calloc(sizeof(char *), ft_word_count(s, c) + 1);
	if (!arr)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i += ft_putword(arr, &s[i], c, word);
			if (s[i] != c && s[i] != '\0')
				return (NULL);
			word++;
		}
		else
			i++;
	}
	return (arr);
}
