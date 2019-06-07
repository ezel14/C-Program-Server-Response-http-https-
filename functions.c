#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header_task6_es.h"


int str_n_len_es(const char* string) 
{
	///Initialize the length
	int length = 0;
	///Create a while loop to check if the first char is not a zero char
	while (*string != '\0') {
		string++;
		length++;
	}
	///Return the length from the function
	return length;
}


char* str_n_str_es(const char* string, const char* sub_string)
{
	///Create a while loop to check when the first char is not equal to a zero char
	while (*string != '\0'){
		///Create an if statement to check if pointer to string is equal to pointer 
		///to sub_string and string compare return value
		if ((*string == *sub_string) && str_cmp_es(string, sub_string)) {
			return (char*)string;
		}
		string++;
	}
	return NULL;
}

int str_cmp_es(const char* string1, const char* string2)
{
	///Check while there is a pointer to char in string1 and string2
	while (*string1 && *string2) {
		///Check if pointer to string1 char is not equal to pointer to string2 char
		if (*string1 != *string2) {
			return 0;
		}
		string1++;
		string2++;
	}
	return *string2 == '\0';
}

char* str_n_chr_es(const char* string, int character)
{
	///Initialize a constant char pointer to NULL
	const char* ptr = NULL;
	size_t i = 0;

	///Create a for loop until a break
	for (i = 0; ;i++) {
		///Check if the string is equal the character
		if ((unsigned char)string[i] == character) {
			ptr = &string[i];
			break;
		}
		if (string[i] == '\0') {
			return NULL;
		}
	}
	///Retrun a pointer to the character
	return (char*)ptr;
}

char* read_stdin(FILE* stream)
{
	///Create an initial max size for the buffer to hold
	unsigned int BUFF_SIZE = 100;
	///Create memory on the heap for the buffer
	char* buffer = calloc(BUFF_SIZE + 1, sizeof(char));
	char c = '\0';
	int i = 0;

	///Get the input from stdin
	while ((c = fgetc(stream)) != '\0' && !feof(stream)) {
		///Increase size if the buffer if full
		if (i == (BUFF_SIZE - 1)) {
			BUFF_SIZE += BUFF_SIZE;
			///Reallocte memory for the buffer if needed
			buffer = realloc(buffer, (BUFF_SIZE + 1) * sizeof(char));
		}
		///Copy the actual read character
		*(buffer + (i++)) = c;
	}
	///Reallocate the memory to the correct size
	buffer = realloc(buffer, (strlen(buffer) + 1) * sizeof(char));
	///Ensures that the buffer is null terminated
	*(buffer + i) = '\0';
	return buffer;
}

char** get_sub_strings(int* count, char* text_line, const char STRING_START[], char** links)
{
	const size_t len_link_begin = strlen(STRING_START);
	int index = *count - 1;
	text_line = strstr(text_line, STRING_START);

	while (index >= 0 && text_line) {
		///Get the size of the string inside quotes
		size_t link_len = next_quote(text_line + len_link_begin + 1) - (text_line + len_link_begin + 1);
		///Check if the length is not zero
		if (link_len) {
			///return a pointer to a new string which is a duplicate of the string
			char* link = strndup(text_line + len_link_begin + 1, link_len);
			links[index] = link;
			index--;
			///Find the first occurence of STRING_START
			text_line = strstr(text_line + len_link_begin + strlen(link) + 2, STRING_START);
		}
		else {
			printf("Empty link.\n");
			text_line = strstr(text_line + len_link_begin, STRING_START);
		}
	}
	return links;
}

unsigned int count_sub_strings(const char* text_line, const char STRING_START[])
{
	///Initialize an usigned int (it can never be zero)
	unsigned int count = 0;

	///Check if not text_line or not String_Start 
	if (!text_line || !STRING_START) {
		return 0;
	}
	else {
		///Find the first occurence of STRING_START in the text_line
		text_line = strstr(text_line, STRING_START);
		///Get the length of STRING_START
		size_t string_start_len = strlen(STRING_START);
		/// While there is a pointer to the the text_line
		while (text_line && *text_line) {
			count++;
			///Find the first occurence of STRING_START
			text_line = strstr(text_line + string_start_len, STRING_START);
		}
	}
	return count;
}

const char *next_quote(const char text_line[]) 
{
  ///Create a loop While the first char in text_line is not equal to a ' " ', a '\'' and '\0'
  while(*text_line != '"' && *text_line != '\'' && *text_line != '\0') {
    text_line++;
  } 
  ///Return the text_line from the function
  return text_line;
} 

char *read_formatted_input(FILE *stream)
{
  /// Initialize a max size for the buffer to hold
  unsigned int BUFF_SIZE = 100;
  ///Create an Initial allocation of the buffer with BUFF_SIZE 
  char *buffer = malloc( sizeof(char)* BUFF_SIZE + 1);  
  char c = '\0';
  int i = 0;

  ///Read stdin 
  while ((c = fgetc(stream)) != EOF && c != '\n') {
    ///Increase the buffer size if the buffer is full
    if (i == (BUFF_SIZE - 1)) {
      BUFF_SIZE += BUFF_SIZE;
      ///Reallocate the memory with a new size tp preserve the data
      buffer = realloc(buffer, (BUFF_SIZE + 1) * sizeof(char));
    }
    ///Copy the actual read character
    *(buffer + (i++)) = c;
  }
  ///Reallocate the memory to the actual size
  buffer = realloc(buffer, (str_n_len_es(buffer) + 1) * sizeof(char));
  ///Ensures the buffer is null terminated
  *(buffer + i) = '\0';
  ///Check if i is qual to zero before returning the buffer 
  if(i == 0) {
    free(buffer);
    buffer = NULL;
  }
  return buffer;
}

char *response_message(long response_code)
{
  char *message = NULL;

  switch(response_code)
  {
    ///Create information responses   
    case 100:
      message = "Continue";
      break;
    case 101:
      message = "Switching";
      break;
    case 102:
      message = "Procssing";
      break;
    ///Create successful responses
    case 200:
      message = "OK";
      break;
    case 201: 
      message = "Created";
      break;
    case 202: 
      message = "Accepted";
    case 203: 
      message = "Non-Authoritative Information";
      break;
    case 204: 
      message = "No Content";
      break;
    case 205: 
      message = "Reset Content";
      break;
    case 206: 
      message = "Partial Content";
      break;
    case 207: 
      message = "Multi-Status";
      break;
    case 208: 
      message = "Already Reported";
      break;
    case 226: 
      message = "IM Used";
      break;
    ///Create redirection responses
    case 300: 
      message = "Multiple Choices";
      break; 
    case 301: 
      message = "Moved Permanently";
      break; 
    case 302: 
      message = "Found";
      break; 
    case 303: 
      message = "See Other";
      break;
    case 304: 
      message = "Not Modified";
      break; 
    case 305: 
      message = "Use Proxy";
      break;
    case 306:
      message = "(Unused)";
      break;
    case 307: 
      message = "Temporary Redirect";
      break;
    case 308: 
      message = "Permanent Redirect";
      break;
    ///Create client error responses
    case 400:
      message = "Bad Request";
      break;
    case 401:
      message = "Unauthorized";
      break;
    case 402:
      message = "Payment Required";
      break;
    case 403:
      message = "Forbidden";
      break;
    case 404:
      message = "Not Found";
      break;
    case 405:
      message = "Method Not Allowed";
      break;
    case 406: 
      message = "Not Acceptable";
      break; 
    case 407: 
      message = "Proxy Authentication Required";
      break; 
    case 408:
      message = "Request Timeout";
      break; 
    case 409: 
      message = "Conflict";
      break; 
    case 410: 
    message = "Gone";
      break; 
    case 411: 
      message = "Length Required";
      break;
    case 412: 
      message = "Precondition Failed";
      break; 
    case 413: 
      message = "Payload Too Large";
      break; 
    case 414: 
      message = "URI Too Long";
      break; 
    case 415: 
      message = "Unsupported Media Type";
      break;
    case 416: 
      message = "Range Not Satisfiable";
      break;
    case 417: 
      message = "Expectation Failed";
      break;
    case 421: 
      message = "Misdirected Request";
      break;
    case 422: 
      message = "Unprocessable Entity";
      break; 
    case 423: 
      message = "Locked";
      break; 
    case 424: 
      message = "Failed Dependency";
      break;
    case 425: 
      message = "Too Early";
      break; 
    case 426:
      message = "Upgrade Required";
      break; 
    case 427:
      message = "Unassigned";
      break;
    case 428:
      message = "Precondition Required";
      break; 
    case 429:  
      message = "Too Many Requests";
      break;
    case 430: 
      message = "Unassigned";
      break; 
    case 431:
      message = "Request Header Fields Too Large";
      break;
    case 451: 
      message = "Unavailable For Legal Reasons";
      break;
    ///Create server error responses
    case 500: 
      message = "Internal Server Error";
      break; 
    case 501:
      message = "Not Implemented";
      break;  
    case 502: 
      message = "Bad Gateway";
      break;  
    case 503: 
      message = "Service Unavailable";
      break; 
    case 504: 
      message = "Gateway Timeout";
      break; 
    case 505: 
      message = "HTTP Version Not Supported";
      break; 
    case 506: 
      message = "Variant Also Negotiates";
      break;  
    case 507: 
      message = "Insufficient Storage";
      break;  
    case 508: 
      message = "Loop Detected";
      break;  
    case 509: 
      message = "Unassigned";
      break;  
    case 510: 
      message = "Not Extended";
      break; 
    case 511: 
      message = "Network Authentication Required";
      break;    
  } 
  return message;      
}
