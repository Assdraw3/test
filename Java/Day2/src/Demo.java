public class Demo {
    //Java's Main Function
    public static void main(String[] args) {
        String name = "Hello World";
        int age = 100;
        double point = 3.14159;
        char alpha = 'a';
        boolean ans = true;
        ans = false;
    //创建一个字符串类型的对象
        //只要引用数据类型可以创建对象
        String str = new String();
        Student stu = new Student();
        for (int i = 0;i <= 10 ;i = i+1)
        {
            int j = 0;
            while (j < 10)
            {
                System.out.println(j * 100);
                j++;
            }
            if (i != 5 && i != 6)
            System.out.println(i);
            else if (i==5)
            System.out.println(stu);
        }

        System.out.println(age);
        System.out.println(point);
        System.out.println(alpha);
        System.out.println(ans);

    }
}
