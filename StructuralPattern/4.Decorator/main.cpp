#include "ConcreteComponent.h"
#include "ConcreteDecorator.h"

int main() {
    FileDataSource* source1 = new FileDataSource("stdout");

    // 将明码数据写入目标文件
    source1->writeData("tomocat");

    // 将压缩数据写入目标文件
    CompressionDecorator* source2 = new CompressionDecorator(source1);
    source2->writeData("tomocat");

    // 将压缩且加密数据写入目标文件
    EncryptionDecorator* source3 = new EncryptionDecorator(source2);
    source3->writeData("tomocat");

    delete source1;
    delete source2;
    delete source3;
}