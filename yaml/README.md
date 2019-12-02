# 固件编译及刷固件方法
### 0、前置条件
请确认已经按照[本方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)连接好TTL工具，并且TTL工具驱动已经正确安装。

### 1、下载固件配置文件（下方右键另存为）
> ####   固件版本定义：
> - [dc1_homeassistant](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_homeassistant.yaml)：用于接入Home Assistant
> - [dc1_mqtt](https://github.com/Samuel-0-0/phicomm_dc1-esphome/raw/master/yaml/dc1_mqtt.yaml)：用于接入mqtt平台


```
配置文件对应版本更新历史

dc1_homeassistant：
v2019.12.02.001:
迁移到1.14版本ESPHome

v2019.03.28.002：
编译固件前请更新esphome及esphome-core到最新版本！
1、优化按钮，解决重启问题


dc1_mqtt：
v2019.12.02.001:
迁移到1.14版本ESPHome

v2019.08.26.001
感谢[yaming116](https://github.com/yaming116) QQ昵称：花开堪折枝的mqtt版本修改及测试，使用mqtt时禁止使用api！


```

### 2、修改固件配置文件
按照自己的情况修改配置文件中substitutions内的参数。其他的配置如果不是很了解就不要去修改了。

```
#--------------------- 只需要改这下面的内容 ---------------------
substitutions:
  #WiFi芯片版本，请勿修改
  board_model: esp01_1m
  #设备名称(多个dc1改成不一样的)
  device_name: phicomm_dc1
  #WiFi_SSID名称
  wifi_ssid: '2L'
  #WiFi密码
  wifi_password: '1122334455'
  #如果SSID是隐藏的，设置为true
  wifi_fast_connect: 'false'
  #WiFi离线多久后重启设备，秒s/分钟min/小时h，不需要此功能设置为0s
  wifi_reboot_timeout: 0s
  #OTA密码
  ota_password: '123456'
  #与客户端（如Home Assistant）失去连接多久后重启设备，秒s/分钟min/小时h，不需要此功能设置为0s
  api_reboot_timeout: 600s
  #电量统计的数据更新时间，秒s/分钟min/小时h
  cse7766_update_interval: 1s
#--------------------- 只需要改这上面的内容 ---------------------
```

### 3、搭建编译环境及刷固件

- Windows

[点此查看](https://github.com/Samuel-0-0/esphome-tools-dc1/tree/master)

- MacOS
**以下方法暂时不可用，请勿使用**

打开终端，执行如下命令：（如需python虚拟环境，请自行配置virtualenv）

```
# 安装 esphome
pip install esphome
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
**以下方法暂时不可用，请勿使用**

> 注意！多个配置文件放在一起除了改文件名还要改device_name: XXX，不能出现device_name重复的现象
1. 安装[官方esphome容器](https://hub.docker.com/r/esphome/esphome)
2. 执行如下命令：
```
docker exec -it esphome_container_name /bin/bash -c "mkdir /usr/src/app/esphome/components/cat9554 && cd /usr/src/app/esphome/components/cat9554 && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/__init__.py && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.cpp && curl -O https://raw.githubusercontent.com/Samuel-0-0/phicomm_dc1-esphome/master/esphome/components/cat9554/cat9554.h"

注意！看清楚上面的命令行，有处地方需要根据实际情况修改，
esphome_container_name  改成实际的容器名字
```
3. 打开浏览器，输入容器IP地址:6052，如：192.168.1.10:6052

