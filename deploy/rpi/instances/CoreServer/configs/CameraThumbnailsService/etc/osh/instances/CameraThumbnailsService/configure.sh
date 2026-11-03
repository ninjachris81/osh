#!/bin/bash

set -euo pipefail

systemctl enable CameraThumbnailsService.timer
systemctl start CameraThumbnailsService.timer