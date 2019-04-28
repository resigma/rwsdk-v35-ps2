// RwMIAttributes.h: interface for the RwMIAttributes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RWMIATTRIBUTES_H__36C1C66B_9726_4579_831D_EE4D626EFD84__INCLUDED_)
#define AFX_RWMIATTRIBUTES_H__36C1C66B_9726_4579_831D_EE4D626EFD84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RwMI.h"
#include "RwCommObject.h"
#include "RwCommAnimatable.h"
#include "RwCommUserData.h"

struct RwMIAttrContainer
{
    vector<int>     m_vInts;
    vector<float>   m_vFloats;
    vector<string>  m_vStrings;
};

/**
*   \ingroup miscenegraph
*
*   This is the base class for all MI objects that need to cache user attributes and user data.
*
*/
class RWMI_API RwMIAttributes  
{
public:
	RwMIAttributes();
	virtual ~RwMIAttributes();

    void AddAttr(const string& name, int value);
    void AddAttr(const string& name, float value);
    void AddAttr(const string& name, const string& value);

    RwCommError GetAttr(const string& name, int& value, int index = 0);
    RwCommError GetAttr(const string& name, float& value, int index = 0);
    RwCommError GetAttr(const string& name, string& value, int index = 0);
    RwCommError GetAttrNames(vector<string>& vNames, vector<RwCommAnimatable::AttributeType> &vAttributeTypes);

    // User data
    RwCommError GetUserData(RwCommUserDataCollection &userDataColl);

    // Get a reference to the user data collection
    RwCommUserDataCollection &GetUserDataCollection() { return m_usrDataCollection; }
    
protected:

    map<string, RwMIAttrContainer>  m_mAttributes;
    RwCommUserDataCollection        m_usrDataCollection;

};

#endif // !defined(AFX_RWMIATTRIBUTES_H__36C1C66B_9726_4579_831D_EE4D626EFD84__INCLUDED_)
