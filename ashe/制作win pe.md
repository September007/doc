
[doc](https://learn.microsoft.com/zh-cn/windows-hardware/manufacture/desktop/boot-to-winpe?view=windows-10)

# 1.下载

nothing to say

# 2. 创建 

## 2.1 创建工作文件 

```bash
# 管理员身份打开新安装的 部署和映像工作环境 这个脚本
# 查看帮助 ,根据你的 cpu架构，选择命令，我是amd64
copype /? 
copype amd64 E:\win_amd64
```

## 2.2 自定义 winpe

[dism help](https://learn.microsoft.com/zh-cn/windows-hardware/manufacture/desktop/add-or-remove-packages-offline-using-dism?view=windows-10)

[win pe ocs list](https://learn.microsoft.com/en-us/windows-hardware/manufacture/desktop/winpe-add-packages--optional-components-reference?view=windows-11#winpe-optional-components--)

[使用 802.1x 身份验证协议连接到有线网络](https://learn.microsoft.com/zh-cn/windows-hardware/manufacture/desktop/winpe-network-drivers-initializing-and-adding-drivers?view=windows-11)
``` bash
# 获取你这个镜像的信息，注意传入的wim文件路径，不知道的话找一找(windows文件search推荐 everything)
# 注意获取到的 名称
Dism /Get-ImageInfo /ImageFile:E:\win_amd64\media\source\install.wim
```
```bash
# 挂载映像， 注意/name 的参数是上一步获取的名称
Dism /Mount-Image /ImageFile:E:\win_amd64\media\source\install.wim /Name:"Microsoft Windows PE (x64)" /MountDir:C:\test\offline

# 添加包
# 我的包路径: C:\Program Files (x86)\Windows Kits\10\Assessment and Deployment Kit\Windows Preinstallation Environment\amd64\WinPE_OCs
# 注意先添加 此路径下的包，再添加语言相关的，子目录下的相应包
cd  C:\Program Files (x86)\Windows Kits\10\Assessment and Deployment Kit\Windows Preinstallation Environment\amd64\WinPE_OCs
Dism /Image:C:\test\offline /Add-Package /PackagePath:.\WinPE-Setup.cab /PackagePath:zh-cn\WinPE-Setup_zh-cn.cab /PackagePath:.\WinPE-FMAPI.cab /PackagePath:WinPE-FontSupport-ZH-CN.cab /PackagePath:WinPE-Dot3Svc.cab 
# powershell 环境
Dism /Image:C:\test\offline /Add-Package /PackagePath:WinPE-WMI.cab /PackagePath:WinPE-NetFx.cab /PackagePath:WinPE-Scripting.cab /PackagePath:WinPE-PowerShell.cab 
```
## 2.3 创建可启动的介质

我只做个镜像文件，稍后我会用yumi将其添加到我的多系统安装U盘上, 关于制作多系统u盘，请参见我的其他文章

```bash
MakeWinPEMedia /ISO E:\win_amd64 E:\winpe_amd64.iso
```

