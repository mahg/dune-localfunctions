// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_LOBATTOBASIS_SPACE_HH
#define DUNE_LOBATTOBASIS_SPACE_HH

#include <dune/finiteelements/lagrangebasis/lobattopoints.hh>
#include <dune/finiteelements/lagrangebasis/interpolation.hh>
#include <dune/finiteelements/lagrangebasis/lagrangebasis.hh>
#include <dune/finiteelements/global/dofmapper.hh>
#include <dune/finiteelements/global/basisproxy.hh>

namespace Dune
{

  template< class GV, class SF, class CF = typename ComputeField< SF, 512 >::Type >
  class LobattoLagrangeSpace
  {
    typedef LobattoLagrangeSpace< GV, SF, CF > This;

    template< int topologyId >
    struct Build;

  public:
    typedef GV GridView;

    typedef typename GridView::Grid::ctype DomainField;
    static const unsigned int dimDomain = GridView::dimension;
    typedef FieldVector< DomainField, dimDomain > DomainVector;

    typedef SF RangeField;
    static const unsigned int dimRange = 1;
    typedef FieldVector< RangeField, dimRange > RangeVector;

    typedef LobattoBasisProvider< dimDomain, RangeField, CF > BasisCreator;
    typedef Dune::LobattoPointsCreator< RangeField, dimDomain > LagrangePointsCreator;
    typedef LagrangePointsCreator LocalCoefficientsCreator;
    typedef LocalLagrangeInterpolationCreator< LagrangePointsCreator > LocalInterpolationCreator;

    typedef unsigned int Key;

    typedef typename BasisCreator::Basis LocalBasis;
    typedef typename LocalInterpolationCreator::LocalInterpolation LocalInterpolation;

    typedef BasisProxy< LocalBasis, typename GridView::template Codim< 0 >::Geometry > Basis;

    typedef Dune::DofMapper< typename GridView::IndexSet, LocalCoefficientsCreator > DofMapper;

    explicit LobattoLagrangeSpace ( const GridView &gridView, const Key &order )
      : gridView_( gridView ),
        dofMapper_( gridView_.indexSet(), order )
    {
      GenericGeometry::ForLoop< Build, 0, numTopologies-1 >::apply( order, dofMapper_, basis_, interpolation_ );
    }

    ~LobattoLagrangeSpace ()
    {
      for( unsigned int topologyId = 0; topologyId < numTopologies; ++topologyId )
      {
        if( basis_[ topologyId ] != 0 )
          BasisCreator::release( *(basis_[ topologyId ]) );
        if( interpolation_[ topologyId ] != 0 )
          LocalInterpolationCreator::release( *(interpolation_[ topologyId ]) );
      }
    }

    const GridView &gridView () const
    {
      return gridView_;
    }

    const DofMapper &dofMapper () const
    {
      return dofMapper_;
    }

    Basis basis ( const typename GridView::template Codim< 0 >::Entity &entity ) const
    {
      const unsigned int topologyId = Dune::GenericGeometry::topologyId( entity.type() );
      const LocalBasis *basis = basis_[ topologyId ];
      assert( basis != 0 );
      return Basis( *basis, entity.geometry() );
    }

    const LocalInterpolation &interpolation ( const typename GridView::template Codim< 0 >::Entity &entity ) const
    {
      const unsigned int topologyId = Dune::GenericGeometry::topologyId( entity.type() );
      const LocalInterpolation *interpolation = interpolation_[ topologyId ];
      assert( interpolation != 0 );
      return *interpolation;
    }

  private:
    static const unsigned int numTopologies = (1 << dimDomain);

    GridView gridView_;
    DofMapper dofMapper_;
    const LocalBasis *basis_[ numTopologies ];
    const LocalInterpolation *interpolation_[ numTopologies ];
  };



  template< class GV, class SF, class CF >
  template< int topologyId >
  struct LobattoLagrangeSpace< GV, SF, CF >::Build
  {
    static void apply ( const Key &order,
                        const DofMapper &dofMapper,
                        const LocalBasis *(&basis)[ numTopologies ],
                        const LocalInterpolation *(&interpolation)[ numTopologies ] )
    {
      typedef typename GenericGeometry::Topology< topologyId, dimDomain >::type Topology;

      basis[ topologyId ] = 0;
      interpolation[ topologyId ] = 0;
      if( dofMapper.topologyRequired( topologyId ) )
      {
        basis[ topologyId ] = &BasisCreator::template basis< Topology >( order );
        interpolation[ topologyId ] = &LocalInterpolationCreator::template localInterpolation< Topology >( order );
      }
    }
  };

}

#endif // #ifndef DUNE_LAGRANGEBASIS_SPACE_HH