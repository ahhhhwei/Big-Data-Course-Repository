import java.sql.*;

public class test1 {
    public static void main(String[] args) {
        String dbUrl = "jdbc:mysql://localhost:3306/bigdata_test";
        String dbUser = "root";
        String dbPassword = "123456";
        try {
            // 1. 获取数据库连接
            Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword);
            // 2. 创建Statement对象
            Statement stmt = conn.createStatement();
            // 3. 执行SQL插入语句
            String insertSql = "INSERT INTO Student (Name, English, Math, Computer) VALUES ('scofield', 45, 89, 100)";
            stmt.executeUpdate(insertSql);
            System.out.println("插入完成");
            // 4. 执行SQL查询
            String selectSql = "SELECT English FROM Student WHERE Name = 'scofield'";
            ResultSet rs = stmt.executeQuery(selectSql);
            // 5. 处理结果集
            while (rs.next()) {
                System.out.println("scofield的英语成绩: " + rs.getInt("English"));
            }
            // 6. 关闭连接和声明
            rs.close();
            stmt.close();
            conn.close();
        } catch (Exception e) {
            // 打印异常信息
            e.printStackTrace();
        }
    }
}