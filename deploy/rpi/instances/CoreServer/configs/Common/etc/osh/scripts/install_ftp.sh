#!/bin/bash

set -e

sudo apt-get install vsftpd -y

sudo useradd ftp_user

sudo passwd ftp_user

#sudo mkhomedir_helper ftp_user