public class ArithmeticT1 {
    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("参数个数错误，需要三个参数：两个整数和一个运算符(+, -, *, /)");
            return;
        }

        try {
            int num1 = Integer.parseInt(args[0]);
            int num2 = Integer.parseInt(args[2]);

            String operator = args[1];

            if (!isValidOperator(operator)) {
                System.out.println("Wrong Input: 输入的运算符不合法");
                return;
            }

            double result = 0;
            switch (operator) {
                case "+":
                    result = num1 + num2;
                    break;
                case "-":
                    result = num1 - num2;
                    break;
                case "*":
                    result = num1 * num2;
                    break;
                case "/":
                    if (num2 == 0) {
                        System.out.println("Wrong Input: 除数不能为0");
                        return;
                    } else {
                        result = (double) num1 / num2;
                    }
                    break;
            }

            System.out.println(num1 + " " + operator + " " + num2 + " = " + result);
        } catch (NumberFormatException e) {
            System.out.println("Wrong Input: 输入的数字不是整数");
        }
    }

    private static boolean isValidOperator(String op) {
        return op.equals("+") || op.equals("-") || op.equals("*") || op.equals("/");
    }
}
