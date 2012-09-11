// FEDeformer Plugin
// Initial code generated by Softimage SDK Wizard
// Executed Tue Sep 11 15:05:16 UTC+0100 2012 by Helge Mathee
// 
#include <xsi_application.h>
#include <xsi_context.h>
#include <xsi_pluginregistrar.h>
#include <xsi_status.h>

#include <xsi_icenodecontext.h>
#include <xsi_icenodedef.h>
#include <xsi_command.h>
#include <xsi_factory.h>
#include <xsi_longarray.h>
#include <xsi_doublearray.h>
#include <xsi_math.h>
#include <xsi_vector2f.h>
#include <xsi_vector3f.h>
#include <xsi_vector4f.h>
#include <xsi_matrix3f.h>
#include <xsi_matrix4f.h>
#include <xsi_rotationf.h>
#include <xsi_quaternionf.h>
#include <xsi_color4f.h>
#include <xsi_shape.h>
#include <xsi_icegeometry.h>
#include <xsi_iceportstate.h>
#include <xsi_indexset.h>
#include <xsi_dataarray.h>
#include <xsi_dataarray2D.h>

// Fabric Engine Includes
#include <FabricEngine/Core.h>

// Defines port, group and map identifiers used for registering the ICENode
enum IDs
{
	ID_IN_scalar = 0,
	ID_IN_vec3 = 1,
	ID_IN_quat = 2,
	ID_IN_xfo = 3,
	ID_IN_scalarArray = 4,
	ID_IN_vec3Array = 5,
	ID_G_100 = 100,
	ID_G_101 = 101,
	ID_G_102 = 102,
	ID_G_103 = 103,
	ID_G_104 = 104,
	ID_G_105 = 105,
	ID_OUT_result = 200,
	ID_TYPE_CNS = 400,
	ID_STRUCT_CNS,
	ID_CTXT_CNS,
	ID_UNDEF = ULONG_MAX
};

XSI::CStatus Register_FEDeformer( XSI::PluginRegistrar& in_reg );

using namespace XSI; 

struct FabricEngineUserData {
   FabricEngine::Core::Client * client;
};

SICALLBACK XSILoadPlugin( PluginRegistrar& in_reg )
{
	in_reg.PutAuthor(L"Helge Mathee");
	in_reg.PutName(L"FE Deformer Plugin");
	in_reg.PutVersion(1,0);

	Register_FEDeformer( in_reg );

	return CStatus::OK;
}

SICALLBACK XSIUnloadPlugin( const PluginRegistrar& in_reg )
{
	CString strPluginName;
	strPluginName = in_reg.GetName();
	Application().LogMessage(strPluginName + L" has been unloaded.",siVerboseMsg);
	return CStatus::OK;
}

CStatus Register_FEDeformer( PluginRegistrar& in_reg )
{
	ICENodeDef nodeDef;
	nodeDef = Application().GetFactory().CreateICENodeDef(L"FEDeformer",L"FEDeformer");

	CStatus st;
	st = nodeDef.PutColor(73,143,187);
	st.AssertSucceeded( ) ;

	st = nodeDef.PutThreadingModel(XSI::siICENodeSingleThreading);
	st.AssertSucceeded( ) ;

	// Add input ports and groups.
	st = nodeDef.AddPortGroup(ID_G_100, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddPortGroup(ID_G_101, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddPortGroup(ID_G_102, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddPortGroup(ID_G_103, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddPortGroup(ID_G_104, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddPortGroup(ID_G_105, 1, 10);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_scalar,ID_G_100,siICENodeDataFloat,siICENodeStructureSingle,siICENodeContextAny,L"scalar",L"scalar",0,CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_vec3,ID_G_101,siICENodeDataVector3,siICENodeStructureSingle,siICENodeContextAny,L"vec3",L"vec3",MATH::CVector3f(1.0,1.0,1.0),CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_quat,ID_G_102,siICENodeDataQuaternion,siICENodeStructureSingle,siICENodeContextAny,L"quat",L"quat",MATH::CQuaternionf(1.0,1.0,1.0,1.0),CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_xfo,ID_G_103,siICENodeDataMatrix44,siICENodeStructureSingle,siICENodeContextAny,L"xfo",L"xfo",MATH::CMatrix4f(1.0,0.0,0.0,1.0, 0.0,1.0,0.0,1.0, 0.0,0.0,1.0,1.0, 0.0,0.0,0.0,1.0 ),CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_scalarArray,ID_G_104,siICENodeDataFloat,siICENodeStructureArray,siICENodeContextAny,L"scalarArray",L"scalarArray",0,CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	st = nodeDef.AddInputPort(ID_IN_vec3Array,ID_G_105,siICENodeDataVector3,siICENodeStructureArray,siICENodeContextAny,L"vec3Array",L"vec3Array",MATH::CVector3f(1.0,1.0,1.0),CValue(),CValue(),ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	// Add output ports.
	st = nodeDef.AddOutputPort(ID_OUT_result,siICENodeDataVector3,siICENodeStructureSingle,siICENodeContextComponent0D,L"result",L"result",ID_UNDEF,ID_UNDEF,ID_UNDEF);
	st.AssertSucceeded( ) ;

	PluginItem nodeItem = in_reg.RegisterICENode(nodeDef);
	nodeItem.PutCategories(L"Fabric Engine");

	return CStatus::OK;
}


SICALLBACK FEDeformer_Evaluate( ICENodeContext& in_ctxt )
{
	// The current output port being evaluated...
	ULONG out_portID = in_ctxt.GetEvaluatedOutputPortID( );
  
	switch( out_portID )
	{		
		case ID_OUT_result :
		{
			// Get the output port array ...			
			CDataArrayVector3f outData( in_ctxt );
			
 			// Get the input data buffers for each port
			CDataArrayFloat scalarData( in_ctxt, ID_IN_scalar );
			CDataArrayVector3f vec3Data( in_ctxt, ID_IN_vec3 );
			CDataArrayQuaternionf quatData( in_ctxt, ID_IN_quat );
			CDataArrayMatrix4f xfoData( in_ctxt, ID_IN_xfo );
			CDataArray2DFloat scalarArrayData( in_ctxt, ID_IN_scalarArray );
			CDataArray2DVector3f vec3ArrayData( in_ctxt, ID_IN_vec3Array );

 			// We need a CIndexSet to iterate over the data 		

			// Note: Specific CIndexSet for scalar is required in single-threading mode			
			CIndexSet scalarIndexSet( in_ctxt, ID_IN_scalar );
			for(CIndexSet::Iterator itscalar = scalarIndexSet.Begin(); itscalar.HasNext(); itscalar.Next())
			{
				Application().LogMessage( CString( scalarData[ itscalar ] ) );
			}

			// Note: Specific CIndexSet for vec3 is required in single-threading mode			
			CIndexSet vec3IndexSet( in_ctxt, ID_IN_vec3 );
			for(CIndexSet::Iterator itvec3 = vec3IndexSet.Begin(); itvec3.HasNext(); itvec3.Next())
			{
				Application().LogMessage( CString( vec3Data[ itvec3 ] ) );
			}

			// Note: Specific CIndexSet for quat is required in single-threading mode			
			CIndexSet quatIndexSet( in_ctxt, ID_IN_quat );
			for(CIndexSet::Iterator itquat = quatIndexSet.Begin(); itquat.HasNext(); itquat.Next())
			{
				Application().LogMessage( CString( quatData[ itquat ] ) );
			}

			// Note: Specific CIndexSet for xfo is required in single-threading mode			
			CIndexSet xfoIndexSet( in_ctxt, ID_IN_xfo );
			for(CIndexSet::Iterator itxfo = xfoIndexSet.Begin(); itxfo.HasNext(); itxfo.Next())
			{
				Application().LogMessage( CString( xfoData[ itxfo ] ) );
			}

			// Note: Specific CIndexSet for scalarArray is required in single-threading mode
			CIndexSet scalarArrayIndexSet( in_ctxt, ID_IN_scalarArray );
			for (CIndexSet::Iterator itscalarArray = scalarArrayIndexSet.Begin(); itscalarArray.HasNext(); itscalarArray.Next())
			{
				CDataArray2DFloat::Accessor scalarArraySubArray = scalarArrayData[itscalarArray];
				for (ULONG i=0; i<scalarArraySubArray.GetCount( ); i++)
				{
					Application().LogMessage( CString( scalarArraySubArray[i] ) );
				}
			}

			// Note: Specific CIndexSet for vec3Array is required in single-threading mode
			CIndexSet vec3ArrayIndexSet( in_ctxt, ID_IN_vec3Array );
			for (CIndexSet::Iterator itvec3Array = vec3ArrayIndexSet.Begin(); itvec3Array.HasNext(); itvec3Array.Next())
			{
				CDataArray2DVector3f::Accessor vec3ArraySubArray = vec3ArrayData[itvec3Array];
				for (ULONG i=0; i<vec3ArraySubArray.GetCount( ); i++)
				{
					Application().LogMessage( CString( vec3ArraySubArray[i] ) );
				}
			}
		}
		break;
		
		// Other output ports...
	};
	
	return CStatus::OK;
}

SICALLBACK FEDeformer_Init( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );

   // allocate userdata
   FabricEngineUserData * usrData = new FabricEngineUserData();
   usrData->client = new FabricEngine::Core::Client(true);

   CValue val = (CValue::siPtrType) usrData;
   ctxt.PutUserData( val ) ;

	return CStatus::OK;
}

SICALLBACK FEDeformer_Term( CRef& in_ctxt )
{
	Context ctxt( in_ctxt );

   CValue val = ctxt.GetUserData();
   FabricEngineUserData * usrData = (FabricEngineUserData*)(CValue::siPtrType)val;

   // free all objects
   delete(usrData->client);
   delete(usrData);

	return CStatus::OK;
}

