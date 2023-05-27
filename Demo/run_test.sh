#!/bin/bash
file_name="$1"
jar_name="$2"

echo "============================================================================"
echo "[Extracting Java information]"
echo "============================================================================"
java -jar ../WALA_test/build/libs/WALA_test.jar "$file_name/$jar_name.jar"

echo ""
echo ""
echo "============================================================================"
echo "[Creating jni,.h for execution error detection]"
echo "============================================================================"
./../jni-project/instrument ../jni-project/example/jni_test.h
cp ../jni-project/example/jni_test_instrumented.h ./"$file_name"

echo ""
echo ""
echo "============================================================================"
echo "[default JNI version]"
echo "============================================================================"
cd "$file_name" && sed -i 's/jni_test_instrumented.h/jni.h/' "$jar_name.cpp" && g++ -I"<JAVA_HOME>\include" -I"<JAVA_HOME>\include\win32" -fPIC -shared -o myjni.so "$jar_name".cpp && javac "$jar_name".java && java "$jar_name"

echo ""
echo ""
echo "============================================================================"
echo "[-Xcheck:jni option JNI version]"
echo "============================================================================"
g++ -I"<JAVA_HOME>\include" -I"<JAVA_HOME>\include\win32" -fPIC -shared -o myjni.so "$jar_name".cpp && javac "$jar_name".java && java -Xcheck:jni "$jar_name"

echo ""
echo ""
echo "============================================================================"
echo "[JNIwiz execution error detectio JNI version]"
echo "============================================================================"
sed -i 's/jni.h/jni_test_instrumented.h/' "$jar_name.cpp" && g++ -I"<JAVA_HOME>\include" -I"<JAVA_HOME>\include\win32" -fPIC -shared -o myjni.so "$jar_name".cpp && javac "$jar_name".java && java "$jar_name"

echo ""
echo ""
echo "============================================================================"
echo "[Finish]"
echo "============================================================================"
