1.有些函数写了多个版本，主函数在测试时未一一列出，但我在写完每个版本都进行了测试，可以保证正确性。

2.不要改动，删除DataStructure文件下的所有文件和文件夹，尤其不能将某个或某几个文件单独取出进行测试，这样可能导致编译不通过（我后来写的很多数据结构重用了之前写的数据结构）。

3.Graph类由于devC++编译不通过，我用的是Visual Studio 2008写的，所以需要用vs才能打开测试，其余均可用devC++测试（vs当然也没问题，打开main.cpp运行即可）。
   -->之后写的程序大多用visual Studio写，不保证devC++能正常运行（devC++在遇到类的继承相关的问题往往不能正确处理）。