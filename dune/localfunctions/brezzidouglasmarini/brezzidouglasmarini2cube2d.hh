// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI2_QUBE2D_LOCALFINITEELEMENT_HH
#define DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI2_QUBE2D_LOCALFINITEELEMENT_HH

#include <dune/geometry/type.hh>

#include "../common/localfiniteelementtraits.hh"
#include "brezzidouglasmarini2cube2d/brezzidouglasmarini2cube2dlocalbasis.hh"
#include "brezzidouglasmarini2cube2d/brezzidouglasmarini2cube2dlocalcoefficients.hh"
#include "brezzidouglasmarini2cube2d/brezzidouglasmarini2cube2dlocalinterpolation.hh"

namespace Dune
{
  /**
   * \brief Second order Brezzi-Douglas-Marini shape functions on quadrilaterals.
   *
   * \tparam D Type to represent the field in the domain.
   * \tparam R Type to represent the field in the range.
   */
  template<class D, class R>
  class BDM2Cube2DLocalFiniteElement
  {

  public:
    typedef LocalFiniteElementTraits<
        BDM2Cube2DLocalBasis<D,R>,
        BDM2Cube2DLocalCoefficients,
        BDM2Cube2DLocalInterpolation<BDM2Cube2DLocalBasis<D,R> > > Traits;

    //! \brief Standard constructor
    BDM2Cube2DLocalFiniteElement ()
    {
      gt.makeQuadrilateral();
    }

    /**
     * \brief Make set number s, where 0 <= s < ??
     *
     * \param s Edge orientation indicator
     */
    BDM2Cube2DLocalFiniteElement (int s) : basis(s), interpolation(s)
    {
      gt.makeQuadrilateral();
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
    BDM2Cube2DLocalBasis<D,R> basis;
    BDM2Cube2DLocalCoefficients coefficients;
    BDM2Cube2DLocalInterpolation<BDM2Cube2DLocalBasis<D,R> > interpolation;
    GeometryType gt;
  };
}
#endif // DUNE_LOCALFUNCTIONS_BREZZIDOUGLASMARINI2_QUBE2D_LOCALFINITEELEMENT_HH