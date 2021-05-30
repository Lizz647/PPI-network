#include <stdio.h>
#include "PPI.h"
#include "visualize.h"

// 示例程序

int main() {
    // 打开string文件
    char path[] = "D:/test/4932.protein.links.v11.0.txt";
    visualize(path,"4932.Q0182 -> 4932.Q0010 -> 4932.Q0017 -> 4932.Q0142");
    return 0;
}

