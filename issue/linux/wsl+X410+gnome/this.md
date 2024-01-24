
#refer 
[online doc](https://x410.dev/cookbook/wsl/running-ubuntu-desktop-in-wsl2/)

after this, add following to ~/.profile
```bash
gui(){
    start-desktop.sh 
}

```

# auto set

```bash
# copy files
echo "xxxx"|sudo -Svp ""

cp .bash_sysinit .bash_ubuntu_desktop ~
cp start-desktop.sh start-from-wsl-cmd.bash ~/bin

cat .bashrc.more.bash >>~/.profile

echo "
export DISPLAY=$(ip route | grep default | awk '{print $3; exit;}'):0.0" >> ~/.profile

# install package
sudo apt update && sudo apt -y upgrade
sudo apt install ubuntu-gnome-desktop default-jre libreoffice-java-common
mkdir -p ~/Desktop ~/Documents ~/Downloads ~/Music ~/Pictures ~/Public ~/Videos
mkdir ~/bin


sudo -k
```