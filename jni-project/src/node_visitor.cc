#include "node_visitor.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace clang;
using namespace std;

namespace instrumentor {

NodeVisitor::NodeVisitor(Rewriter &R, const LangOptions &langOptions) :
  rewriter(R), lang_opt(langOptions) {}

bool NodeVisitor::VisitDecl(Decl *d) {
  vector<string> class_func = {"DefineClass","FindClass"}; //JNI functions
  vector<string> method_func = {"GetMethodID", "GetStaticMethodID"};
  if(auto record_d = dyn_cast<CXXRecordDecl>(d)) {
    if(record_d->getNameAsString() == "JNIEnv_") {
      for(auto method_d : record_d->methods()) {
        if(auto func_d = dyn_cast<FunctionDecl>(method_d)){
          Stmt* body = func_d->getBody();
          SourceLocation begin_loc = body->getBeginLoc().getLocWithOffset(1);
	  string name = func_d->getNameInfo().getName().getAsString();

	  for(int i=0; i<func_d->getNumParams(); i++){
	    if(func_d->getParamDecl(i)->getType()->isPointerType()){
	      char* parameter_null;
              string param_name = func_d->parameters()[i]->getQualifiedNameAsString();
	      asprintf(&parameter_null, "\n\tif(!%s) {\n\t\tprintf(\"[JNI %s] %s parameter: null-pointer\\n\");\n\t\texit(-1);\n\t}", param_name.c_str(), name.c_str(), param_name.c_str());
	      rewriter.InsertTextAfter(begin_loc,parameter_null);
              free(parameter_null);
	    }
	  }
	  
	  if(name == "Java_JNI_init"){
	    //wala result 
	    ifstream file;
	    file.open("/home/greenare0410/Documents/repo/WALA_test/wala_result.txt", ifstream::in);
	    string wala_str;
	    vector<string> java_class;
	    map<string, vector<pair<string, string>>> java_method;
	    map<string, vector<pair<string, string>>> static_java_method;
	    map<string, vector<pair<string, string>>> java_field;
            map<string, vector<pair<string, string>>> static_java_field;
	    getline(file, wala_str);
	    stringstream ss(wala_str);
    	    ss.str(wala_str);
    	    string wala_temp;
    	    while(ss >> wala_temp) {
              java_class.push_back(wala_temp);
    	    }	
	    string wala_c;
	    string wala_name;
	    string wala_s;
	    string check_num;
	    while(wala_str != ""){
	      getline(file, wala_str);
	      stringstream ss(wala_str);
	      ss.str(wala_str);
	      ss >> wala_str;
	      wala_c = wala_str;
	      ss >> wala_str;
              check_num = wala_str;
	      ss >> wala_str;
	      wala_name = wala_str;
	      ss >> wala_str;
	      wala_s = wala_str;
	      vector<pair<string,string>> wala_info;
	      if((java_method.find(wala_c) != java_method.end()) && (check_num == "2")){
		wala_info = java_method[wala_c];
	        wala_info.push_back(make_pair(wala_name, wala_s));
                java_method[wala_c] = wala_info;	
	      }else if((static_java_method.find(wala_c) != static_java_method.end()) && (check_num == "1")){
		wala_info = static_java_method[wala_c];
                wala_info.push_back(make_pair(wala_name, wala_s));
                static_java_method[wala_c] = wala_info;
              }else if(check_num == "2") {
                wala_info.push_back(make_pair(wala_name, wala_s));
                java_method[wala_c] = wala_info;
	      }else if(check_num == "1"){
	        wala_info.push_back(make_pair(wala_name, wala_s));
                static_java_method[wala_c] = wala_info;
	      }else if((java_field.find(wala_c) != java_field.end()) && (check_num == "4")){
                wala_info = java_field[wala_c];
                wala_info.push_back(make_pair(wala_name, wala_s));
                java_field[wala_c] = wala_info;
              }else if((static_java_field.find(wala_c) != static_java_field.end()) && (check_num == "3")){
                wala_info = static_java_field[wala_c];
                wala_info.push_back(make_pair(wala_name, wala_s));
                static_java_field[wala_c] = wala_info;
              }else if(check_num == "4") {
                wala_info.push_back(make_pair(wala_name, wala_s));
                java_field[wala_c] = wala_info;
              }else if(check_num == "3"){
                wala_info.push_back(make_pair(wala_name, wala_s));
                static_java_field[wala_c] = wala_info;
	      }
	    }
	    file.close();

	    char* init_class;
            asprintf(&init_class, "\n\tif(class_map.empty() && class_vector.empty()){");
            rewriter.InsertTextAfter(begin_loc, init_class);
            for (auto iter : java_class){
              asprintf(&init_class, "\n\t\tclass_vector.push_back(\"%s\");", iter.c_str());
              rewriter.InsertTextAfter(begin_loc, init_class);
            }
	    asprintf(&init_class, "\n\t}");
            rewriter.InsertTextAfter(begin_loc, init_class);
            free(init_class);
	    
	    char* init_method;
	    asprintf(&init_method, "\n\tif(func_map.empty() && static_func_map.empty()){");
	    rewriter.InsertTextAfter(begin_loc, init_method);
	    asprintf(&init_method, "\n\t\tvector<pair<string, string>> v;\n\t\tvector<pair<string, string>> sv;");
            rewriter.InsertTextAfter(begin_loc, init_method);
	    for(auto class_iter : java_class){
	      vector<pair<string,string>> temp = java_method[class_iter];
	      vector<pair<string,string>> stemp = static_java_method[class_iter];
	      for(auto method_iter : temp){
                asprintf(&init_method, "\n\t\tv.push_back(make_pair(\"%s\", \"%s\"));", method_iter.first.c_str(), method_iter.second.c_str());
                rewriter.InsertTextAfter(begin_loc, init_method);
              }
	      for(auto method_iter : stemp){
                asprintf(&init_method, "\n\t\tsv.push_back(make_pair(\"%s\", \"%s\"));", method_iter.first.c_str(), method_iter.second.c_str());
                rewriter.InsertTextAfter(begin_loc, init_method);
              }
	      asprintf(&init_method, "\n\t\tfunc_map[\"%s\"] = v;\n\t\tstatic_func_map[\"%s\"] = sv;\n\t\tv.clear();\n\t\tsv.clear();", class_iter.c_str(), class_iter.c_str());
              rewriter.InsertTextAfter(begin_loc, init_method);
	    }
	    asprintf(&init_method, "\n\t}");
	    rewriter.InsertTextAfter(begin_loc, init_method);
            free(init_method);

	    char* init_field;
            asprintf(&init_field, "\n\tif(field_map.empty() && static_field_map.empty()){");
            rewriter.InsertTextAfter(begin_loc, init_field);
            asprintf(&init_field, "\n\t\tvector<pair<string, string>> f;\n\t\tvector<pair<string, string>> sf;");
            rewriter.InsertTextAfter(begin_loc, init_field);
            for(auto class_iter : java_class){
              vector<pair<string,string>> temp = java_field[class_iter];
              vector<pair<string,string>> stemp = static_java_field[class_iter];
              for(auto field_iter : temp){
                asprintf(&init_field, "\n\t\tf.push_back(make_pair(\"%s\", \"%s\"));", field_iter.first.c_str(), field_iter.second.c_str());
                rewriter.InsertTextAfter(begin_loc, init_field);
              }
              for(auto field_iter : stemp){
                asprintf(&init_field, "\n\t\tsf.push_back(make_pair(\"%s\", \"%s\"));", field_iter.first.c_str(), field_iter.second.c_str());
                rewriter.InsertTextAfter(begin_loc, init_field);
              }
              asprintf(&init_field, "\n\t\tfield_map[\"%s\"] = f;\n\t\tstatic_field_map[\"%s\"] = sf;\n\t\tf.clear();\n\t\tsf.clear();", class_iter.c_str(), class_iter.c_str());
              rewriter.InsertTextAfter(begin_loc, init_field);
            }
            asprintf(&init_field, "\n\t}");
            rewriter.InsertTextAfter(begin_loc, init_field);
            free(init_field);
	  }

	}	
      }
    }
  }
  return true;
}

bool NodeVisitor::VisitStmt(Stmt *s) {
  return true;
}

bool NodeVisitor::VisitFunctionDecl(FunctionDecl *f) {

  return true;
}

NodeConsumer::NodeConsumer(Rewriter &R, const LangOptions &langOpts) :
  visitor(R, langOpts) {}

void NodeConsumer::HandleTranslationUnit(clang::ASTContext &Context) {
  visitor.TraverseDecl(Context.getTranslationUnitDecl());
}

}  // instrumentor
