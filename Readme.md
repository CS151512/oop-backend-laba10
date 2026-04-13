# OmniCalc & Time Service Suite

![header_github](./img/header_github.png)

>[!IMPORTANT] 
> Данный проект представляет собой экосистему из двух
> независимых микросервисов, объединенных через Nginx Reverse 
> Proxy. Система демонстрирует продвинутые принципы ООП на C++, 
> работу с асинхронными HTTP-запросами, контейнеризацию и 
> персистентное хранение данных в PostgreSQL.


## Архитектура

```
laba_10/
├── services/
│   ├── math-service/            # Микросервис математических вычислений
│   │   ├── domain/              # Модели (Rational, Complex, Pair)
│   │   ├── service/             # Бизнес-логика
│   │   ├── controller/          # REST API (httplib)
│   │   ├── repository/          # Логирование операций в БД
│   │   ├── CMakeLists.txt
│   │   └── Dockerfile
│   ├── time-service/            # Микросервис управления временем
│   │   ├── domain/              # Модель Time (нормализация, валидация)
│   │   ├── service/             # Логика работы с репозиторием
│   │   ├── repository/          # Слой доступа к PostgreSQL (libpqxx)
│   │   ├── controller/          # API эндпоинты
│   │   └── Dockerfile
│   └── web-ui/                  # Frontend (Vue 3 + Nginx)
├── docker-compose.yml           # Оркестрация всей системы
└── nginx/                       # Конфигурация Reverse Proxy
```

![architecture](./img/archihecture.png)

## Схема базы данных

```mermaid
erDiagram
    TIME_RECORDS {
        serial id PK
        int hours "0-23"
        int minutes "0-59"
        int seconds "0-59"
        varchar formatted_time "HH:MM:SS"
        timestamp created_at
    }

    MATH_OPERATIONS {
        serial id PK
        varchar operation_name "e.g. Rational Add"
        jsonb input_data "Args in JSON"
        varchar result "Final value"
        timestamp created_at
    }
```

## Какие бывают запросы

> [!TIP]
> 200 OK <- сервер принял данные и произвел расчет
> ```shell
> curl 
> ```
> ответ:
> ```json
> {
> "area" : 235.619449
> }
> ```
> ![img_router_1](./img/img.png)
> 
> 200 OK <- сервер принял данные и произвел расчет
> ```shell
> curl 
> ```
> ответ:
> ```json
> {
> "result" : "6+8i"
> }
> ```
> ![img_router_2](./img/img_1.png)
> 
> 200 OK <- сервер принял две дроби и произвел расчеты
> ```shell
> curl 
> ```
> ответ:
> ```json
> {
> "result" : "1"
> }
> ```
> 
> ![img_router_3](./img/img_2.png)
> 
> 200 OK <- сервер принял данные и произвел расчет площади
> ```shell
> curl 
> ```
> ответ:
> ```json
> {
> "area" : "2.9047038"
> }
> ```
> ![img_router_4](./img/img_3.png)
> 

## Теперь как не надо

>[!CAUTION]
> 400 (Bad Request) <- **какое-то из полей пустое**
> ![img_err_1](./img/img_5.png)
> 
> ![img_err_4](./img/img_8.png)
> 
> ![img_err_4](./img/img_11.png)
> 
> 400 (Bad Request) <- **неправильный формат ввода**
> ![img_err_2](./img/img_6.png)
> 
> 400 (Bad Request) <- **деление на ноль**
> ![img_err_3](./img/img_7.png)
> 
> 500 (Internal Server Error) <- **мне было лень обрабатывать это**
> ![img_err_4](./img/img_9.png)
> 
> 400 (Bad Request) <- **радиус не может быть отрицательным**
> ![img_err_4](./img/img_10.png)
>

## Запуск
>[!IMPORTANT]
>  **Запуск через докер**
> ```shell
> cd infrastructure
> docker compose up -d --build
> ```
> 
> **Вот так можно посмотреть БДшку**
> ```shell
> пока лень писать сорр
> ```

![footer](./img/footer_github.png)

---
**by finnik**