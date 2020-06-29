// upngo - Project creation utility

// Updates added upon recommendation
// Currently only supports c/c++

// Matthew Todd Geiger
// Jun 24 05:30

// Standard header
#include "stdafx.h"
#include "upngo.h"

int main(const int argc, const char** const argv, const char** const envp) {
	UNUSED(envp);

	if(argc < 2)
		USAGE(argv[0], "<PROJECTNAME>");

	printf("Creating project...\n");

	upngo_info project_info = {0};
	CCCSTR c_strProjectName = (CCCSTR)argv[1];

	if(init_upngo(&project_info, (CCCSTR)c_strProjectName) != TRUE)
		ERRQ("Failed to initialize upngo");

	DEBUG("Project Name: %s", project_info.c_strProjectName);

	create_directory_structure(&project_info);	

	destroy_upngo(&project_info);		

	return 0;
}
