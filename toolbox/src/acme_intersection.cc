/*
(***********************************************************************)
(*                                                                     *)
(* The ACME project                                                    *)
(*                                                                     *)
(* Copyright (c) 2020, Davide Stocco and Enrico Bertolazzi.            *)
(*                                                                     *)
(* The ACME project and its components are supplied under the terms of *)
(* the open source BSD 2-Clause License. The contents of the ACME      *)
(* project and its components may not be copied or disclosed except in *)
(* accordance with the terms of the BSD 2-Clause License.              *)
(*                                                                     *)
(* URL: https://opensource.org/licenses/BSD-2-Clause                   *)
(*                                                                     *)
(*    Davide Stocco                                                    *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: davide.stocco@unitn.it                                   *)
(*                                                                     *)
(*    Enrico Bertolazzi                                                *)
(*    Department of Industrial Engineering                             *)
(*    University of Trento                                             *)
(*    e-mail: enrico.bertolazzi@unitn.it                               *)
(*                                                                     *)
(***********************************************************************)
*/

///
/// file: acme_intersection.cc
///

#include "acme_intersection.hh"

namespace acme
{

  /*\
   |   ___       _                          _   _
   |  |_ _|_ __ | |_ ___ _ __ ___  ___  ___| |_(_) ___  _ __
   |   | || '_ \| __/ _ \ '__/ __|/ _ \/ __| __| |/ _ \| '_ \
   |   | || | | | ||  __/ |  \__ \  __/ (__| |_| | (_) | | | |
   |  |___|_| |_|\__\___|_|  |___/\___|\___|\__|_|\___/|_| |_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  entity *
  intersection(
    entity const *entity0_in,
    entity const *entity1_in,
    real          tolerance)
  {
    integer slide      = entity0_in->level() * 100 + entity1_in->level();
    bool    collide    = false;
    entity *entity_out = nullptr;
    if (entity0_in->isPoint() || entity1_in->isPoint())
    {
      switch (slide)
      {

        // - - - - - - - - - - - - - - POINT - - - - - - - - - - - - - -

      case 202:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 203:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 204:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 205:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 206:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 207:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 208:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 302:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 402:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 502:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 602:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 702:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 802:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<point const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      default:
        ACME_ERROR("acme::intersection(entity, entity): exception not handled (punctual).\n")
        collide = false;
        break;
      }
    }
    else if (isCollinear(entity0_in, entity1_in))
    {
      switch (slide)
      {

        // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

      case 303:
        entity_out = new line();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<line *>(entity_out),
          tolerance);
        break;

      case 304:
        entity_out = new ray();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<ray *>(entity_out),
          tolerance);
        break;

      case 306:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

      case 403:
        entity_out = new ray();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ray *>(entity_out),
          tolerance);

        break;

      case 404:
        entity_out = new ray();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<ray *>(entity_out),
          tolerance);
        if (!collide)
          delete entity_out;
        else
          break;

        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        if (!collide)
          delete entity_out;
        else
          break;

        ACME_ERROR("acme::intersection(ray, ray): Exception not handled");
        break;

      case 406:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

      case 603:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 604:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 606:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

      default:
        ACME_ERROR("acme::intersection(entity, entity): exception not handled (colliear).\n")
        break;
      }
    }
    else if (isCoplanar(entity0_in, entity1_in))
    {
      switch (slide)
      {

        // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

      case 303:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 304:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 305:
        entity_out = new line();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<line *>(entity_out),
          tolerance);
        break;

      case 306:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 307:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 308:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

      case 403:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 404:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 405:
        entity_out = new ray();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<ray *>(entity_out),
          tolerance);
        break;

      case 406:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 407:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 408:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - PLANE - - - - - - - - - - - - - -

      case 503:
        entity_out = new line();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<line *>(entity_out),
          tolerance);
        break;

      case 504:
        entity_out = new ray();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<ray *>(entity_out),
          tolerance);
        break;

      case 505:
        entity_out = new plane();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<plane *>(entity_out),
          tolerance);
        break;

      case 506:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 507:
        entity_out = new triangle();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<triangle *>(entity_out),
          tolerance);
        break;

      case 508:
        entity_out = new disk();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<disk *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

      case 603:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 604:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 605:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 606:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 607:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 608:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - TRIANGLE - - - - - - - - - - - - - -

      case 703:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 704:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 705:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 706:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 707:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

      case 708:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - DISK - - - - - - - - - - - - - -

      case 803:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 804:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 805:
        entity_out = new disk();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<disk *>(entity_out),
          tolerance);
        break;

      case 806:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 807:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

      case 808:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

      default:
        ACME_ERROR("acme::intersection(entity, entity): exception not handled (coplanar).\n")
        break;
      }
    }
    else
    {
      switch (slide)
      {

        // - - - - - - - - - - - - - - LINE - - - - - - - - - - - - - -

      case 303:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 304:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 305:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 306:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 307:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 308:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 309:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - RAY - - - - - - - - - - - - - -

      case 403:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 404:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 405:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 406:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 407:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 408:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 409:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - PLANE - - - - - - - - - - - - - -

      case 503:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 504:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 505:
        entity_out = new line();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<line *>(entity_out),
          tolerance);
        break;

      case 506:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 507:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 508:
        collide = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 509:
        entity_out = new disk();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<disk *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - SEGMENT - - - - - - - - - - - - - -

      case 603:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 604:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 605:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 606:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 607:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 608:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 609:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - TRIANGLE - - - - - - - - - - - - - -

      case 703:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 704:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 705:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 706:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 707:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 708:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 709:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - DISK - - - - - - - - - - - - - -

      case 803:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 804:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 805:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 806:
        entity_out = new point();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<point *>(entity_out),
          tolerance);
        break;

      case 807:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 808:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 809:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<disk const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - BALL - - - - - - - - - - - - - -

      case 903:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<line const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 904:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<ray const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 905:
        entity_out = new disk();
        collide    = intersection(
          *dynamic_cast<plane const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<disk *>(entity_out),
          tolerance);
        break;

      case 906:
        entity_out = new segment();
        collide    = intersection(
          *dynamic_cast<segment const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<segment *>(entity_out),
          tolerance);
        break;

      case 907:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<triangle const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

      case 908:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<disk const *>(entity1_in),
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

      case 909:
        entity_out = new none();
        collide    = intersection(
          *dynamic_cast<ball const *>(entity0_in),
          *dynamic_cast<ball const *>(entity1_in),
          *dynamic_cast<none *>(entity_out),
          tolerance);
        break;

        // - - - - - - - - - - - - - - DEFAULT - - - - - - - - - - - - - -

      default:
        ACME_ERROR("acme::intersection(entity, entity): exception not handled (general).\n")
        break;
      }
    }
    if (!collide)
    {
      delete entity_out;
      entity_out = new none();
      return entity_out;
    }
    return entity_out;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |    ____      _ _ _
   |   / ___|___ | | (_)_ __   ___  __ _ _ __
   |  | |   / _ \| | | | '_ \ / _ \/ _` | '__|
   |  | |__| (_) | | | | | | |  __/ (_| | |
   |   \____\___/|_|_|_|_| |_|\___|\__,_|_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line0_in,
    line const &line1_in,
    line       &line_out,
    real        tolerance)
  {
    if (isCollinear(line0_in, line1_in, tolerance))
    {
      line_out = line0_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const &ray0_in,
    ray const &ray1_in,
    ray       &ray_out,
    real       tolerance)
  {
    if (isCollinear(ray0_in, ray1_in, tolerance) && ray0_in.direction().dot(ray1_in.direction()) > 0.0)
    {
      if (ray0_in.isInside(ray1_in.origin(), tolerance))
      {
        ray_out = ray1_in;
        return true;
      }
      else if (ray1_in.isInside(ray0_in.origin(), tolerance))
      {
        ray_out = ray0_in;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const &ray0_in,
    ray const &ray1_in,
    segment   &segment_out,
    real       tolerance)
  {
    if (isCollinear(ray0_in, ray1_in, tolerance) && ray0_in.direction().dot(ray1_in.direction()) < 0.0)
    {
      if (ray0_in.isInside(ray1_in.origin(), tolerance) && ray1_in.isInside(ray0_in.origin(), tolerance))
      {
        segment_out.vertex(0) = ray0_in.origin();
        segment_out.vertex(1) = ray1_in.origin();
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const &segment0_in,
    segment const &segment1_in,
    segment       &segment_out,
    real           tolerance)
  {
    if (isCollinear(segment0_in, segment1_in, tolerance))
    {
      //
      //   p0       p1   p0       p1
      //   o---s0---o    o---s1---o
      //
      point s0_p0(segment0_in.vertex(0));
      point s0_p1(segment0_in.vertex(1));
      point s1_p0(segment1_in.vertex(0));
      point s1_p1(segment1_in.vertex(1));
      int   sx_px_in_sx =
        int(segment0_in.isInside(s1_p1, tolerance)) +
        int(segment0_in.isInside(s1_p0, tolerance)) * 10 +
        int(segment1_in.isInside(s0_p1, tolerance)) * 100 +
        int(segment1_in.isInside(s0_p0, tolerance)) * 1000;

      switch (sx_px_in_sx)
      {
      //
      //                    Segments coincides
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      1      |      1      |      1      |      1      |
      case 1111: // 1111
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s0_p1;
        return true;

      //                       An extrema coincides
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      0      |      1      |      1      |      1      |
      // |      1      |      0      |      1      |      1      |
      // |      1      |      1      |      0      |      1      |
      // |      1      |      1      |      1      |      0      |
      case 111: // 0111
        segment_out.vertex(0) = s1_p0;
        segment_out.vertex(1) = s1_p1;
        return true;

      case 1011: // 1011
        segment_out.vertex(0) = s1_p0;
        segment_out.vertex(1) = s1_p1;
        return true;

      case 1101: // 1101
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s0_p1;
        return true;

      case 1110: // 1110
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s0_p1;
        return true;

      //                      Partial overlap
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      0      |      1      |      0      |      1      |
      // |      0      |      1      |      1      |      0      |
      // |      1      |      0      |      0      |      1      |
      // |      1      |      0      |      1      |      0      |
      case 101: // 0101
        segment_out.vertex(0) = s0_p1;
        segment_out.vertex(1) = s1_p1;
        return true;

      case 110: // 0110
        segment_out.vertex(0) = s0_p1;
        segment_out.vertex(1) = s1_p0;
        return true;

      case 1001: // 1001
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s1_p1;
        return true;

      case 1010: // 1010
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s1_p0;
        return true;

      //                 One segment is inside
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      1      |      1      |      0      |      0      |
      // |      0      |      0      |      1      |      1      |
      case 1100: // 1100
        segment_out.vertex(0) = s0_p0;
        segment_out.vertex(1) = s0_p1;
        return true;

      case 11: // 0011
        segment_out.vertex(0) = s1_p0;
        segment_out.vertex(1) = s1_p1;
        return true;

      //                   No intersection case
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      0      |      0      |      0      |      0      |
      case 0: // 0000
        return false;

      //                  Exception not handled
      // | s0_p0_in_s1 | s0_p1_in_s1 | s1_p0_in_s0 | s1_p1_in_s0 |
      // |      0      |      0      |      0      |      1      |
      // |      0      |      0      |      1      |      0      |
      // |      0      |      1      |      0      |      0      |
      // |      1      |      0      |      0      |      0      |
      default:
        ACME_ERROR("acme::intersection(segment, segment, segment): exception not handled.\n")
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line_in,
    ray const  &ray_in,
    ray        &ray_out,
    real        tolerance)
  {
    if (isCollinear(line_in, ray_in, tolerance))
    {
      ray_out = ray_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const    &line_in,
    segment const &segment_in,
    segment       &segment_out,
    real           tolerance)
  {
    if (isCollinear(line_in, segment_in, tolerance))
    {
      segment_out = segment_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const     &ray_in,
    segment const &segment_in,
    segment       &segment_out,
    real           tolerance)
  {
    point point_0(segment_in.vertex(0));
    point point_1(segment_in.vertex(1));
    if (isCollinear(ray_in, segment_in, tolerance))
    {
      if (ray_in.isInside(point_0, tolerance) && ray_in.isInside(point_1, tolerance))
      {
        segment_out = segment_in;
        return true;
      }
      else if (ray_in.isInside(point_0, tolerance) && !ray_in.isInside(point_1, tolerance))
      {
        segment_out.vertex(0) = ray_in.origin();
        segment_out.vertex(1) = point_0;
        return true;
      }
      else if (!ray_in.isInside(point_0, tolerance) && ray_in.isInside(point_1, tolerance))
      {
        segment_out.vertex(0) = ray_in.origin();
        segment_out.vertex(1) = point_1;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   ____                   _               _
   |  |  _ \ _   _ _ __   ___| |_ _   _  __ _| |
   |  | |_) | | | | '_ \ / __| __| | | |/ _` | |
   |  |  __/| |_| | | | | (__| |_| |_| | (_| | |
   |  |_|    \__,_|_| |_|\___|\__|\__,_|\__,_|_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const &point0_in,
    point const &point1_in,
    point       &point_out,
    real         tolerance)
  {
    if (point0_in.isApprox(point1_in, tolerance))
    {
      point_out = point0_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const &point_in,
    line const  &line_in,
    point       &point_out,
    real         tolerance)
  {
    if (line_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const &point_in,
    ray const   &ray_in,
    point       &point_out,
    real         tolerance)
  {
    if (ray_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const &point_in,
    plane const &plane_in,
    point       &point_out,
    real         tolerance)
  {
    if (plane_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const   &point_in,
    segment const &segment_in,
    point         &point_out,
    real           tolerance)
  {
    if (segment_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const    &point_in,
    triangle const &triangle_in,
    point          &point_out,
    real            tolerance)
  {
    if (triangle_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    point const &point_in,
    disk const  &disk_in,
    point       &point_out,
    real         tolerance)
  {
    if (disk_in.isInside(point_in, tolerance))
    {
      point_out = point_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  /*\
   |    ____                      _
   |   / ___| ___ _ __   ___ _ __(_) ___
   |  | |  _ / _ \ '_ \ / _ \ '__| |/ __|
   |  | |_| |  __/ | | |  __/ |  | | (__
   |   \____|\___|_| |_|\___|_|  |_|\___|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line0_in,
    line const &line1_in,
    point      &point_out,
    real        tolerance)
  {
    if (!isParallel(line0_in, line1_in, tolerance))
    {
      point origin_0(line0_in.origin());
      vec3  direction_0(line0_in.direction());
      point origin_1(line1_in.origin());
      vec3  direction_1(line1_in.direction());

      vec3 a(direction_0.cross(direction_1));
      vec3 b((origin_1 - origin_0).cross(direction_1));
      real t    = b.dot(a) / a.dot(a);
      point_out = origin_0 + (t * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const &ray0_in,
    ray const &ray1_in,
    point     &point_out,
    real       tolerance)
  {
    if (!isParallel(ray0_in, ray1_in, tolerance))
    {
      point origin_0(ray0_in.origin());
      vec3  direction_0(ray0_in.direction());
      point origin_1(ray1_in.origin());
      vec3  direction_1(ray1_in.direction());

      vec3 a_0(direction_0.cross(direction_1));
      vec3 b_0((origin_1 - origin_0).cross(direction_1));
      real t0 = b_0.dot(a_0) / a_0.dot(a_0);

      vec3 a_1(-a_0);
      vec3 b_1((origin_0 - origin_1).cross(direction_0));
      real t1 = b_1.dot(a_1) / a_1.dot(a_1);

      if (t0 < 0.0 || t1 < 0.0)
        return false;
      point_out = origin_0 + (t0 * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const &segment0_in,
    segment const &segment1_in,
    point         &point_out,
    real           tolerance)
  {
    if (!isParallel(segment0_in, segment1_in, tolerance))
    {
      point origin_0(segment0_in.vertex(0));
      vec3  direction_0(segment0_in.toVector());
      point origin_1(segment1_in.vertex(0));
      vec3  direction_1(segment1_in.toVector());

      vec3 a_0(direction_0.cross(direction_1));
      vec3 b_0((origin_1 - origin_0).cross(direction_1));
      real t0 = b_0.dot(a_0) / a_0.dot(a_0);

      vec3 a_1(-a_0);
      vec3 b_1((origin_0 - origin_1).cross(direction_0));
      real t1 = b_1.dot(a_1) / a_1.dot(a_1);

      if (t0 < 0.0 || t1 < 0.0 || t0 > 1.0 || t1 > 1.0)
        return false;
      point_out = origin_0 + (t0 * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line_in,
    ray const  &ray_in,
    point      &point_out,
    real        tolerance)
  {
    if (!isParallel(line_in, ray_in, tolerance))
    {
      point origin_0(line_in.origin());
      vec3  direction_0(line_in.direction());
      point origin_1(ray_in.origin());
      vec3  direction_1(ray_in.direction());

      vec3 a_0(direction_0.cross(direction_1));
      vec3 b_0((origin_1 - origin_0).cross(direction_1));
      real t0 = b_0.dot(a_0) / a_0.dot(a_0);

      vec3 a_1(-a_0);
      vec3 b_1((origin_0 - origin_1).cross(direction_0));
      real t1 = b_1.dot(a_1) / a_1.dot(a_1);

      if (t1 < 0.0)
        return false;
      point_out = origin_0 + (t0 * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const    &line_in,
    segment const &segment_in,
    point         &point_out,
    real           tolerance)
  {
    if (!isParallel(line_in, segment_in, tolerance))
    {
      point origin_0(line_in.origin());
      vec3  direction_0(line_in.direction());
      point origin_1(segment_in.vertex(0));
      vec3  direction_1(segment_in.toVector());

      vec3 a_0(direction_0.cross(direction_1));
      vec3 b_0((origin_1 - origin_0).cross(direction_1));
      real t0 = b_0.dot(a_0) / a_0.dot(a_0);

      vec3 a_1(-a_0);
      vec3 b_1((origin_0 - origin_1).cross(direction_0));
      real t1 = b_1.dot(a_1) / a_1.dot(a_1);

      if (t1 < 0.0 || t1 > 1.0)
        return false;
      point_out = origin_0 + (t0 * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const     &ray_in,
    segment const &segment_in,
    point         &point_out,
    real           tolerance)
  {
    if (!isParallel(ray_in, segment_in, tolerance))
    {
      point origin_0(ray_in.origin());
      vec3  direction_0(ray_in.direction());
      point origin_1(segment_in.vertex(0));
      vec3  direction_1(segment_in.toVector());

      vec3 a_0(direction_0.cross(direction_1));
      vec3 b_0((origin_1 - origin_0).cross(direction_1));
      real t0 = b_0.dot(a_0) / a_0.dot(a_0);

      vec3 a_1(-a_0);
      vec3 b_1((origin_0 - origin_1).cross(direction_0));
      real t1 = b_1.dot(a_1) / a_1.dot(a_1);

      if (t0 < 0.0 || t1 < 0.0 || t1 > 1.0)
        return false;
      point_out = origin_0 + (t0 * direction_0);
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |    ____            _
   |   / ___|___  _ __ | | __ _ _ __   __ _ _ __
   |  | |   / _ \| '_ \| |/ _` | '_ \ / _` | '__|
   |  | |__| (_) | |_) | | (_| | | | | (_| | |
   |   \____\___/| .__/|_|\__,_|_| |_|\__,_|_|
   |             |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane0_in,
    plane const &plane1_in,
    plane       &plane_out,
    real         tolerance)
  {
    if (isCoplanar(plane0_in, plane1_in, tolerance))
    {
      plane_out = plane0_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    triangle const &triangle0_in,
    triangle const &triangle1_in,
    none           &none_out,
    real            tolerance)
  {
    ACME_ERROR("acme::intersection(triangle, triangle): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    disk const &disk0_in,
    disk const &disk1_in,
    none       &none_out,
    real        tolerance)
  {
    ACME_ERROR("acme::intersection(disk, disk): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ball const &ball0_in,
    ball const &ball1_in,
    none       &none_out,
    real        tolerance)
  {
    ACME_ERROR("acme::intersection(ball, ball): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const  &line_in,
    plane const &plane_in,
    line        &line_out,
    real         tolerance)
  {
    if (isCoplanar(line_in, plane_in, tolerance))
    {
      line_out = line_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const     &line_in,
    triangle const &triangle_in,
    segment        &segment_out,
    real            tolerance)
  {
    point point0, point1, point2;
    bool  bool0 = intersection(line_in, triangle_in.edge(0), point0, tolerance);
    bool  bool1 = intersection(line_in, triangle_in.edge(1), point1, tolerance);
    bool  bool2 = intersection(line_in, triangle_in.edge(2), point2, tolerance);

    if (bool0 && bool1 && !bool2)
    {
      segment_out.vertex(0) = point0;
      segment_out.vertex(1) = point1;
      return true;
    }
    else if (!bool0 && bool1 && bool2)
    {
      segment_out.vertex(0) = point1;
      segment_out.vertex(1) = point2;
      return true;
    }
    else if (bool0 && !bool1 && bool2)
    {
      segment_out.vertex(0) = point2;
      segment_out.vertex(1) = point0;
      return true;
    }
    else if (bool0 && bool1 && bool2)
    {
      if (point0.isApprox(point1, tolerance))
      {
        segment_out.vertex(0) = point1;
        segment_out.vertex(1) = point2;
        return true;
      }
      else if (point1.isApprox(point2, tolerance))
      {
        segment_out.vertex(0) = point0;
        segment_out.vertex(1) = point1;
        return true;
      }
      else if (point0.isApprox(point2, tolerance))
      {
        segment_out.vertex(0) = point0;
        segment_out.vertex(1) = point1;
        return true;
      }
      else
      {
        ACME_ERROR("acme::intersection(line, triangle, segment): exception not handled.\n")
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line_in,
    disk const &disk_in,
    segment    &segment_out,
    real        tolerance)
  {
    real  disk_radius = disk_in.radius();
    point disk_center(disk_in.center());
    point line_origin(line_in.origin());
    vec3  line_direction(line_in.direction());
    vec3  diff(line_origin - disk_center);

    real a2 = line_direction.dot(line_direction);
    real a1 = diff.dot(line_direction);
    real a0 = diff.dot(diff) - disk_radius * disk_radius;

    real discriminant = a1 * a1 - a0 * a2;
    if (discriminant < -tolerance)
      return false;

    real inv = 1 / a2;
    if (std::abs(discriminant) < tolerance)
    {
      point int_point(line_origin - (a1 * inv) * line_direction);
      segment_out.vertex(0) = int_point;
      segment_out.vertex(1) = int_point;
      return true;
    }
    real root             = std::sqrt(discriminant);
    segment_out.vertex(0) = line_origin - ((a1 + root) * inv) * line_direction;
    segment_out.vertex(1) = line_origin - ((a1 - root) * inv) * line_direction;
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const   &ray_in,
    plane const &plane_in,
    ray         &ray_out,
    real         tolerance)
  {
    if (isCoplanar(ray_in, plane_in, tolerance))
    {
      ray_out = ray_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const      &ray_in,
    triangle const &triangle_in,
    segment        &segment_out,
    real            tolerance)
  {
    segment tmp_segment;
    if (intersection(line(ray_in.origin(), ray_in.direction()), triangle_in, tmp_segment, tolerance))
      return intersection(ray_in, tmp_segment, segment_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const  &ray_in,
    disk const &disk_in,
    segment    &segment_out,
    real        tolerance)
  {
    real  disk_radius = disk_in.radius();
    point disk_center(disk_in.center());
    point ray_origin(ray_in.origin());
    vec3  ray_direction(ray_in.direction());
    vec3  diff(ray_origin - disk_center);

    real a2 = ray_direction.dot(ray_direction);
    real a1 = diff.dot(ray_direction);
    real a0 = diff.dot(diff) - disk_radius * disk_radius;

    real discriminant = a1 * a1 - a0 * a2;
    if (discriminant < -tolerance)
      return false;

    real inv = 1 / a2;
    if (std::abs(discriminant) < tolerance)
    {
      real t = -a1 * inv;
      if (t < 0.0)
        return false;
      point int_point(ray_origin + t * ray_direction);
      segment_out.vertex(0) = int_point;
      segment_out.vertex(1) = int_point;
      return true;
    }
    real root = std::sqrt(discriminant);
    real t0   = -(a1 + root) * inv;
    real t1   = -(a1 - root) * inv;
    if (t0 < 0.0 && t1 < 0.0)
      return false;
    t0                    = std::max(0.0, t0);
    t1                    = std::max(0.0, t1);
    segment_out.vertex(0) = ray_origin + t0 * ray_direction;
    segment_out.vertex(1) = ray_origin + t1 * ray_direction;
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const   &plane_in,
    segment const &segment_in,
    segment       &segment_out,
    real           tolerance)
  {
    if (isCoplanar(plane_in, segment_in, tolerance))
    {
      segment_out = segment_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const    &plane_in,
    triangle const &triangle_in,
    triangle       &triangle_out,
    real            tolerance)
  {
    if (isCoplanar(plane_in, triangle_in, tolerance))
    {
      triangle_out = triangle_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane_in,
    disk const  &disk_in,
    disk        &disk_out,
    real         tolerance)
  {
    if (isCoplanar(plane_in, disk_in, tolerance))
    {
      disk_out = disk_in;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const  &segment_in,
    triangle const &triangle_in,
    segment        &segment_out,
    real            tolerance)
  {
    line    tmp_line(segment_in.vertex(0), segment_in.toUnitVector());
    segment tmp_segment;
    if (intersection(tmp_line, triangle_in, tmp_segment, tolerance))
      return intersection(segment_in, tmp_segment, segment_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const &segment_in,
    disk const    &disk_in,
    segment       &segment_out,
    real           tolerance)
  {
    if (segment_in.isDegenerated(tolerance) || disk_in.isDegenerated(tolerance))
      return false;

    real  disk_radius = disk_in.radius();
    point disk_center(disk_in.center());
    point segment_origin(segment_in.vertex(0));
    vec3  segment_direction(segment_in.toVector());
    vec3  diff(segment_origin - disk_center);

    real a2 = segment_direction.dot(segment_direction);
    real a1 = diff.dot(segment_direction);
    real a0 = diff.dot(diff) - disk_radius * disk_radius;

    real discriminant = a1 * a1 - a0 * a2;
    if (discriminant < -tolerance)
      return false;

    real inv = 1 / a2;
    if (std::abs(discriminant) < tolerance)
    {
      real t = -a1 * inv;
      if (t < 0.0 || t > 1.0)
        return false;
      point int_point(segment_origin + t * segment_direction);
      segment_out.vertex(0) = int_point;
      segment_out.vertex(1) = int_point;
      return true;
    }
    real root = std::sqrt(discriminant);
    real t0   = -(a1 + root) * inv;
    real t1   = -(a1 - root) * inv;
    if ((t0 < 0.0 && t1 < 0.0) || (t0 > 1.0 && t1 > 1.0))
      return false;
    t0                    = std::max(0.0, std::min(t0, 1.0));
    t1                    = std::max(0.0, std::min(t1, 1.0));
    segment_out.vertex(0) = segment_origin + t0 * segment_direction;
    segment_out.vertex(1) = segment_origin + t1 * segment_direction;
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    triangle const &triangle_in,
    disk const     &disk_in,
    none           &none_out,
    real            tolerance)
  {
    ACME_ERROR("acme::intersection(triangle, disk): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   _   _              ____            _
   |  | \ | | ___  _ __  / ___|___  _ __ | | __ _ _ __   __ _ _ __
   |  |  \| |/ _ \| '_ \| |   / _ \| '_ \| |/ _` | '_ \ / _` | '__|
   |  | |\  | (_) | | | | |__| (_) | |_) | | (_| | | | | (_| | |
   |  |_| \_|\___/|_| |_|\____\___/| .__/|_|\__,_|_| |_|\__,_|_|
   |                               |_|
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane0_in,
    plane const &plane1_in,
    line        &line,
    real         tolerance)
  {
    vec3 normal0(plane0_in.normal().normalized());
    vec3 normal1(plane1_in.normal().normalized());
    real d0 = -plane0_in.d();
    real d1 = -plane1_in.d();

    vec3 direction = normal0.cross(normal1);
    real dot       = normal0.dot(normal1);
    real norm      = direction.norm();
    if (isApprox(norm * norm, 0.0, tolerance))
    {
      return false;
    }
    else
    {
      real invDet      = 1.0 / (1.0 - dot * dot);
      real c0          = (d0 - dot * d1) * invDet;
      real c1          = (d1 - dot * d0) * invDet;
      line.origin()    = c0 * normal0 + c1 * normal1;
      line.direction() = direction;
      return true;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane0_in,
    plane const &plane1_in,
    plane const &plane2_in,
    point       &point_out,
    real         tolerance)
  {
    vec3 normal0(plane0_in.normal());
    vec3 normal1(plane1_in.normal());
    vec3 normal2(plane2_in.normal());

    mat3 Mat;
    Mat << normal0, normal1, normal2;
    real det = Mat.determinant();
    if (isApprox(det, 0.0, tolerance))
    {
      return false;
    }
    else
    {
      point_out = (normal1.cross(normal2) * -plane0_in.d() +
                   normal2.cross(normal0) * -plane1_in.d() +
                   normal0.cross(normal1) * -plane2_in.d()) /
                  det;
      return true;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    triangle const &triangle0_in,
    triangle const &triangle1_in,
    segment        &segment_out,
    real            tolerance)
  {
    line tmp_line;
    if (intersection(triangle0_in.layingPlane(), triangle1_in.layingPlane(), tmp_line, tolerance))
    {
      segment tmp_segment0, tmp_segment1;
      intersection(tmp_line, triangle0_in, tmp_segment0, tolerance);
      intersection(tmp_line, triangle1_in, tmp_segment1, tolerance);
      return intersection(tmp_segment0, tmp_segment1, segment_out, tolerance);
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    disk const &disk0_in,
    disk const &disk1_in,
    segment    &segment_out,
    real        tolerance)
  {
    line tmp_line;
    if (intersection(disk0_in.layingPlane(), disk1_in.layingPlane(), tmp_line, tolerance))
    {
      segment tmp_segment0, tmp_segment1;
      intersection(tmp_line, disk0_in, tmp_segment0, tolerance);
      intersection(tmp_line, disk1_in, tmp_segment1, tolerance);
      return intersection(tmp_segment0, tmp_segment1, segment_out, tolerance);
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const  &line_in,
    plane const &plane_in,
    point       &point_out,
    real         tolerance)
  {
    vec3 origin(line_in.origin());
    vec3 direction(line_in.direction());
    real det = plane_in.normal().dot(direction);
    if (std::abs(det) > tolerance)
    {
      real t    = (plane_in.origin() - origin).dot(plane_in.normal()) / det;
      point_out = origin + t * direction;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const     &line_in,
    triangle const &triangle_in,
    point          &point_out,
    real            tolerance)
  {
    point vertex0(triangle_in.vertex(0));
    point vertex1(triangle_in.vertex(1));
    point vertex2(triangle_in.vertex(2));
    vec3  edge1(vertex1 - vertex0);
    vec3  edge2(vertex2 - vertex0);
    point origin(line_in.origin());
    vec3  direction(line_in.direction());

    vec3 h, s, q;
    real a, f, u, v;
    h = direction.cross(edge2);
    a = edge1.dot(h);
    if (a > -tolerance && a < tolerance)
      return false;
    f = 1.0 / a;
    s = origin - vertex0;
    u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
      return false;
    q = s.cross(edge1);
    v = f * direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
      return false;
    real t    = f * edge2.dot(q);
    point_out = origin + t * direction;
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line_in,
    disk const &disk_in,
    point      &point_out,
    real        tolerance)
  {
    if (intersection(line_in, disk_in.layingPlane(), point_out, tolerance))
      return disk_in.isInside(point_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    line const &line_in,
    ball const &ball_in,
    segment    &segment_out,
    real        tolerance)
  {
    vec3 origin(line_in.origin());
    vec3 direction(line_in.toUnitVector());
    vec3 diff(origin - ball_in.center());
    real a0    = diff.dot(diff) - ball_in.radius() * ball_in.radius();
    real a1    = direction.dot(diff);
    real discr = a1 * a1 - a0;
    if (discr > tolerance)
    {
      real root             = std::sqrt(discr);
      segment_out.vertex(0) = origin + (-a1 - root) * direction;
      segment_out.vertex(1) = origin + (-a1 + root) * direction;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const   &ray_in,
    plane const &plane_in,
    point       &point_out,
    real         tolerance)
  {
    vec3 origin(ray_in.origin());
    vec3 direction(ray_in.direction());
    real det = direction.dot(plane_in.normal());
    if (std::abs(det) > tolerance)
    {
      real t = -(origin - plane_in.origin()).dot(plane_in.normal()) / det;
      if (t > tolerance)
      {
        point_out = origin + t * direction;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const      &ray_in,
    triangle const &triangle_in,
    point          &point_out,
    real            tolerance)
  {
    point vertex0(triangle_in.vertex(0));
    point vertex1(triangle_in.vertex(1));
    point vertex2(triangle_in.vertex(2));
    vec3  edge1(vertex1 - vertex0);
    vec3  edge2(vertex2 - vertex0);
    point origin(ray_in.origin());
    vec3  direction(ray_in.direction());

    vec3 h, s, q;
    real a, f, u, v;
    h = direction.cross(edge2);
    a = edge1.dot(h);
    if (a > -tolerance && a < tolerance)
      return false;
    f = 1.0 / a;
    s = origin - vertex0;
    u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
      return false;
    q = s.cross(edge1);
    v = f * direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
      return false;
    real t = f * edge2.dot(q);
    if (t >= 0.0)
    {
      point_out = origin + t * direction;
      return true;
    }
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const  &ray_in,
    disk const &disk_in,
    point      &point_out,
    real        tolerance)
  {
    if (intersection(ray_in, disk_in.layingPlane(), point_out, tolerance))
      return disk_in.isInside(point_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    ray const  &ray_in,
    ball const &ball_in,
    segment    &segment_out,
    real        tolerance)
  {
    vec3 origin(ray_in.origin());
    vec3 direction(ray_in.toUnitVector());
    vec3 diff(origin - ball_in.center());
    real a0    = diff.dot(diff) - ball_in.radius() * ball_in.radius();
    real a1    = direction.dot(diff);
    real discr = a1 * a1 - a0;
    if (discr > tolerance)
    {
      real root = std::sqrt(discr);
      real t0   = -a1 - root;
      real t1   = -a1 + root;
      if (t0 < 0.0 && t1 < 0.0)
        return false;
      t0                    = std::max(t0, 0.0);
      t1                    = std::max(t1, 0.0);
      segment_out.vertex(0) = origin + t0 * direction;
      segment_out.vertex(1) = origin + t1 * direction;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const   &plane_in,
    segment const &segment_in,
    point         &point_out,
    real           tolerance)
  {
    vec3 origin(segment_in.vertex(0));
    vec3 direction(segment_in.toVector());
    real det = direction.dot(plane_in.normal());
    if (std::abs(det) > tolerance)
    {
      real t = -(origin - plane_in.origin()).dot(plane_in.normal()) / det;
      if (t >= 0.0 && t <= 1.0)
      {
        point_out = origin + t * direction;
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const    &plane_in,
    triangle const &triangle_in,
    segment        &segment_out,
    real            tolerance)
  {
    line tmp_line;
    if (intersection(plane_in, triangle_in.layingPlane(), tmp_line, tolerance))
      return intersection(tmp_line, triangle_in, segment_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane_in,
    disk const  &disk_in,
    segment     &segment_out,
    real         tolerance)
  {
    line tmp_line;
    if (intersection(plane_in, disk_in.layingPlane(), tmp_line, tolerance))
      return intersection(tmp_line, disk_in, segment_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    plane const &plane_in,
    ball const  &ball_in,
    disk        &disk_out,
    real         tolerance)
  {
    vec3 normal(plane_in.unitNormal());
    real signed_distance = (ball_in.center() - plane_in.origin()).dot(normal);
    real distance        = std::abs(signed_distance);
    if (distance <= ball_in.radius())
    {
      disk_out.radius() = std::sqrt((ball_in.radius() + distance) * (ball_in.radius() - distance));
      disk_out.center() = ball_in.center() - signed_distance * normal;
      disk_out.normal() = normal;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const  &segment_in,
    triangle const &triangle_in,
    point          &point_out,
    real            tolerance)
  {
    point vertex0(triangle_in.vertex(0));
    point vertex1(triangle_in.vertex(1));
    point vertex2(triangle_in.vertex(2));
    vec3  edge1(vertex1 - vertex0);
    vec3  edge2(vertex2 - vertex0);
    point origin(segment_in.vertex(0));
    vec3  direction(segment_in.toVector());

    vec3 h, s, q;
    real a, f, u, v;
    h = direction.cross(edge2);
    a = edge1.dot(h);
    if (a > -tolerance && a < tolerance)
      return false;
    f = 1.0 / a;
    s = origin - vertex0;
    u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
      return false;
    q = s.cross(edge1);
    v = f * direction.dot(q);
    if (v < 0.0 || u + v > 1.0)
      return false;
    real t = f * edge2.dot(q);
    if (t >= 0.0 && t <= 1.0)
    {
      point_out = origin + direction * t;
      return true;
    }
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const &segment_in,
    disk const    &disk_in,
    point         &point_out,
    real           tolerance)
  {
    if (intersection(disk_in.layingPlane(), segment_in, point_out, tolerance))
      return disk_in.isInside(point_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    segment const &segment_in,
    ball const    &ball_in,
    segment       &segment_out,
    real           tolerance)
  {
    vec3 origin(segment_in.vertex(0));
    vec3 direction(segment_in.toVector());
    vec3 diff(origin - ball_in.center());
    real a0    = diff.dot(diff) - ball_in.radius() * ball_in.radius();
    real a1    = direction.dot(diff);
    real discr = a1 * a1 - a0;
    if (discr > tolerance)
    {
      real root = std::sqrt(discr);
      real t0   = -a1 - root;
      real t1   = -a1 + root;
      if ((t0 < 0.0 && t1 < 0.0) || (t0 > 1.0 && t1 > 1.0))
        return false;
      t0                    = std::max(t0, 0.0);
      t0                    = std::min(t0, 1.0);
      t1                    = std::max(t1, 0.0);
      t1                    = std::min(t1, 1.0);
      segment_out.vertex(0) = origin + t0 * direction;
      segment_out.vertex(1) = origin + t1 * direction;
      return true;
    }
    else
    {
      return false;
    }
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    triangle const &triangle_in,
    disk const     &disk_in,
    segment        &segment_out,
    real            tolerance)
  {
    segment tmp_segment;
    if (intersection(disk_in.layingPlane(), triangle_in, tmp_segment, tolerance))
      return intersection(tmp_segment, disk_in, segment_out, tolerance);
    else
      return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    triangle const &triangle_in,
    ball const     &ball_in,
    none           &none_out,
    real            tolerance)
  {
    ACME_ERROR("acme::intersection(triangle, ball): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    disk const &disk_in,
    ball const &ball_in,
    none       &none_out,
    real        tolerance)
  {
    ACME_ERROR("acme::intersection(disk, ball): function not supported")
    return false;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
   |   __  __ _              _ _
   |  |  \/  (_)___  ___ ___| | | __ _ _ __   ___  ___  _   _ ___
   |  | |\/| | / __|/ __/ _ \ | |/ _` | '_ \ / _ \/ _ \| | | / __|
   |  | |  | | \__ \ (_|  __/ | | (_| | | | |  __/ (_) | |_| \__ \
   |  |_|  |_|_|___/\___\___|_|_|\__,_|_| |_|\___|\___/ \__,_|___/
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  bool
  intersection(
    aabb const &aabb0_in,
    aabb const &aabb1_in,
    aabb       &aabb_out,
    real        tolerance)
  {
    if (!(aabb0_in.intersects(aabb1_in)))
      return false;

    for (size_t i = 0; i < 3; ++i)
    {
      if (aabb0_in.max(i) <= aabb1_in.max(i))
        aabb_out.max(i) = aabb0_in.max(i);
      else
        aabb_out.max(i) = aabb1_in.max(i);
      if (aabb0_in.min(i) <= aabb1_in.min(i))
        aabb_out.min(i) = aabb1_in.min(i);
      else
        aabb_out.min(i) = aabb0_in.min(i);
    }
    return true;
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

} // namespace acme

///
/// eof: acme_intersection.cc
///