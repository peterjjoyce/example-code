/**
* This is a short example of how a class template works in Java
**/


public class PetersNumberType<T> {

    private T n;

    public void setNum(T num) {
        this.n = num;
    }

    public T getNum() {
        return this.n;
    }

    public static void main(String[] args) {
        PetersNumberType<Integer> intNumber = new PetersNumberType<Integer>();
        intNumber.setNum(new Integer(42));

        PetersNumberType<Double> doubleNumber = new PetersNumberType<Double>();
        doubleNumber.setNum(new Double(3.1415));

        System.out.println(intNumber.getNum() + "is an int.");
        System.out.println("     ...but also a PetersNumberType.");

        System.out.println(doubleNumber.getNum() + "is a double.");
        System.out.println("     ...but also a PetersNumberType.");
    }
}