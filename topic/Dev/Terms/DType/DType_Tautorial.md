---
title: DType Super Tautorial (DType Standard Engine)
category:
  - [Dev,DType]
draft: true
typora-root-url: DType Super Tautorial
date: 2023-05-19 17:38:36
tags:
---

此章介绍使用DType绘制字体，并介绍排版方法

## DType 渲染引擎 
  [Home](https://www.d-type.com/page/about)
  一套高性能和便携式软件库，用于渲染高质量文本和分辨率无关的可扩展二维图形

绘制字体流程大致如下

 1. 创建引擎实例
 2. 加载字体
 3. 加载字形信息
 4. 绘制
 5. 排版


## 1. 创建引擎实例

调用dtEngineIniViaStream 时，提供的 DT_STREAM有点讲究
  虽然只指定了 dtype.inf ，但是该文件中指定了其他的好些依赖文件
```text
// config/dtype.inf
{
0,system/ini/dtype.fls
0,system/ini/dtype.pat
0,system/ini/gs256.gsl
}
```
**这些依赖文件的路径都是相对路径，所以要求 copy这些文件到指定位置, 不然会初始化失败的**

```cpp  
  DT_SWORD dtEngineIniViaStream(DT_DTENGINE* engine, const DT_STREAM_DESC* sd, DT_INIT_INFO* init_info);

  DT_STREAM(sd_ini,"config/dtype.inf")
  stdout = fopen("/dev/null", "w");
  auto init_ret = dtEngineIniViaStream(&ret, &sd_ini, DV_NULL);
  fclose(stdout);
  stdout = oldStdOut;
```


## 2. 加载字体

```cpp
DT_ID_SWORD dtFontAddViaStream(DT_DTENGINE engine, DT_ID_SWORD font_format_id, const DT_CHAR* fuid, DT_SWORD fcnr, DT_ID_SWORD cmap_id, DT_ID_UBYTE caching, DT_ID_UBYTE hinting, const DT_STREAM_DESC* sd);
DT_SWORD dtFontGetMetrics(DT_DTENGINE engine, DT_ID_SWORD font_index, DT_UWORD* font_xbs, DT_UWORD* font_ybs, DT_RECT_SWORD* extent);
```
  添加字体之后，一般返回值都是 ok的 引擎的字体目录索引，问题是加载不一定成功，等到 绘制时拿到的就是 0值的 advance 和 extent，实际是失败了
  所以 加载完字体之后需要检查 该字体（加载结果）的字体信息（metrics）以检查实际 成功与否, 这便用上了 [`dtFontGetMetrics`](#字体基本信息)

  加载 字体时，主要有个参数需要理解的是 font_format_id:
```text
0 (DV_FONT_DTYPE) — for D-Type fonts (.dtf)
3 (DV_FONT_OPENTYPE_TTF) — for TrueType/OpenType fonts (.ttf/.otf) and font collections (.ttc) with TrueType outlines
5 (DV_FONT_OPENTYPE_CFF) — for OpenType (.otf) fonts and font collections (.ttc) with Type 2/CFF outlines
8 (DV_FONT_TYPE1) — for Adobe Type 1 fonts (.pfb or .pfa)
12 (DV_FONT_PSTYPE3) — for Adobe Type 3 PostScript fonts (.ps)
16 (DV_FONT_BARECFF) — for Bare CFF fonts (.cff)
```

加载字体时匹配字体后缀，尝试按某些 font_format_id 加载
configs 是 无构造开销的静态数据
```cpp
int Helper::DT::DTLoadFont(DT_DTENGINE engine, const char *font_path, int font_type_hint)
{
#define DTYPE        "\u0000"
#define OPENTYPE_TTF "\u0003"
#define OPENTYPE_CFF "\u0005"
#define TYPE1        "\u0008"
#define PSTYPE3      "\u000c"
#define BARECFF      "\u0010"
    struct
    {
        const char *const suffix;
        const char       *candiates;
    } static const configs[] = {
        {".cff", BARECFF OPENTYPE_CFF OPENTYPE_TTF},
        {".ps",  PSTYPE3                          },
        {".pfb", TYPE1                            },
        {".pfa", TYPE1                            },
        {".otf", OPENTYPE_CFF OPENTYPE_TTF        },
        {".ttc", OPENTYPE_CFF OPENTYPE_TTF        },
        {".ttf", OPENTYPE_TTF                     },
        {".dtf", DTYPE                            }
    };

    int font_index = -1;
    for (auto &config : configs)
    {
        if (font_index == -1 && strlen(config.suffix) <= strlen(font_path) &&
            !strcmp(config.suffix, font_path + (strlen(font_path) - strlen(config.suffix))))
        {
            std::vector<int> candiates;
            if (font_type_hint > 0)
                candiates.push_back(font_type_hint);
            candiates.insert(candiates.end(), config.candiates, config.candiates + strlen(config.candiates));
            for (auto font_format_id : candiates)
            {
                DT_STREAM_FILE(sd_font, font_path);
                font_index = dtFontAddViaStream(engine, font_format_id, NULL, 0, -1, 0, 1, &sd_font);
                if (font_index != -1)
                {
                    DT_UWORD      font_xbs, font_ybs;
                    DT_RECT_SWORD extent;
                    int           result = dtFontGetMetrics(engine, font_index, &font_xbs, &font_ybs, &extent);
                    if (1 != result)
                    {
                        dtFontRemove(engine, font_index);
                        font_index = -1;
                    }
                    else
                        break;
                }
            }
        }
    }
    return font_index;
}
```

## 3. 加载字形信息
```cpp
DT_SWORD dtGlyphGetMetricsPlus(DT_DTENGINE engine, DT_ID_SWORD font_index, DT_ID_ULONG glyph_index, DT_ADVANCE* advance, DT_RECT_SWORD* extent, DT_SWORD reserved);
DT_SWORD dtCharGetMetricsPlus(DT_DTENGINE engine, DT_ID_SWORD font_index, DT_ID_ULONG char_code, DT_ADVANCE* advance, DT_RECT_SWORD* extent, DT_SWORD reserved);
DT_ID_ULONG dtFontGetGlyphIndex(DT_DTENGINE engine, DT_ID_SWORD font_index, DT_ID_ULONG char_code);
```
字符: char 
字形: glyph

字符 对应一个字形(`dtFontGetGlyphIndex`)，但是 `glyph` 还可以表示 非字符的 图形
所以此处使用字形来指代更一般的 绘制目标


字形信息主要是 步长, 字形范围矩形框
* `步长`: 建议的 字体占用矩形大小(至少会拿到占用长度)
* `字形范围矩形框`:  说明字形像素实际触及的 最左、最右、最上、最下 的横纵坐标值
可视化观察这些参数的实际意义 见[排版](#5排版)

#### dtCharGetMetricsPlus
| Parameter     | Description                                                  |
| ------------- | ------------------------------------------------------------ |
| *engine*      | Handle of the previously created Standard Engine instance.   |
| *font_index*  | Font index of the font or font instance in the Font Catalog. |
| *char_code*   | Unicode character code of the glyph.                         |
| *glyph_index* | Font dependent index of the glyph.                           |
| *advance*     | A pointer to the DT_ADVANCE structure that will receive the horizontal and vertical origin, advance width and advance height of the glyph in font units.However, if you do not wish to receive this information, you may set the *advance* pointer to DV_NULL. Otherwise, this must be a valid pointer to the DT_ADVANCE structure. |
| *extent*      | A pointer to the DT_RECT_SWORD  structure that will receive the glyph's extent. This is the minimum (x, y) and maximum (x, y) coordinate for the glyph in font units. If you do not wish to receive this information, you may set the *extent* pointer to DV_NULL. Otherwise, this must be a valid pointer to the DT_RECT_SWORD structure.See the comments below for additional details. |


## 4. 绘制
```cpp
DT_SWORD dtOutputSetAsMDC(DT_DTENGINE engine, DT_ID_SWORD format, DT_ID_SWORD subformat, const DT_MDC* memory_surface, DT_SWORD clip_x, DT_SWORD clip_y, DT_SWORD clip_w, DT_SWORD clip_h);
DT_SWORD dtTypesetterSetTypeEffects(DT_DTENGINE engine, const DT_TYPE_EFFECTS_L* type, DT_UBYTE reserved);
DT_SWORD dtGlyphDoOutput(DT_DTENGINE engine, DT_ID_ULONG glyph_index, DT_FLOAT x, DT_FLOAT y, DT_SWORD reserved, DT_BMP* memory_bitmap);
```

* `dtOutputSetAsMDC`： 设置输出位图平面
* `dtTypesetterSetTypeEffects`： 设置 字形 映射(宽高，横纵倾斜...)
* `dtGlyphDoOutput`： 输出 字形到位图

`dtTypesetterSetTypeEffects` 的主要参数 type 示例值
其中 transform.size_h 和size_v 将用来作为 说明 字形绘制大小的参数
```cpp
DT_TYPE_EFFECTS type = {MYFONT_SIMPLE, 0, 0, {{200, 200, 0, 0, 20}}, {0, 0, 0, 0, 0, DV_SCALE_100}};

/*
   The above initialization is the same as

   type.font_index = MYFONT_SIMPLE;
   type.reserved = 0;
   type.descriptor = 0;
   type.transform.params.size_h = 200;
   type.transform.params.size_v = 200;
   type.transform.params.skew_h = 0;
   type.transform.params.skew_v = 0;
   type.transform.params.rotation = 20;
   type.linedecor.thickness = 0;
   type.linedecor.segment = 0;
   type.linedecor.shift = 0;
   type.linedecor.dash_size = 0;
   type.linedecor.flags = 0;
   type.linedecor.scale_id = DV_SCALE_100;
*/ 

dtTypesetterSetTypeEffects(engine, &type, 0);
```

`dtGlyphDoOutput` 参数如下

| Parameter      | Description                                                |
| -------------- | --------------------------------------------------------- |
| *engine*       | Handle of the previously created Standard Engine instance. |
| *char_code*    | Unicode character code of the glyph to be rendered.        |
| *glyph_index*  | Font dependent index of the glyph to be rendered.          |
| *x*            | Glyph's X coordinate in pixels.                            |
| *y*            | Glyph's Y coordinate in pixels.                            |
| *reserved*     | Reserved for future use. Must be set to 0.                 |
| *memory_bitmap*| \*\*                                                       |

其中 char_code 是 字形的 unicode 值, 简单获取为 `L'繁'` 或者 `wchar_t` 的值 也可以 (只要 程序当前locale正确应该就ok)



## 5.排版

排版 主要关注的是，字形位置
### 术语定义
* advance_x (x轴步长): 当前字形左边沿 到 下一字形 左边沿 的坐标差值
* extent: 包裹 字形的最小矩形盒子(边当然平行于坐标轴)
* * xmn: x轴左界
* * xmx: x轴右界
* * ymn: y轴下界
* * ymx: y轴上界
* * 注意: x轴或者y轴的 `单位` 和 [字体基本信息](#字体基本信息) 有关( `font_xbs`,`font_ybs`)

### 字体基本信息
```cpp
DT_SWORD dtFontGetMetrics(DT_DTENGINE engine, DT_ID_SWORD font_index, DT_UWORD* font_xbs, DT_UWORD* font_ybs, DT_RECT_SWORD* extent);
```
| Parameter      | Description                                                |
| -------------- | --------------------------------------------------------- |
| *engine*     | Handle of the previously created Standard Engine instance.   |
| *font_index* | Font index of the font or font instance in the Font Catalog. |
| *font_xbs*   | A valid pointer to the DT_UWORD type that will receive the base font width (or units per em-square in the horizontal direction), in font units.However, if you do not wish to receive the value of the above parameter, you may set this pointer to DV_NULL. |
| *font_ybs*   | A valid pointer to the DT_UWORD type that will receive the base font height (or units per em-square in the vertical direction), in font units.However, if you do not wish to receive the value of the above parameter, you may set this pointer to DV_NULL. |
| *extent*     | A pointer to the DT_RECT_SWORD structure that will receive global font extent as defined in the font file. This is the minimum (x, y) and maximum (x, y) coordinate for the entire font in font units. If you do not wish to receive this information, you may set the *extent* pointer to DV_NULL. Otherwise, this must be a valid pointer to the DT_RECT_SWORD structure. |

字体基本信息里的 extent基本用不上，但是，`font_xbs` 与 `font_ybs` 是两个很重要的数值
`font_xbs` 与 `font_ybs` 规定了  `字体基本宽高`

### 字形信息 
通过 [3-加载字形信息](#3-加载字形信息) 一节的 api，我们加载到了 字形的 `advance`(包括 `advance_x`的信息) 和 `extent`

### Demo演示
此节 说明以上 `字体基本信息` `dtTypesetterSetTypeEffects`的 `size_h` `size_v` 与 字形信息  `advance_x` `extent`的意义

* 红色边框 : 由`dtCharDoOutput`::x、y 与 `DT_STYLE_EFFECTS::size_h size_v` 指定的范围，代表了 `font_xbs` 与 `font_ybs` 对应的范围
* 绿色边框 : 由 字形信息 `extent` 指定的范围, 是字形的边界范围

![output](d_type_demo_out.bmp)

字体和字形 信息如下
输出格式 见 [`demo source`](d_type_demo.cpp)
```text
        xybs:  1000 1000        extent:  -994 2930-1050 1810     /usr/share/fonts/opentype/noto/NotoSerifCJK-Light.ttc
ch: W   advance:     0  880 1045 1000   extent:    13 1037   -7  725     Box:   100  100  100  100
ch: l   advance:     0  880  330 1000   extent:    35  295    0  802     Box:   220  100  100  100
ch: ?   advance:     0  880 1000 1000   extent:    51  956  400  509     Box:   340  100  100  100
ch: 1   advance:     0  880  472 1000   extent:    74  426    0  735     Box:   460  100  100  100
ch: .   advance:     0  880  325 1000   extent:   105  219  -14   99     Box:   100  220  100  100
ch: ?   advance:     0  880 1000 1000   extent:    43  322  -81  198     Box:   220  220  100  100
ch: ,   advance:     0  880  325 1000   extent:    65  219 -174   97     Box:   340  220  100  100
ch: ,   advance:     0  880 1000 1000   extent:    82  228 -191  113     Box:   460  220  100  100
```
