// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI1_SIMPLEX2D_LOCALFINITEELEMENT_HH
#define DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI1_SIMPLEX2D_LOCALFINITEELEMENT_HH

#include <dune/geometry/type.hh>

#include "../common/localfiniteelementtraits.hh"
#include "brezzidouglasmarini1simplex2d/brezzidouglasmarini1simplex2dlocalbasis.hh"
#include "brezzidouglasmarini1simplex2d/brezzidouglasmarini1simplex2dlocalcoefficients.hh"
#include "brezzidouglasmarini1simplex2d/brezzidouglasmarini1simplex2dlocalinterpolation.hh"

namespace Dune
{

  /**
   * \brief First order Brezzi-Douglas-Marini shape functions on triangles.
   *
   * \tparam D Type to represent the field in the domain.
   * \tparam R Type to represent the field in the range.
   */
  template<class D, class R>
  class BDM1Simplex2DLocalFiniteElement
  {

  public:
    typedef LocalFiniteElementTraits<
        BDM1Simplex2DLocalBasis<D,R>,
        BDM1Simplex2DLocalCoefficients,
        BDM1Simplex2DLocalInterpolation<BDM1Simplex2DLocalBasis<D,R> > > Traits;

    //! \brief Standard constructor
    BDM1Simplex2DLocalFiniteElement ()
    {
      gt.makeTriangle();
    }

    /**
     * \brief Make set number s, where 0 <= s < 8
     *
     * \param s Edge orientation indicator
     */
    BDM1Simplex2DLocalFiniteElement (int s) : basis(s), interpolation(s)
    {
      gt.makeTriangle();
    }

    const typename Traits::LocalBasisType& localBasis () const
    {
      return basis;
    }

    const typename Traits::LocalCoefficientsType& localCoefficients () const
    {
      return coefficients;
    }

    const typename Traits::LocalInterpolationType& localInterpolation () const
    {
      return interpolation;
    }

    GeometryType type () const
    {
      return gt;
    }

  private:
    BDM1Simplex2DLocalBasis<D,R> basis;
    BDM1Simplex2DLocalCoefficients coefficients;
    BDM1Simplex2DLocalInterpolation<BDM1Simplex2DLocalBasis<D,R> > interpolation;
    GeometryType gt;
  };
}
#endif // DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI1_SIMPLEX2D_LOCALFINITEELEMENT_HH
