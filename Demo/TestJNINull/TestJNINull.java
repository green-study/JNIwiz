public class TestJNINull {
   int n = 0;
   static String x = "hi";
   static {
      System.load("/home/greenare0410/Documents/repo/Demo/TestJNINull/myjni.so"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Native method that calls back the constructor and return the constructed object.
   // Return an Integer object with the given int.
   private native Integer gettingIntegerObject(int number);
 
   public static void main(String args[]) {
      TestJNINull obj = new TestJNINull();
      System.out.println("In Java, the number is :" + obj.gettingIntegerObject(9999));
   }
}
