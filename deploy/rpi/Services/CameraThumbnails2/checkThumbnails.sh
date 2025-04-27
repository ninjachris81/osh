#!/bin/bash

IMAGE_DIR=/var/ftp_data/images
VIDEO_DIR=/var/ftp_data/videos
MAX_DAYS_IMAGE=7
MAX_DAYS_VIDEO=14

scripts/checkThumbnails.sh $IMAGE_DIR $VIDEO_DIR $MAX_DAYS_IMAGE $MAX_DAYS_VIDEO