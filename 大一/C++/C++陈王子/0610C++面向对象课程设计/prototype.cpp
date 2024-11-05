#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

// 职称枚举类型
enum Title {
    AssistantEngineer,
    Engineer,
    SeniorEngineer,
    ProfessorSeniorEngineer
};

// 部门枚举类型
enum Department {
    PersonnelDepartment,
    TechnicalDepartment,
    LogisticsDepartment,
    InformationDepartment
};

// 职务枚举类型
enum JobTitle {
    OrdinaryEmployee,
    EngineerStaff,
    TeamLeader,
    DepartmentHead,
    CompanyLeader
};

// 员工信息类
class Employee {
public:
    Employee() = default;
    Employee(int id, string name, int age, string education, string nationality, string major, Title title, Department department, JobTitle jobTitle)
        : m_id(id), m_name(name), m_age(age), m_education(education), m_nationality(nationality), m_major(major), m_title(title), m_department(department), m_jobTitle(jobTitle) {}

    // Getter and Setter
    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    string getName() const { return m_name; }
    void setName(string name) { m_name = name; }

    int getAge() const { return m_age; }
    void setAge(int age) { m_age = age; }

    string getEducation() const { return m_education; }
    void setEducation(string education) { m_education = education; }

    string getNationality() const { return m_nationality; }
    void setNationality(string nationality) { m_nationality = nationality; }

    string getMajor() const { return m_major; }
    void setMajor(string major) { m_major = major; }

    Title getTitle() const { return m_title; }
    void setTitle(Title title) { m_title = title; }

    Department getDepartment() const { return m_department; }
    void setDepartment(Department department) { m_department = department; }

    JobTitle getJobTitle() const { return m_jobTitle; }
    void setJobTitle(JobTitle jobTitle) { m_jobTitle = jobTitle; }

private:
    int m_id;
    string m_name;
    int m_age;
    string m_education;
    string m_nationality;
    string m_major;
    Title m_title;
    Department m_department;
    JobTitle m_jobTitle;
};

// 员工管理系统类
class EmployeeManagementSystem {
public:
    // 菜单函数
    void showMenu();

    // 文件读写函数
    void saveDataToFile();
    void loadDataFromFile();

    // 操作员工数据函数
    void addEmployee();
    void modifyEmployee();
    void removeEmployee();
    void queryEmployee();
    void showTitleEmployees();
    void showDepartmentEmployeeNums();
    void sortEmployeesByField();

private:
    list<Employee> m_employeeList;
};

/**
 * @brief 显示菜单
 */
void EmployeeManagementSystem::showMenu()
{
    cout << "========== 员工管理系统 ==========" << endl;
    cout << "1. 添加员工" << endl;
    cout << "2. 修改员工" << endl;
    cout << "3. 删除员工" << endl;
    cout << "4. 查询员工" << endl;
    cout << "5. 显示各职称的员工信息" << endl;
    cout << "6. 显示各部门的员工数量" << endl;
    cout << "7. 根据不同的字段信息排序显示" << endl;
    cout << "0. 退出程序" << endl;
    cout << "==================================" << endl;
    cout << "请输入您的选择：";
}

/**
 * @brief 从文件中读取数据
 */
void EmployeeManagementSystem::loadDataFromFile()
{
    ifstream inFile("employee_data.txt");
    if (!inFile) {
        cout << "没有员工数据文件，将创建一个新文件\n";
        return;
    }

    while (inFile.good()) {
        int id, age;
        string name, education, nationality, major;
        Title title;
        Department department;
        JobTitle jobTitle;

        inFile >> id >> name >> age >> education >> nationality >> major >> title >> department >> jobTitle;

        if (id != 0) {
            m_employeeList.emplace_back(Employee(id, name, age, education, nationality, major, title, department, jobTitle));
        }
    }

    cout << "员工数据加载成功！" << endl;
}

/**
 * @brief 保存数据到文件
 */
void EmployeeManagementSystem::saveDataToFile()
{
    ofstream outFile("employee_data.txt");

    for (const auto& employee : m_employeeList) {
        outFile << employee.getId() << " "
            << employee.getName() << " "
            << employee.getAge() << " "
            << employee.getEducation() << " "
            << employee.getNationality() << " "
            << employee.getMajor() << " "
            << employee.getTitle() << " "
            << employee.getDepartment() << " "
            << employee.getJobTitle() << endl;
    }

    cout << "员工数据保存成功！" << endl;
}

/**
 * @brief 添加员工信息
 */
void EmployeeManagementSystem::addEmployee()
{
    int id, age;
    string name, education, nationality, major;
    Title title;
    Department department;
    JobTitle jobTitle;

    cout << "请输入员工ID：";
    cin >> id;

    for (const auto& employee : m_employeeList) {
        if (employee.getId() == id) {
            cout << "员工ID已经存在，请重新输入。" << endl;
            return;
        }
    }

    cout << "请输入员工姓名：";
    cin >> name;

    cout << "请输入员工年龄：";
    cin >> age;

    cout << "请输入员工受教育程度：";
    cin >> education;

    cout << "请输入员工民族：";
    cin >> nationality;

    cout << "请输入员工专业：";
    cin >> major;

    cout << "请输入员工职称（1. 助理工程师 2. 工程师 3. 高级工程师 4. 教授级高级工程师）：";
    int titleNum;
    cin >> titleNum;

    if (titleNum < 1 || titleNum > 4) {
        cout << "职称编号无效，请重新输入。" << endl;
        return;
    }

    title = static_cast<Title>(titleNum - 1);

    cout << "请输入员工部门（1. 人事部 2. 技术部 3. 后勤部 4. 信息部）：";
    int departmentNum;
    cin >> departmentNum;

    if (departmentNum < 1 || departmentNum > 4) {
        cout << "部门编号无效，请重新输入。" << endl;
        return;
    }

    department = static_cast<Department>(departmentNum - 1);

    cout << "请输入员工职务（1. 普通员工 2. 工程师 3. 团队领导 4. 部门领导 5. 公司领导）：";
    int jobTitleNum;
    cin >> jobTitleNum;

    if (jobTitleNum < 1 || jobTitleNum > 5) {
        cout << "职务编号无效，请重新输入。" << endl;
        return;
    }

    jobTitle = static_cast<JobTitle>(jobTitleNum - 1);

    m_employeeList.emplace_back(Employee(id, name, age, education, nationality, major, title, department, jobTitle));

    cout << "员工添加成功！" << endl;
}

/**
 * @brief 修改员工信息
 */
void EmployeeManagementSystem::modifyEmployee()
{
    int id;
    cout << "请输入要修改的员工ID：";
    cin >> id;

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    cout << "请输入要修改的字段（1. 姓名 2. 年龄 3. 受教育程度 4. 民族 5. 专业 6. 职称 7. 部门 8. 职务）：";
    int fieldNum;
    cin >> fieldNum;

    switch (fieldNum) {
    case 1: {
        string name;
        cout << "请输入新的姓名：";
        cin >> name;
        it->setName(name);
        break;
    }
    case 2: {
        int age;
        cout << "请输入新的年龄：";
        cin >> age;
        it->setAge(age);
        break;
    }
    case 3: {
        string education;
        cout << "请输入新的受教育程度：";
        cin >> education;
        it->setEducation(education);
        break;
    }
    case 4: {
        string nationality;
        cout << "请输入新的民族：";
        cin >> nationality;
        it->setNationality(nationality);
        break;
    }
    case 5: {
        string major;
        cout << "请输入新的专业：";
        cin >> major;
        it->setMajor(major);
        break;
    }
    case 6: {
        cout << "请输入新的职称（1. 助理工程师 2. 工程师 3. 高级工程师 4. 教授级高级工程师）：";
        int titleNum;
        cin >> titleNum;

        if (titleNum < 1 || titleNum > 4) {
            cout << "职称编号无效，请重新输入。" << endl;
            return;
        }

        Title title = static_cast<Title>(titleNum - 1);
        it->setTitle(title);
        break;
    }
    case 7: {
        cout << "请输入新的部门（1. 人事部 2. 技术部 3. 后勤部 4. 信息部）：";
        int departmentNum;
        cin >> departmentNum;

        if (departmentNum < 1 || departmentNum > 4) {
            cout << "部门编号无效，请重新输入。" << endl;
            return;
        }

        Department department = static_cast<Department>(departmentNum - 1);
        it->setDepartment(department);

        break;
    }
    case 8: {
        cout << "请输入新的职务（1. 普通员工 2. 工程师 3. 团队领导 4. 部门领导 5. 公司领导）：";
        int jobTitleNum;
        cin >> jobTitleNum;

        if (jobTitleNum < 1 || jobTitleNum > 5) {
            cout << "职务编号无效，请重新输入。" << endl;
            return;
        }

        JobTitle jobTitle = static_cast<JobTitle>(jobTitleNum - 1);
        it->setJobTitle(jobTitle);
        break;
    }
    default:
        cout << "字段编号无效，请重新输入。" << endl;
        return;
    }

    cout << "员工信息修改成功！" << endl;
}

/**
 * @brief 删除员工信息
 */
void EmployeeManagementSystem::removeEmployee()
{
    int id;
    cout << "请输入要删除的员工ID：";
    cin >> id;

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    m_employeeList.erase(it);

    cout << "员工删除成功！" << endl;
}

/**
 * @brief 查询员工信息
 */
void EmployeeManagementSystem::queryEmployee()
{
    int id;
    cout << "请输入要查询的员工ID：";
    cin >> id;

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    cout << "员工信息如下：" << endl;
    cout << "------------------------------" << endl;
    cout << "编号：" << it->getId() << endl;
    cout << "姓名：" << it->getName() << endl;
    cout << "年龄：" << it->getAge() << endl;
    cout << "受教育程度：" << it->getEducation() << endl;
    cout << "民族：" << it->getNationality() << endl;
    cout << "专业：" << it->getMajor() << endl;
    cout << "职称：" << it->getTitle() << endl;
    cout << "部门：" << it->getDepartment() << endl;
    cout << "职务：" << it->getJobTitle() << endl;
}

/**
 * @brief 显示各职称的员工信息
 */
void EmployeeManagementSystem::showTitleEmployees()
{
    cout << "===== 各职称的员工信息 =====" << endl;
    cout << "助理工程师：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == AssistantEngineer; }) << endl;
    cout << "工程师：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == Engineer; }) << endl;
    cout << "高级工程师：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == SeniorEngineer; }) << endl;
    cout << "教授级高级工程师：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == ProfessorSeniorEngineer; }) << endl;
}

/**
 * @brief 显示各部门员工数量
 */
void EmployeeManagementSystem::showDepartmentEmployeeNums()
{
    cout << "===== 各部门员工数量 =====" << endl;
    cout << "人事部：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getDepartment() == PersonnelDepartment; }) << endl;
    cout << "技术部：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getDepartment() == TechnicalDepartment; }) << endl;
    cout << "后勤部：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getDepartment() == LogisticsDepartment; }) << endl;
    cout << "信息部：" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getDepartment() == InformationDepartment; }) << endl;
}

/**
 * @brief 根据不同的字段排序显示员工信息
 */
void EmployeeManagementSystem::sortEmployeesByField()
{
    cout << "请输入排序字段：1.编号 2.姓名 3.年龄 4.职称 5.部门 6.职务：";
    int fieldNum;
    cin >> fieldNum;

    switch (fieldNum) {
    case 1:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getId() < e2.getId(); });
        break;
    case 2:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getName() < e2.getName(); });
        break;
    case 3:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getAge() < e2.getAge(); });
        break;
    case 4:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getTitle() < e2.getTitle(); });
        break;
    case 5:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getDepartment() < e2.getDepartment(); });
        break;
    case 6:
        sort(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e1, const Employee& e2) { return e1.getJobTitle() < e2.getJobTitle(); });
        break;
    default:
        cout << "字段编号无效，请重新输入。" << endl;
        return;
    }

    cout << "员工信息如下：" << endl;
    cout << "------------------------------" << endl;
    for (const auto& employee : m_employeeList) {
        cout << "编号：" << employee.getId() << endl;
        cout << "姓名：" << employee.getName() << endl;
        cout << "年龄：" << employee.getAge() << endl;
        cout << "受教育程度：" << employee.getEducation() << endl;
        cout << "民族：" << employee.getNationality() << endl;
        cout << "专业：" << employee.getMajor() << endl;
        cout << "职称：" << employee.getTitle() << endl;
        cout << "部门：" << employee.getDepartment() << endl;
        cout << "职务：" << employee.getJobTitle() << endl;
        cout << "------------------------------" << endl;
    }
}