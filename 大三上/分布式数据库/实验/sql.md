

## sql

### 建库

```sql
create database wenjw_db0 charset = 'utf8';
create database wenjw_db1 charset = 'utf8';
```

### 建表

```sql
use wenjw_db0;
CREATE TABLE wenjw_Stu0 (
    Sno INT PRIMARY KEY,
    Sname VARCHAR(100),
    Sdept VARCHAR(100),
    Stel VARCHAR(20),
    Sex VARCHAR(10),
    Sage INT,
    Saddr VARCHAR(200),
    Spost VARCHAR(10)
);

CREATE TABLE wenjw_Cou (
    Cno INT PRIMARY KEY,
    Cname VARCHAR(100),
    Cdept VARCHAR(100),
    Ctea VARCHAR(100),
    Cdate VARCHAR(20),
    CScore INT,
    Caddr VARCHAR(200)
);

CREATE TABLE wenjw_SC0 (
    Sno INT,
    Cno INT,
    Grade DECIMAL(4, 1) NOT NULL CHECK (Grade BETWEEN 0 AND 100),
    PRIMARY KEY (Sno, Cno),
    FOREIGN KEY (Sno) REFERENCES wenjw_Stu0(Sno),
    FOREIGN KEY (Cno) REFERENCES wenjw_Cou(Cno)
);
```

```sql
use wenjw_db;
CREATE TABLE wenjw_Stu1 (
    Sno INT PRIMARY KEY,
    Sname VARCHAR(100),
    Sdept VARCHAR(100),
    Stel VARCHAR(20),
    Sex VARCHAR(10),
    Sage INT,
    Saddr VARCHAR(200),
    Spost VARCHAR(10)
);

CREATE TABLE wenjw_Cou (
    Cno INT PRIMARY KEY,
    Cname VARCHAR(100),
    Cdept VARCHAR(100),
    Ctea VARCHAR(100),
    Cdate VARCHAR(20),
    CScore INT,
    Caddr VARCHAR(200)
);

CREATE TABLE wenjw_SC1 (
    Sno INT,
    Cno INT,
    Grade DECIMAL(4, 1) NOT NULL CHECK (Grade BETWEEN 0 AND 100),
    PRIMARY KEY (Sno, Cno),
    FOREIGN KEY (Sno) REFERENCES wenjw_Stu1(Sno),
    FOREIGN KEY (Cno) REFERENCES wenjw_Cou(Cno)
);
```

### 插入数据

```sql
INSERT INTO wenjw_Stu (Sno, Sname, Sdept, Stel, Sex, Sage, Saddr, Spost) VALUES 
(2101, '温家伟', '理学院', '19858180826', '男', 19, '山西省', '037000'),
(2102, '金娇薄', '计院', '19157934071', '女', 20, '浙江省', '315000'),
(2103, '毛假发', '法学院', '15678901234', '女', 21, '美国', '510000'),
(2104, '曾辽远', '理学院', '13609876543', '男', 20, '山东市', '518000'),
(2005, '秋晓荷', '理学院', '13789012345', '女', 21, '浙江省', '610000'),
(2006, '朱甜甜', '计院', '15908765432', '女', 20, '吉林省', '311100');
```

```sql
INSERT INTO wenjw_Cou (Cno, Cname, Cdept, Ctea, Cdate, CScore, Caddr) VALUES 
(12011, '分布式数据库', '计院', '范玉雷', '大三上', 3, '健行楼'),
(12012, '人工智能', '计院', '高楠', '大三上', 3, '健行楼'),
(12013, '数字图像处理', '计院', '刘盛', '大三上', 2, '广知楼'),
(12014, '数学建模', '理学院', '周凯', '大二下', 3, '健行楼'),
(12015, '运筹学', '理学院', '丁晓东', '大二下', 4, '广知楼'),
(12016, '数据结构', '计院', '蒋莉', '大二上', 4, '郁文楼'),
(12017, '大学物理', '理学院', '施建青', '大一下', 3, '新教楼'),
(12018, '程序设计基础C', '计院', '蒋莉', '大一上', 4, '子良楼');
```

```sql
INSERT INTO wenjw_SC (Sno, Cno, Grade) VALUES 
(2101, 12011, 100),
(2101, 12012, 100),
(2101, 12013, 100),
(2101, 12014, 100),
(2101, 12018, 100),

(2102, 12011, 65),
(2102, 12013, 55),
(2102, 12015, 59),
(2102, 12016, 58),
(2102, 12017, 60),

(2103, 12012, 60),
(2103, 12013, 15),
(2103, 12015, 55),
(2103, 12017, 66),
(2103, 12018, 55),

(2104, 12014, 79),
(2104, 12015, 80),
(2104, 12016, 73),
(2104, 12017, 66),
(2104, 12018, 85),

(2005, 12012, 70),
(2005, 12013, 75),
(2005, 12014, 81),
(2005, 12016, 68),
(2005, 12018, 58),

(2006, 12013, 88),
(2006, 12014, 96),
(2006, 12015, 87),
(2006, 12016, 92),
(2006, 12018, 100);
```

```sql
INSERT INTO wenjw_Stu (Sno, Sname, Sdept, Stel, Sex, Sage, Saddr, Spost) VALUES 
(2105, '张宇', '理学院', '15935231685', '男', 19, '辽宁省', '025000'),
(2106, '周宇浪', '计院', '13118722410', '男', 20, '河南省', '014500');
```

```sql
INSERT INTO wenjw_Stu (Sno, Sname, Sdept, Stel, Sex, Sage, Saddr, Spost) VALUES 
(2111, '陈王子', '理学院', '12345670890', '男', 19, '北京市', '037000');
```

```sql
INSERT INTO wenjw_Stu (Sno, Sname, Sdept, Stel, Sex, Sage, Saddr, Spost) VALUES 
(2112, '张三', '计院', '18914160052', '男', 19, '上海市', '062000');
```

