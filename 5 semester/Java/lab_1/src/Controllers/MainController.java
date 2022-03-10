package Controllers;

import Models.Distance;
import Views.ConsoleView;

import java.util.Scanner;

public class MainController {
    Distance distance;

    public void Run() {
        double meter;
        double centimeter;
        Scanner in = new Scanner(System.in);
        while (true) {
            try {
                System.out.println("Введите количество метров:");
                meter = Double.parseDouble(in.next());
                break;
            } catch (Exception e) {
                System.out.println("Введены неверные данные\n");
            }
        }
        while (true) {
            try {
                System.out.println("Введите количество сантиметров:");
                centimeter = Double.parseDouble(in.next());
                break;
            } catch (Exception e) {
                System.out.println("Введены неверные данные\n");
            }
        }
        distance = new Distance(meter, centimeter);

        ConsoleView.View(distance);
    }

}
