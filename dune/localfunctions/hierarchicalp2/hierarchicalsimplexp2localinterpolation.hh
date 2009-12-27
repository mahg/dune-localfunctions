// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_HIERARCHICAL_SIMPLEX_P2_LOCALINTERPOLATION_HH
#define DUNE_HIERARCHICAL_SIMPLEX_P2_LOCALINTERPOLATION_HH

#include "../common/localinterpolation.hh"

namespace Dune
{
  /**
     \tparam LB The LocalBasis implementation
   */
  template<class LB>
  class HierarchicalSimplexP2LocalInterpolation
#ifdef DUNE_VIRTUAL_SHAPEFUNCTIONS
    : public LocalInterpolationInterface<typename LB::Traits::DomainType, typename LB::Traits::RangeType>
#endif
  {
  public:

    template<typename F, typename C>
    void interpolate (const F& f, std::vector<C>& out) const
    {
      typename LB::Traits::DomainType x;
      typename LB::Traits::RangeType y;

      dune_static_assert(LB::Traits::dimDomain <=3, "LocalInterpolation for HierarchicalSimplexP2 finite elements"
                         " is only implemented for dimDomain <=3!");

      switch (LB::Traits::dimDomain) {

      case 1 :

        out.resize(3);

        // First: the two vertex dofs
        x[0] = 0.0;   f.evaluate(x, y);    out[0] = y;
        x[0] = 1.0;   f.evaluate(x, y);    out[2] = y;

        // Then: the edge dof
        x[0] = 0.5;   f.evaluate(x, y);
        out[1] = y - 0.5*(out[0] + out[2]);

        break;


      case 2 :

        out.resize(6);

        // First: the three vertex dofs
        x[0] = 0.0;    x[1] = 0.0;      f.evaluate(x, y);    out[0] = y;
        x[0] = 1.0;    x[1] = 0.0;      f.evaluate(x, y);    out[2] = y;
        x[0] = 0.0;    x[1] = 1.0;      f.evaluate(x, y);    out[5] = y;

        // Then: the three edge dofs
        x[0] = 0.5;    x[1] = 0.0;      f.evaluate(x, y);
        out[1] = y - 0.5*(out[0] + out[2]);

        x[0] = 0.0;    x[1] = 0.5;      f.evaluate(x, y);
        out[3] = y - 0.5*(out[0] + out[5]);

        x[0] = 0.5;    x[1] = 0.5;      f.evaluate(x, y);
        out[4] = y - 0.5*(out[2] + out[5]);

        break;

      case 3 :

        out.resize(10);

        // First: the four vertex dofs
        x[0] = 0.0;    x[1] = 0.0;     x[2] = 0.0;    f.evaluate(x, y);    out[0] = y;
        x[0] = 1.0;    x[1] = 0.0;     x[2] = 0.0;    f.evaluate(x, y);    out[2] = y;
        x[0] = 0.0;    x[1] = 1.0;     x[2] = 0.0;    f.evaluate(x, y);    out[5] = y;
        x[0] = 0.0;    x[1] = 0.0;     x[2] = 1.0;    f.evaluate(x, y);    out[9] = y;

        // Then: the six edge dofs
        x[0] = 0.5;    x[1] = 0.0;     x[2] = 0.0;    f.evaluate(x, y);
        out[1] = y - 0.5*(out[0] + out[2]);

        x[0] = 0.0;    x[1] = 0.5;     x[2] = 0.0;    f.evaluate(x, y);
        out[3] = y - 0.5*(out[0] + out[5]);

        x[0] = 0.5;    x[1] = 0.5;     x[2] = 0.0;    f.evaluate(x, y);
        out[4] = y - 0.5*(out[2] + out[5]);

        x[0] = 0.0;    x[1] = 0.0;     x[2] = 0.5;    f.evaluate(x, y);
        out[6] = y - 0.5*(out[0] + out[9]);

        x[0] = 0.5;    x[1] = 0.0;     x[2] = 0.5;    f.evaluate(x, y);
        out[7] = y - 0.5*(out[2] + out[9]);

        x[0] = 0.0;    x[1] = 0.5;     x[2] = 0.5;    f.evaluate(x, y);
        out[8] = y - 0.5*(out[5] + out[9]);

        break;

      }
    }

#if DUNE_VIRTUAL_SHAPEFUNCTIONS
    typedef LocalInterpolationInterface<typename LB::Traits::DomainType, typename LB::Traits::RangeType> Base;

    void interpolate(const typename Base::FunctionType& f, typename std::vector<typename Base::CoefficientType>& out) const
    {
      interpolate<typename Base::FunctionType, typename Base::CoefficientType>(f, out);
    }
#endif

  };
}

#endif
