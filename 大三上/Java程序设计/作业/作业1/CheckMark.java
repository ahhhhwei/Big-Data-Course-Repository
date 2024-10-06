import java.util.Scanner;

public class CheckMark {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入分数:");
        int mark = scanner.nextInt();
        if (mark >= 50) {
            System.out.println("PASS");
        } else {
            System.out.println("FAIL");
        }
        scanner.close();
    }
}
