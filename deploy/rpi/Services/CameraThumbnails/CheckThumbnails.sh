#!/bin/bash

#IM_CONVERT="/mnt/host/d/Program Files/ImageMagick-7.1.1-Q16-HDRI/magick.exe"
IM_CONVERT=/usr/bin/convert
IMAGE_DIR=/var/ftp_data
MAX_DAYS=7

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
	    "$IM_CONVERT" $inputFile -thumbnail 200x200 -quality 80 $outputFile
	fi
    done;
}

cd $IMAGE_DIR
maxDate=$(date +%s)
echo "$maxDate"
#7 days
maxDate="$(($maxDate - $MAX_DAYS * 86400))"
echo "$maxDate"
formattedDate=$(date --date @"$maxDate")

for f in * ; do
    if [ -d "$f" ]; then
	fileDate=$(stat -c %Y $f)
	if (( fileDate < maxDate )); then
 	    echo "$f is older than $formattedDate: $fileDate"
	    echo "Removing old directory $f"
	    rm -r $f
	else
	    echo "Processing images in $f"
	    createThumbnails $f
	fi
    fi
done

echo "Finished"
