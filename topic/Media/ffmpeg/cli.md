---
categories: ["ffmpeg","CLI"]
title: "ffmpeg commands"
date: 2023-03-15T10:45:48+08:00
draft: false
include_toc: true
---
doc: [https://ffmpeg.org/ffmpeg.html](https://ffmpeg.org/ffmpeg.html)

### Convert audio stream to raw pcm
destination audio format: PCM S16 48000 STERO 
```bash
ffmpeg -i Sample_BeeMoved_48kHz16bit.m4a -ar 48000  -ac 2 -vn -f s16le   audio_sample_ar48_sf16_ac2.pcm
```