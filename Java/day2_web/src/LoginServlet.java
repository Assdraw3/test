import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    //重写

    /**
     *
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        //处理中文乱码
        request.setCharacterEncoding("utf-8");
        response.setContentType("text/html;charset=UTF-8");
        System.out.println("客户端成功访问了服务端");

        String username = request.getParameter( "username");
        String password = request.getParameter( "password");

        //获取集合对象
        ArrayList<User> userArrayList = getUsers();
        boolean flag = false;
        //遍历集合对象
        for (User user: userArrayList)
        {
            if (user.getUsername().equals(username) && user.getPassword().equals(password))
            {
                flag = true;
            }
        }

        System.out.println(flag);
        if (flag == true)
        {
            response.getWriter().print("success!");
        }
        else
        {
            response.getWriter().print("failed!");
        }



    }
    public ArrayList<User> getUsers(){
        //创建一个集合
        ArrayList<User> users = new ArrayList<>();
        //创建用户变量
        User user1 = new User();
        user1.setUsername("jack");
        user1.setPassword("123456");
        User user2 = new User();
        user2.setUsername("jack");
        user2.setPassword("666666");

        users.add(user1);
        users.add(user2);

        return users;
    }
}
