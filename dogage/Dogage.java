import java.util.Scanner;

public class Dogage {

    private static final int DOG_FIRST_YEAR_TO_HUMAN_YEARS = 15;
    private static final int DOG_YEAR_TO_HUMAN_YEARS = 4;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        boolean humanToDog = false;
        boolean dogToHuman = false;

        while (!humanToDog && !dogToHuman) {
            System.out.print("[H]uman or [D]og: ");
            String input = scanner.nextLine();

            if (input.equals("H")) {
                humanToDog = true;
            } else if (input.equals("D")) {
                dogToHuman = true;
            } else {
                System.err.println("Error: invalid whatever.");
            }
        }

        int years = 0;
        boolean gotValidInt = false;

        while (!gotValidInt) {
            System.out.print("Enter years: ");
            String strYears = scanner.nextLine();
            try {
                years = Integer.parseInt(strYears);
                gotValidInt = true;
            } catch (NumberFormatException e) {
                System.err.println("Error: invalid integer");
            }
        }

        if (years == 0) {
            System.out.println("Result: 0");
            System.exit(0);
        }

        int result = 0;

        if (dogToHuman) {
             result = DOG_FIRST_YEAR_TO_HUMAN_YEARS;
            for (int i = 0; i < years - 1; ++i) {
                result += DOG_YEAR_TO_HUMAN_YEARS;
            }
        } else {
            result = 1;
            result += (years - DOG_FIRST_YEAR_TO_HUMAN_YEARS) / DOG_YEAR_TO_HUMAN_YEARS;
        }

        System.out.printf("Result: %d\n", result);
    }

}
