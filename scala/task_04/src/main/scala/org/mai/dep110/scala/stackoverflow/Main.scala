package org.mai.dep110.scala.stackoverflow

import org.mai.dep110.scala.iris.Config
import scopt.OptionParser

object Main extends App {
/*

StackOverflowLoader 1.0
Usage: StackOverflowLoader [load|clean|init|extract]

Command: load [options]
Load - это команда загрузки данных из файлов
  --path <value>           Путь к папке с файлами
  -a, --append             Не удалять данные при загрузке. По умолчанию данные будут перезатираться
Command: clean [options]
Удалить данные из базы данных
  -dt, --dropTables        Удалить таблицы
Command: init [options]
Создать таблицы
  -f, --forse              Пересоздать таблицы, если существуют
Command: extract [options]
Выгрузить данные в csv формате
  -q, --query              Запрос на выбор данных
  --file                   Файл, куда выгрузятся данные

* */
val parser = new OptionParser[Config]("StackOverflowLoader") {
    head("StackOverflowLoader","1.0")
    cmd("load")
    .action((_,c)=>c.copy(commandLoad = "load"))
    .text("Load - это команда загрузки данных из файлов")
    .children(
      opt[String]("path")
        .required()
        .action((f,c)=>c.copy(file = f))
        .text("Путь к папке с файлами"),
      opt[Unit]("append")
        .abbr("a")
        .action((f, c) => c.copy(append = true))
        .text("Не удалять данные при загрозке. По умолчанию данные будут перезатираться"))
      cmd("clean")
        .action((_, c) => c.copy(commandClear = "clean"))
        .text("Удалить данные из базы данных")
        .children(
          opt[Unit]("dropTables")
              .abbr("dt")
               .action((_, c) => c.copy(dropTables = true))
                .text("Удалить таблицы"))
  cmd("init")
    .action((_, c) => c.copy(commandInit = "init"))
    .text("Создать таблицы")
    .children(
      opt[Unit]("forse")
        .abbr("f")
        .action((_, c) => c.copy(forse = true))
        .text("Пересоздать таблицы, если существуют")
    )

  cmd("extract")
    .action((_,c)=>c.copy(commandLoad = "extract"))
    .text("Выгрузить данные в csv формате")
    .children(
      cmd("query")
        .abbr("q"),
      cmd("file")

    )
      }

}


