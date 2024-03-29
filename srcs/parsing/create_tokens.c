//	NORM
//		-missing header

#include "spash_parsing.h"
#include "spash_error.h"
#include "spash.h"
#include "libft.h"

/**
 * @brief Get the words value while respecting quoting rules.
 * @param data the main data stuct
 * @param ptr a pointer to the begining of the word
 * @return the words value or NULL if a quote was unclosed (updating error)
 */
char	*get_word_value(t_data *data, char *ptr)
{
	char	*value;
	char	quote;
	int		i;

	i = 0;
	while (ptr && ptr[i] && !ft_strchr(METACHARACTERS, ptr[i]))
	{
		if (ptr[i] == SINGLE_QUOTE || ptr[i] == DOUBLE_QUOTE)
		{
			quote = ptr[i++];
			while (ptr[i] && ptr[i] != quote)
				i++;
			if (!ptr[i])
				return (uncquote_error(data, quote), NULL);
		}
		i++;
	}
	value = ft_substr(ptr, 0, i);
	if (!value)
		(sperr(data, MFAIL, "get_word_value", 2), exit_prg(data));
	return (value);
}

/**
 * @brief Get the tokens data from the command line
 * @param data the main data struct
 * @param tk current token
 * @param grammar a string table containing the predefined grammar
 * @param ptr a pointer to the current location on command line
 */
void token_data(t_data *data, t_token *tk, char **grammar, char *ptr)
{
	if (!*ptr)
		tk->op = NEWLINE;
	while (*ptr && tk->op != NONE)
	{
		tk->value = grammar[tk->op];
		if (!ft_strncmp(ptr, tk->value, ft_strlen(tk->value)))
			break;
		tk->op++;
	}
	if (tk->op == IN_RED || tk->op == HEREDOC_RED || tk->op == OUTTR_RED
		|| tk->op == OUTAP_RED)
		tk->type = RED_OP;
	else if (tk->op != NONE)
		tk->type = CTRL_OP;
	else
		tk->type = WORD;
	if (tk->op == NEWLINE)
		tk->value = S_NEWLINE;
	else if (tk->op == NONE)
		tk->value = get_word_value(data, ptr);
}

/**
 * @brief Malloc and add a new token to the end of the list
 * @param data the main data struct
 * @return a pointer to the new token
 */
t_token	*add_token(t_data *data)
{
	t_token	*tk_new;
	t_token	*tk_last;

	tk_last = data->tk_lst;
	while (tk_last && tk_last->next)
		tk_last = tk_last->next;
	tk_new = (t_token *)ft_calloc(1, sizeof (t_token));
	if (!tk_new)
		(sperr(data, MFAIL, NULL, 139), exit_prg(data));
	if (!data->tk_lst)
		data->tk_lst = tk_new;
	else
	{
		tk_last->next = tk_new;
		tk_new->prev = tk_last;
	}
	return (tk_new);
}

/**
 * @brief Create a list of tokens from the cmd line
 * @param data the main data struct
 */
void	create_tokens(t_data *data)
{
	char 	*ptr;
	t_token	*tk;

	tk = NULL;
	ptr = data->c_line;
	while (!tk || tk->op != NEWLINE)
	{
		while (*ptr == SPACE)
			ptr++;
		tk = add_token(data);
		token_data(data, tk, data->grammar, ptr);
		ptr += ft_strlen(tk->value);
	}
}
