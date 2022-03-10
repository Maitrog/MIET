package Views;

import Models.Distance;

public class ConsoleView {

    public static void View(Distance distance) {
        System.out.printf("%.2f м %.2f см = %d фут %d дюйм", distance.meter, distance.centimeter, distance.ft,
                distance.inch);
    }
}
