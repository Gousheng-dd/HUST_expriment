开发平台：Windows 10 +VS2017
编译步骤：需要包含源码目录下相应目录如GBN下的五个源码文件以及第三方组件目录下所有.cpp和.h文件，特别需要注意，stdafx.h中包含netsimlib.lib使用的相对路径"../../netsimlib.lib"，编译时请根据netsimlib.lib路径进行适当修改
运行说明：为保证正确运行编译时务必正确设置stdatx.h中netsimlib.lib路径