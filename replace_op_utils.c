char	*combine_str(char *s1, char *s2, char *s3, int *i)
{
	char	*ret;

	if (!s1 || !s2 || !s3)
		allocat_error();
	if (s2[1] == OP_AND_IF || s2[1] == OP_OR_IF
		|| s2[1] == OP_IN_HEREDOC || s2[1] == OP_OUT_HEREDOC)
		*i += 2;
	else
		*i += 1;
	ret = ft_strjoin_free(ft_strjoin(s1, s2), s3);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (ret);
}