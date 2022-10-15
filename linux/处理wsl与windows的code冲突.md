#

原生code使用wsl的code
```bash
# ~/.profile
alias code=/usr/bin/code
# 使用软链接使用windows code, 
ln -s "/mnt/c/Users/lull/AppData/Local/Programs/Microsoft VS Code/bin/code" wcode
```