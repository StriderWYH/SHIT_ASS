# SHIT_ASS
lyx is our son!!!  
基拉基拉  
k-fucking-d  
有关 new CA1 文件夹：暂时包括修改后的centerheap.h 以及build.cpp  
  修改内容：将centernode中其他部分删除，仅留下id部分，同时将build函数改为maindata的类成员函数，在从本地队列调出来以后先存入maindata再加入到centerheap中  
有关database.h :在maindata中新增了centerheap类型的变量，用于遍历和排序。   
b_tree 文件夹：包括b树和b+树的基本代码以及操作  
database文件夹： 包括数据库的基本构建操作  
三种priority type遵循的rules：
  0：之前定义的basic rule
  1：年长先治
  2：先到先治
1
2
