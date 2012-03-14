//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2012, John Haddon. All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//  
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//  
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//  
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//////////////////////////////////////////////////////////////////////////

#include "OpenEXR/ImathBoxAlgo.h"

#include "IECore/AttributeBlock.h"

#include "Gaffer/Context.h"

#include "GafferScene/SceneProcedural.h"
#include "GafferScene/ScenePlug.h"

using namespace std;
using namespace Imath;
using namespace IECore;
using namespace Gaffer;
using namespace GafferScene;

SceneProcedural::SceneProcedural( ScenePlugPtr scenePlug, const Gaffer::Context *context, const std::string &scenePath )
	:	m_scenePlug( scenePlug ), m_context( new Context( *context ) ), m_scenePath( scenePath )
{
	m_context->set( "scene:path", m_scenePath );
}

SceneProcedural::~SceneProcedural()
{
}

Imath::Box3f SceneProcedural::bound() const
{
	Context::Scope scopedContext( m_context );
	Box3f b = m_scenePlug->boundPlug()->getValue();
	M44f t = m_scenePlug->transformPlug()->getValue();
	return transform( b, t );
}

void SceneProcedural::render( RendererPtr renderer ) const
{	
	AttributeBlock attributeBlock( renderer );
	Context::Scope scopedContext( m_context );
		
	renderer->concatTransform( m_scenePlug->transformPlug()->getValue() );
		
	ConstPrimitivePtr primitive = m_scenePlug->geometryPlug()->getValue();
	if( primitive )
	{
		primitive->render( renderer );
	}
	
	ConstStringVectorDataPtr childNames = m_scenePlug->childNamesPlug()->getValue();
	for( vector<string>::const_iterator it=childNames->readable().begin(); it!=childNames->readable().end(); it++ )
	{
		string childScenePath = m_scenePath + "/" + *it;
		renderer->procedural( new SceneProcedural( m_scenePlug, m_context, childScenePath ) );
	}	
}
