UPNGO - Project generation

Version 1.0:
	- Create skeleton directory in /opt/upngo(check example);
	- upngo <PROJECTNAME> will create a project based on the skeleton directory
	
BUILD:
	make release
	sudo make install

Details:
	upngo project creation utility will copy the project skeleton in /etc/upngo

File template variables:
	*PRJNAME* = Project Name

Usage:
	upngo <PROJECT_NAME>
