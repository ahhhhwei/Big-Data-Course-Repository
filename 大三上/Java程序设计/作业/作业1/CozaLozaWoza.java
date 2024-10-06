public class CozaLozaWoza {
    public static void main(String[] args) {
        int lowerLimit = 1;
        int upperLimit = 110;
        int numbersPerLine = 11;

        for (int i = lowerLimit; i <= upperLimit; i++) {
            if (i % 3 == 0) {
                System.out.print("Coza");
            } if (i % 5 == 0) {
                System.out.print("Loza");
            } if (i % 7 == 0) {
                System.out.print("Woza");
            } if (i % 3 != 0 && i % 5 != 0 && i % 7 != 0) {
                System.out.print(i);
            }
	    System.out.print(" ");

            if (i % numbersPerLine == 0) {
                System.out.println();
            }
        }
    }
}
