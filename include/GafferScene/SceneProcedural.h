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

#ifndef GAFFERSCENE_SCENEPROCEDURAL_H
#define GAFFERSCENE_SCENEPROCEDURAL_H

#include "IECore/Renderer.h"

namespace Gaffer
{

IE_CORE_FORWARDDECLARE( Context )

} // namespace Gaffer

namespace GafferScene
{

IE_CORE_FORWARDDECLARE( ScenePlug )

/// The SceneProcedural class passes the output from a ScenePlug to an IECore::Renderer
/// in a tree of nested deferred procedurals.
class SceneProcedural : public IECore::Renderer::Procedural
{

	public :

		IE_CORE_DECLAREMEMBERPTR( SceneProcedural );

		/// A copy of context is taken.
		SceneProcedural( ScenePlugPtr scenePlug, const Gaffer::Context *context, const std::string &scenePath="/" );
		virtual ~SceneProcedural();
		
		virtual Imath::Box3f bound() const;
		virtual void render( IECore::RendererPtr renderer ) const;
				
	protected :
		
		ScenePlugPtr m_scenePlug;
		Gaffer::ContextPtr m_context;
		std::string m_scenePath;
		
};

IE_CORE_DECLAREPTR( SceneProcedural );

} // namespace GafferScene

#endif // GAFFERSCENE_SCENEPROCEDURAL_H
