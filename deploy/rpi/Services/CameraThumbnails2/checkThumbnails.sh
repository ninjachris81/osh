#!/bin/bash

IMAGE_DIR=/var/ftp_data/backyard/images
VIDEO_DIR=/var/ftp_data/backyard/videos
MAX_DAYS_IMAGE=30
MAX_DAYS_VIDEO=30

scripts/checkThumbnails.sh $IMAGE_DIR $VIDEO_DIR $MAX_DAYS_IMAGE $MAX_DAYS_VIDEO