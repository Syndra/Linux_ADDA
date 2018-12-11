# Linux_ADDA
설치 및 구동 방법
1. Mysql 설치
    sudo apt-get install mysql-server
2. Nodejs 설치
    sudo apt-get install npm
3. 데이터베이스 설정
    sudo mysql -u root -p;
    use mysql;
    update user set password=password('1111') where user='root';
    create database 4linux;
    create table logs (
        Id INT NOT NULL AUTO_INCREMENT,
        Date DATETIME NOT NULL,
        Temp DOUBLE NOT NULL,
        Light DOUBLE NOT NULL,
        Press DOUBLE NOT NULL,
        Alti DOUBLE NOT NULL,
        CONSTRAINT logs_PK PRIMARY KEY (Id)
    );
    create table wakeuplog(
        Id INT NOT NULL AUTO_INCREMENT,
        Alarmon DATETIME NOT NULL,
        Alarmoff DATETIME NOT NULL,
        Temp DOUBLE NOT NULL,
        Light DOUBLE NOT NULL,
        Press DOUBLE NOT NULL,
        Alti DOUBLE NOT NULL
        CONSTRAINT logs_PK PRIMARY KEY (Id)
    );
    
    위 과정 진행시 데이터베이스의 사용자 변경이나 비밀번호 변경이 있다면, main.c 에서 해당 소스를 수정해야 합니다.
    
4. 서버 구동
    cd ./nodejs
    node express.js &
5. 프로그램 빌드
    make
6. 프로그램 실행
    sudo ./program
