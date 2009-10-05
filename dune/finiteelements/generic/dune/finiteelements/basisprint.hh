// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef BASISPRINT
#define BASISPRINT
#include <dune/finiteelements/multiindex.hh>
namespace Dune {
  template <int deriv,class Basis>
  void basisPrint(std::ostream &out, Basis &basis)
  {
    const int dimension = Basis::dimension;
    typedef MultiIndex< dimension > Field;

    unsigned int size = basis.size();

    out << "% Number of base functions:  " << size << std::endl;
    out << "% Derivative order: " << deriv << std::endl;
    // std::vector< typename Basis::RangeVector > y( size );
    std::vector< Dune::FieldVector<Field,dimension+1> > y( size );
    // std::vector< typename Basis::RangeVector > y( size*basis.derivSize(deriv) );
    FieldVector< Field, dimension > x;
    for( int i = 0; i < dimension; ++i )
      x[ i ].set( i, 1 );
    basis.template evaluate<deriv>( x, y );
    out << y << std::endl;
  }
};
#endif // BASISPRINT
