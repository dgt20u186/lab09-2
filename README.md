[![Build Status](https://travis-ci.org/morsiiik/lab08.svg?branch=tutorial)](https://travis-ci.org/morsiiik/lab08)

# Laboratory work VIII

Данная лабораторная работа посвещена изучению систем автоматизации развёртывания и управления приложениями на примере **Docker**

```sh
$ open https://docs.docker.com/get-started/
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Выполнить инструкцию учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial


```sh
$ export GITHUB_USERNAME=<имя_пользователя> 
```

```
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab07 lab08
$ cd lab08
$ git submodule update --init
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08
```
4.  В файле Dockerfile указываем операционную систему и версию

```sh
$ cat > Dockerfile <<EOF
FROM ubuntu:18.04
EOF
```
5. задаем докеру что делать при запуске ВМ (обновления системы и установка пакетов)

```sh
$ cat >> Dockerfile <<EOF
RUN apt update
RUN apt install -yy gcc g++ cmake
EOF
```
6. Задаем текущий каталог
```sh
$ cat >> Dockerfile <<EOF
COPY . print/
WORKDIR print
EOF
```
7. собираем смэйк

```sh
$ cat >> Dockerfile <<EOF
RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
RUN cmake --build _build
RUN cmake --build _build --target install
EOF
```
8. env = export 

```sh
$ cat >> Dockerfile <<EOF
ENV LOG_PATH /home/logs/log.txt
EOF
```
9. создаем доп.каталог для logs
```sh
$ cat >> Dockerfile <<EOF
VOLUME /home/logs
EOF
```
10. создаем WORKDIR
```sh
$ cat >> Dockerfile <<EOF
WORKDIR _install/bin
EOF
```
11. эта команда вызывает утилиту demo, что была создана в предыдущих лабораторных. 

```sh
$ cat >> Dockerfile <<EOF
ENTRYPOINT ./demo
EOF
```
Кратко о сделанном: мы создали весь файл, который явл. скриптом в своем собственном формате. Можем вызывать саму утилиту докер, которая будет создавать машину, которая будет "для нас" работать.
12. вызываем утилиту docker. -t это тег. тег - logger
```sh
$ docker build -t logger .
```
13. позволяет вывести (просмотреть) список, тех  ВМ, что есть

```sh
$ docker images
```
14.  Мы находимся сейчас в раб папке,где мы можем вызывать докер. Мы хотим развернуть ВМ и для этого мы 
создаем logs. Затем: делаем docker run - запуск машины, -it - подключаем к машине терминал. после этого нужно подключить каталог, что мы создали внутрь машины. Испольузем -v для этого. logger - это имя машины, которую мы назвали в докер билт.
  Должна быть выведена работа утилиты demo. Все, что проспиано в качестве команд будет выведено на экран.


```sh 
$ mkdir logs
$ docker run -it -v "$(pwd)/logs/:/home/logs/" logger
text1
text2
text3
<C-D>
```
15. docker inspect logger - показывает, что происходит с машиной

```sh
$ docker inspect logger
```
16. cat logs/log.txt позволяет посмотреть, что утилита вывела в лог
```sh
$ cat logs/log.txt
```
17. Заменяем README.md 
```sh
$ gsed -i 's/lab07/lab08/g' README.md
```
18. Редактируем тревис для запуска докера
```sh
$ vim .travis.yml
/lang<CR>o
services:
- docker<ESC> //  сама клавиша
jVGdo
script:
- docker build -t logger .<ESC>
:wq
```

```sh
$ git add Dockerfile
$ git add .travis.yml
$ git commit -m"adding Dockerfile"
$ git push origin master
```
19. Нужно сделать Docker работающим внутри travis'а. Выполянем это.
```sh
$ travis login --auto
$ travis enable
```
```
## Links
- [Book](https://www.dockerbook.com)
- [Instructions](https://docs.docker.com/engine/reference/builder/)
```
Copyright (c) 2015-2021 The ISC Authors
```
