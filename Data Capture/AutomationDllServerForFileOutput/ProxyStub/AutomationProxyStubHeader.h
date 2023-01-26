

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for AutomationServerTypeLib.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AutomationProxyStubHeader_h__
#define __AutomationProxyStubHeader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAutomationFileWriter_FWD_DEFINED__
#define __IAutomationFileWriter_FWD_DEFINED__
typedef interface IAutomationFileWriter IAutomationFileWriter;

#endif 	/* __IAutomationFileWriter_FWD_DEFINED__ */


#ifndef __CAutomationFileWriter_FWD_DEFINED__
#define __CAutomationFileWriter_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAutomationFileWriter CAutomationFileWriter;
#else
typedef struct CAutomationFileWriter CAutomationFileWriter;
#endif /* __cplusplus */

#endif 	/* __CAutomationFileWriter_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IAutomationFileWriter_INTERFACE_DEFINED__
#define __IAutomationFileWriter_INTERFACE_DEFINED__

/* interface IAutomationFileWriter */
/* [oleautomation][dual][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAutomationFileWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F5BDE086-36D5-4d01-99B8-2D4882D90DB6")
    IAutomationFileWriter : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE WriteIntoFile( 
            /* [in] */ BSTR __MIDL__IAutomationFileWriter0000,
            /* [in] */ BSTR __MIDL__IAutomationFileWriter0001) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IAutomationFileWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAutomationFileWriter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAutomationFileWriter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAutomationFileWriter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAutomationFileWriter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAutomationFileWriter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAutomationFileWriter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAutomationFileWriter * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *WriteIntoFile )( 
            IAutomationFileWriter * This,
            /* [in] */ BSTR __MIDL__IAutomationFileWriter0000,
            /* [in] */ BSTR __MIDL__IAutomationFileWriter0001);
        
        END_INTERFACE
    } IAutomationFileWriterVtbl;

    interface IAutomationFileWriter
    {
        CONST_VTBL struct IAutomationFileWriterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAutomationFileWriter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAutomationFileWriter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAutomationFileWriter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAutomationFileWriter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAutomationFileWriter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAutomationFileWriter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAutomationFileWriter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAutomationFileWriter_WriteIntoFile(This,__MIDL__IAutomationFileWriter0000,__MIDL__IAutomationFileWriter0001)	\
    ( (This)->lpVtbl -> WriteIntoFile(This,__MIDL__IAutomationFileWriter0000,__MIDL__IAutomationFileWriter0001) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAutomationFileWriter_INTERFACE_DEFINED__ */



#ifndef __AutomationServerTypeLib_LIBRARY_DEFINED__
#define __AutomationServerTypeLib_LIBRARY_DEFINED__

/* library AutomationServerTypeLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AutomationServerTypeLib;

EXTERN_C const CLSID CLSID_CAutomationFileWriter;

#ifdef __cplusplus

class DECLSPEC_UUID("A5F85CE7-D53F-4c66-93D9-00743A87D188")
CAutomationFileWriter;
#endif
#endif /* __AutomationServerTypeLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


