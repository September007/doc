
#include <vector>
#include <cstring>
#include <functional>
#include <sstream>
#include <fstream>
#include <core-cpp/dtype_l1.h>
// D-Type CPP Engine
#include "core-cpp/dtengine.cpp"

#include <Helper/project/project.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <Helper/stb_image/stb_image_write.h> // for write bitmap

#define DT_ASSET_ROOT   CMAKE_SOURCE_DIR "/extern/D-Type/"
#define DT_ASSET(asset) DT_ASSET_ROOT asset
#define LL "%5d"
#define DTLOG(lvl,...) fprintf(stdout,__VA_ARGS__)
// resources
#define dtype_inf "/home/lull/Downloads/dtype-general-8.2.1.3/D-Type/exec/tools/config/dtype.inf"

#ifdef __linux__
#    define default_font "/usr/share/fonts/opentype/noto/NotoSerifCJK-Light.ttc"
#elif
#    define default_font "C:/Windows/Fonts/msgothic.ttc"
#endif

void        writeDC(DT_MDC &dc_mem, const char *name);
DT_DTENGINE _1_CreateDTEngine()
{
    DT_DTENGINE  ret;
    DT_INIT_INFO init_info = {0, 0, -1, 0, 0, 0, 0};
    std::string  ini_data;
    {
        std::stringstream ss;
        std::ifstream     in(dtype_inf);
        ss << in.rdbuf();
        ini_data = ss.str();
    }
    // DT_STREAM_FILE(sd_ini, "config/dtype.inf");
    DT_STREAM_FILE(sd_ini, dtype_inf);
    // DT_STREAM_MEMORY(sd_ini,(const unsigned char*)ini_data.data(),ini_data.size());

#ifdef __GNUC__
    auto oldStdOut = stdout;
    stdout = fopen("/dev/null", "w");
    auto init_ret = dtEngineIniViaStream(&ret, &sd_ini, &init_info);
    fclose(stdout);
    stdout = oldStdOut;
#else
    auto init_ret = dtEngineIniViaStream(&ret, &sd_ini, DV_NULL);
#endif
    return ret;
}

int DTLoadFont(DT_DTENGINE engine, const char *font_path, int font_type_hint)
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
                    else{
                        
                        DTLOG(info,
                            "\txybs: " LL LL " \textent: " LL LL LL LL "\t %s\n",
                            font_xbs, font_ybs,
                            extent.xmn, extent.xmx, extent.ymn, extent.ymx,
                            font_path);
                            break;
                    }
                }
            }
        }
    }
    return font_index;
}

int _2_LoadFont(DT_DTENGINE engine, const char *font_file)
{
    return DTLoadFont(engine, font_file, -1);
}

struct Col
{
    int  r, g, b;
    bool ifa;
    int  a;
};
void colorize(uint8_t *p, Col c)
{
    ((uint8_t *)p)[0] = c.r;
    ((uint8_t *)p)[1] = c.g;
    ((uint8_t *)p)[2] = c.b;
    if (c.ifa)
        ((uint8_t *)p)[3] = c.a;
};
void colorizeLine(uint8_t *p, int w, int h, int comp, int x, int y, int cx, int cy, Col c)
{
    // linear

    if (x == cx)
    {
        if (y > cy)
            std::swap(y, cy);
        for (int i = y; i <= cy; ++i)
            colorize(p + ((h - i) * w + x) * comp, c);
    }
    else
    {
        if (x > cx)
        {
            std::swap(x, cx);
            std::swap(y, cy);
        }
        for (int i = x; i <= cx; ++i)
        {
            int curY = 1.0 * (i - x) / (cx - x) * (cy - y) + y;
            colorize(p + ((h - curY) * w + i) * comp, c);
        }
    }
};
void colorizeRecTangle(uint8_t *p, int pw, int ph, int comp, int x, int y, int w, int h, Col c)
{
    colorizeLine(p, pw, ph, comp, x, y, x + w, y, c);
    colorizeLine(p, pw, ph, comp, x, y + h, x + w, y + h, c);
    colorizeLine(p, pw, ph, comp, x, y, x, y + h, c);
    colorizeLine(p, pw, ph, comp, x + w, y, x + w, y + h, c);
}
int Draw(int w, int h, int comp, const char *target_file)
{
    DT_DTENGINE engine = _1_CreateDTEngine();
    DT_ID_SWORD font_index = _2_LoadFont(engine, default_font);
    assert(font_index != -1);
    // 3. 加载 字体信息
    DT_UWORD      font_xbs, font_ybs;
    DT_RECT_SWORD font_extent;
    int           result = dtFontGetMetrics(engine, font_index, &font_xbs, &font_ybs, &font_extent);
    assert(result == 1);

    // 4.绘制
    std::vector<uint8_t> bitmap(w * h * comp, 255);
    DT_MDC               dc_mem;
    // 4.1 设置内存位图
    dc_mem.w = w;
    dc_mem.h = h;
    dc_mem.l = comp * w * h;
    dc_mem.m = bitmap.data();
    dtOutputSetAsMDC(engine, comp * 8, comp == 4 ? 3 : 0, &dc_mem, 0, 0, w, h);
    dtTypesetterSetSizeSubscale(engine, 1, 1,0);

    auto DrawBox = [&](int ch, int cx, int cy, int dw, int dh)
    {
        DT_TYPE_EFFECTS_L effect{
            font_index, 0, 0, {{200, 200, 0, 0, 0}}, {0, 0, 0, 0, 0, DV_SCALE_100}};
        effect.transform.params.size_h = dw;
        effect.transform.params.size_v = dh;

        dtTypesetterSetTypeEffects(engine, &effect, 0);
        DT_STYLE_EFFECTS styleEffect{0,{0},{0},DV_NULL};
        dtOutputSetStyleEffects(engine, &styleEffect, 0);
        DT_UBYTE mh,mv;
        // 加载字形信息
        DT_ADVANCE    advance{0};
        DT_RECT_SWORD extent{0};
        dtCharGetMetricsPlus(engine, font_index, ch, &advance, &extent, 0);
        int extDW = dw * (extent.xmx - extent.xmn) / font_xbs;
        int extDH = dh * (extent.ymx - extent.ymn) / font_ybs;
        int extX = cx + dw * (extent.xmn) / font_xbs;
        int extY = cy +dh - dh * (extent.ymx) / font_ybs;

        // 红色盒子
        Col sizeBoxCol = {255, 0, 0, comp == 4, 255};
        // 绿色盒子
        Col extentBoxCol = {0, 255, 0, comp == 4, 255};

        // sizeBox  :{ [cx,cx+dw] x [cy,cy+dh] }
        colorizeRecTangle(bitmap.data(), w, h, comp, cx, cy, dw, dh, sizeBoxCol);
        // extentCol :{ [extX,extX+extDW] x [extY,extY+extDH] }
        colorizeRecTangle(bitmap.data(), w, h, comp, extX, extY, extDW, extDH, extentBoxCol);

        dtCharDoOutput(engine, ch, cx, cy + dh, 0, 0);
        dtTypesetterGetSizeSubscale(engine,&mh,&mv);

        {   // help info
            // clang-format off
    fwprintf(stderr,L"ch: %lc",ch);
    fflush(stderr);
    fprintf(stdout,
        "\tadvance: " LL LL LL LL " \textent: " LL LL LL LL " \t Box: " LL LL LL LL "\t"
        "\n",
        advance.x, advance.y, advance.w, advance.h,
        extent.xmn, extent.xmx, extent.ymn, extent.ymx,
        int(cx),int(cy), effect.transform.params.size_h,effect.transform.params.size_v);
            // clang-format on
        }
    };

    int dw = 100;
    int dh = 100;
    int cx = 100;
    int cy = 100;
    int offsetX = dw + 20;
    int offsetY = dh + 20;
#define WWW     4
#define HHH     4
#define NOX(no) (cx + (no % WWW) * offsetX)
#define NOY(no) (cy + (no / WWW) * offsetY)
#define NOXY(no) NOX(no), NOY(no)
    const wchar_t *chs = L"Wl一1"
                         ".。,，";
    for(int i =0;i<std::wcslen(chs);++i)
        DrawBox(chs[i],NOXY(i),dw,dh);

    writeDC(dc_mem, "d_type_demo_out");
    dtEngineExt(engine);
}

int main()
{
    Draw(600, 400, 4, "Draw.bmp");
}

void writeDC(DT_MDC &dc_mem, const char *name)
{
    int  w = dc_mem.w, h = dc_mem.h;
    int  comp = dc_mem.l / w / h;
    auto compname = std::string(name) + ".bmp";
    // stbi_write_bmp(compname.c_str(), w,h, comp, dc_mem.m + (w * comp * (h - 1)), -w * comp);
    stbi_flip_vertically_on_write(true);
    stbi_write_bmp(compname.c_str(), w, h, comp, dc_mem.m);
};