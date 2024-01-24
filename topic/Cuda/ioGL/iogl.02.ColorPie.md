---
categories:
 - ["Topics","cuda"]
title: "Iogl.02.ColorPie"
date: 2023-02-07T09:15:57+08:00
draft: false
include_toc: true
---

# Iogl.02.ColorPie

steps:
* create cpu frames
* cpu render pixel in it
* cuda copy frame to opengl texture
* opengl render this frame

## render
```cpp
struct FragParam
{
    double time;
    int    w, h;
    int    razerR = 1, razerC = 1;
    double radiusOfRazer = 0.5;
    int    ROffset = 0, COffset = 0;
};

tuple<uint8_t, uint8_t, uint8_t, uint8_t> FragRender(int r, int c, FragParam const param)
{
    double w = param.w, h = param.h;
    r += param.ROffset;
    c += param.COffset;
    if (((r / h - 0.5) * (r / h - 0.5) + (c / w - 0.5) * (c / w - 0.5)) > param.radiusOfRazer * param.radiusOfRazer)
    {
        r = r / param.razerR * param.razerR;
        c = c / param.razerC * param.razerC;
    }
    int factor = 256;
    int red = factor * r / h;
    int green = factor * c / w;
    return {red, green, 0, 1};
}
```
## trans data from cpu to gpu
call cuMemcpy2D to transform data
there is a weired problem still unresolved:
    if i dont call glGenerateMipmap(tex), then the luminance of pixels is decreasing with the vertex-data:position.
    like(dont call genMipmap) : set L=-0.7,R=0.7;then the rendered frame luminance is about 0.55x of the true pixel-data;
```cpp
void TransHostData(void *data, size_t sz)
{
    NV_API_CALL(cuGraphicsMapResources(1, &texRes, 0));
    // // this is for texture object
    // NV_API_CALL(cuGraphicsResourceGetMappedPointer(&texResDevicePtr, &texResDevicePtrLength, texRes));
    // RAW_LOG_ASSERT(CULogger(), "MemCpy", texResDevicePtrLength >= sz,);
    // NV_API_CALL(cuMemcpy(texResDevicePtr, (CUdeviceptr)data, sz));

    NV_API_CALL(cuGraphicsSubResourceGetMappedArray(&texResArr, texRes, 0, 0));
    CUDA_MEMCPY2D cp{};
    cp.srcMemoryType = CUmemorytype::CU_MEMORYTYPE_HOST;
    cp.srcHost = data;
    cp.srcPitch = tex.width * tex_comp_cnt;

    cp.dstMemoryType = CUmemorytype::CU_MEMORYTYPE_ARRAY;
    cp.dstArray = texResArr;
    cp.WidthInBytes = tex.width * tex_comp_cnt;

    cp.Height = tex.height;

    NV_API_CALL(cuMemcpy2D(&cp));
    NV_API_CALL(cuGraphicsUnmapResources(1, &texRes, 0));

    // /* dont know why, but after the video meemory copy, seems need regenerate this mipmap */
    glActiveTexture(tex.targetTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
}
```