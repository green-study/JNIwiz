public class TestJNIField {
   int n = 0;
   static String x = "hi";
   static {
      System.load("/home/greenare0410/Documents/repo/Demo/TestJNIField/myjni.so"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Native method that calls back the constructor and return the constructed object.
   // Return an Integer object with the given int.
   private native Integer getIntegerObject(int number);
 
   public static void main(String args[]) {
      TestJNIField obj = new TestJNIField();
      System.out.println("In Java, the number is :" + obj.getIntegerObject(9999));
   }
}
