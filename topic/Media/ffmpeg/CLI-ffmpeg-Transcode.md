---
title: ffmpeg 转换逻辑分析
category:
 - [,"Media","ffmpeg"]
draft: true
url-root: CLI-ffmpeg-Transcode
date: 2023-06-08 19:16:05
tags:
---
`ffmpeg version: n6.0`

## transcode

核心函数 transcode























## vscode launch.json debug task config
```json
        {
            "name": "ffmpeg_g",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/ffmpeg_g",
            "args": [
                "-i",
                "${workspaceFolder}/extern/media/sample_960x400_ocean_with_audio.mp4",
                "-c:v",
                "h264",
                "${workspaceFolder}/extern/media/debug_out_ffmpeg_g.mp4",
            ],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/build",
            "environment": [
                {
                    "name": "LD_LIBRARY_PATH",
                    "value": "${env:LD_LIBRARY_PATH}:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libavcodec:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libavdevice:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libavfilter:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libavformat:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libavutil:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libpostproc:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libswresample:${workspaceFolder}/extern/ffmpeg-cmake/ffmpeg/libswscale"
                }
            ],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "将反汇编风格设置为 Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }
```
