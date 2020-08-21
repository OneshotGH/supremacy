#pragma once

// pre-declares.
class CRecvProxyData;
class RecvProp;
class RecvTable;

// prototypes.
// these are networkable entity ptrs.
using CreateClientClass_t = void*( __cdecl* )( int index, int serial );
using CreateEvent_t       = void*( __cdecl* )( );

// other prototypes.
using ArrayLengthRecvProxy_t  = void( __cdecl* )( void* ptr, int id, int len );
using RecvVarProxy_t          = void( __cdecl* )( CRecvProxyData* data, void* struct_ptr, void* out );
using DataTableRecvVarProxy_t = void( __cdecl* )( RecvProp* prop, void** out, void* data, int id );

// types of props.
enum SendPropType {
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_String,
	DPT_Array,
	DPT_DataTable
};

class RecvProp {
public:
	char					*m_pVarName;
	int						 m_RecvType;
	int						 m_Flags;
	int						 m_StringBufferSize;
	bool					 m_bInsideArray;
	const void*				 m_pExtraData;
	RecvProp				*m_pArrayProp;
	ArrayLengthRecvProxy_t	 m_ArrayLengthProxy;
	RecvVarProxy_t			 m_ProxyFn;
	DataTableRecvVarProxy_t	 m_DataTableProxyFn;
	RecvTable				*m_pDataTable;
	int						 m_Offset;
	int						 m_ElementStride;
	int						 m_nElements;
	const char				*m_pParentArrayPropName;
};

class RecvTable {
public:
	RecvProp		*m_pProps;
	int				 m_nProps;
	void*			 m_pDecoder;
	char			*m_pNetTableName;
	bool			 m_bInitialized;
	bool			 m_bInMainList;
};

class ClientClass {
public:
	CreateClientClass_t m_pCreate;
	CreateEvent_t	    m_pCreateEvent;
	char*				m_pNetworkName;
	RecvTable*			m_pRecvTable;
	ClientClass*		m_pNext;
	int					m_ClassID;
};

class DVariant {
public:
	union {
		float	     m_Float;
		long	     m_Int;
		char		*m_pString;
		void		*m_pData;
		float	     m_Vector[ 3 ];
		long long	 m_Int64;
	};

	SendPropType     m_Type;
};

class CRecvProxyData {
public:
	const RecvProp	*m_pRecvProp;
	DVariant		 m_Value;
	int				 m_iElement;
	int				 m_ObjectID;
};