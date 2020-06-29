// Much needed functions
#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

U32 get_file_length(int fd, U32 cur_file_pos);
int open_file_buffer(CCCSTR file_name, BOOL writeable, char ** buf);
void *ec_malloc(U32 bytes);
char* strers(char *base_ptr, const char *ins_ptr, U32 erase_len);
char* strins(char *base_ptr, const char *ins_ptr, const char* const new_str);

// Erase section of string and shrink buffer
char* strers(char *base_ptr, const char *ins_ptr, U32 erase_len) {
        char *new = NULL;
        U32 start_len = 0, end_len = 0;

        // data needed for ptr arithmatic
        start_len = ins_ptr - base_ptr;
        end_len = strlen(ins_ptr) - erase_len;

        // Allocate memory for new string
        if((new = (char *)ec_malloc(start_len + end_len + 1)) == NULL)
                return NULL;

        // Copy data
        memcpy(new, base_ptr, start_len);
        memcpy(new + start_len, base_ptr + start_len + erase_len, end_len);

        // Free old data
        free(base_ptr);

        return new;
}

// Insert string into string
char* strins(char *base_ptr, const char *ins_ptr, const char* const new_str) {
        char *new_buf = NULL;
        U32 start_len = 0, end_len = 0, new_str_len = 0, total_len = 0;

        // Calculate start and end lengths
        start_len = (ins_ptr - base_ptr) + 1;
        end_len = strlen(ins_ptr) - 1;
        new_str_len = strlen(new_str);
        total_len = start_len + end_len + new_str_len;

        // Allocate space for new buffer
        if((new_buf = (char *)ec_malloc(total_len + 1)) == NULL)
                return NULL;

        // Copy into new buffer
        memcpy(new_buf, base_ptr, start_len);
        memcpy(new_buf + start_len, new_str, new_str_len);
        memcpy(new_buf + start_len + new_str_len, base_ptr + start_len, end_len);

        // Free old data and return new buffer
        free(base_ptr);

        return new_buf;
}

U32 get_file_length(int fd, U32 cur_file_pos) {
	lseek(fd, 0, SEEK_SET);
	U32 len = lseek(fd, 0, SEEK_END);
	lseek(fd, cur_file_pos, SEEK_SET);	
	
	return len;
}

int open_file_buffer(CCCSTR file_name, BOOL writeable, char ** buf) {
	int fd = 0;
	int flag = O_RDONLY;
	U32 file_len = 0;

	// If you want file descriptor to be writeable
	if(writeable == TRUE)
		flag = O_RDWR;

	// open file
	if((fd = open(file_name, flag)) == -1)
		return -1;

	file_len = get_file_length(fd, 0);

	if((*buf = (char *)ec_malloc(file_len + 1)) == NULL)
		return -1;

	if(read(fd, *buf, file_len) == -1)
		return -1;

	return fd;
}

void *ec_malloc(U32 bytes) {
	void *ptr = NULL;
	if((ptr = malloc(bytes)) == NULL)
		return NULL;

	memset((char *)ptr, 0, bytes);

	return ptr;
}
