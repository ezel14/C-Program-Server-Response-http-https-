#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h> 
#include "header_task6_es.h"

void server_response(char *url);

int main(void)
{   
  ///Create a const char string for "http"
  const char STRING_START[] = "http";
  ///Create an integer size
  int SIZE = 100;
  ///Initialize a counter for the amount of urls
  int i = 0;
  ///Initialize a pointer for the url
  char *url = NULL;
  ///Initialize a pointer for the urls and allocate memory 
  char **urls = calloc(sizeof(char*), SIZE);
  
  ///Use a While loop to read and allocate memory for the urls
  while((url = read_formatted_input(stdin)) != NULL) {  
    urls[i] = url;
    i++;
	  ///Check if i is equal to SIZE before reallocating
    if(i == SIZE) {
      SIZE = SIZE*2;
      urls = realloc(urls, sizeof(char*)* SIZE);
    }
  }  
  ///Use a for loop to loop over the urls
  for(size_t j = 0; j < i; j++) {
    ///Check if there is STRING_START in urls[j] before passing to the function
    if(str_n_str_es(urls[j], STRING_START) != NULL) {
      ///Pass in the url one at a time to the server_response function
      server_response(urls[j]);  
      free(urls[j]);    
    }
  } 
  ///Free the pointer
  free(urls);
}
