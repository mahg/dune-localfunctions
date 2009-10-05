// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_LAGRANGEBASIS_INTERPOLATION_HH
#define DUNE_LAGRANGEBASIS_INTERPOLATION_HH

#include <dune/finiteelements/lagrangebasis/lagrangepoints.hh>

namespace Dune
{

  // External Forward Declarations
  // -----------------------------

  template< class Topology, class F >
  class MonomialBasis;



  // LocalLagrangeInterpolation
  // --------------------------

  template< class Topology, class F >
  class LocalLagrangeInterpolation
  {
    typedef LocalLagrangeInterpolation< Topology, F > This;

  public:
    typedef F Field;

    static const unsigned int dimDomain = Topology::dimension;

  private:
    typedef Dune::LagrangePoints< F, dimDomain > LagrangePoints;
    typedef Dune::LagrangePointsCreator< F, dimDomain > LagrangePointsCreator;

    const LagrangePoints &lagrangePoints_;

  public:
    LocalLagrangeInterpolation ( const unsigned int order )
      : lagrangePoints_( LagrangePointsCreator::template lagrangePoints< Topology >( order ) )
    {}

    ~LocalLagrangeInterpolation ()
    {
      LagrangePointsCreator::release( lagrangePoints_ );
    }

    template< class Function >
    void interpolate ( const Function &function, std::vector< Field > &coefficients )
    {
      typedef typename LagrangePoints::iterator Iterator;

      coefficients.resize( lagrangePoints_.size() );

      unsigned int index = 0;
      const Iterator end = lagrangePoints_.end();
      for( Iterator it = lagrangePoints_.begin(); it != end; ++it )
        coefficients[ index++ ] = function( *it );
    }

    template< class Matrix >
    void interpolate ( const MonomialBasis< Topology, F > &basis, Matrix &coefficients )
    {
      typedef typename LagrangePoints::iterator Iterator;

      coefficients.resize( lagrangePoints_.size(), basis.size( ) );

      unsigned int index = 0;
      const Iterator end = lagrangePoints_.end();
      for( Iterator it = lagrangePoints_.begin(); it != end; ++it )
        basis.evaluate( it->point(), coefficients.rowPtr( index++ ) );
    }

    template< class Matrix, class Basis >
    void interpolate ( const Basis &basis, Matrix &coefficients )
    {
      typedef typename LagrangePoints::iterator Iterator;

      coefficients.resize( lagrangePoints_.size(), basis.size( ) );

      unsigned int index = 0;
      const Iterator end = lagrangePoints_.end();
      for( Iterator it = lagrangePoints_.begin(); it != end; ++it )
        basis.evaluate( it->point(), coefficients.rowPtr( index++ ) );
    }
  };

}

#endif // #ifndef DUNE_LAGRANGEBASIS_INTERPOLATION_HH