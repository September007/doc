#refer
https://code.visualstudio.com/docs/cpp/launch-json-reference

# example

```json
{
    "configurations": [
        {
            "type": "cppdbg",
            "name": "debug foo.g",
            "request": "launch",
            "cwd": ".",
            "debugServerArgs": "-s foo.debug",
            "linux": {
                "MIMode": "gdb",
                "miDebuggerPath": "/usr/bin/gdb",
                "program": "${workspaceRoot}/src/debug-symbol/foo.g",
                "sourceFileMap":{
                    "/mnt/c":"/balah/balah"
                }
            },
            "windows": {
                "program": "${workspaceRoot}/src/debug-symbol/foo.exe"
            },
            "symbolLoadInfo": {
                "loadAll": true,
                "exceptionList": ""
            }
        },
        {
            "type": "cppdbg",
            "name": "debug foo.g.strip-all.with-debug-link",
            "program": "${workspaceFolder}/src/debug-symbol/foo.g.strip-all.with-debug-link",
            "request": "launch",
            "cwd": "."
        }
    ],
"version": "0.2.0"
}
```

# launchCompleteCommand

# Debugging dump files

# sourceFileMap

# debugServerArgs

pass args to debugger
like

# note

program : need specify **full path** of executable file, use ${workspaceFolder} for it
