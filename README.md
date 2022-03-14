## 斐讯DC1插座利用ESPHome自制固件方式接入开源智能家居平台

![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/%E4%BA%A7%E5%93%81%E5%9B%BE2.jpg?raw=true)

## WHY
众所周知的原因，斐讯服务器已经不能正常访问，插座的APP控制已经无法正常实现，需要有另外的方式实现插座的控制。

已有的方法为内网劫持实现，具体可参考[这里](https://bbs.hassbian.com/thread-5637-1-1.html)。

这次要实现的是通过一个自定义的固件，来完整实现DC1联网控制。

## 为什么选择ESPHome制作固件
[ESPHome](https://esphome.io/)是一个只需写几行配置文件就可以实现ESP8266/ESP32接入智能家居系统的强大开源项目。其极高的可扩展性和易用性是本次选择的主要原因。 

## 已支持接入的开源智能家居平台
以下排序随机，不分优劣。合适自己的就好。

### 1、Home Assistant
Home Assistant 是一款基于 Python 的智能家居开源系统，支持众多品牌的智能家居设备，可以轻松实现设备的语音控制、自动化等。
- [官方网站](https://www.home-assistant.io/)
- [国内论坛](https://bbs.hassbian.com/forum.php)
- [关于本固件的讨论帖](https://bbs.hassbian.com/thread-6628-1-1.html)

#### 接入方法
1. 按照[TTL接线方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/cookbook)接线
2. 按照[固件编译及刷固件方法](https://github.com/Samuel-0-0/phicomm_dc1-esphome/tree/master/yaml)更新固件
3. Home Assistant中[设置]-[集成]-添加esphome组件
4. 输入dc1对应的ip地址
5. 配置lovelace

### 2、ioBroker
ioBroker是基于nodejs的物联网的集成平台，为物联网设备提供核心服务、系统管理和统一操作方式。
- [官方网站](http://www.iobroker.net)
- [中文资料可以参考这里](https://doc.iobroker.cn/#/_zh-cn/)
- [国内论坛](https://bbs.iobroker.cn)
#### 接入方法
ioBroker相关接入问题可以加QQ群776817275咨询

### 3、其他支持mqtt的平台
理论上来说，只要是支持mqtt的平台都可以实现接入。

#### 接入方法
添加对应的topic

## TODO LIST
- [x] 分析硬件，获得主要芯片的资料
- [x] 确定各引脚对应关系
- [x] 获得原版固件的log信息（启动、控制）
- [x] 控制实现推演
- [x] 用逻辑分析仪分析U7的I2C数据
- [x] 分析U7的IO逻辑
- [x] 编写U7控制驱动程序
- [x] 电量统计芯片CSE7766功能的实现
- [x] 编写测试固件
- [x] 按钮及网络控制功能完善
- [x] 断电记忆功能完善
- [x] MQTT接入完善
- [X] 迁移IO驱动以支持ESPHome 1.14 （感谢老妖）
## 可能存在的BUG
- 可能会出现开关重置的现象，大致是因为wifi模块重启造成，配置文件默认重启功能已禁用

## 正在进行中
- 如果没有其他特别的情况，本项目正式完结。

# 开发过程回顾
## 1、已知的一些硬件资料
### WiFi模组
WiFi模组型号为芯海[CSM64F02](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/doc/CSM64F02%20WiFi%E6%A8%A1%E7%BB%84%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8CV1.3.pdf)，经过分析，这款模组和乐鑫的[ESP-WROOM-02](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/doc/esp-wroom-02%E6%8A%80%E6%9C%AF%E8%A7%84%E6%A0%BC%E4%B9%A6.pdf)是一样的。

![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/WiFi%E6%A8%A1%E7%BB%84.jpg?raw=true)
### U7
IO扩展芯片，具体型号暂时未知，经过逻辑分析仪的逻辑分析（感谢killadm和老妖），可能是cat9554的变种（山寨版）。

![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/U7.jpg?raw=true)
### U11
电量统计芯片，具体型号为[CSE7766](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/doc/U11_CSE7766%E7%94%A8%E6%88%B7%E6%89%8B%E5%86%8C.pdf)。

![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/U11%E7%94%B5%E9%87%8F%E7%BB%9F%E8%AE%A1%E8%8A%AF%E7%89%87.jpg?raw=true)
### 继电器
继电器型号为[永能家用继电器YX201系列](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/doc/%E6%B0%B8%E8%83%BD%E5%AE%B6%E7%94%A8%E7%BB%A7%E7%94%B5%E5%99%A8YX201.pdf)的产品，控制电压为5V。

![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/%E7%BB%A7%E7%94%B5%E5%99%A8.jpg?raw=true)

## 2、各芯片引脚对应关系
### 主控制板正面
![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/%E4%B8%BB%E6%8E%A7%E5%88%B6%E6%9D%BF%E6%AD%A3%E9%9D%A2_%E6%A0%87%E6%B3%A8.jpg?raw=true)

### 主控制板背面
![image](https://github.com/Samuel-0-0/dc1-esphome-home-assistant/blob/master/image/%E4%B8%BB%E6%8E%A7%E5%88%B6%E6%9D%BF%E8%83%8C%E9%9D%A2_%E6%A0%87%E6%B3%A8.jpg?raw=true)

## 致谢
以下排名不分先后，为随机。
- killadm：导出原始固件，提供WiFi芯片对比图，主控制板WiFi模块、U7移除后的PCB照片，U7逻辑分析数据采集
- 老妖：U7驱动编写，U7逻辑分析
- 实验幼儿园小二班扛把子：测试引脚走向
- Heller、巴山耗子：初期资料整理
- 风中的summer：提供清晰的电路板照片、拆机过程照片
- OttoWinter：esphome的作者

感谢各位使用本方法的玩家，欢迎加入QQ群776817275

## 免责申明
以上纯属个人爱好，因为使用上述方法造成的任何问题，不承担任何责任。

部分图片来源于网络，如果涉及版权，请通知删除。

trigger
