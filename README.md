# Хеджирование опционных контрактов


## Теоретическое введение

Модель Блэка — Шоулза (Black-Scholes model) является одной из самых известных моделей ценообразования европейских опционов. 

### Содержание проекта

`useless.c` - программа выпоняет все команды, записанные в *.txt* файле 

`./useless com_bsm.txt` - запуск makefile для реализации модели Блэка-Шоулза (`class Black_Scholes_model`) и построения графиков
зависимостей цены базового актива от времени до срока погашения опциона (`stocks.py`) и создание видеоклипа (`stocks-gif.py`).

`./useless com_delta.txt` - запуск makefile для дельта-хеджирования (`class Hedging-simulator`) и построения гистограммы распределения числа сценариев в зависимости от прибыли держателя короткой позиции по опциону (bank balance) (`delta.py`).

Результаты работы:

- Таблица **bsm-data.csv** с данными о цене базового актива(акции) согласно модели BSM и таблица со значениями итоговой прибыли для различных сценариев хеджирования **delta-data.csv**. **.csv** файлы создаются с помощью библиотек в Python и используются в качестве dataframework для построения графиков.

- Файл **complex.pdf**, генерируемый `example.py` и заполняемый на основании **.csv** файлов.

- **Dynamics.gif** (fps = 6) - динамика цены акции. Создание с помощью библиотеки `moviepy`.

- **Delta-hedging.png** и **Stocks-simulation.png** - итоговые графики, загружаемый в **complex.pdf**.
