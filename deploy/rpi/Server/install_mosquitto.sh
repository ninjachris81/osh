sudo apt-get install -y mosquitto
sudo mkdir /etc/mosquitto
sudo touch /etc/mosquitto/mosquitto.conf
sudo echo -e "bind_address 0.0.0.0\nallow_anonymous true" >> /etc/mosquitto/mosquitto.conf
sudo service mosquitto restart
