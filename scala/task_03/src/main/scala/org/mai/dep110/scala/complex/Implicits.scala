package org.mai.dep110.scala.complex

case class Complex[A: Arithmetic](re: A, im: A) {
  override def toString: String = s"$re+${im}i"

  def +(that: Complex[A]): Complex[A] = implicitly[Arithmetic[A]].plus(this, that)
  def -(that: Complex[A]): Complex[A] = implicitly[Arithmetic[A]].subtract(this, that)
}

trait Arithmetic[A] {
  def plus(left: Complex[A], right: Complex[A]): Complex[A]
  def subtract(left: Complex[A], right: Complex[A]): Complex[A]
}

object Implicits {

  implicit object DoubleComplex extends Arithmetic[Double] {
    override def plus(left: Complex[Double], right: Complex[Double]): Complex[Double] = Complex(left.re + right.re, left.im + right.im)
    override def subtract(left: Complex[Double], right: Complex[Double]): Complex[Double] = Complex(left.re - right.re, left.im - right.im)

  }

  implicit object IntComplex extends Arithmetic[Int] {
    override def plus(left: Complex[Int], right: Complex[Int]): Complex[Int] = Complex(left.re + right.re, left.im + right.im)
    override def subtract(left: Complex[Int], right: Complex[Int]): Complex[Int] = Complex(left.re - right.re, left.im - right.im)
  }

  implicit object LongComplex extends Arithmetic[Long] {
    override def plus(left: Complex[Long], right: Complex[Long]): Complex[Long] = Complex(left.re + right.re, left.im + right.im)
    override def subtract(left: Complex[Long], right: Complex[Long]): Complex[Long] = Complex(left.re - right.re, left.im - right.im)
  }

  implicit def double2Complex(d: Double): Complex[Double] = Complex(d, 0.0)
  implicit def int2Complex(i: Int): Complex[Int] = Complex(i, 0)
  implicit def long2Complex(l : Long) : Complex[Long] = Complex(l,0)

  implicit def tuple2Complex[A: Arithmetic](number: (A, A)): Complex[A] = Complex(number._1, number._2)

  implicit class intComplex(d: Int) {
    def real: Complex[Int] = Complex(d, 0)
    def imaginary: Complex[Int] = Complex(0, d)
  }

  //
  implicit class doubleComplex(d: Double) {
    def real: Complex[Double] = Complex(d, 0.0)
    def imaginary: Complex[Double] = Complex(0.0, d)
  }

}
