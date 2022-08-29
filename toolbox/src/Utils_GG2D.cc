/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2017                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                |
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

///
/// file: Utils_GG2D.cc
///

#include "Utils_GG2D.hh"

namespace Utils {

  /*\
   |   ____       _       _   ____  ____
   |  |  _ \ ___ (_)_ __ | |_|___ \|  _ \
   |  | |_) / _ \| | '_ \| __| __) | | | |
   |  |  __/ (_) | | | | | |_ / __/| |_| |
   |  |_|   \___/|_|_| |_|\__|_____|____/
  \*/

  /*\
   |   ____                                  _   ____  ____
   |  / ___|  ___  __ _ _ __ ___   ___ _ __ | |_|___ \|  _ \
   |  \___ \ / _ \/ _` | '_ ` _ \ / _ \ '_ \| __| __) | | | |
   |   ___) |  __/ (_| | | | | | |  __/ | | | |_ / __/| |_| |
   |  |____/ \___|\__, |_| |_| |_|\___|_| |_|\__|_____|____/
   |              |___/
  \*/

  #if 0

  template <typename Real>
  Real
  Segment2D<Real>::signed_distance( Point2D<Real> const & P ) const;

  template <typename Real>
  Point2D<Real>
  Segment2D<Real>::projection( Point2D<Real> const & P, Real & s, Real & t ) const;

  template <typename Real>
  Point2D<Real>
  Segment2D<Real>::eval( Real & s ) const;

  template <typename Real>
  Point2D<Real>
  Segment2D<Real>::eval( Real & s, Real & t ) const;

  #endif

  /*\
   |   ____            ____  ____
   |  | __ )  _____  _|___ \|  _ \
   |  |  _ \ / _ \ \/ / __) | | | |
   |  | |_) | (_) >  < / __/| |_| |
   |  |____/ \___/_/\_\_____|____/
  \*/

  /*\
   |   _____     _                   _      ____  ____
   |  |_   _| __(_) __ _ _ __   __ _| | ___|___ \|  _ \
   |    | || '__| |/ _` | '_ \ / _` | |/ _ \ __) | | | |
   |    | || |  | | (_| | | | | (_| | |  __// __/| |_| |
   |    |_||_|  |_|\__,_|_| |_|\__, |_|\___|_____|____/
   |                           |___/
  \*/

  /*\
   |   ____       _                         ____  ____
   |  |  _ \ ___ | |_   _  __ _  ___  _ __ |___ \|  _ \
   |  | |_) / _ \| | | | |/ _` |/ _ \| '_ \  __) | | | |
   |  |  __/ (_) | | |_| | (_| | (_) | | | |/ __/| |_| |
   |  |_|   \___/|_|\__, |\__, |\___/|_| |_|_____|____/
   |                |___/ |___/
  \*/

  /*
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  */

  template class Point2D<float>;
  template class Point2D<double>;

  template class Segment2D<float>;
  template class Segment2D<double>;

  template class Box2D<float>;
  template class Box2D<double>;

  template class Triangle2D<float>;
  template class Triangle2D<double>;

  template class Polygon2D<float>;
  template class Polygon2D<double>;

}

///
/// eof: Utils_GG2D.cc
///
