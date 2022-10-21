/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2022                                                      |
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
/// file: Utils_HJPatternSearch.cc
///

#include "Utils_HJPatternSearch.hh"

namespace Utils {

  // =================================================================
  // Setup
  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::set_tolerance( Real tol ) {
    UTILS_ASSERT(
      tol > 0,
      "set_tolerance({}) argument must be >0\n", tol
    );
    m_tolerance      = tol;
    m_sqrt_tolerance = sqrt(tol);
  }

  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::set_max_iterations( integer mit ) {
    UTILS_ASSERT(
      mit > 0,
      "set_max_iterations({}) argument must be >0\n", mit
    );
    m_max_iteration = mit;
  }

  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::set_max_fun_evaluation( integer mfev ) {
    UTILS_ASSERT(
      mfev > 0,
      "set_max_fun_evaluation({}) argument must be >0\n", mfev
    );
    m_max_fun_evaluation = mfev;
  }

  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::set_max_num_stagnation( integer nstg ) {
    UTILS_ASSERT(
      nstg > 0,
      "set_max_num_stagnation({}) argument must be >0\n", nstg
    );
    m_max_num_stagnation = nstg;
  }

  // =================================================================
  // Allocate
  // =================================================================
  template <typename Real>
  void
  HJPatternSearch<Real>::allocate( integer n ) {
    m_N = n;
    integer ntot = n*10;
    m_base_value.reallocate( ntot, "HJPatternSearch::allocate" );

    new (&this->m_h)              MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_d)              MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_search_sign)    MapVec( m_base_value( size_t(n) ), n );

    new (&this->m_x)              MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_x_center)       MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_x_best)         MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_x_current_best) MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_x_temporary)    MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_p)              MapVec( m_base_value( size_t(n) ), n );
    new (&this->m_p1)             MapVec( m_base_value( size_t(n) ), n );
  }

  // =================================================================
  // Setup
  // =================================================================
  template <typename Real>
  void
  HJPatternSearch<Real>::setup( HJFunc & fun, Console const * console ) {
    // HJPatternSearch The constructor initialize the solver
    // parameters and check the inputs when the class is instanciated.
    m_fun     = fun;
    m_console = console;
    allocate( fun->num_variables(), fun->num_parameters() );
  }

  // =================================================================
  // Evaluate function
  // =================================================================

  template <typename Real>
  Real
  HJPatternSearch<Real>::eval_function( MapVec const & x, MapVec & pars ) const {
    // eval_function This method evaluate the value function and counts the
    // number of evaluations in one iteration

    // update statistic
    ++m_fun_evaluation;

    bool ok = m_fun->check_if_admissible( x.data() );
    if ( ok ) ok = m_fun->update_parameters( x.data(), pars.data() );
    if ( ok ) return m_fun->evaluate_function( x.data(), pars.data() );
    return Utils::Inf<Real>();
  }

  // =================================================================
  // info
  // =================================================================

  template <typename Real>
  string
  HJPatternSearch<Real>::info() const {
    string res = fmt::format("\nOptimization stats:\n");
    if ( m_iteration_count >= m_max_iteration ) {
      res += fmt::format(
        "iteration number reached  Max Iteration Limit = {}\n",
        m_max_iteration
      );
    } else if ( m_fun_evaluation >= m_max_fun_evaluation ) {
      res += fmt::format(
        "function evaluations {} exceeded the maximum limit [{}]\n",
        m_fun_evaluation, m_max_fun_evaluation
      );
    } else if ( m_num_stagnation >= m_max_num_stagnation ) {
      res += fmt::format(
        "exceed #stagnation steps {} [max {}]\n",
        m_num_stagnation, m_max_num_stagnation
      );
    } else {
      res += fmt::format(
        "mesh size h = {} less than tolerance = {}\n",
        h_norm_inf(), m_tolerance
      );
    }
    res += fmt::format(
      "[#iterations/#feval] F(x_best): [{}/{}]  {:6}\n\n",
      m_iteration_count, m_fun_evaluation, m_fun_best
    );
    return res;
  }

  // =================================================================
  // Search
  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::search() {
    /*
    // SEARCH This method call the explore method on the first
    // iteration and then continue to call explore until a stencil
    // fails. In the case of a stencil failure, it tries once to go
    // back of half a step along the search direction by setting x_center
    // equal to the base point x_best.
    // If the stencil fails again, it exits the while loop and stencil_failure
    // is set to zero in order to signal that a reduction of h is necessary.
    */
    ++m_iteration_count; // augment counter
    // Print info
    if ( m_verbose > 0 && m_console->get_level() >= 3 ) {
      string line = "-------------------------------------------------------------------------";
      string msg = fmt::format(
        "Iteration={} f(x_best)/#f/|h| = {:.6} / {} / {:.6}\n",
        m_iteration_count,
        m_fun_best,
        m_fun_evaluation,
        h_norm_inf()
      );
      if ( m_verbose > 2 ) {
        for ( integer ii = 0; ii < m_N; ++ii )
          msg += fmt::format( "x[{}] = {:.6}\n", ii, m_x(ii) );
      }
      msg += fmt::format("{}\n",line);
      m_console->message( msg, 3 );
    }

    // Explore the first iteration point
    m_x_best.noalias()   = m_x; // Move the base point to the current iteration
    m_x_center.noalias() = m_x; // Set the new stencil center
    m_stencil_failure    = false;

    explore();

    // Continue exploring until stencil failure or exceed of
    while ( m_fun_evaluation < m_max_fun_evaluation ) {
      m_d.noalias()        = m_x - m_x_best; // Compute search direction
      m_x_best.noalias()   = m_x;            // Move the base point to the current iteration
      m_x_center.noalias() = m_x + m_d;      // Set the new stencil center at a distance 2d from x_best

      explore(); // Explore the stencil centered in x_center

      // If there is a stencil failure, move x_center back to the past
      // iteration x (which is equal to x_best) and explore
      if ( m_stencil_failure ) {
        m_x_center.noalias() = m_x_best;
        explore(); // Explore the stencil centered in x_center
      }

      // If there is a stencil failure again, the search method
      // will terminate (and h must be reduced to continue the algorithm)
      if ( m_stencil_failure ) break;

      // Check whether the current best point is changed or it is
      // still the initial base point x_best

      // if the new point is different in at least one of the direction,
      // break and use the flag keep to assert the new point is different
      // from the previous
      bool do_break = true;
      for ( integer ii = 0; do_break && ii < m_N; ++ii )
        do_break = 0.5 * m_h[ii] >= abs(m_x[ii]-m_x_best[ii] );
      if ( do_break ) break;
    }
  }

  // =================================================================
  // Explore
  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::explore() {
    /*
    // EXPLORE This method explore all points on the stencil center at
    // x_temporary = x_center and updates the current iteration x to the current
    // best point x_current_best. If the current best point x_current_best is worse than the
    // base point x_best, the current iteration x will remain constant
    // (x = x_best) and stencil failure flag stencil_failure will be set to zero.
    */
    // Initialize
    m_fun_best = eval_function( m_x_best );
    m_d.setZero();
    m_stencil_failure          = true;
    m_x_current_best.noalias() = m_x_best;
    m_x_temporary.noalias()    = m_x_center;    // temporary point representing the center of the stencil

    // ----------------------------------------------------------------------------------------
    // Cycle on all stencil directions

    for ( integer j = 0; j < m_N; ++j ) {
      Real s_dirh = m_search_sign(j) * m_h(j);
      m_p.noalias() = m_x_temporary; m_p(j) += s_dirh;
      Real fp = eval_function( m_p );
      if ( fp >= m_fun_best ) {
        m_p1.noalias() = m_x_temporary; m_p1(j) -= s_dirh; // try the opposite direction
        Real fp1 = eval_function( m_p1 );
        if ( fp1 < fp ) {
          m_p.noalias() = m_p1; fp = fp1;
          // change priority of search direction to the opposite verse
          m_search_sign(j) = -m_search_sign(j);
        }
      }
      // Update temporary and current best point before checking
      // the remaining directions j
      if ( fp < m_fun_best ) {
        m_x_temporary.noalias()    = m_p;   // move temporary point
        m_x_current_best.noalias() = m_p;   // new current best point
        m_fun_best                 = fp;    // new best value function
        m_stencil_failure          = false; // update stencil failure flag
      }
    }
    if ( !m_stencil_failure )
      m_x.noalias() = m_x_current_best; // update the current iteration to current best
  }

  // =================================================================
  // Run
  // =================================================================

  template <typename Real>
  void
  HJPatternSearch<Real>::run( Real x_sol[], Real h ) {
    // RUN This method run the whole Hooke-Jeeves algorithm. Search
    // is repeated until it fails, then the scal h is reduced. When h
    // is less than a threshold, the method returns the solution.

    // initialize current iteration to guess for the first iteration
    std::copy_n( x_sol, m_N, m_x.data() );

    m_stencil_failure = false; // initialize stencil failure flag
    m_fun_best        = eval_function(m_x,m_pars);

    m_x_center.noalias()    = m_x; // initialize stencil center to guess for the first iteration
    m_pars_center.noalias() = m_pars;
    m_x_best.noalias()      = m_x; // initialize base point to guess for the first iteration
    m_pars_best.noalias()   = m_pars;

    m_search_sign.setOnes();   // Initialize search verse vector to all ones (first verse will be positive for each direction)

    m_h.fill(h);

    m_iteration_count = 0; // initialize explore iteration counter
    m_fun_evaluation  = 0; // initialize function evaluation counter
    m_num_stagnation  = 0;

    Real fun_last_best = m_fun_best;

    while ( h_norm_inf() > m_tolerance && m_fun_evaluation < m_max_fun_evaluation ) {
      search();
      // If iteration limit is reached,stop. Otherwise, reduce
      // mesh size and continue
      if ( m_iteration_count >= m_max_iteration ) break;
      m_h *= m_rho; // reduce the scale
      // check stagnation
      if ( fun_last_best <= m_fun_best ) {
        if ( ++m_num_stagnation > m_max_num_stagnation ) break;
      } else {
        m_num_stagnation = 0;
      }
      fun_last_best = m_fun_best;
    }
    std::copy_n( m_x.data(), m_N, x_sol );
  }
}

///
/// eof: Utils_HJPatternSearch.c
///
