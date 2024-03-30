#include <iostream>
#include <vector>
#include <memory>

// 组件接口
class FileSystemComponent {
public:
    virtual void display() const = 0;
};

// 叶子节点：文件
class File : public FileSystemComponent {
public:
    File(std::string name) : name(name) {}

    void display() const override {
        std::cout << "File: " << name << std::endl;
    }

private:
    std::string name;
};

// 容器节点：文件夹
class Folder : public FileSystemComponent {
public:
    void addComponent(std::shared_ptr<FileSystemComponent> component) {
        components.push_back(component);
    }

    void display() const override {
        std::cout << "Folder" << std::endl;
        for (auto& component : components) {
            component->display();
        }
    }

private:
    std::vector<std::shared_ptr<FileSystemComponent>> components;
};

int main() {
    // 创建文件系统
    std::shared_ptr<Folder> rootFolder = std::make_shared<Folder>();
    std::shared_ptr<File> file1 = std::make_shared<File>("file1.txt");
    std::shared_ptr<File> file2 = std::make_shared<File>("file2.txt");
    std::shared_ptr<Folder> subFolder = std::make_shared<Folder>();

    // 构建文件系统结构
    rootFolder->addComponent(file1);
    rootFolder->addComponent(file2);
    rootFolder->addComponent(subFolder);
    subFolder->addComponent(std::make_shared<File>("subFile.txt"));

    // 显示文件系统
    rootFolder->display();

    return 0;
}
