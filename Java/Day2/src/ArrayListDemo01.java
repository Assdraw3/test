import java.util.ArrayList;
import java.util.Objects;

public class ArrayListDemo01 {
    public static void main(String[] args) {
        ArrayList list = new ArrayList();
        Student stu = new Student();
        //往集合中存放数据
        list.add(100);
        list.add(3.14);
        list.add(false);
        list.add("Hello");
        list.add(stu);
        //通过循环的方式来打印数据
        //for(存放的数据类型 遍历到的每一个元素)
        //Object 来接受所有的子类
        for(Object obj: list){

            System.out.println(obj);

        }
        //创建一个集合对象，来存放person对象
        ArrayList<Person> arrayList = new ArrayList<>();
        Person one = new Person();
        one.setAge(100);
        one.setName("Jack");
        arrayList.add(one);
        Person two = new Person();
        two.setAge(50);
        two.setName("Tom");
        arrayList.add(two);
        for (Person per: arrayList)
        {
            System.out.println(per.getName());
            System.out.println(per.getAge());
        }






    }
}
