---
categories: 
 - [,"Media","ffmpeg"]
 - ["CLI"]
title: "ffmpeg commands"
date: 2023-03-15T10:45:48+08:00
draft: false
include_toc: true
---
doc: [https://ffmpeg.org/ffmpeg.html](https://ffmpeg.org/ffmpeg.html)

## Utils

### stream_specifier


### Convert audio stream to raw pcm
destination audio format: PCM S16 48000 STERO 
```bash
ffmpeg -i Sample_BeeMoved_48kHz16bit.m4a -ar 48000  -ac 2 -vn -f s16le   audio_sample_ar48_sf16_ac2.pcm
```

### selecting streams
```
-map [-]input_file_id[:stream_specifier][?] | [linklabel] (output)
```
Create one or more streams in the output file. This option has two forms for specifying the data source(s): 
  the first selects one or more streams from some input file (specified with -i)
  the second takes an output from some complex filtergraph (specified with -filter_complex or -filter_complex_script).
```bash
# follow are equaled
ffmpeg -i vaa.mp4  -i a.mp3 -map 0:0 -map 0:1 -map 0:2 -map 1:0  merged.mp4
ffmpeg -i vaa.mp4  -i a.mp3 -map 0                     -map 1:0  merged.mp4
ffmpeg -i vaa.mp4  -i a.mp3 -map 0:v -map 0:a          -map 0:a  merged.mp4
```
