package org.mai.dep810.scala.iris

import org.mai.dep810.scala.iris.PetalSize.PetalSize

import scala.io.Source
import scala.util.Try

object IrisExample
{
  def main(args: Array[String]): Unit =
  {
    var flowers: List[Iris] = loadFromFile("iris.data")
    println(flowers)

    //get average sepal width
    val avgSepalLength = flowers.map(iris => iris.sepalWidth).sum/flowers.size
    println(avgSepalLength)

    //get average petal square - petal width multiplied on petal length
    val avgPetalLength = flowers.map(iris => iris.petalWidth*iris.petalLength).sum/flowers.size
    println(avgPetalLength)

    //get average petal square for flowers with sepal width > 4
    val avg2PetalSquare = flowers
        .filter(iris => iris.sepalWidth >4)
        .map(iris => iris.petalLength*iris.petalWidth)
        .sum / flowers.count(iris => iris.sepalWidth >4)

    val tuple = flowers
        .filter(iris => iris.sepalWidth > 4)
        .foldLeft(Tuple2[Double,Double](0,0))
    {
      (accumulator,flower) =>
        (accumulator._1 + flower.petalWidth * flower.petalLength,accumulator._2 + 1)
    }

    println(tuple._1/tuple._2)
    println(avg2PetalSquare)

    //get flowers grouped by Petal size (PetalSize.Small, etc.) with function getPetalSize
    val groupsByPetalSize = flowers.groupBy(iris=>getPetalSize(iris))
    println(groupsByPetalSize)

    //get max sepal width for flowers grouped by species
    val maxSepalWidthForGroupsBySpecies = flowers
      .groupBy(iris=> iris.species)
      .map((species)=>(species._1,species._2.map(specie=>specie.sepalWidth).max))
    println(maxSepalWidthForGroupsBySpecies)
  }

  def loadFromFile(path: String): List[Iris] =
  {
    Source
      .fromFile(path)
      .getLines
      .map(line => line.toIris)
      .filter
      {
        case Some(iris) => true
        case None => false
      }
      .map
      {
        case Some(iris) => iris
      }
      .toList
  }

  implicit class StringToIris(str: String)
  {
    def toIris: Option[Iris] = str.split(",") match
    {
      case Array(a,b,c,d,e) if isDouble(a) && isDouble(b) && isDouble(c) && isDouble(d) =>
        Some(
          Iris(
            a.toDouble,
            b.toDouble,
            c.toDouble,
            d.toDouble,
            e))
      case others => None
    }

    def isDouble(str: String): Boolean = Try(str.toDouble).isSuccess
  }

  def getPetalSize(iris: Iris): PetalSize =
  {
    val petalSquare = iris.petalLength * iris.petalWidth
    if(petalSquare < 2.0)
      PetalSize.Small
    if(petalSquare < 5.0)
      PetalSize.Medium
    PetalSize.Large
  }

}

object PetalSize extends Enumeration {
  type PetalSize = Value
  val Large, Medium, Small = Value
}

case class Iris(sepalLength: Double, sepalWidth: Double, petalLength: Double, petalWidth: Double, species: String)
