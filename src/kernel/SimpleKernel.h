#ifndef _SIMPLEKERNEL_H___
#define _SIMPLEKERNEL_H___

#include "kernel/Kernel.h"
#include "features/SimpleFeatures.h"

template <class ST> class CSimpleKernel : public CKernel
{
	public:
		CSimpleKernel(long cachesize) : CKernel(cachesize)
		{
		}

		/** initialize your kernel
		 * where l are feature vectors to occur on left hand side
		 * and r the feature vectors to occur on right hand side
		 *
		 * when training data is supplied as both l and r do_init should
		 * be true; when testing it must be false and thus no further
		 * initialization of the preprocessor in the kernl
		 * will be done (like determining the scale factor when rescaling the kernel).
		 * instead the previous values will be used (which where hopefully obtained
		 * on training data/loaded)
		 */
		virtual void init(CSimpleFeatures<ST>* l, CSimpleFeatures<ST>* r, bool do_init)
		{
			assert(l!=0);
			assert(r!=0);
			lhs=l;
			rhs=r;
			CKernel::init();
		}

		/** return feature class the kernel can deal with
		  */
		inline virtual EFeatureClass get_feature_class() { return C_SIMPLE; }

		/// get left/right hand side of features used in kernel
		inline virtual CFeatures* get_lhs() { return lhs; }
		inline virtual CFeatures* get_rhs() { return rhs; }

	protected:
		/// feature vectors to occur on left hand side
		CSimpleFeatures<ST>* lhs;
		/// feature vectors to occur on right hand side
		CSimpleFeatures<ST>* rhs;
};
#endif
