package example;

import java.io.File;
import java.io.IOException;
import java.util.jar.JarFile;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.HashMap;
 
import com.ibm.wala.classLoader.IClass;
import com.ibm.wala.classLoader.IMethod;
import com.ibm.wala.classLoader.IField;
import com.ibm.wala.ipa.callgraph.AnalysisScope;
import com.ibm.wala.ipa.cha.ClassHierarchy;
import com.ibm.wala.ipa.cha.ClassHierarchyFactory;
import com.ibm.wala.ipa.cha.ClassHierarchyException;
import com.ibm.wala.ipa.cha.IClassHierarchy;
import com.ibm.wala.core.util.config.AnalysisScopeReader;
import com.ibm.wala.types.ClassLoaderReference;
import com.ibm.wala.core.util.io.FileProvider;
 
 
class Data_sig {
	String cls;
	String cls_pkg;
	String name;
	String sig;
	String check_static;

	public Data_sig(String c, String c_p, String n, String s, String cs){
		this.cls = c;
		this.cls_pkg = c_p;
		this.name = n;
		this.sig = s;
		this.check_static = cs;
	}
}
public class WalaTest {
	public static void main(String args[]) throws IOException, ClassHierarchyException {
 
			File exFile = new FileProvider().getFile("Java60RegressionExclusions.txt");
			if(args.length != 1) {
				System.out.println("1 target jar file required.");
				System.exit(-1);
			}
			String jarFilePath = args[0];
			File jar_file = new File(jarFilePath);
            		String jarFileName = jar_file.getName();
			String jar_name = jarFileName.substring(0,jarFileName.lastIndexOf("."));
			File file = new File("/home/greenare0410/Documents/repo/WALA_test/wala_result.txt");
			if(!file.exists()){
				file.createNewFile();
			}
			HashMap<String,HashSet<Data_sig>> java_info = new HashMap<>(); 
			BufferedWriter writer = new BufferedWriter(new FileWriter(file));
			AnalysisScope scope = AnalysisScopeReader.instance.makeJavaBinaryAnalysisScope(args[0], exFile);
			ClassHierarchy cha = ClassHierarchyFactory.make(scope);
			for (IClass c : cha) {
				if(!c.getReference().getClassLoader().equals(ClassLoaderReference.Application)){
					continue;
				}
				String cname_pkg = c.getName().toString();
				String cname = c.getName().getClassName().toString();
				if(cname_pkg.startsWith("L")){
					cname_pkg = cname_pkg.substring(1);
				}
				if(cname.equals(jar_name)){
					if(!(java_info.containsKey(cname_pkg))){
						java_info.put(cname_pkg, new HashSet<>());
					}
					for (IMethod m : c.getAllMethods()) {
						String mname = m.getName().toString();
						String msig = m.getSignature().toString();
						boolean mstatic = m.isStatic();
						msig = msig.substring(msig.lastIndexOf("("),msig.length());
						HashSet<Data_sig> temp = java_info.get(cname_pkg);
						if(mstatic){
							temp.add(new Data_sig(cname, cname_pkg, mname, msig, "1"));
						}else{
							temp.add(new Data_sig(cname, cname_pkg, mname, msig, "2"));
						}
						java_info.put(cname_pkg, temp);
					}
					for(IField f : c.getAllFields()){
                                                String fname = f.getName().toString();
                                                String fsig = f.getFieldTypeReference().toString();
						fsig = fsig.substring((fsig.lastIndexOf(",")+1),(fsig.length()-1));
						if(fsig.startsWith("L")){
							fsig = fsig + ";";
						}
						boolean fstatic = f.isStatic();
						HashSet<Data_sig> temp = java_info.get(cname_pkg);
						if(fstatic){
                                                	temp.add(new Data_sig(cname, cname_pkg, fname, fsig, "3"));
						}else{
							temp.add(new Data_sig(cname, cname_pkg, fname, fsig, "4"));
						}
						java_info.put(cname_pkg, temp);
                                        }
				}
			}
			for(String key : java_info.keySet()){
                                 writer.write(key + " ");
			}
                        writer.newLine();
                        for(String key : java_info.keySet()){
                                for(Data_sig ob : java_info.get(key)){
                                        //writer.write(key + " " + ob.func + " " + ob.sig);

                                        writer.write(key +" "+ ob.check_static +" "+ ob.name+" "+ob.sig);
                                        writer.newLine();
                                }
                        }
			writer.flush();
			writer.close();
 
 
	}
}
