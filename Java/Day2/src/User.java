public class User {

    //private 私有的访问权限修饰符
    //public 提供公众的访问权限
    private String username = "jack";//在开发的过程中我们需要对一些属性进行保护，不希望直接对外界提供访问方式
    private String idCard;
    //方法
    public String getUsername(){
        return username;
    }

}
