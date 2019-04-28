// RwCommTransform.h: interface for the RwCommTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RWCOMMTRANSFORM_H__07D1AA21_9292_4CE0_B204_185BD55B9BA9__INCLUDED_)
#define AFX_RWCOMMTRANSFORM_H__07D1AA21_9292_4CE0_B204_185BD55B9BA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RwCommAnimatable.h"


#define RwCommTranslateAnimation    "Translate"
#define RwCommTranslateXAnimation   "TranslateX"
#define RwCommTranslateYAnimation   "TranslateY"
#define RwCommTranslateZAnimation   "TranslateZ"
#define RwCommRotateAnimation       "Rotate"
#define RwCommRotateXAnimation      "RotateX"
#define RwCommRotateYAnimation      "RotateY"
#define RwCommRotateZAnimation      "RotateZ"
#define RwCommScaleAnimation        "Scale"
#define RwCommScaleXAnimation       "ScaleX"
#define RwCommScaleYAnimation       "ScaleY"
#define RwCommScaleZAnimation       "ScaleZ"
#define RwCommVisibilityAnimation   "Visibility"

class RwCommShape;

const RwCommType RwCommTransformType("RwCommTransform");

/**
*  \ingroup commscenegraph  
*
*   This object positions a scene graph element in 3D space. The transformation object is a
*   hierarchical element, each one holding a list of child transformations. The hierarchical
*   relationship between two transformations represents their relationship in 3D local space 
*   Each transformation holds a pointer to an abstract RwCommShape object, representing a
*   generic shape which is attached to the transformation. 
*/
class RWCOMM_API RwCommTransform : public RwCommAnimatable  
{
public:

    enum ChannelType
    {
        VISIBILITY = 1,
        TRANSFORM = 2
    };

	RwCommTransform();
	virtual ~RwCommTransform();

    // Type methods
	virtual RwCommType	    GetType() const { return RwCommTransformType; }
	virtual void            GetTypeHierarchy(vector<RwCommType>& vTypeVec) const;

	// Matrix querys
    /**
     *  \param matrix is filled with the local space transformation matrix.
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
	virtual RwCommError	    GetObjMatrix(RwCommMatrix& matrix) const = 0;

    /**
     *  \param matrix is filled with the world space transformation matrix.
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
	virtual RwCommError 	GetWorldMatrix(RwCommMatrix& matrix) const = 0;

    // Visibility
    /**
     *  Each transformation contains visibility information, specifying if the
     *  transformation and its shape are visible/invisible. If a transformation
     *  is invisible, all of its children are invisible as well.
     *
     *  \param bIsVisible is filled with the visibility value.
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
    virtual RwCommError     GetVisibility(bool& bIsVisible) const = 0;

    // Tagging
    /**
     *  Each transform can be tagged with a specific integer value. The tagging
     *  mechanism is specific to each application and is implemented by the 
     *  RenderWare Exporter plugin.
     *
     *  \param tagValue is filled with the tag value.
     *  \param bAutoGenerated returns true if the tag was auto generated,
     *         false if it was user specified.
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
    virtual RwCommError     GetNodeTagValue(int &tagValue, bool &bAutoGenerated) const = 0;

    // If the transform has its own custom axis system, return its orientation
    /**
     *  Each transform can have it's own axis system that you can query with
     *  this function. There are some third-party plugins that do this, but
     *  In most cases this function will return RWCOMM_FAIL.
     *
     *  \param matrix is filled with the transformation matrix to the new axis system.
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
    virtual RwCommError 	GetAxisSystem(RwCommMatrix& matrix) const { return RWCOMM_NOT_IMPLEMENTED; }
    
    // Hierarchy methods
    /**
     *  \param pParent is the transformation object to be set as a parent.
     */
	void		            SetParent(RwCommTransform* pParent) { m_pParent = pParent; }

    /**
     *  \return the parent transformation object.
     */
	RwCommTransform         *GetParent() const { return m_pParent; }

   	void                    AddChild(RwCommTransform* pChild);
	int                     GetNumChildren() const;
	RwCommTransform         *GetChild(int i) const;

    // Shape methods
    void                    SetShape(RwCommShape* pShape);

    /**
     *  \return the shape object attached to the transform.
     */
    RwCommShape             *GetShape() const                       { return m_pShape; }

    // Vertex scaling
    /**
     *  Different 3D applications have different pivot points implementation. This
     *  function will return the pre-scale & post-scale pivot transformations. The final scaling
     *  matrix is given by:
     * 
     * \verbatim
        S'(v) = preScale * S(v) * postScale, where:
        v is the scaling vector
        S(v) is: S(v)[0][0] = v[0], S(v)[1][1] = v[1], S(v)[2][2] = v[2]
        \endverbatim
     *
     *  \param preScale the pre-scale transformation
     *  \param postScale the post-scale trasnformations
     *
     *  \return RWCOMM_SUCCESS if successful, RWCOMM_FAIL otherwise.
     */
    virtual RwCommError     GetScalePivots(RwCommMatrix & preScale, RwCommMatrix & postScale) const { return RWCOMM_NOT_IMPLEMENTED; }

protected:
    RwCommTransform*	    m_pParent;
	vector<RwCommTransform*> m_vChildren;
    RwCommShape*            m_pShape;
};

#endif // !defined(AFX_RWCOMMTRANSFORM_H__07D1AA21_9292_4CE0_B204_185BD55B9BA9__INCLUDED_)