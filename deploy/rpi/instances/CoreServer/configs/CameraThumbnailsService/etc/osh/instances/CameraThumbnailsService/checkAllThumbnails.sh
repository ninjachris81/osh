#!/bin/bash

# Front Door
IMAGE_DIR=/var/ftp_data/frontDoor/images
VIDEO_DIR=/var/ftp_data/frontDoor/videos
MAX_DAYS_IMAGE=7
MAX_DAYS_VIDEO=14

./checkThumbnails.sh $IMAGE_DIR $VIDEO_DIR $MAX_DAYS_IMAGE $MAX_DAYS_VIDEO

# Backyard
IMAGE_DIR=/var/ftp_data/backyard/images
VIDEO_DIR=/var/ftp_data/backyard/videos
MAX_DAYS_IMAGE=7
MAX_DAYS_VIDEO=14

./checkThumbnails.sh $IMAGE_DIR $VIDEO_DIR $MAX_DAYS_IMAGE $MAX_DAYS_VIDEO