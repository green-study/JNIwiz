# JNIwiz: JNI 상호작용 실행 오류 탐지기 자동 합성
#### 2023 CNU Project Fair
Team HOLO  
Member 김수빈

#### 비고
LLVM, WALA는 외부 기술로 별도 설치가 필요합니다.
해당 소스코드에 사용된 경로는 대다수가 절대경로로 추후 상대경로로 변경될 예정입니다.

## Preliminary
### Install LLVM
Link: https://github.com/llvm/llvm-project

### Install WALA
Link: https://github.com/wala/WALA

## WALA_test (자바 정보 분석기)
자바 정보를 추출하기 위한 정적분석 소스코드 (with WALA)

## jni-project (JNI 헤더 파일 합성기)
jni.h에 실행 오류 탐지 코드 추가를 위한 instrumentation 소스코드 (with LLVM)

![image](https://github.com/green-study/JNIwiz/assets/70996958/1a4d36cd-c8d6-474b-8eae-1263ed63289b)

## Demo
데모용 테스트 소스코드 모음 파일

## Development environment
```
Ubuntu: Ubuntu 20.04.1 LTS
WALA: Version 1.6.0
LLVM: clang version 10.0.0-4ubuntu1
g++: g++ (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Gradle: Gradle 4.4.1
Java: openjdk version "11.0.19"
```
