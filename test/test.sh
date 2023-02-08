#!/bin/bash
#现在是正方形
n=0
read -p "请输入行数数码:" f
while [ $n -lt $f ]
do
         i=0
         while [ $i -lt $f ]
         do
         echo -n "[]"
        let i++
         done
        echo ""
         let n++
done
# ————————————————
# 版权声明：本文为CSDN博主「好好先生uw」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
# 原文链接：https://blog.csdn.net/m0_55847566/article/details/118387006