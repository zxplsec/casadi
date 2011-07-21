/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef ACADO_INTERNAL_HPP
#define ACADO_INTERNAL_HPP

#include "acado_interface.hpp"
#include "acado_function.hpp"
#include "casadi/fx/fx_internal.hpp"
#include <stack>

/** \brief  forward declarations */
namespace ACADO{
  class OCP;
  class Time;
  class DifferentialState;
  class DifferentialStateDerivative;
  class AlgebraicState;
  class Control;
  class Parameter;
  class DifferentialEquation;
  class IntermediateState;
  class OCP;
  class OptimizationAlgorithm;
}
namespace CasADi{

  
class AcadoInternal : public FXInternal{
  friend class AcadoInterface;
  
  /** \brief  Constructor only accessable from the AcadoOCPSolver pointer class */
  explicit AcadoInternal(const FX& ffcn, const FX& mfcn, const FX& cfcn, const FX& rfcn);
  
  /** \brief  Set a user-provided integrator */
  void setIntegrators(const std::vector<Integrator>& integrators);
  
  public:
    
    /** \brief  Destructor */
    virtual ~AcadoInternal();

    // clone
    virtual AcadoInternal* clone() const{ return new AcadoInternal(*this);}
    
    /** \brief  Initialize the solver */
    virtual void init();
    
    /** \brief  Solve the problem */
    virtual void evaluate(int nfdir, int nadir);
    
    // Dimensions
    int nt_, nxd_, nxa_, nu_, np_, nxdot_;
    int nx_;
    
    // Number of shooting nodes
    int n_nodes_;
    
    // Number of non-linear path constraints
    int nc_;
    
    // Number of initial value constraints
    int nr_;
        
    /** \brief  Public pointers to ACADO classes  */
    ACADO::TIME                   *t_;
    ACADO::DifferentialState     *xd_;
    ACADO::AlgebraicState        *xa_;
    ACADO::Control                *u_;
    ACADO::Parameter              *p_;
    ACADO::DifferentialStateDerivative *xdot_;
    ACADO::IntermediateState     *arg_;

    ACADO::DifferentialEquation   *f_;
    ACADO::OCP                   *ocp_;
    ACADO::OptimizationAlgorithm *algorithm_;

    // DAE rhs (if any)
    AcadoFunction ffcn_;

    // Casadi integrator (if any)
    std::vector<Integrator> integrators_;
    
    // Meyer term
    AcadoFunction mfcn_;

    // Constraint function
    AcadoFunction cfcn_;
    
    // Initial equation
    AcadoFunction rfcn_;
    
    // Manage integrator backends
    int getRef(void *);
    void returnRef(int ref);
    
    std::vector<void*> backends_;
    std::stack<int> free_backends_;
    
    
    
    
};

} // namespace CasADi

#endif //ACADO_INTERNAL_HPP
