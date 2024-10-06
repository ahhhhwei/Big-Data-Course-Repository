#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QRegExp>
#include <QTextStream>
#include <QInputDialog>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

int countTime = 0;
using namespace std;
map<vector<string>, string> processText(const string& filePath);
void removeVectorElements(std::vector<std::string>& mainVector
, const std::vector<std::string>& elementsToRemove);
string IN = "";
string filePath = "/home/seed/QT_code/2023_10_5/rules.txt";
auto kvmap = processText(filePath);
void f(string str, vector<std::string>& rules, string& ret, bool& is_end)
{
    cout << rules.size() <<endl;
    if (rules.size() == 0)
        return;
    for (auto it = kvmap.begin(); it != kvmap.end(); ++it) {
        if (it->second == str) {
            const std::vector<std::string>& key = it->first;
            for (auto e : key) {
                cout << e << ' ';
                ret += e;
                ret += ' ';
            }
            cout << "->" << str;
            ret += "->";
            ret += str;
            ret += '\n';
            cout << endl;
            for (auto e : key) {
                for (auto E : rules)
                {
                    if (E == e)
                    {
                        vector<string> temp;
                        temp.push_back(E);
                        removeVectorElements(rules, temp);
                        if (rules.size() == 0)
                        {
                            is_end = true;
                            return;
                        }
                    }
                }
                f(e, rules, ret, is_end);
            }
        }
    }
}


void removeVectorElements(std::vector<std::string>& mainVector, const std::vector<std::string>& elementsToRemove) {
    mainVector.erase(std::remove_if(mainVector.begin(), mainVector.end(),[&elementsToRemove](const std::string& element) {
    return std::find(elementsToRemove.begin(), elementsToRemove.end(), element) != elementsToRemove.end();
                                    }),
                     mainVector.end());
}

void displayImage(const QString& imagePath)
{
    QMap<QString, QString> imagePaths;
    imagePaths["./ZJUTpictures/xinjiao.jpg"] = "新教楼";
    imagePaths["./ZJUTpictures/jiahe.jpg"] = "家和堂";
    imagePaths["./ZJUTpictures/jiahe2lou.jpg"] = "家和二楼";
    imagePaths["./ZJUTpictures/moganshantushuguan.jpg"] = "莫干山图书馆";
    imagePaths["./ZJUTpictures/cunzhong.jpg"] = "存中楼";
    imagePaths["./ZJUTpictures/banqiu.jpg"] = "板球馆";
    // 创建窗口
    QWidget *window = new QWidget;
    window->setWindowTitle(imagePaths[imagePath]);

    // 创建QLabel控件，并设置图片
    QLabel *label = new QLabel(window);
    QPixmap pixmap(imagePath);
    label->setPixmap(pixmap);

    // 调整QLabel控件的大小和位置
    label->resize(pixmap.width(), pixmap.height());

    // 调整窗口的大小和位置
    int windowWidth = pixmap.width();   // 调整窗口宽度
    int windowHeight = pixmap.height(); // 调整窗口高度
    window->resize(windowWidth, windowHeight);
    window->move(50, 200);
    window->show();
}

// 定义一个结构体表示k-v对
struct KVPair {
    vector<string> key;
    string value;
};

bool in(string& s, vector<string>& v)
{
    for (auto& e : v) {
        if (e == s) {
            return true;
        }
    }
    return false;
}

bool notin(string& s, vector<string>& v) {
    for (auto& e : v) {
        if (e == s) {
            return false;
        }
    }
    return true;
}

// 处理文本，提取k-v对
map<vector<string>, string> processText(const string& filePath)
{
    // 打开文件
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Failed to open the file." << endl;
        return {};
    }

    // 初始化文本
    vector<string> text;
    string line;
    while (getline(file, line)) {
        text.push_back(line);
    }
    file.close();

    // 定义一个 map 存储 k-v 对
    map<vector<string>, string> kvMap;

    // 处理文本
    for (const auto& sentence : text) {
        if (sentence.empty()) {
            continue;
        }

        // 在句子中查找“是”字的位置
        size_t pos = sentence.rfind("是");
        if (pos == string::npos) {
            continue;
        }

        // 将句子按“是”字分成两部分
        string key_string = sentence.substr(0, pos - 1);
        string value = sentence.substr(pos + 3);

        // 将key_string按逗号分割成多个部分
        vector<string> keys;
        size_t start = 0;
        size_t end = key_string.find(",");
        while (end != string::npos) {
            string key_part = key_string.substr(start, end - start);
            // 去除字符串中的空格和标点符号
            key_part.erase(remove_if(key_part.begin(), key_part.end(), ::isspace), key_part.end());
            key_part.erase(remove_if(key_part.begin(), key_part.end(), ::ispunct), key_part.end());
            keys.push_back(key_part);
            start = end + 1;
            end = key_string.find(",", start);
        }
        // 处理最后一个部分
        string last_key_part = key_string.substr(start);
        last_key_part.erase(remove_if(last_key_part.begin(), last_key_part.end(), ::isspace), last_key_part.end());
        last_key_part.erase(remove_if(last_key_part.begin(), last_key_part.end(), ::ispunct), last_key_part.end());
        keys.push_back(last_key_part);

        // 添加 k-v 对到 map
        kvMap[keys] = value;
    }

    return kvMap;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("阿伟的产生式系统");
    window.resize(480, 480);

    // 创建菜单栏
    QMenuBar *menuBar = new QMenuBar(&window);
    window.setMenuBar(menuBar);

    // 创建菜单
    QMenu *fileMenu1 = menuBar->addMenu("系统设置");
    QMenu *fileMenu2 = menuBar->addMenu("知识库");
    QMenu *fileMenu3 = menuBar->addMenu("事实库");
    QMenu *fileMenu4 = menuBar->addMenu("推理");

    // 创建动作
    // 系统设置
    QAction *action11 = fileMenu1->addAction("设置系统名称");
    QAction *action12 = fileMenu1->addAction("设置系统谓词");

    // 知识库
    QAction *action2 = fileMenu2->addAction("输入/修改规则");

    // 事实库
    QAction *action3 = fileMenu3->addAction("输入/修改事实");

    // 推理
    QAction *action41 = fileMenu4->addAction("正向推理");
    QAction *action42 = fileMenu4->addAction("反向推理");

    // 连接动作的槽函数
    QObject::connect(action11, &QAction::triggered, [&]() {
        bool ok;
        QString systemName = QInputDialog::getText(&window, "设置系统名称", "请输入系统名称:", QLineEdit::Normal, "", &ok);
        if (ok && !systemName.isEmpty()) {
            window.setWindowTitle(systemName);
            qDebug() << "系统名称：" << systemName;
        }
    });

    QObject::connect(action12, &QAction::triggered, [&]() {
        // 创建一个对话框，包含一个 QTextEdit 控件和两个按钮：保存和取消
        QDialog dialog;
        QVBoxLayout layout(&dialog);
        QTextEdit textEdit;
        layout.addWidget(&textEdit);

        QHBoxLayout buttonLayout;
        QPushButton saveButton("保存");
        QPushButton cancelButton("取消");
        buttonLayout.addWidget(&saveButton);
        buttonLayout.addWidget(&cancelButton);
        layout.addLayout(&buttonLayout);

        // 设置对话框的标题和大小
        dialog.setWindowTitle("设置系统谓词:");
        dialog.resize(400, 400);

        QObject::connect(&cancelButton, &QPushButton::clicked, [&]() {
            dialog.reject();
        });

        // 选择要打开的文件路径
        QString openFilePath = "/home/seed/QT_code/2023_10_5/System_predicate.txt";

        // 检查文件路径是否为空
        if (!openFilePath.isEmpty()) {
            // 打开文件并读取内容
            QFile file(openFilePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileContent = in.readAll();
                file.close();

                // 将文件内容显示在 QTextEdit 中
                textEdit.setPlainText(fileContent);
            }
        }

        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            dialog.accept();
            // 获取用户在 QTextEdit 中编辑的文本
            QString inputText = textEdit.toPlainText();

            // 选择保存文件的路径
            QString saveFilePath = openFilePath;

            // 检查文件路径是否为空
            if (!saveFilePath.isEmpty())
            {
                // 将用户输入的文本保存到文件中
                QFile file(saveFilePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << inputText;
                    file.close();
                    qDebug() << "文件保存成功";
                }
                else
                {
                    qDebug() << "文件保存失败";
                    QMessageBox::critical(&dialog, "错误", "文件保存失败，请检查文件路径和权限。");
                }
            }
        });

        dialog.exec();
    });

    QObject::connect(action2, &QAction::triggered, [&]() {
        // 创建一个对话框，包含一个 QTextEdit 控件和两个按钮：保存和取消
        QDialog dialog;
        QVBoxLayout layout(&dialog);
        QTextEdit textEdit;
        layout.addWidget(&textEdit);

        QHBoxLayout buttonLayout;
        QPushButton saveButton("保存");
        QPushButton cancelButton("取消");
        buttonLayout.addWidget(&saveButton);
        buttonLayout.addWidget(&cancelButton);
        layout.addLayout(&buttonLayout);

        // 设置对话框的标题和大小
        dialog.setWindowTitle("输入");
        dialog.resize(400, 400);

        QObject::connect(&cancelButton, &QPushButton::clicked, [&]() {
            dialog.reject();
        });

        // 选择要打开的文件路径
        QString openFilePath = "/home/seed/QT_code/2023_10_5/rules.txt";

        // 检查文件路径是否为空
        if (!openFilePath.isEmpty()) {
            // 打开文件并读取内容
            QFile file(openFilePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileContent = in.readAll();
                file.close();

                // 将文件内容显示在 QTextEdit 中
                textEdit.setPlainText(fileContent);
            }
        }

        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            dialog.accept();
            // 获取用户在 QTextEdit 中编辑的文本
            QString inputText = textEdit.toPlainText();

            // 选择保存文件的路径
            QString saveFilePath = openFilePath;

            // 检查文件路径是否为空
            if (!saveFilePath.isEmpty())
            {
                // 将用户输入的文本保存到文件中
                QFile file(saveFilePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << inputText;
                    file.close();
                    qDebug() << "文件保存成功";
                }
                else
                {
                    qDebug() << "文件保存失败";
                    QMessageBox::critical(&dialog, "错误", "文件保存失败，请检查文件路径和权限。");
                }
            }
        });

        dialog.exec();
    });

    QObject::connect(action3, &QAction::triggered, [&]() {
        // 创建一个对话框，包含一个 QTextEdit 控件和两个按钮：保存和取消
        QDialog dialog;
        QVBoxLayout layout(&dialog);
        QTextEdit textEdit;
        layout.addWidget(&textEdit);

        QHBoxLayout buttonLayout;
        QPushButton saveButton("保存");
        QPushButton cancelButton("取消");
        buttonLayout.addWidget(&saveButton);
        buttonLayout.addWidget(&cancelButton);
        layout.addLayout(&buttonLayout);

        // 设置对话框的标题和大小
        dialog.setWindowTitle("输入");
        dialog.resize(400, 400);

        QObject::connect(&cancelButton, &QPushButton::clicked, [&]() {
            dialog.reject();
        });

        // 选择要打开的文件路径
        QString openFilePath = "/home/seed/QT_code/2023_10_5/facts.txt";

        // 检查文件路径是否为空
        if (!openFilePath.isEmpty()) {
            // 打开文件并读取内容
            QFile file(openFilePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                QString fileContent = in.readAll();
                file.close();

                // 将文件内容显示在 QTextEdit 中
                textEdit.setPlainText(fileContent);
            }
        }

        QObject::connect(&saveButton, &QPushButton::clicked, [&]() {
            dialog.accept();
            // 获取用户在 QTextEdit 中编辑的文本
            QString inputText = textEdit.toPlainText();

            // 选择保存文件的路径
            QString saveFilePath = openFilePath;

            // 检查文件路径是否为空
            if (!saveFilePath.isEmpty())
            {
                // 将用户输入的文本保存到文件中
                QFile file(saveFilePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << inputText;
                    file.close();
                    qDebug() << "文件保存成功";
                }
                else
                {
                    qDebug() << "文件保存失败";
                    QMessageBox::critical(&dialog, "错误", "文件保存失败，请检查文件路径和权限。");
                }
            }
        });

        dialog.exec();
    });

    QObject::connect(action41, &QAction::triggered, [&]() {
        string filePath = "/home/seed/QT_code/2023_10_5/rules.txt";
        auto kvMap = processText(filePath);
        string ret = "推理过程如下：\n";


        cout << "规则读取成功!" << endl;
        std::string input = /*"位于西湖区,正对门外是石牛";*/IN;
        std::vector<std::string> result;
        std::stringstream ss(input);
        std::string token;

        while (std::getline(ss, token, ',')) {
            result.push_back(token);
        }

        // 打印解析结果
        for (auto& str : result) {
            std::cout << str << std::endl;
        }

        QString filePath1 = "/home/seed/QT_code/2023_10_5/facts.txt";
        QFile file1(filePath1);

        if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open file: " << filePath1;
            return 1;
        }

        QTextStream in(&file1);
        QVector<QString> zjutPlaces;

        QRegExp rx("\\(([^)]+)\\)");

        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line.startsWith("ZJUTplace"))
            {
                int pos = rx.indexIn(line);
                if (pos != -1)
                {
                    QString place = rx.cap(1);

                    zjutPlaces.push_back(place);
                }
            }
        }

        file1.close();
        qDebug() << zjutPlaces[0];

        std::vector<std::string> strVector;
        // 把QString转换成string并打印
        for (const QString& str : zjutPlaces)
        {
            strVector.push_back(str.toStdString());
        }
        for (const string& place : strVector)
        {
            cout << place << endl;
        }
        bool B = false;
        string answer;
        countTime = 0;
        bool Timeflag = true;
        while (1)
        {
            ++countTime;
            if(countTime >= 100)
            {
                QMessageBox::information(nullptr, "提示", "无推理结果！");
                Timeflag = false;
                break;
            }
            for (auto it = kvMap.begin(); it != kvMap.end(); ++it)
            {
                // 遍历每一条规则前件的每一个部分，如果某一条规则的前件的某一部分不在输入的语句里，则这条规则不起作用，跳过
                const std::vector<std::string>& key = it->first;
                bool flag = true;
                for (auto e : key)
                {
                    if (notin(e, result))
                    {
                        flag = false;
                        break;
                    }
                }
                // 如果全在，则执行flag
                if (flag)
                {
                    result.push_back(it->second);
                    removeVectorElements(result, it->first);
                    for (int i = 0; i < key.size(); ++i)
                    {
                        cout << key[i];
                        ret += key[i];
                        if (i != key.size() - 1)
                        {
                            cout << ", ";
                            ret += ", ";
                        }
                    }
                    cout << "->" << it->second << endl;
                    ret += "->";
                    ret += it->second;
                    ret += "\n";
                    for (auto e : result)
                    {
                        for (auto f : strVector)
                        {

                            if (e == f)
                            {
                                answer = e;
                                B = true;
                            }
                        }
                    }
                }

            }
            if (B)
            {
                break;
            }
        }
        cout << answer << endl;
        ret += "\n\n最终结果：";
        ret += answer;
        ret += "\n";
        QTextEdit *textEdit = new QTextEdit();
        QString RET = QString::fromStdString(ret);
        textEdit->setText(RET);
        // 创建图片路径的键值对
        QMap<QString, QString> imagePaths;
        imagePaths["新教楼"] = "./ZJUTpictures/xinjiao.jpg";
        imagePaths["家和堂"] = "./ZJUTpictures/jiahe.jpg";
        imagePaths["家和二楼"] = "./ZJUTpictures/jiahe2lou.jpg";
        imagePaths["莫干山图书馆"] = "./ZJUTpictures/moganshantushuguan.jpg";
        imagePaths["存中楼"] = "./ZJUTpictures/cunzhong.jpg";
        imagePaths["板球馆"] = "./ZJUTpictures/banqiu.jpg";
        imagePaths["养贤府"] = "./ZJUTpictures/yangxian.jpg";
        QString imagePath1 = imagePaths[QString::fromStdString(answer)];
        displayImage(imagePath1);
        if (Timeflag)
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("正向推理");
            msgBox.setText(RET);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            Timeflag = false;
        }
    });

    QObject::connect(action42, &QAction::triggered, [&]() {
        string filePath = "/home/seed/QT_code/2023_10_5/rules.txt";
        auto kvMap = processText(filePath);
        string ret = "反向推理过程如下：\n";

        cout << "规则读取成功!" << endl;
        std::string input = IN;
        std::stringstream ss0(input);
        std::string part1, part2;
        ss0 >> part1 >> part2;
        std::vector<std::string> result;
        std::stringstream ss(part1);
        std::string token;

        while (std::getline(ss, token, ',')) {
            result.push_back(token);
        }
        string answer = part2;

        countTime = 0;
        bool Timeflag = true;

        while (1) {
            ++countTime;
            if(countTime >= 100) {
                QMessageBox::information(nullptr, "提示", "无推理结果！");
                Timeflag = false;
                break;
            }
            bool is_end = false;
            f(answer, result, ret, is_end);
            if (is_end)
                break;
        }


        QTextEdit *textEdit = new QTextEdit();
        QString RET = QString::fromStdString(ret);
        textEdit->setText(RET);
        // 创建图片路径的键值对
        QMap<QString, QString> imagePaths;
        imagePaths["新教楼"] = "./ZJUTpictures/xinjiao.jpg";
        imagePaths["家和堂"] = "./ZJUTpictures/jiahe.jpg";
        imagePaths["家和二楼"] = "./ZJUTpictures/jiahe2lou.jpg";
        imagePaths["莫干山图书馆"] = "./ZJUTpictures/moganshantushuguan.jpg";
        imagePaths["存中楼"] = "./ZJUTpictures/cunzhong.jpg";
        imagePaths["板球馆"] = "./ZJUTpictures/banqiu.jpg";
        imagePaths["养贤府"] = "./ZJUTpictures/yangxian.jpg";
        QString imagePath1 = imagePaths[QString::fromStdString(answer)];
        displayImage(imagePath1);
        if (Timeflag) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("反向推理");
            msgBox.setText(RET);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
            Timeflag = false;
        }
    });


    // 创建提交按钮，并设置大小
    QPushButton *submitButton = new QPushButton("提交", &window);
    submitButton->setFixedSize(80, 30);

    // 将提交按钮添加到水平布局中，并设置布局属性为居中对齐
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(); // 在按钮前插入一个伸缩项，用于居中对齐
    buttonLayout->addWidget(submitButton);
    buttonLayout->addStretch(); // 在按钮后插入一个伸缩项，用于居中对齐

    // 将输入控件添加到垂直布局中
    QVBoxLayout *inputLayout = new QVBoxLayout;
    QLineEdit *lineEdit = new QLineEdit;
    inputLayout->addWidget(lineEdit);
    inputLayout->addLayout(buttonLayout); // 将水平布局添加到垂直布局中

    // 将垂直布局添加到QWidget中，并设置为窗口的中央部件
    QWidget *widget = new QWidget(&window);
    widget->setLayout(inputLayout);
    window.setCentralWidget(widget);


    // 连接槽函数
    QObject::connect(submitButton, &QPushButton::clicked, [&]() {
        QString input = lineEdit->text();
        IN = input.toStdString();
        qDebug() << "input:" << input;
    });

    window.show();

    return app.exec();
}
