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

/** This function gets the response from the server.
 * @author Eli Smith
 * @param[in] url - The string to copy (char *)
 * @test server_response("https://example.com/") --> 200 OK
 * @test server_response("https://google.com/") --> 404 Not Found
 * @date 04/05/2019
*/
void server_response(char *url)
{
  ///Start a libcurl easy session 
  CURL *curl = curl_easy_init();

  ///Check if curl is not null
  if(curl) {

    CURLcode res;

    ///Set the options for the curl easy handle
    curl_easy_setopt(curl, CURLOPT_URL, url);
    ///Url is redirected, so we tell libcurl to follow redirection
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    ///Perform the download request without getting the body content
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    ///Use curl_easy_perform to perform the entire request 
    res = curl_easy_perform(curl);

    ///Check if there is no errors
    if(res == CURLE_OK) {
      
      ///Create a variable to hold the response code
      long response_code;

      ///Use curl handle to extract information
      res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      ///Print the url and the resulting response
      printf("%s %ld %s\n", url, response_code, response_message(response_code));
    }
    ///Terminate the libcurl easy handle
    curl_easy_cleanup(curl);
  } else {
    printf("An error occured");
    exit(EXIT_FAILURE);
  }
}