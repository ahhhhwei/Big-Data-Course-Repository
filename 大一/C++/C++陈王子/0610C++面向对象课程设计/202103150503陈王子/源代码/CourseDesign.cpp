#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <vector>
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

// 岗位枚举类型
enum JobTitle {
    OrdinaryEmployee,
    EngineerStaff,
    TeamLeader,
    DepartmentHead,
    CompanyLeader
};

// 获取职称对应的中文名称
string getTitleChinese(Title title) {
    switch (title) {
    case AssistantEngineer:
        return "助理工程师";
    case Engineer:
        return "工程师";
    case SeniorEngineer:
        return "高级工程师";
    case ProfessorSeniorEngineer:
        return "教授级高级工程师";
    default:
        return "";
    }
}


// 获取部门对应的中文名称
string getDepartmentChinese(Department department) {
    switch (department) {
    case PersonnelDepartment:
        return "人事部";
    case TechnicalDepartment:
        return "技术部";
    case LogisticsDepartment:
        return "后勤部";
    case InformationDepartment:
        return "信息部";
    default:
        return "";
    }
}

// 获取岗位对应的中文名称
string getJobTitleChinese(JobTitle jobTitle) {
    switch (jobTitle) {
    case OrdinaryEmployee:
        return "普通员工";
    case EngineerStaff:
        return "工程师";
    case TeamLeader:
        return "团队组长";
    case DepartmentHead:
        return "部门负责人";
    case CompanyLeader:
        return "公司领导";
    default:
        return "";
    }
}


Title getTitleEnum(const string& titleStr)
{
    if (titleStr == "助理工程师"||titleStr=="1") {
        return Title::AssistantEngineer;
    }
    else if (titleStr == "工程师"||titleStr == "2") {
        return Title::Engineer;
    }
    else if (titleStr == "高级工程师" || titleStr == "3") {
        return Title::SeniorEngineer;
    }
    else if (titleStr == "教授级高级工程师" || titleStr == "4") {
        return Title::ProfessorSeniorEngineer;
    }
    else {
        cout<<"非法职称，默认助理工程师\n"<<endl;
        return Title::AssistantEngineer;
    }
}


Department getDepartmentEnum(const string& dptStr)
{
    if (dptStr == "人事部"||dptStr == "1") {
        return Department::PersonnelDepartment;
    }
    else if (dptStr == "技术部" || dptStr == "2") {
        return Department::TechnicalDepartment;
    }
    else if (dptStr == "后勤部" || dptStr == "3") {
        return Department::LogisticsDepartment;
    }
    else if (dptStr == "信息部" || dptStr == "4") {
        return Department::InformationDepartment;
    }
    else {
        cout << "非法部门，默认人事部\n" << endl;
        return Department::PersonnelDepartment;
    }
}

JobTitle getJobTitleEnum(const string& jobStr)
{
    if (jobStr == "普通员工"|| jobStr == "1") {
        return JobTitle::OrdinaryEmployee;
    }
    else if (jobStr == "工程师" || jobStr == "2") {
        return JobTitle::EngineerStaff;
    }
    else if (jobStr == "团队组长" || jobStr == "3") {
        return JobTitle::TeamLeader;
    }
    else if (jobStr == "部门负责人" || jobStr == "4") {
        return JobTitle::DepartmentHead;
    }
    else if (jobStr == "公司领导" || jobStr == "5") {
        return JobTitle::CompanyLeader;
    }
    else {
        cout << "非法岗位，默认普通员工\n" << endl;
        return JobTitle::OrdinaryEmployee;
    }
}




// 员工信息类
class Employee {

    friend class EmployeeManagementSystem;

private:
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
    void showAllEmployeeInfo();
    

private:
    bool isDuplicateEmployee(int id) const;
    list<Employee> m_employeeList;
};

/**
 * @brief 显示菜单
 */

void EmployeeManagementSystem::showMenu()
{
    std::cout << "========== Prince 员工管理系统 ==========" << std::endl
        << "1.  添加员工" << std::endl
        << "2.  修改员工" << std::endl
        << "3.  删除员工" << std::endl
        << "4.  查询员工" << std::endl
        << "5.  显示各职称的员工信息" << std::endl
        << "6.  显示各部门的员工数量" << std::endl
        << "7.  根据不同的字段信息排序显示" << std::endl
        << "8.  显示所有员工的信息" << std::endl
        << "9.  从文件读取员工信息" << std::endl
        << "10. 向文件写入员工信息" << std::endl
        << "0.  退出管理系统" << std::endl
        << "=========================================" << std::endl
        << "请输入您的选择：";
}

/*
void EmployeeManagementSystem::showMenu()
{
    wcout << L"\n========== Prince 员工管理系统 ==========" << endl;
    wcout << L"❶  👥添加员工" << endl;
    wcout << L"❷  📝修改员工信息" << endl;
    wcout << L"❸  🗑️删除员工" << endl;
    wcout << L"❹  🔍查询员工" << endl;
    wcout << L"❺  💼📊显示各职称的员工数量" << endl;
    wcout << L"❻  🏫📊显示各部门的员工数量" << endl;
    wcout << L"❼  🔢根据不同的字段信息排序显示" << endl;
    wcout << L"❽  👥💻显示所有员工的信息" << endl;
    wcout << L"❾  📂从文件读取员工信息" << endl;
    wcout << L"❿  💾向文件写入员工信息" << endl;
    wcout << L"0.  🚪退出管理系统" << endl;
    wcout << L"=========================================" << endl;
    wcout << L"请输入您的选择：";
}
*/


/**
 * @brief 根据 ID 看链表中是否有重复 ID
 */
bool EmployeeManagementSystem::isDuplicateEmployee(int id) const
{
    for (auto& emp : m_employeeList) {
        if (emp.getId() == id) {
            return true;
        }
    }
    return false;
}

/**
 * @brief 从文件中读取数据
 */
void EmployeeManagementSystem::loadDataFromFile()
{
    ifstream inFile("employee_data.txt");
    if (!inFile) {
        cout << "没有发现员工数据文件\n";
        ofstream outFile("employee_data.txt");
        if (!outFile) {
            cout << "无法创建全新的员工数据文件，数据保存失败！" << endl;
            return;
        }
        return;
    }

    string line;
    getline(inFile, line);
    int empNum=stoi(line.substr(line.find(':') + 1));//读职工数量

    for (int i = 0; i < empNum; ++i) {
        getline(inFile, line); // 读取空行
        getline(inFile, line); // 读取 id
        int id = stoi(line.substr(line.find(':') + 1));

        getline(inFile, line); // 读取 name
        string name = line.substr(line.find(':') + 1);

        getline(inFile, line); // 读取 age
        int age = stoi(line.substr(line.find(':') + 1));

        getline(inFile, line); // 读取 education
        string education = line.substr(line.find(':') + 1);

        getline(inFile, line); // 读取 nationality
        string nationality = line.substr(line.find(':') + 1);

        getline(inFile, line); // 读取 major
        string major = line.substr(line.find(':') + 1);

        getline(inFile, line); // 读取 title
        string titleStr = line.substr(line.find(':') + 1);
        Title title = getTitleEnum(titleStr);

        getline(inFile, line); // 读取 department
        string dptStr = line.substr(line.find(':') + 1);
        Department dpt = getDepartmentEnum(dptStr);

        getline(inFile, line); // 读取 jobTitle
        string jobStr = line.substr(line.find(':') + 1);
        JobTitle jobTitle = getJobTitleEnum(jobStr);

        if (id != 0 && !isDuplicateEmployee(id)) {
            Employee employee(id, name, age, education, nationality, major, title, dpt, jobTitle);
            m_employeeList.push_back(employee);
        }
    }

    cout << "员工数据加载成功！" << endl;
}



/**
 * @brief 往文件中写数据
 */
void EmployeeManagementSystem::saveDataToFile() 
{
    ofstream outFile("employee_data.txt", std::ofstream::trunc);
    if (!outFile) {
        cout << "无法创建员工数据文件，数据保存失败！" << endl;
        return;
    }

    // 写入员工数量
    int empNum = m_employeeList.size();
    outFile << "职工数量:" << empNum << endl;

    // 依次写入每个员工的信息
    for (auto& emp : m_employeeList) {
        outFile << endl;   // 空行
        outFile << "编号:" << emp.getId() << endl;
        outFile << "姓名:" << emp.getName() << endl;
        outFile << "年龄:" << emp.getAge() << endl;
        outFile << "受教育程度:" << emp.getEducation() << endl;
        outFile << "民族:" << emp.getNationality() << endl;
        outFile << "专业:" << emp.getMajor() << endl;
        outFile << "职称:" << getTitleChinese(emp.getTitle()) << endl;
        outFile << "部门:" << getDepartmentChinese(emp.getDepartment()) << endl;
        outFile << "岗位:" << getJobTitleChinese(emp.getJobTitle()) << endl;
    }

    cout << "\n员工数据保存成功！" << endl;
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
    while (cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "输入有误，请重新输入员工ID：";
        cin >> id;
    }

    if (isDuplicateEmployee(id)) {
        cout << "员工ID已经存在，请重新输入。" << endl;
        return;
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

    while (titleNum < 1 || titleNum > 4||cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "您需要输入一个1-4的数字，请重新输入员工职称编号：";
        cin >> titleNum;
    }

    title = static_cast<Title>(titleNum - 1);

    cout << "请输入员工部门（1. 人事部 2. 技术部 3. 后勤部 4. 信息部）：";
    int departmentNum;
    cin >> departmentNum;

    while (departmentNum < 1 || departmentNum > 4||cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "您需要输入一个1-4的数字。\n请重新输入部门职称编号：";
        cin >> departmentNum;
    }


    department = static_cast<Department>(departmentNum - 1);

    cout << "请输入员工岗位（1. 普通员工 2. 工程师 3. 团队领导 4. 部门领导 5. 公司领导）：";
    int jobTitleNum;
    cin >> jobTitleNum;

    if (jobTitleNum < 1 || jobTitleNum > 5||cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "您需要输入一个1-5的数字。\n请重新输入员工岗位编号：" << endl;
        return;
    }

    jobTitle = static_cast<JobTitle>(jobTitleNum - 1);

    m_employeeList.emplace_back(Employee(id, name, age, education, nationality, major, title, department, jobTitle));

    cout << "\n员工数据添加成功！\n" << endl;
}

/**
 * @brief 修改员工信息
 */
void EmployeeManagementSystem::modifyEmployee()
{
    int id;
    cout << "请输入要修改的员工ID：";
    cin >> id;
    while (cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "输入有误，请重新输入员工ID：";
        cin >> id;
    }

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    cout << "请输入要修改的字段（1. 姓名 2. 年龄 3. 受教育程度 4. 民族 5. 专业 6. 职称 7. 部门 8. 岗位）：";
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

        while (titleNum < 1 || titleNum > 4 || cin.fail()) {
            cin.clear();            // 清除错误状态
            cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
            cout << "您需要输入一个1-4的数字，请重新输入员工职称编号：";
            cin >> titleNum;
        }

        Title title = static_cast<Title>(titleNum - 1);
        it->setTitle(title);
        break;
    }
    case 7: {
        cout << "请输入员工部门（1. 人事部 2. 技术部 3. 后勤部 4. 信息部）：";
        int departmentNum;
        cin >> departmentNum;

        while (departmentNum < 1 || departmentNum > 4 || cin.fail()) {
            cin.clear();            // 清除错误状态
            cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
            cout << "您需要输入一个1-4的数字。\n请重新输入部门职称编号：";
            cin >> departmentNum;
        }

        Department department = static_cast<Department>(departmentNum - 1);
        it->setDepartment(department);

        break;
    }
    case 8: {
        cout << "请输入新的岗位（1. 普通员工 2. 工程师 3. 团队领导 4. 部门领导 5. 公司领导）：";
        int jobTitleNum;
        cin >> jobTitleNum;

        if (jobTitleNum < 1 || jobTitleNum > 5 || cin.fail()) {
            cin.clear();            // 清除错误状态
            cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
            cout << "您需要输入一个1-5的数字。\n请重新输入员工岗位编号：" << endl;
            return;
        }

        JobTitle jobTitle = static_cast<JobTitle>(jobTitleNum - 1);
        it->setJobTitle(jobTitle);
        break;
    }
    default:
        cout << "字段编号无效，请重新输入。" << endl;
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        return;
    }

    cout << "\n员工信息修改成功！\n" << endl;
}

/**
 * @brief 删除员工信息
 */
void EmployeeManagementSystem::removeEmployee()
{
    int id;
    cout << "请输入要删除的员工ID：";
    cin >> id;

    while (cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "您需要输入员工的编号。" << endl;
        return;
    }

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    m_employeeList.erase(it);

    cout << "员工删除成功！" << endl;
}


void EmployeeManagementSystem::showAllEmployeeInfo() 
{
    cout << "\n所有员工信息如下：" << endl;
    cout << "------------------------------" << endl;
    for (const auto& employee : m_employeeList) {
        
        cout << "编号：" << employee.getId() << endl;
        cout << "姓名：" << employee.getName() << endl;
        cout << "年龄：" << employee.getAge() << endl;
        cout << "受教育程度：" << employee.getEducation() << endl;
        cout << "民族：" << employee.getNationality() << endl;
        cout << "专业：" << employee.getMajor() << endl;
        cout << "职称：" << getTitleChinese(employee.getTitle()) << endl;
        cout << "部门：" << getDepartmentChinese(employee.getDepartment()) << endl;
        cout << "岗位：" << getJobTitleChinese(employee.getJobTitle()) << endl;
        
        /*
        cout << "\t编号：" << employee.getId() << "\t姓名：" << employee.getName() << "\t年龄：" << employee.getAge() << 
            "\t学历："<< employee.getEducation() << "\t民族：" << employee.getNationality() << "\t专业：" << employee.getMajor() <<
            "\t职称：" << getTitleChinese(employee.getTitle()) << "\t部门：" << getDepartmentChinese(employee.getDepartment())<<
            "\t岗位：" << getJobTitleChinese(employee.getJobTitle()) << endl;
        */
        cout << "------------------------------" << endl;
    }
}


/**
 * @brief 查询员工信息
 */
void EmployeeManagementSystem::queryEmployee()
{
    int id;
    cout << "请输入要查询的员工ID：";
    cin >> id;

    while (cin.fail()) {
        cin.clear();            // 清除错误状态
        cin.ignore(100, '\n');  // 消耗掉输入流中的错误字符
        cout << "您需要输入员工的编号。" << endl;
        return;
    }

    auto it = find_if(m_employeeList.begin(), m_employeeList.end(), [id](const Employee& e) { return e.getId() == id; });

    if (it == m_employeeList.end()) {
        cout << "没有找到ID为" << id << "的员工" << endl;
        return;
    }

    cout << "查询到的员工信息如下：" << endl;
    cout << "------------------------------" << endl;
    cout << "编号：" << it->getId() << endl;
    cout << "姓名：" << it->getName() << endl;
    cout << "年龄：" << it->getAge() << endl;
    cout << "受教育程度：" << it->getEducation() << endl;
    cout << "民族：" << it->getNationality() << endl;
    cout << "专业：" << it->getMajor() << endl;
    cout << "职称：" << getTitleChinese(it->getTitle()) << endl;
    cout << "部门：" << getDepartmentChinese(it->getDepartment() )<< endl;
    cout << "岗位：" << getJobTitleChinese(it->getJobTitle()) << endl;
}

/**
 * @brief 显示各职称的员工信息
 */




void EmployeeManagementSystem::showTitleEmployees()
{
    cout << "===== 各职称的员工信息 =====" << endl;

    // 定义一个 map，用于存放各职称对应的员工列表
    map<Title, vector<Employee>> titleEmployeesMap;
    for (const auto& emp : m_employeeList)
    {
        // 将员工按照职称分组
        titleEmployeesMap[emp.getTitle()].emplace_back(emp);
    }

    // 遍历 map，输出各职称的员工数量和员工信息
    for (const auto& item : titleEmployeesMap)
    {
        Title title = item.first;
        cout << "\n职称：" << getTitleChinese(title) << "\t员工数量：" << item.second.size() << endl;
        cout << getTitleChinese(title)<<"员工信息：" << endl;
        for (const auto& emp : item.second)
        {
            cout << "\t编号：" << emp.getId() << "\t姓名：" << emp.getName() << "\t年龄：" << emp.getAge() << "\t学历："
                << emp.getEducation() << "\t籍贯：" << emp.getNationality() << "\t专业：" << emp.getMajor() << endl;
        }
    }
    cout << endl;
}


/*
void EmployeeManagementSystem::showTitleEmployees()
{
    cout << "===== 各职称的员工信息 =====" << endl;
    cout << "助理工程师数量：\n" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == AssistantEngineer; }) << endl;
    cout << "工程师数量：\n" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == Engineer; }) << endl;
    cout << "高级工程师数量：\n" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == SeniorEngineer; }) << endl;
    cout << "教授级高级工程师数量：\n" << count_if(m_employeeList.begin(), m_employeeList.end(), [](const Employee& e) { return e.getTitle() == ProfessorSeniorEngineer; }) << endl;
}

*/

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
    cout << "请输入排序字段：1.编号 2.姓名 3.年龄 4.职称 5.部门 6.岗位：";
    int fieldNum;
    cin >> fieldNum;

    if (fieldNum == 1) {
        cout << "根据员工编号排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getId() < e2.getId(); });
    }
    else if (fieldNum == 2) {
        cout << "根据员工姓名排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getName() < e2.getName(); });
    }
    else if (fieldNum == 3) {
        cout << "根据员工年龄排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getAge() < e2.getAge(); });
    }
    else if (fieldNum == 4) {
        cout << "根据员工职称排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getTitle() < e2.getTitle(); });
    }
    else if (fieldNum == 5) {
        cout << "根据员工部门排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getDepartment() < e2.getDepartment(); });
    }
    else if (fieldNum == 6) {
        cout << "根据员工岗位排序。" << endl;
        m_employeeList.sort([](const Employee& e1, const Employee& e2) { return e1.getJobTitle() < e2.getJobTitle(); });
    }
    else {
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
        cout << "职称：" << getTitleChinese(employee.getTitle()) << endl;
        cout << "部门：" << getDepartmentChinese(employee.getDepartment()) << endl;
        cout << "岗位：" << getJobTitleChinese(employee.getJobTitle())<< endl;
        cout << "------------------------------" << endl;
    }
}




int main() {
    //_setmode(_fileno(stdout), _O_U16TEXT);//让控制台启用Unicode 16
    //wcout << L"❶  👥添加员工" << endl;
    
    EmployeeManagementSystem ems;

    // 加载数据
    ems.loadDataFromFile();

    // 显示菜单
    while (true) {
        ems.showMenu();
        int choice;
        cin >> choice;
        switch (choice) {
        case 0:
            cout << "\n谢谢您使用 Prince 员工信息管理系统。欢迎下次再来！" << endl;
            ems.saveDataToFile();
            return 0;
        case 1:
            ems.addEmployee();
            ems.saveDataToFile();
            break;
        case 2:
            ems.modifyEmployee();
            ems.saveDataToFile();
            break;
        case 3:
            ems.removeEmployee();
            ems.saveDataToFile();
            break;
        case 4:
            ems.queryEmployee();
            break;
        case 5:
            ems.showTitleEmployees();
            break;
        case 6:
            ems.showDepartmentEmployeeNums();
            break;
        case 7:
            ems.sortEmployeesByField();
            break;
        case 8:
            ems.showAllEmployeeInfo();
            break;
        case 9:
            ems.loadDataFromFile();
            break;
        case 10:
            ems.saveDataToFile();
            break;
        default:
            cout << "输入有误，请重新输入！" << endl;
            break;
        }
    }

    return 0;
    
}