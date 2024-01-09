/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:42:42 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/09 19:22:34 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createHeaderFile(const char *inputFileName, const char *outputFileName);

int main() {
    const char *inputFileName = "ps_funcs.c";
    const char *outputFileName = "output.h";

    createHeaderFile(inputFileName, outputFileName);

    printf("Header file generated successfully!\n");

    return 0;
}

int	check_braces(char *line)
{
	static int	brace_count;
	int	i;
	int	has_brace;

	i = 0;
	has_brace = 0;
	while (line[i])
	{
		if (line[i] == '{')
			brace_count++;
		else if (line[i] == '}')
		{
			brace_count--;
			has_brace = 1;
		}
		i++;
	}
	if (!brace_count && !has_brace)
		return (1);
	else
		return (0);
}

int	check_comment(char *line)
{
	static int	comm_count;
	int	i;
	int	has_comm;

	i = 0;
	has_comm = 0;
	while (line[i])
	{
		if (line[i] == '/' && line[i+1] == '*')
			comm_count++;
		else if (line[i] == '*' && line[i+1] == '/')
		{
			comm_count--;
			has_comm = 1;
		}
		else if (line[i] == '/' && line[i+1] == '/')
			return (0);
		i++;
	}
	if (!comm_count && !has_comm)
		return (1);
	else
		return (0);
}

void	add_semi_colon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (strlen(line) > 1 && line[i-2] == ')')
	{
		line[i - 1] = ';';
		line[i] = '\n';
		line[i + 1] = 0;
	}
}

int	print_struct(char *line, int braces)
{
	static int	is_struct;
	int	i;

	if (strstr(line, "struct"))
		is_struct = 1;
	else if (braces && !strstr(line, "struct"))
		is_struct = 0;
	if (is_struct)
		return (1);
	else
		return (0);
}

void createHeaderFile(const char *inputFileName, const char *outputFileName) {
	int braces;
	FILE *inputFile = fopen(inputFileName, "r");

    if (inputFile == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen(outputFileName, "w");

    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    fprintf(outputFile, "#ifndef GENERATED_HEADER_H\n");
    fprintf(outputFile, "#define GENERATED_HEADER_H\n\n");

    char line[256];

    while (fgets(line, sizeof(line), inputFile) != NULL)
	{
		braces = check_braces(line);
        if ((braces && *line != '\n' && check_comment(line)) | print_struct(line, braces))
		{
			add_semi_colon(line);
			fprintf(outputFile, "%s", line);
		}
    }

    fprintf(outputFile, "\n#endif // GENERATED_HEADER_H\n");

    fclose(inputFile);
    fclose(outputFile);
}

