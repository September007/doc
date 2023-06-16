---
title: ffmpeg source tips
category:
  - [Media,ffmpeg]
draft: true
url-root: tips
date: 2023-06-01 23:07:55
tags:
---

## ffprobe

ffprobe 输出包的顺序仅仅是 av_read_frame 的顺序
```cpp
// ffprobe.c main::probe_file::read_packets::read_interval_packets 
while (!av_read_frame(fmt_ctx, pkt)) {
  show_packet(w, ifile, pkt, i++);
}
```
但这不一定是是 数据包在文件中的顺序，因为某些流需要parser，parser在输出包（这个行为发生在 av_read_frame 内部）之前，需要获取到下一个同流的包（在demux结束之前）。所以如果有需要parse的流存在的话，输出的包顺序和实际包的顺序就可能不太一样
