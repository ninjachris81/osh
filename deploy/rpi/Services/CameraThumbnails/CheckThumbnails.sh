#!/bin/bash

# must be run in image base folder

IM_CONVERT="/mnt/host/d/Program Files/ImageMagick-7.1.1-Q16-HDRI/magick.exe"

function createThumbnails {
    local dir="$1/images"
    local thumbnailDir="$dir/thumbnails"
    if [ ! -d "$thumbnailDir" ]; then
	echo "Creating thumbnails in $dir"
	mkdir $thumbnailDir
    fi
    
    for imageFile in $dir/*.jpg; do
	local inputFile="$imageFile"
	local outputFile="$dir/thumbnails/$(basename $imageFile)"
	echo "$inputFile -> $outputFile"
	if [ -f $outputFile ]; then
	    echo "Thumbnail exists"
	else
	    "$IM_CONVERT" convert $inputFile -thumbnail 200x200 -quality 80 $outputFile
	fi
    done;
}

maxDate=$(date +%s)
echo "$maxDate"
#7 days
maxDate="$(($maxDate - 604800))"
echo "$maxDate"
formattedDate=$(date --date @"$maxDate")

for f in * ; do
    if [ -d "$f" ]; then
	fileDate=$(stat -c %Y $f)
	if (( fileDate < maxDate )); then
 	    echo "$f is older than $formattedDate: $fileDate"
	    echo "Removing old directory $f"
	    #rmdir $f
	else
	    echo "Processing images in $f"
	    #createThumbnails $f
	fi
    fi
done
