
if [ -f ~/.bash_sysinit ]; then
	    . ~/.bash_sysinit
fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
	    PATH="$HOME/bin:$PATH"
fi

if [ -f ~/.bash_ubuntu_desktop ]; then
	    . ~/.bash_ubuntu_desktop
fi

gui(){
    start-desktop.sh 
}

# To use Visual Studio Code with the Windows Subsystem for Linux, please install Visual Studio Code in Windows and uninstall the Linux version in WSL. You can then use the `code` command in a WSL terminal just as you would in a normal command prompt.
# Do you want to continue anyway? [y/N] y
# To no longer see this prompt, start Visual Studio Code with the environment variable DONT_PROMPT_WSL_INSTALL defined.
export DONT_PROMPT_WSL_INSTALL=

alias code=/usr/bin/code

