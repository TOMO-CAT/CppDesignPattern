#include "Caretaker.h"

int main() {
    // 创建原发器和负责人
    Editor editor;
    Command command(&editor);

    // 定义初始状态
    editor.setText("TOMOCAT");
    editor.setCursor(21, 34);
    editor.setSelectionWidth(3.4);

    // 保存状态
    command.makeBackup();

    // 更改编辑器状态
    editor.setText("KKKK");
    editor.setCursor(111, 222);
    editor.setSelectionWidth(111.222);

    // 撤销
    command.undo();

    return 0;
}