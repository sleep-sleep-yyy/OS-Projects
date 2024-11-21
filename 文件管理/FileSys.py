import os
import pickle
from datetime import datetime
from PyQt5.QtWidgets import QLineEdit,QDialogButtonBox,QDialog,QLabel,QApplication, QMainWindow, QTreeWidget, QTreeWidgetItem, QTableWidget, QTableWidgetItem, QVBoxLayout, QPushButton, QWidget, QHBoxLayout, QInputDialog, QMessageBox, QTextEdit

class Superblock:
    def __init__(self, block_size, num_blocks):
        self.block_size = block_size
        self.num_blocks = num_blocks
        self.free_blocks = [True] * num_blocks  # True表示空闲，False表示已分配


class FAT:
    def __init__(self, num_blocks):
        self.table = [-2] * num_blocks  # -2表示空闲块，-1表示文件结束，否则指向下一个块

    def find_blank(self):
        for i in range(len(self.table)):
            if self.table[i] == -2:
                return i
        return -1

    def write(self, data, disk):
        start = -1
        cur = -1
        while data:
            new_loc = self.find_blank()
            if new_loc == -1:
                raise Exception("磁盘空间不足!")
            # 说明在处理后续块，所以指向下一块的地址
            if cur != -1:
                self.table[cur] = new_loc
            else:
                start = new_loc
            cur = new_loc
            # 返回剩余数据，这里的write是block的write
            data = disk[cur].write(data)
            self.table[cur] = -1
        return start

    def delete(self, start, disk):
        if start == -1:
            return
        # 利用循环清除文件所在磁盘块
        while self.table[start] != -1:
            disk[start].clear()
            las = self.table[start]
            self.table[start] = -2
            start = las
        self.table[start] = -2
        disk[start].clear()

    def update(self, start, data, disk):
        self.delete(start, disk)
        return self.write(data, disk)

    def read(self, start, disk):
        data = ""
        while self.table[start] != -1:
            data += disk[start].read()
            start = self.table[start]
        data += disk[start].read()
        return data
#一个磁盘块
class DiskBlock:
    def __init__(self, block_size):
        self.block_size = block_size
        self.data = ""

    def write(self, data):
        if len(data) <= self.block_size:
            self.data = data
            return ""
        else:
            # 将 data 的前 self.block_size 字节写入当前磁盘块 (self.data) 中
            # 返回从 self.block_size 字节开始到数据末尾的部分
            self.data = data[:self.block_size]
            return data[self.block_size:]

    def read(self):
        return self.data

    def clear(self):
        self.data = ""

class FCB:
    def __init__(self, name, is_directory, first_block, size):
        self.name = name
        self.is_directory = is_directory
        self.first_block = first_block
        self.size = size
        self.modification_time = datetime.now()

    def update_modification_time(self):
        self.modification_time = datetime.now()


class FileSystem:
    def __init__(self, disk_name, block_size, num_blocks):
        self.disk_name = disk_name
        self.block_size = block_size
        self.num_blocks = num_blocks
        self.superblock = None
        self.fat = None
        self.disk = [DiskBlock(block_size) for _ in range(num_blocks)]
        self.current_dir = "\\"
        self.directory = {"/": {}}  # 根目录

    # 简单的消息通知小窗口
    def show_message_box(self, title, message, icon=QMessageBox.Information):
        msg_box = QMessageBox(icon, title, message, QMessageBox.Ok)
        msg_box.exec()
    # 即重新初始化
    def format_disk(self):
        self.superblock = Superblock(self.block_size, self.num_blocks)
        self.fat = FAT(self.num_blocks)
        self.directory = {"/": {}}
        self.current_dir = "\\"
        self.save_state_to_disk()

    def get_current_dir_dict(self):
        if self.current_dir == "\\":
            return self.directory["/"]
        dirs = self.current_dir.strip("\\").split("\\")
        current_dir_dict = self.directory["/"]
        for dir in dirs:
            if dir:
                current_dir_dict = current_dir_dict[dir]
        return current_dir_dict

    def save_state_to_disk(self):
        with open(self.disk_name, 'wb') as f:
            pickle.dump(self.superblock, f)
            pickle.dump(self.fat, f)
            pickle.dump(self.directory, f)
            pickle.dump(self.disk, f)

    def load_state_from_disk(self):
        if os.path.exists(self.disk_name):
            with open(self.disk_name, 'rb') as f:
                self.superblock = pickle.load(f)
                self.fat = pickle.load(f)
                self.directory = pickle.load(f)
                self.disk = pickle.load(f)
        else:
            self.format_disk()

    def create_subdirectory(self, dir_name):
        current_dir_dict = self.get_current_dir_dict()
        if dir_name in current_dir_dict:
            self.show_message_box("错误", f"文件夹 '{dir_name}' 已存在")
            return
        current_dir_dict[dir_name] = {}

    def delete_subdirectory(self, dir_name):
        current_dir_dict = self.get_current_dir_dict()
        if dir_name not in current_dir_dict:
            self.show_message_box("错误", f"文件夹 '{dir_name}' 不存在.")
            return
        del current_dir_dict[dir_name]

    def list_directory(self):
        current_dir_dict = self.get_current_dir_dict()
        contents = []
        for name, entry in current_dir_dict.items():
            if isinstance(entry, dict):
                path = self.current_dir.rstrip("\\") + "\\" + name
                contents.append({"name": name, "type": "Directory", "size": "", "modified": "", "path": path})
            else:
                path = self.current_dir.rstrip("\\") + "\\" + name
                mod_time = entry.modification_time.strftime("%Y-%m-%d %H:%M:%S")
                contents.append({"name": name, "type": "File", "size": entry.size, "modified": mod_time, "path": path})
        return contents

    def change_directory(self, dir_name):
        if dir_name == "..":
            if self.current_dir == "\\":
                self.show_message_box("错误", f"已经位于根目录.")
                return
            parent_dir = "\\".join(self.current_dir.strip("\\").split("\\")[:-1])
            if parent_dir == "":
                parent_dir = "\\"
            self.current_dir = parent_dir
        else:
            current_dir_dict = self.get_current_dir_dict()
            if dir_name in current_dir_dict and isinstance(current_dir_dict[dir_name], dict):
                new_dir = self.current_dir.rstrip("\\") + "\\" + dir_name
                self.current_dir = new_dir
            else:
                self.show_message_box("错误",f" 文件夹 '{dir_name}' 不存在.")

    def create_file(self, file_name):
        current_dir_dict = self.get_current_dir_dict()
        if file_name in current_dir_dict:
            self.show_message_box("错误",f" 文件 '{file_name}' 已存在.")
            return
        new_entry = FCB(file_name, False, -1, 0)
        current_dir_dict[file_name] = new_entry

    def delete_file(self, file_name):
        current_dir_dict = self.get_current_dir_dict()
        if file_name not in current_dir_dict:
            self.show_message_box("错误",f" 文件 '{file_name}' 未找到.")
            return
        entry = current_dir_dict[file_name]
        self.fat.delete(entry.first_block, self.disk)
        del current_dir_dict[file_name]

    def rename_file(self, old_name, new_name):
        current_dir_dict = self.get_current_dir_dict()
        if old_name not in current_dir_dict:
            self.show_message_box("错误", f"'{old_name}' 未找到.")
            return
        if new_name in current_dir_dict:
            self.show_message_box("错误", f"'{new_name}' 已存在.")
            return

        entry = current_dir_dict[old_name]
        if isinstance(entry, FCB):  # 是文件
            entry.name = new_name
            entry.update_modification_time()
            current_dir_dict[new_name] = entry
            del current_dir_dict[old_name]
        elif isinstance(entry, dict):  # 是目录
            current_dir_dict[new_name] = current_dir_dict.pop(old_name)

    def write_file(self, file_name, data):
        current_dir_dict = self.get_current_dir_dict()
        if file_name not in current_dir_dict:
            self.show_message_box("错误",f" 文件 '{file_name}' 未找到.")
            return
        entry = current_dir_dict[file_name]
        first_block = self.fat.update(entry.first_block, data, self.disk)
        entry.first_block = first_block
        entry.size = len(data)
        entry.update_modification_time()
    def read_file(self, file_name):
        current_dir_dict = self.get_current_dir_dict()
        if file_name not in current_dir_dict:
            return ""
        entry = current_dir_dict[file_name]
        if not isinstance(entry, FCB):
            return ""
        data = self.fat.read(entry.first_block, self.disk)
        return data

    def is_file(self, name):
        current_dir_dict = self.get_current_dir_dict()
        return name in current_dir_dict and isinstance(current_dir_dict[name], FCB)

    def is_directory(self, name):
        current_dir_dict = self.get_current_dir_dict()
        return name in current_dir_dict and isinstance(current_dir_dict[name], dict)


class RenameDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("重命名")

        self.layout = QVBoxLayout(self)

        self.old_name_label = QLabel("改:")
        self.old_name_input = QLineEdit(self)

        self.new_name_label = QLabel("为:")
        self.new_name_input = QLineEdit(self)

        self.layout.addWidget(self.old_name_label)
        self.layout.addWidget(self.old_name_input)
        self.layout.addWidget(self.new_name_label)
        self.layout.addWidget(self.new_name_input)

        self.button_box = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel, self)
        self.button_box.accepted.connect(self.accept)
        self.button_box.rejected.connect(self.reject)
        self.layout.addWidget(self.button_box)

    def get_names(self):
        return self.old_name_input.text(), self.new_name_input.text()


class FileSystemApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.fs = FileSystem("fileSys.dat", block_size=4096, num_blocks=1024)
        self.fs.load_state_from_disk()
        self.initUI()
        self.text_editors = []  # 用于存储打开的文本编辑器窗口

    def create_button(self, text, function):
        button = QPushButton(text)
        button.clicked.connect(function)
        self.button_layout.addWidget(button)
    def initUI(self):
        self.setWindowTitle("文件系统")
        self.setGeometry(100, 100, 1200, 800)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.layout = QHBoxLayout(self.central_widget)

        # 左侧文件目录
        self.tree = QTreeWidget()
        self.tree.setHeaderLabels(["文件目录"])
        self.layout.addWidget(self.tree, 2)  # 设置宽度比例为2

        # 中间按钮布局
        self.button_layout = QVBoxLayout()
        self.create_button("格式化", self.format_disk)
        self.create_button("创建文件夹", self.create_directory)
        self.create_button("创建文件", self.create_file)
        self.create_button("打开...", self.open_item)
        self.create_button("写入...", self.write_item)
        self.create_button("删除...", self.delete_item)
        self.create_button("重命名", self.rename_item)
        self.create_button("返回上一级", self.go_up)
        self.layout.addLayout(self.button_layout, 1)  # 设置宽度比例为1

        # 右侧文件内容
        self.file_layout = QVBoxLayout()
        self.current_dir_label = QLabel(self.fs.current_dir)
        self.file_layout.addWidget(self.current_dir_label)
        self.file_table = QTableWidget()
        self.file_table.setColumnCount(5)
        self.file_table.setHorizontalHeaderLabels(["名称", "文件类型", "大小", "修改日期", "位置"])
        self.file_table.setEditTriggers(QTableWidget.NoEditTriggers)  # 设置为不可编辑
        self.file_layout.addWidget(self.file_table)
        self.layout.addLayout(self.file_layout, 7)  # 设置宽度比例为7

        self.load_directory_structure()
        self.load_directory_contents()

    # 更新目录
    def load_directory_structure(self):
        self.tree.clear()
        self.add_directory_items(self.tree.invisibleRootItem(), self.fs.directory["/"])
    def add_directory_items(self, parent_item, directory_dict):
        for name, entry in directory_dict.items():
            item = QTreeWidgetItem([name])
            parent_item.addChild(item)
            if isinstance(entry, dict):
                self.add_directory_items(item, entry)

    # 更新右侧文件条目
    def load_directory_contents(self):
        contents = self.fs.list_directory()
        self.file_table.setRowCount(len(contents))
        for row, entry in enumerate(contents):
            self.file_table.setItem(row, 0, QTableWidgetItem(entry["name"]))
            self.file_table.setItem(row, 1, QTableWidgetItem(entry["type"]))
            self.file_table.setItem(row, 2, QTableWidgetItem(str(entry["size"])))
            self.file_table.setItem(row, 3, QTableWidgetItem(entry["modified"]))
            self.file_table.setItem(row, 4, QTableWidgetItem(entry["path"]))
        self.current_dir_label.setText(self.fs.current_dir)

    def format_disk(self):
        self.fs.format_disk()
        self.load_directory_structure()
        self.load_directory_contents()
        QMessageBox.information(self, "Info", "成功格式化")

    def rename_item(self):
        dialog = RenameDialog(self)
        if dialog.exec_():
            old_name, new_name = dialog.get_names()
            if old_name and new_name:
                self.fs.rename_file(old_name, new_name)
                self.load_directory_structure()
                self.load_directory_contents()

    def go_up(self):
        self.fs.change_directory("..")
        self.load_directory_contents()

    def create_directory(self):
        dir_name, ok = QInputDialog.getText(self, "创建文件夹", "文件夹名称:")
        if ok and dir_name:
            self.fs.create_subdirectory(dir_name)
            self.load_directory_structure()
            self.load_directory_contents()

    def create_file(self):
        file_name, ok = QInputDialog.getText(self, "创建文件", "文件名称:")
        if ok and file_name:
            self.fs.create_file(file_name)
            self.load_directory_contents()

    def delete_item(self):
        item_name, ok = QInputDialog.getText(self, "删除", "输入文件或文件夹名称:")
        if ok and item_name:
            if self.fs.is_file(item_name):
                self.fs.delete_file(item_name)
            elif self.fs.is_directory(item_name):
                self.fs.delete_subdirectory(item_name)
            else:
                QMessageBox.warning(self, "错误", "文件或文件夹未找到.")
                return
            self.load_directory_structure()
            self.load_directory_contents()

    def open_item(self):
        item_name, ok = QInputDialog.getText(self, "打开", "输入文件或文件夹名称:")
        if ok and item_name:
            if self.fs.is_directory(item_name):
                self.fs.change_directory(item_name)
                self.load_directory_contents()
            elif self.fs.is_file(item_name):
                data = self.fs.read_file(item_name)
                editor = QTextEdit()
                editor.setText(data)
                editor.setReadOnly(True)  # 设置为只读
                editor.setWindowTitle(item_name)
                editor.setMinimumSize(600, 400)  # 设置最小尺寸
                editor.show()
                self.text_editors.append(editor)  # 将编辑器存储到列表中
            else:
                QMessageBox.warning(self, "错误", "文件或文件夹未找到.")

    def write_item(self):
        item_name, ok = QInputDialog.getText(self, "写入", "输入文件名称:")
        if ok and item_name:
            if self.fs.is_file(item_name):
                content, ok = QInputDialog.getMultiLineText(self, "写入", "输入写入内容:")
                if ok:
                    self.fs.write_file(item_name, content)
                    self.load_directory_contents()
            else:
                QMessageBox.warning(self, "错误", "文件未找到.")

    def on_tree_item_double_clicked(self, item, column):
        self.fs.change_directory(item.text(0))
        self.load_directory_contents()


    def closeEvent(self, event):
        self.fs.save_state_to_disk()
        super().closeEvent(event)


def main():
    app = QApplication([])
    window = FileSystemApp()
    window.show()
    app.exec_()


if __name__ == "__main__":
    main()
