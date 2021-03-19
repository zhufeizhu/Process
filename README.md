## 编译
1. 工程目录下创建build目录并进入
```
    mkdir build && cd build
```
2. 执行make指令生成目标文件并将目标文件移动到build目录下
```
    make && make mymv
```
3. 运行并将结果称定向到output文件
```
    ./process ../test.txt > ../output.txt
```
4. 运行结果保存在output.txt文件中