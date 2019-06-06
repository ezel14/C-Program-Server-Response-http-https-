#ifndef HEADER_TASK6_ES_H
#define HEADER_TASK6_ES_H

int str_n_len_es(const char *string);
char *str_n_str_es(const char *string, const char *sub_string);
int str_cmp_es(const char *string1, const char *string2);
char* str_n_chr_es(const char* string, int character);
char **get_sub_strings(int *count, char *text_line, const char STRING_START[], char **links);
unsigned int count_sub_strings(const char *text_line, const char STRING_START[]);
const char *next_quote(const char *text_line);
char *read_stdin(FILE *stream);
char *read_formatted_input(FILE *stream);
char *response_message(long response_code);

#endif