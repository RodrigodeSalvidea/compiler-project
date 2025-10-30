#include "./nextChar.h"
#include "../include/logging.h"
//something odd happened here


char file_buffer[BUFFER_LENGTH * 2];
int last_content_index = -1;
bool terminated = false;
int content_index;
unsigned long int max_file_index = 0;
unsigned long int current_file_index = 0;
void nextChar(int inFD, char *char_ptr){

  int bytes_read;
  if (terminated){
	*char_ptr = file_buffer[content_index++];
	content_index %= (2*BUFFER_LENGTH);
	if (content_index >= last_content_index){
		*char_ptr = -1;
	}
	return;
  }

  if ((content_index % BUFFER_LENGTH) == 0 && (current_file_index == max_file_index)){
	bytes_read = read(inFD, file_buffer + content_index,BUFFER_LENGTH); 
	if (bytes_read < BUFFER_LENGTH){
		assert(bytes_read >= 0 && "reading the input encountered some error");
		terminated = true;
		last_content_index = bytes_read;
	}
  }

  *char_ptr = file_buffer[content_index++];
  content_index%= (2 * BUFFER_LENGTH);
  current_file_index++;
  max_file_index = current_file_index > max_file_index ? current_file_index : max_file_index;
  return;
}

void rollBack(){
  current_file_index--;
  content_index = content_index - 1;
  content_index = (content_index >= 0) ? content_index : 2*BUFFER_LENGTH +  content_index;
}
