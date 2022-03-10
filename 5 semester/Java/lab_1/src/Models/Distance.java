package Models;

public class Distance {
    public double meter;
    public double centimeter;
    public long ft;
    public long inch;

    public Distance(double meter, double centimeter) {
        this.meter = meter;
        this.centimeter = centimeter;
        double cm = centimeter + meter * 100;
        inch = Math.round(cm / 2.54);
        ft = inch / 12;
        inch %= 12;
    }
}
