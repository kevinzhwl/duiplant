duiplant
========
该项目来源自启程软件（SetoutSoft）的 DuiEngine。  
代码源自 http://code.taobao.org/p/duiengine/src/  
最近同步更细时间： 2014-4-25


DuiEngine新手指南(原版)
---------

DuiEngine是启程软件深度改写金山卫士的bkwin界面库形成的一个开源界面库，目前由本人维护。

本界面库为全免费开源库，采用MIT协议，无需授权，不提供任何担保，但是请在产品中保持一份DuiEngine的license。

使用中碰到问题可以到QQ群提问，本人一般时间都在，尽量是在自己尝试后不能解决时再提问。QQ群： 229313785


注意!!!!!

使用前建议先安装wizard目录下的VS向导，安装后会在VS的新建工程中增加一个DuiEngineWizard的工程类型，使用这个向导可以一步生成一个最简单的使用DuiEngine的框架程序。向导安装后如果生成的工程编译失败，很可能是在向导中定义的环境变量DUIENGINEPATH没有生效，请注销或者重启一下系统。

doc文件夹下有几个简单的文档，无聊时可以随便看看。

dui-demo是一个介绍内置控件使用的工程，有问题请先比较与dui-demo的差异。

编译碰到问题请尝试重新编译duiengine，再编译其它的使用duiengine的程序，如dui-demo。
dui-demo的debug_dll配置还需要lua脚本及zip支持，请先编译zip及scriptModule下相关目录。

启程软件 2014年1月9日

DuixEngine(DuiPlant)新手指南
----------

DuixEngine 是一个DuiEngine的个人维护版本。

DuixEngine基于 2014-4-25的DuiEngine版本，改变了DuiEngine一些头文件的目录结构，所以基于DuiEngine的项目不能直接过渡到DuixEngine。

DuixEngine是
---------

 * 由 托管在svn库中，改为 托管在git中；done
 * 由 msvc2008项目，改为 msvc2010项目；done
 * 由 ansi字符集，改为 unicode字符集；done(as-is)
 * 由 扁平目录结构，改为 代码，工具，文档三大块结构；done
 * 由 内部构建，改为 与源代码分离式构建；working
 * 增加库的内聚，减少对外部设置的依赖；
 * 增加类似cmake install的发布工具；working
 * 增加对cmake工具的支持；working
 * 可能还有其他暂时没想到

DuiEngine不是
----------

 * 修正DuiEngnine库中的各种缺陷，除非其导致不能通过编译等基础工作无法完成；
 * 给DuiEngine库添加新的功能、控件、工具等等；
 

DuixEngine名字由来
-----------

DuixEngine对DuiEngine的改变主要是在对头文件目录组织的改变，这样在指定includepath之后，将不再使用形如

    #include "duibasic.h"
而改为
    
    #include <dui/duibasic.h>
所以

    X = ><

DuiPlant是指整个项目，包括代码、文档、工具等；DuixEngine则是指核心的界面引擎。
	
更新日志
----------
2014-5-13：基本目录定型，初步增加cmake支持，并且可以运行。

2014-4-30：全部迁移到msvs2010

2014-4-25：项目起步