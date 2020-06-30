// upngo source linkage...
#include "upngo_types.h" 

extern BOOL init_upngo(p_upngo_info project_info, CCCSTR c_strProjectName);
extern void destroy_upngo(p_upngo_info project_info);

// Creates directory structure of project - Automatically error checked/handled
extern void create_directory_structure(const p_upngo_info c_strProjectName); 
