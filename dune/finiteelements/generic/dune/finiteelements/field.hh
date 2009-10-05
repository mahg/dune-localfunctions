// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_FIELD_HH
#define DUNE_FIELD_HH

#include <dune/alglib/multiprecision.hh>

namespace Dune
{

  // Unity
  // -----

  template< class Field >
  struct Unity
  {
    operator Field () const
    {
      return Field( 1 );
    }
  };



  template< class Field >
  Field operator+ ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u + f;
  }

  template< class Field >
  Field operator- ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u - f;
  }

  template< class Field >
  Field operator* ( const Unity< Field > &u, const Field &f )
  {
    return f;
  }

  template< class Field >
  Field operator/ ( const Unity< Field > &u, const Field &f )
  {
    return (Field)u / f;
  }



  // Zero
  // ----

  template< class Field >
  struct Zero
  {
    operator Field () const
    {
      return Field( 0 );
    }
  };

  template< class Field >
  inline bool operator< ( const Zero< Field > &, const Field &f )
  {
    return f > 1e-12;
  }

  template< class Field >
  inline bool operator< ( const Field &f, const Zero< Field > & )
  {
    return f < -1e-12;
  }

  template< class Field >
  inline bool operator> ( const Zero< Field > &z, const Field &f )
  {
    return f < z;
  }

  template< class Field >
  inline bool operator> ( const Field &f, const Zero< Field > &z )
  {
    return z < f;
  }

  template <unsigned int precision>
  inline void field_cast(const AlgLib::MultiPrecision<precision> &f1, double &f2)
  {
    f2 = f1.toDouble();
  }
  template <class F2,class F1>
  inline void field_cast(const F1 &f1, F2 &f2)
  {
    f2 = f1;
  }

  template <class F2,class F1,int dim>
  inline void field_cast(const FieldVector<F1,dim> &f1, FieldVector<F2,dim> &f2)
  {
    for (int d=0; d<dim; ++d)
      field_cast(f1[d],f2[d]);
  }

  template <class F2,class F1>
  inline F2 field_cast(const F1 &f1)
  {
    F2 f2;
    field_cast(f1,f2);
    return f2;
  }
}

#endif // #ifndef DUNE_FIELD_HH
