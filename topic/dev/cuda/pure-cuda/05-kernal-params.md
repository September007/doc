---
categories: ["cuda"]
title: "05 Kernal Params"
date: 2023-02-06T22:11:47+08:00
draft: false
include_toc: true
---

## cuda synatx
https://docs.nvidia.com/cuda/cuda-c-programming-guide/#execution-configuration
https://blog.csdn.net/qq_39575835/article/details/83027440

[block + thread](https://img-blog.csdn.net/2018101221015866?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM5NTc1ODM1/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

```cuda
kernal_func<<< Dg, Db, Ns, S >>>(...);
```
## dim3 index

### calc index
```c++
int idx = (gridDim.x*gridDim.y*blockIdx.z+gridDim.x*blockIdx.y+blockIdx.x)*blockDim.x*blockDim.y*blockDim.z+ blockDim.x * blockDim.y * threadIdx.z + blockDim.x * threadIdx .y + threadIdx.x;

// or

int __device__ alphabitOrderIndex(unsigned int *str, unsigned int *base, int sz)
{
    int cnt = 0;
    for (int i = 0; i < sz; ++i)
    {
        cnt = cnt * base[i] + str[i];
    }
    return cnt;
};
unsigned int idxs[] = {blockIdx.z, blockIdx.y, blockIdx.x, threadIdx.z, threadIdx.y, threadIdx.x},
            bases[] = {GridDim.z, GridDim.y, GridDim.x, blockDim.z, blockDim.y, blockDim.x};
int idx = alphabitOrderIndex(idxs, bases, 6);
```

as you can see, blockIdx is corrdinate in GridDim, threadIdx is corrdinate in blockDim, there are all dim3{int x,y,z;}

# source code
