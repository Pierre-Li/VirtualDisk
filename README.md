# 虚拟磁盘，实现在命令行进行操作的虚拟磁盘

使用C++编写一个运行在命令行模式下的，虚拟磁盘的软件。虚拟磁盘软件能够在内存中模拟一个磁盘，通过接受命令，可以在内存中完成一些文件操作的功能。

## 要求  
使用VS作为编译工具（Vs2017）。   
可以使用任意版本的STL、可以使用最新的C++标准。  
使用面向对象的c++。 使用3种以上设计模式进行编写。  
运行期间或者程序结束时，不得出现异常退出。不得有内存泄露。  
要有足够的健壮性和容错性。  
所有的路径要能够支持中文、支持正反斜杠。  

## 相关概念  
斜杠方向：本软件要求同时支持正斜杠和反斜杠，例如c:\abc和c:/abc 这两个路径是等价的。  
绝对路径和相对路径：绝对路径指的是以盘符开始的路径，例如C:\a\b\c\1.txt。相对路径指的是相对当前路径的路径。例如：当前目录是C:\a\b\c，那么../abc 表示的是C:\a\b\abc目录。  
符号链接：符号链接（软链接）是一类特殊的文件， 其包含指向其它文件或者目录的引用。其他信息详见维基百科的【符号链接】词条，以及windows的mklink命令。  
磁盘路径表示方法：有的命令需要从真正的磁盘中索引数据，为了避免和虚拟磁盘的路径发生冲突，规定：以@开头的字符串表示该路径是真正磁盘的路径，例如copy @c:\1.txt c:\1\1.txt 表示将真正的计算机磁盘下c:\1.txt拷贝到虚拟磁盘中的c:\1\1.txt。  
路径中的通配符：星号(星星) 表示路径中的0个或多个字符；问号(?)表示路径中的1个字符。例如love?.txt，查找以love开头的一个字符结尾的txt类型的文件。c:\1\a*，表示c:\1\目录下a开头的任意文件。 

## 程序需要支持的命令  
程序需要支持以下命令：  
dir：列出当前目录下的目录和文件    
md：创建目录  
rd：删除目录  
cd：切换当前目录  
del：删除文件  
copy：拷贝文件  
ren：重命名  
move：移动  
mklink：创建符号链接  
save：将虚拟磁盘序列化到一个文件中  
load：从一个文件中反序列化为虚拟磁盘  
cls：清屏  
