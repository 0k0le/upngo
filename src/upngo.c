// upngo func src...
#include "stdafx.h"
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define DIRECTORY_BUFFER_SIZE 1024
#define PROJECT_NAME_INDEX 0
#define PROJECT_SKELETON_DIR "/opt/upngo/skeleton"
#define MAX_DIR_LEVELS 12

// Project directory names
//static char *g_folders[] = {"bin", "bin-int", "external", "src", "bin/debug", "bin/release"};
static char *g_replace[] = {"*PRJNAME*"};

static char *find_replace(char *file_buffer, const char* before, const char* after) {
	char *ptr = NULL;
	U32 offset = 0;

	while((ptr = strstr(file_buffer + offset, before)) != NULL) {	
		offset = (ptr - file_buffer);

		if((file_buffer = strers(file_buffer, file_buffer + offset, strlen(before))) == NULL)
			return NULL;

		if((file_buffer = strins(file_buffer, file_buffer + (offset - 1), after)) == NULL)
			return NULL;
	}	

	return file_buffer;
}

BOOL init_upngo(p_upngo_info project_info, CCCSTR c_strProjectName) {
	project_info->c_strProjectName = (char *)ec_malloc(strlen(c_strProjectName) + 1);
	if(project_info->c_strProjectName == NULL)
		return FALSE;

	strcpy(project_info->c_strProjectName, c_strProjectName);

	return TRUE;	
}

void destroy_upngo(p_upngo_info project_info) {
	free(project_info->c_strProjectName);
}

// Creates directory structure, will shutdown process if any step fails
void create_directory_structure(const p_upngo_info project_info) {
	DIR *dir = NULL;
	struct dirent *directory = NULL;
	
	char write_directory[DIRECTORY_BUFFER_SIZE] = {0};	
	U32 level_page_save[MAX_DIR_LEVELS] = {0}; 
	for(U32 i = 0; i < ELEMENTSINARRAY(level_page_save); i++)
		level_page_save[i] = 0; 

	// Create project directory
	if(mkdir(project_info->c_strProjectName, 0755) == -1)
		ERRQ("Failed to create project directory");

	// Navigate into directory
	if(chdir(project_info->c_strProjectName) == -1)
		ERRQ("Failed to navigate into project directory");

	// Record project directory
	if(getcwd(write_directory, DIRECTORY_BUFFER_SIZE) == NULL)
		ERRQ("Failed to get CWD");

	strcat(write_directory, "/");

	chdir(PROJECT_SKELETON_DIR);

	// Open handle to skeleton dir
	if((dir = opendir("./")) == NULL)
		ERRQ("Failed to open project skeleton directory");

	DEBUG("Project Base Directory: %s", write_directory);

	register int dir_level = 0;

	// Navigate directory structure
	do {
		// No more objects in current directory
		if((directory = readdir(dir)) == NULL) {
			dir_level--;
			
			closedir(dir);
			chdir("../");
			if((dir = opendir("./")) == NULL)
				ERRQ("Failed to open directory!\n");

			for(U32 i = 0; i < level_page_save[dir_level] + 1; i++)
				readdir(dir);

			char *ptr = &write_directory[strlen(write_directory)] - 2;
			while(ptr > write_directory && *ptr != '/')
				ptr--;

			*(ptr + 1) = 0;
			
				
		} else if(strcmp(directory->d_name, ".") != 0 && strcmp(directory->d_name, "..") != 0) {
			// Found valid directory
			if(directory->d_type == DT_DIR) {
				//DEBUG("OBJ: %s", directory->d_name);

				char temp[512] = {0};
				sprintf(temp, "%s/", directory->d_name);

				strcat(write_directory, temp);

				DEBUG("%s", write_directory);
				if(mkdir(write_directory, 0755) == -1)
					ERRQ("Failed to write to directory!");

				dir_level++;
				closedir(dir);
				if(chdir(directory->d_name) == -1)
					ERRQ("Failed to change directory");
				if((dir = opendir("./")) == NULL)
                                	ERRQ("Failed to open directory!\n");
			} else if(directory->d_type == DT_REG) {
				char *file_buf = NULL;
				int fd = 0;
				int temp_fd = 0;				

				// Open file
				if((fd = open_file_buffer(directory->d_name, FALSE, &file_buf)) == -1)
					ERRQ("FATAL ERROR");


				if(get_file_length(fd, 0) > 1) {
					DEBUG("WRITING FILE: %s", directory->d_name);
					if((file_buf = find_replace(file_buf, g_replace[PROJECT_NAME_INDEX], project_info->c_strProjectName)) == NULL)
						ERRQ("Failed to replace string!");

					char file_directory_write[DIRECTORY_BUFFER_SIZE + 1024] = {0};
					sprintf(file_directory_write, "%s%s", write_directory, directory->d_name);

					if((temp_fd = open(file_directory_write, O_CREAT | O_WRONLY, 0666)) == -1)
						ERRQ("Failed to create file!");

					if(write(temp_fd, file_buf, strlen(file_buf)) == -1)
						ERRQ("Failed to write file!");

					close(temp_fd);
				}
				
				close(fd);
				free(file_buf);
							
			}
		}

		level_page_save[dir_level]++;	
	} while(dir_level >= 0);

	closedir(dir);	
}











