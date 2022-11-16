# Ubuntu22.04 vscode GDB internal error
/build/gdb-wIRHdd/gdb-12.0.90/gdb/value.c:1731: internal-error: value_copy: Assertion `arg->contents != nullptr' failed.
https://github.com/microsoft/vscode-cpptools/issues/9135
https://github.com/microsoft/vscode-cpptools/issues/103#issuecomment-1151217772

    使用U22.10
or  
```bash
wget https://launchpad.net/ubuntu/+source/gdb/12.1-0ubuntu1/+build/23606376/+files/gdb_12.1-0ubuntu1_amd64.deb
sudo apt install ./gdb_12.1-0ubuntu1_amd64.deb
```