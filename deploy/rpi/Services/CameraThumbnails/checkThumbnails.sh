#!/bin/bash

#IM_CONVERT="/mnt/host/d/Program Files/ImageMagick-7.1.1-Q16-HDRI/magick.exe"
IM_CONVERT=/usr/bin/convert
FFMPEG_CMD=/usr/bin/ffmpeg

IMAGE_DIR=/var/ftp_data/images
VIDEO_DIR=/var/ftp_data/videos
MAX_DAYS_IMAGE=7
MAX_DAYS_VIDEO=14

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

function createVideoThumbnails {
    local dir="$1/videos"
    local thumbnailDir="$dir/thumbnails"
    if [ ! -d "$thumbnailDir" ]; then
		echo "Creating thumbnails in $dir"
		mkdir $thumbnailDir
    fi

    for imageFile in $dir/*.mp4; do
		local inputFile="$imageFile"
		local outputFile="$dir/thumbnails/$(basename $imageFile)"
		echo "$inputFile -> $outputFile"
		if [ -f $outputFile ]; then
			echo "Thumbnail exists"
		else
			"$FFMPEG_CMD" -i $inputFile -ss 00:00:01.000 -frames:v 1 $outputFile
			"$IM_CONVERT" $outputFile -thumbnail 200x200 -quality 80 $outputFile
		fi
    done;
}

function processImages {
	cd $IMAGE_DIR
	maxDate=$(date +%s)
	echo "$maxDate"
	#7 days
	maxDate="$(($maxDate - $MAX_DAYS_IMAGE * 86400))"
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
}

function processVideos {
	cd $VIDEO_DIR
	maxDate=$(date +%s)
	echo "$maxDate"
	#14 days
	maxDate="$(($maxDate - $MAX_DAYS_VIDEO * 86400))"
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
			createVideoThumbnails $f
		fi
		fi
	done
}

processImages
processVideos

echo "Finished"
