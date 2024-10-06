class NoTriangleException extends Exception {
    public NoTriangleException(String message) {
        super(message);
    }
}

class Triangle {
    private int x, y, z;

    public Triangle(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public void showInfo() {
        System.out.println("三角形三边长分别为：" + x + ", " + y + ", " + z);
    }

    public double getArea() throws NoTriangleException {
        if (x + y > z && x + z > y && y + z > x) {
            double p = (x + y + z) / 2.0;
            return Math.sqrt(p * (p - x) * (p - y) * (p - z));
        } else {
            throw new NoTriangleException("无法构成三角形");
        }
    }
}

public class TestTriangle {
    public static void main(String[] args) {
        try {
            int x = Integer.parseInt(args[0]);
            int y = Integer.parseInt(args[1]);
            int z = Integer.parseInt(args[2]);

            Triangle triangle = new Triangle(x, y, z);
            triangle.showInfo();

            double area = triangle.getArea();
            System.out.println("三角形的面积为：" + area);
        } catch (NumberFormatException e) {
            System.out.println("输入格式错误，必须输入三个整数作为三角形的三边长。");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("参数数量不足，必须输入三个整数作为三角形的三边长。");
        } catch (NoTriangleException e) {
            System.out.println("错误：" + e.getMessage());
        }
    }
}