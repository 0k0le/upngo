#ifndef __FUNC_H
#define __FUNC_H

// Much needed functions
#include "types.h"

extern U32 get_file_length(int fd, U32 cur_file_pos);
extern int open_file_buffer(CCCSTR file_name, BOOL writeable, char ** buf);
extern void *ec_malloc(U32 bytes);
extern char* strers(char *base_ptr, const char *ins_ptr, U32 erase_len);
extern char* strins(char *base_ptr, const char *ins_ptr, const char* const new_str);

#endif
