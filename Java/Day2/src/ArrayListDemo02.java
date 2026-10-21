import java.util.ArrayList;

public class ArrayListDemo02 {
    public static void main(String[] args) {
        System.out.println();
        //创建一个集合对象
        ArrayList<Person> list = new ArrayList<Person>();
        //创建person对象
        Person person1 = new Person();
            person1.setName("张三");
            person1.setAge(23);
        Person person2 = new Person();
            person2.setName("李四");
            person2.setAge(18);
        Person person3 = new Person();
            person3.setName("王五");
            person3.setAge(25);
        Person person4 = new Person();
            person4.setName("老六");
            person4.setAge(27);
        Person person5 = new Person();
            person5.setName("七七");
            person5.setAge(77);

        list.add(person1);
        list.add(person2);
        list.add(person3);
        list.add(person4);
        list.add(person5);

        System.out.println("年龄大于25岁的有");
        //对集合进行便利
        for (Person person: list)
        {
            if (person.getAge() > 25)
            {
                System.out.println(person.getName());
            }
        }

    }
}
