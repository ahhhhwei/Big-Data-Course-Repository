import java.util.Scanner;

public class Calc {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("请输入一个正整数n：");
        int n = scanner.nextInt();

        double sum = 1.0;
        for (int i = 2; i <= n; i++) {
            if (i % 2 == 0) {
                sum -= 1.0 / i;
            } else {
                sum += 1.0 / i;
            }
        }

        System.out.printf("e = %.3f", sum);

        scanner.close();
    }
}
