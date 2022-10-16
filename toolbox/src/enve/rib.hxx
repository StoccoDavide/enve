/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                     *
 * This file is part of the ENVE project.                              *
 *                                                                     *
 * Copyright (c) 2022, Davide Stocco. All rights reserved.             *
 *                                                                     *
 * The ENVE project can not be copied and/or distributed without       *
 * the express permission of Davide Stocco.                            *
 *                                                                     *
 *    Davide Stocco                                                    *
 *    Department of Industrial Engineering                             *
 *    University of Trento                                             *
 *    e-mail: davide.stocco@unitn.it                                   *
 *                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/

///
/// file: rib.hxx
///

#ifndef INCLUDE_ENVE_RIB
#define INCLUDE_ENVE_RIB

#include "triangleground.hxx"
#include "mesh.hxx"
#include "flat.hxx"
#include "output.hxx"

namespace enve
{

  /*\
   |        _ _
   |   _ __(_) |__
   |  | '__| | '_ \
   |  | |  | | |_) |
   |  |_|  |_|_.__/
   |
  \*/

  //! Rib for wheel representation
  class rib : public disk
  {
  public:
    typedef std::shared_ptr<rib const> ptr;    //!< Pointer to rib object
    typedef std::vector<rib::ptr>      vecptr; //!< Vector of pointers to rib objects

  private:
    integer m_id;    //!< ID (-)
    real    m_y;     //!< Y-axis component  (m)
    real    m_width; //!< Width (m)
    real    m_angle; //!< Inclination angle (rad)

  public:
    //! Rib copy constructor
    rib(rib const &) = default;

    //! Rib move constructor
    rib(rib &&) = default;

    //! Rib assignment operator    
    rib & operator=(const rib &) = delete;

    //! Rib move assignment operator    
    rib & operator=(rib &&) = delete;
    
    //! Rib class destructor
    ~rib(void) override = default;

    //! Rib class constructor
    rib(void);

    //! Rib class constructor
    rib(
      integer id,     //!< ID (-)
      real    radius, //!< Radius (m)
      real    y,      //!< Laying plane (-)
      real    width,  //!< Width (m)
      real    angle   //!< inclination angle (rad)
    );

    //! Copy rib object
    void
    copy(
      rib const & rib_obj //!< Input object
    );

    //! Check if objects are (almost) equal
    bool
    isApprox(
      rib  const & rib_obj,                 //!< Input object
      real         tolerance = EPSILON_LOW //!< Tolerance
    ) const;

    //! Get ID reference (-)
    integer &
    id(void);

    //! Get ID const reference (-)
    integer const &
    id(void)
    const;

    //! Get width coefficient scaling factor reference (m)
    real &
    width(void);

    //! Get width coefficent scaling factor const reference (m)
    real const &
    width(void)
    const;

    //! Get angle coefficient scaling factor reference (rad)
    real &
    angle(void);

    //! Get angle coefficent scaling factor const reference (rad)
    real const &
    angle(void)
    const;

    //! Evaluate rib contact with no ground
    bool
    envelop(
      affine const & pose, //!< Input 4x4 affine transformation pose
      output       & out        //!< Rib contact parameters output
    ) const;

    //! Evaluate rib contact with flat ground
    bool
    envelop(
      triangleground::vecptr const & ground, //!< Local triangles candidate list
      affine                 const & pose,   //!< Input 4x4 affine transformation pose
      std::string            const   method, //!< Enveloping model (choose from: "geometric" or "sampling")
      output                       & out     //!< Rib contact parameters output
    ) const;

    //! Evaluate rib contact with flat ground
    bool
    envelop(
      ground::flat const & ground, //!< Local flat ground object
      affine       const & pose,   //!< Input 4x4 affine transformation pose
      std::string  const   method, //!< Enveloping model (choose from: "geometric" or "sampling")
      output             & out     //!< Rib contact parameters output
    ) const;

  private:
    //! Evaluate rib contact with flat ground (geometric enveloping model)
    bool
    envelopGeometric(
      triangleground::vecptr const & ground, //!< Local triangles candidate list
      affine                 const & pose,   //!< Input 4x4 affine transformation
      output                       & out     //!< Rib contact parameters output
    ) const;

    //! Evaluate rib contact with flat ground (geometric enveloping model)
    bool
    envelopGeometric(
      ground::flat const & ground, //!< Local flat ground object
      affine       const & pose,   //!< Input 4x4 affine transformation
      output             & out     //!< Rib contact parameters output
    ) const;

    //! Evaluate rib contact with flat ground (sampling enveloping model)
    bool
    envelopSampling(
      triangleground::vecptr const & ground, //!< Local triangles candidate list
      affine                 const & pose,   //!< Input 4x4 affine transformation
      output                       & out     //!< Rib contact parameters output
    ) const;

    //! Evaluate rib contact with flat ground (sampling enveloping model)
    bool
    envelopSampling(
      ground::flat const & ground, //!< Local flat ground object
      affine       const & pose,   //!< Input 4x4 affine transformation
      output             & out     //!< Rib contact parameters output
    ) const;

    //! Evaluate contact through line intersection envelop model
    bool
    samplingLine(
      triangleground::vecptr const & ground,          //!< Local triangles candidate list
      line                   const & sampling_line,   //!< Sampling line
      point                        & contact_point,   //!< Contact point
      real                         & contact_friction //!< Contact friction
    ) const;

    //! Evaluate contact through line intersection envelop model
    bool
    samplingLine(
      ground::flat const & ground,          //!< Local flat ground object
      line         const & sampling_line,   //!< Sampling line
      point              & contact_point,   //!< Contact point
      real               & contact_friction //!< Contact friction
    ) const;

  }; // class rib

} // namespace enve

#endif

///
/// eof: rib.hxx
///
