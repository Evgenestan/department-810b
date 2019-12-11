import Dependencies._

lazy val root = (project in file(".")).
  settings(
    inThisBuild(List(
      organization := "org.mai.dep810.scala",
      scalaVersion := "2.12.5",
      version      := "0.1.0-SNAPSHOT"
    )),
    name := "Lession10",
    libraryDependencies ++= Seq(scalaTest % Test, h2, xml)
  )
