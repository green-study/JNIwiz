public class TestJNI {
   static {
      System.load("/home/greenare0410/Documents/repo/Demo/NullTest/myjni.so"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Native method that calls back the constructor and return the constructed object.
   // Return an Integer object with the given int.
   private native Integer getIntegerObject(int number);
   int narr[];
   static int arr[];

   public void temp(){
	  String x = null;
   }
   
   public static void temp2 (int x, int y){
	   int z = x + y;
   }

   public static void main(String args[]) {
      TestJNI obj = new TestJNI();
      System.out.println("[java] Request result to C++"); 
      Integer result = obj.getIntegerObject(9999);
      System.out.println("[java] Received result from C++");
   }
}
