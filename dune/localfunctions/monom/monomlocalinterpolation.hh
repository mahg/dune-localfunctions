// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_MONOMLOCALINTERPOLATION_HH
#define DUNE_MONOMLOCALINTERPOLATION_HH

#include <vector>

#include <dune/common/deprecated.hh>
#include <dune/common/geometrytype.hh>
#include <dune/common/fvector.hh>
#include <dune/common/fmatrix.hh>
#include <dune/grid/common/quadraturerules.hh>

namespace Dune
{

  template<class LB, unsigned int size>
  class MonomLocalInterpolation
  {
    typedef typename LB::Traits::DomainType D;
    typedef typename LB::Traits::DomainFieldType DF;
    static const int dimD=LB::Traits::dimDomain;
    typedef typename LB::Traits::RangeType R;
    typedef typename LB::Traits::RangeFieldType RF;

    typedef QuadratureRule<DF,dimD> QR;
    typedef typename QR::iterator QRiterator;

    void init() {
      if(size != lb.size())
        DUNE_THROW(Exception, "size template parameter does not match size of "
                   "local basis");

      const QRiterator qrend = qr.end();
      for(QRiterator qrit = qr.begin(); qrit != qrend; ++qrit) {
        std::vector<R> base;
        lb.evaluateFunction(qrit->position(),base);

        for(unsigned int i = 0; i < size; ++i)
          for(unsigned int j = 0; j < size; ++j)
            Minv[i][j] += qrit->weight() * base[i] * base[j];
      }
      Minv.invert();
    }

  public:
    MonomLocalInterpolation (const GeometryType::BasicType &bt_,
                             const LB &lb_) DUNE_DEPRECATED
      : gt(bt_, dimD), lb(lb_), Minv(0)
        , qr(QuadratureRules<DF,dimD>::rule(gt, 2*lb.order()))
    { init(); }

    MonomLocalInterpolation (const GeometryType &gt_,
                             const LB &lb_)
      : gt(gt_), lb(lb_), Minv(0)
        , qr(QuadratureRules<DF,dimD>::rule(gt, 2*lb.order()))
    { init(); }

    //! determine coefficients interpolating a given function
    template<typename F, typename C>
    void interpolate (const F& f, std::vector<C>& out) const
    {
      out.clear();
      out.resize(size, 0);

      const QRiterator qrend = qr.end();
      for(QRiterator qrit = qr.begin(); qrit != qrend; ++qrit) {
        //TODO: mass matrix
        R y;
        f.evaluate(qrit->position(),y);

        std::vector<R> base;
        lb.evaluateFunction(qrit->position(),base);

        for(unsigned int i = 0; i < size; ++i)
          for(unsigned int j = 0; j < size; ++j)
            out[i] += Minv[i][j] * qrit->weight() * y * base[j];
      }
    }

  private:
    GeometryType gt;
    const LB &lb;
    FieldMatrix<RF, size, size> Minv;
    const QR &qr;
  };

}

#endif //DUNE_MONOMLOCALINTERPOLATION_HH
