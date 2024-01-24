
# rule guide

    since 

# cur key set

```json
// 将键绑定放在此文件中以覆盖默认值auto[]
[
    {
        "key": "ctrl+k ctrl+f",
        "command": "editor.action.formatDocument.none",
        "when": "editorTextFocus && !editorHasDocumentFormattingProvider && !editorReadonly"
    },
    {
        "key": "shift+alt+f",
        "command": "-editor.action.formatDocument.none",
        "when": "editorTextFocus && !editorHasDocumentFormattingProvider && !editorReadonly"
    },
    {
        "key": "f5",
        "command": "cmake.debugTarget",
        "when": "cmake:enableFullFeatureSet && inCMakeProject && !cmake:hideDebugCommand && !inDebugMode"
    },
    {
        "key": "ctrl+k ctrl+k",
        "command": "bookmarks.toggle",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+k",
        "command": "-bookmarks.toggle",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+m ctrl+m",
        "command": "editor.action.toggleMinimap"
    },
    {
        "key": "alt+b",
        "command": "cmake.configure"
    },
    {
        "key": "alt+e",
        "command": "workbench.action.switchWindow"
    },
    {
        "key": "ctrl+alt+s",
        "command": "workbench.action.files.saveAll"
    },
    {
        "key": "ctrl+k ctrl+n",
        "command": "bookmarks.jumpToPrevious",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+j",
        "command": "-bookmarks.jumpToPrevious",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+k ctrl+m",
        "command": "bookmarks.jumpToNext",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+alt+l",
        "command": "-bookmarks.jumpToNext",
        "when": "editorTextFocus"
    },
    {
        "key": "ctrl+oem_1",
        "command": "workbench.action.terminal.toggleTerminal",
        "when": "terminal.active"
    },
    {
        "key": "ctrl+oem_3",
        "command": "-workbench.action.terminal.toggleTerminal",
        "when": "terminal.active"
    },
    {
        "key": "ctrl+numpad9",
        "command": "workbench.action.quickOpenTerm"
    },
    {
        "key": "alt+oem_4",
        "command": "editor.action.previousMatchFindAction",
        "when": "findInputFocussed"
    },
    {
        "key": "alt+oem_6",
        "command": "editor.action.nextMatchFindAction",
        "when": "editorFocus && findInputFocussed"
    },
    {
        "key": "enter",
        "command": "-editor.action.nextMatchFindAction",
        "when": "editorFocus && findInputFocussed"
    },
    {
        "key": "f2 right",
        "command": "workbench.action.splitEditorToRightGroup"
    },
    {
        "key": "f2 left",
        "command": "workbench.action.splitEditorToLeftGroup"
    },
    {
        "key": "f2 up",
        "command": "workbench.action.splitEditorUp"
    },
    {
        "key": "f2 down",
        "command": "workbench.action.splitEditorDown"
    },
    {
        "key": "f1 n",
        "command": "welcome.showNewFileEntries"
    },
    {
        "key": "ctrl+alt+win+n",
        "command": "-welcome.showNewFileEntries"
    }
]
```