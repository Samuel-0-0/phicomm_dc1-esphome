# 固件编译及刷固件方法
### 0、前置条件
请确认已经按照[本方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)连接好TTL工具，并且TTL工具驱动已经正确安装。

### 1、下载固件配置文件（下方右键另存为）
> ####   固件版本定义：
> - [dc1_homeassistant](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant.yaml)：相对稳定版本，用于接入Home Assistant
> - [dc1_homeassistant_test](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant_test.yaml)：测试版本，用于接入Home Assistant
> - dc1_mqtt：相对稳定版本，用于接入mqtt平台
> - dc1_mqtt_test：测试版本，用于接入mqtt平台

### 2、修改固件配置文件
按照自己的情况修改配置文件中substitutions内的参数。其他的配置如果不是很了解就不要去修改了。
```
#--------------------- 只需要改这下面的内容 ---------------------
substitutions:
  #WiFi模组版本，型号中带B的为csm64f02_b，不带B的为csm64f02
  board_model: csm64f02_b
  #设备名称(多个dc1改成不一样的)
  device_name: phicomm_dc1
  #WiFi_SSID名称
  wifi_ssid: 'SSID'
  #WiFi密码
  wifi_password: '12345678'
  #OTA密码
  ota_password: '123456'
#--------------------- 只需要改这上面的内容 ---------------------
```

关于WiFi模组版本的选择，请查看下图，找出自己对应的芯片版本即可。
看红色箭头的位置，带B的为csm64f02_b，不带B的为csm64f02

![image](https://github.com/Samuel-0-0/phicomm_dc1-esphome/blob/master/yaml/%E6%A8%A1%E7%BB%84%E5%9E%8B%E5%8F%B7%E9%80%89%E6%8B%A9.jpg?raw=true)

### 3、搭建编译环境及刷固件
**因platformio需要python2.7的环境，所以python2.7为必须。**
- Windows 系统

1. 下载 [git安装包-64位](https://github.com/git-for-windows/git/releases/download/v2.21.0.windows.1/PortableGit-2.21.0-64-bit.7z.exe) / [git安装包-32位](https://github.com/git-for-windows/git/releases/download/v2.21.0.windows.1/PortableGit-2.21.0-32-bit.7z.exe)
2. 下载 [python2.7安装包-64位](https://www.python.org/ftp/python/2.7.16/python-2.7.16.amd64.msi) / [python2.7安装包-32位](https://www.python.org/ftp/python/2.7.16/python-2.7.16.msi)
3. 下载 [DC1刷机工具（自搭环境版）](https://github.com/Samuel-0-0/esphome-tools-dc1) 并解压
4. 解压Git安装包内所有文件到Prerequisites\git里面，如下图
5. 安装python到指定位置，如下图
6. 运行DC1工具箱，选择(2)升级编译环境，等待完成。


- MacOS

> MacOS自带python2.7，所以无需再安装。

> [从此处下载esphome](https://github.com/Samuel-0-0/esphome-core)（打开页面后，右上角「 Clone or download 」 → 「 Download ZIP 」），下载后解压缩。

> 打开终端，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）
```
# 进入esphome的setup.py所在目录
cd xxxxx
# 编译 esphome
# 如提示权限不足，命令前加上sudo
python setup.py build
# 安装 esphome
python setup.py install
# 进入配置文件所在目录
cd xxxxx
# 编译固件(xxxxx.yaml为你的配置文件名字)
esphome xxxxx.yaml compile
# 刷固件（线刷或者OTA皆可）
esphome xxxxx.yaml upload
```

- Linux
> 与MacOS类似，参考MacOS的方法

- Docker
> docker版本暂无
