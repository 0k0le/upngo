#!/bin/sh

PROJECTNAME=upngo
PROJECTDIR=$HOME/dev/$PROJECTNAME

# Run debug executable
$PROJECTDIR/bin/debug/$PROJECTNAME $*
