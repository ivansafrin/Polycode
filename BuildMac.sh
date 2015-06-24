#!/bin/sh
#
# A complete build script for Polycode on Mac OS X
# Author: Mark Austin <ganthore@gmail.com>
#
# Make sure you have the following libraries and tools installed prior to running a build
# Xcode
# py-ply
# pkgconfig
# cmake
#
# With macports you can easily install most of the needed libs with the following command:
# sudo port install py-ply pkgconfig cmake
#

# Note: Building with macports versions will require changing your python version to the macports version
# so that the lua binding build
# sudo port select python python27

#
# Start
#

#
# Validate that the build command exited cleanly
#
function validate(){
	if [ $? -eq 0 ]; then
	    echo "[INFO] Build command executed successfully."
	else
	    echo "[ERROR] One of the build commands failed!"
		exit 1
	fi
}

function cleanup(){
	# Do not remove this by default since it takes a while to download stuff
	# if [ -d Dependencies/Build ]; then
	# 	rm -fr Dependencies/Build
	# 	echo "[INFO] Removed previous Dependencies/Build folder."
	# fi

	if [ -d Build ]; then
		rm -fr Build
		echo "[INFO] Removed previous Build folder."
	fi

	if [ -d Standalone/Build ]; then
		rm -fr Standalone/Build
		echo "[INFO] Removed previous Standalone/Build folder."
	fi
}

#
# Cleanup
#
cleanup

#
# Build debug and release static dependencies
#
mkdir -p Dependencies/Build
cd Dependencies/Build
cmake -G Xcode ..
validate
xcodebuild -target ALL_BUILD -configuration Debug
validate
xcodebuild -target ALL_BUILD -configuration Release
validate
cd ../../

#
# Build polycode player and bindings
#
mkdir -p Build
cd Build
cmake -G Xcode .. -DPOLYCODE_BUILD_BINDINGS=1 -DPOLYCODE_BUILD_PLAYER=1
validate
xcodebuild -DPOLYCODE_BUILD_BINDINGS=1 -DPOLYCODE_BUILD_PLAYER=1 -target ALL_BUILD -configuration Debug
validate
xcodebuild -target PolycodeLua -configuration Debug
validate
xcodebuild -target install -configuration Debug
validate
xcodebuild -DPOLYCODE_BUILD_BINDINGS=1 -DPOLYCODE_BUILD_PLAYER=1 -target ALL_BUILD -configuration Release
validate
xcodebuild -target PolycodeLua -configuration Release
validate
xcodebuild -target install -configuration Release
validate
cd ../

#
# Build standalone
#
mkdir -p Standalone/Build
cd Standalone/Build
cmake -G "Unix Makefiles" ..
validate
make install
validate
cd ../../

#
# Build IDE
#
cd IDE/Build/Mac\ OS\ X/
xcodebuild
validate

#
# End
#
exit 0
