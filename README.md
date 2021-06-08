[![Build Status](https://travis-ci.org/morsiiik/lab07.svg?branch=tutorial)](https://travis-ci.org/morsiiik/lab07)

## Laboratory work VII

Данная лабораторная работа посвещена изучению систем управления пакетами на примере **Hunter**

```sh
$ open https://github.com/ruslo/hunter
```
**Hunter** -это кроссплатформенный менеджер пакетов, управляемый CMake, для проектов на C/C++. С помощью **Hunter** можно организовать сборки для Linux, Windows, macOS, iOS, Android, Raspberry Pi и других платформ. Сторонние внешние проекты легко настраиваются,позволяя иметь множество вариантов каталогов  на основе комбинаций версий для сборки, статических/общих, параметров CMake-D, Release/Debug и т. Д. 

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab07** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
$ export GITHUB_USERNAME=morsiiik  
$ alias gsed=sed                             #заменяем sed на gsed
```

```sh
$ cd ${GITHUB_USERNAME}/workspace   
$ pushd .                         
$ source scripts/activate         
```

```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab06 projects/lab07   #клонируем репозиторий из lab06 в директорию projects/lab07
$ cd projects/lab07                                                     #переходим директорию projects/lab05
$ git remote remove origin                                             #отключаемся от гита
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab07   #подключаемся к новому репозиторию
```

```sh
$ mkdir -p cmake                                                                        #создаем директорию cmake
$ wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake #подключаем хантер
$ gsed -i -e '/cmake_minimum_required(VERSION 3.4)/a\                                 #добавляем текст после указанной строки
include("cmake/HunterGate.cmake") \
HunterGate( \
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz" \
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d" \
) \
' CMakeLists.txt
```

```sh
$ git rm -rf third-party/gtest                                        #так как хантер сам подключает тесты, удаляем gtest
$ gsed -i -e '/set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")/a\      #добавляем текст 
hunter_add_package(GTest) \
find_package(GTest CONFIG REQUIRED) \
' CMakeLists.txt
$ gsed -i -e 's/add_subdirectory(third-party/gtest)/' CMakeLists.txt   #удаляем строку
$ gsed -i -e 's/gtest_main/GTest::main/' CMakeLists.txt                 #заменим строки
```

```sh
$ cmake -H. -B_builds -DBUILD_TESTS=ON     #меняем значение переменной BUILD TESTS на ON
$ cmake --build _builds                     #запускаем сборку
$ cmake --build _builds --target test        #запускаем сборку test
$ ls -la $HOME/.hunter                        #выводим информацию о файле .hunter
```

```sh
$ git clone https://github.com/cpp-pm/hunter $HOME/projects/hunter      #клонируем репозиторий по ссылке в директорию $HOME/projects/hunter
$ export HUNTER_ROOT=$HOME/projects/hunter                             #добавляем новый путь к переменной PATH
$ rm -rf _builds                                                      #удаляем папку _builds
$ cmake -H. -B_builds -DBUILD_TESTS=ON
$ cmake --build _builds                                              #запускаем сборку
$ cmake --build _builds --target test                               #запускаем сборку test
```

```sh
$ cat $HUNTER_ROOT/cmake/configs/default.cmake | grep GTest      #вывод в консоль указанного файла. Вывод только строк, содержащих подстроку GTest
$ cat $HUNTER_ROOT/cmake/projects/GTest/hunter.cmake            #выводим данные файла hunter.cmake
$ mkdir cmake/Hunter                                           #создаем в директории cmake папку Hunter
$ cat > cmake/Hunter/config.cmake <<EOF                       #создаем и записываем файл config.cmake в директории Hunter
hunter_config(GTest VERSION 1.7.0-hunter-9)
EOF
# add LOCAL in HunterGate function
```

```sh
$ mkdir demo                    #создаем в директорию demo
$ cat > demo/main.cpp <<EOF    #создаем и записываем файл main.cpp в директории demo
#include <print.hpp>
#include <cstdlib>
int main(int argc, char* argv[])
{
  const char* log_path = std::getenv("LOG_PATH");
  if (log_path == nullptr)
  {
    std::cerr << "undefined environment variable: LOG_PATH" << std::endl;
    return 1;
  }
  std::string text;
  while (std::cin >> text)
  {
    std::ofstream out{log_path, std::ios_base::app};
    print(text, out);
    out << std::endl;
  }
}
EOF
$ gsed -i -e '/endif()/a\                #добавляем в CMakeLists.txt данные
add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(demo print)
install(TARGETS demo RUNTIME DESTINATION bin)
' CMakeLists.txt
```

```sh
$ mkdir tools                                                     #создаем в директорию tools
$ git submodule add https://github.com/ruslo/polly tools/polly   #добавляем утилиту polly
$ tools/polly/bin/polly.py --test                               #тестируем через утилиту polly
$ tools/polly/bin/polly.py --install --clear                    #устанавливаем
$ tools/polly/bin/polly.py --toolchain clang-cxx14            #запускаем toolchain clang-cxx14
```
