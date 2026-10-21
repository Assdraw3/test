public class Person {
    private String name;
    private int age;
    //alt + insert快捷键

    //为了给私有的属性赋值
    public void setName(String name) {
        this.name = name;
    }
    //this当前类的
    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }
}
