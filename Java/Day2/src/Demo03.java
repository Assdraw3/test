public class Demo03
{
    public static void main(String[] args) {
        Animal animal = new Animal();
        animal.eat();
        animal.name = "Tiger";
        animal.age = 15;
        System.out.println("This " + animal.name);
        System.out.println("It\'s age is " + animal.age);
    }
}
