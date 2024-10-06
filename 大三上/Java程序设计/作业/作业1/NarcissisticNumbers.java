public class NarcissisticNumbers {
    public static void main(String[] args) {
        for (int i = 100; i <= 999; i++) {
            int hundreds = i / 100;
            int tens = (i / 10) % 10;
            int ones = i % 10;

            if (hundreds * hundreds * hundreds + tens * tens * tens + ones * ones * ones == i) {
                System.out.print(i + " ");
            }
        }
    }
}
