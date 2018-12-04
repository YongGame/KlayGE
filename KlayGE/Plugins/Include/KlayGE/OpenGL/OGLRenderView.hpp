// OGLRenderView.hpp
// KlayGE OpenGL渲染视图类 头文件
// Ver 3.9.0
// 版权所有(C) 龚敏敏, 2006-2009
// Homepage: http://www.klayge.org
//
// 3.9.0
// 支持Texture Array (2009.8.5)
//
// 3.3.0
// 初次建立 (2006.5.31)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#ifndef _OGLRENDERVIEW_HPP
#define _OGLRENDERVIEW_HPP

#pragma once

#include <KlayGE/RenderView.hpp>
#include <KlayGE/Texture.hpp>

#include <KlayGE/OpenGL/OGLTexture.hpp>

namespace KlayGE
{
	class OGLRenderTargetView : public RenderTargetView
	{
	public:
		OGLRenderTargetView();
		virtual ~OGLRenderTargetView();

		GLuint GLTexture() const
		{
			return gl_tex_;
		}

	protected:
		void DoClearColor(Color const & clr);
		void DoDiscardColor();

	protected:
		GLuint gl_tex_;
		GLuint gl_fbo_;
		GLuint index_;
	};

	class OGLDepthStencilView : public DepthStencilView
	{
	public:
		OGLDepthStencilView();
		virtual ~OGLDepthStencilView();

		void ClearDepth(float depth) override;
		void ClearStencil(int32_t stencil) override;
		void ClearDepthStencil(float depth, int32_t stencil) override;

		GLuint GLTexture() const
		{
			return gl_tex_;
		}

	protected:
		void DoClearDepthStencil(uint32_t flags, float depth, int32_t stencil);
		void DoDiscardDepthStencil();

	protected:
		GLuint gl_tex_;
		GLuint gl_fbo_;
	};

	class OGLScreenRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLScreenRenderTargetView(uint32_t width, uint32_t height, ElementFormat pf);

		void ClearColor(Color const & clr) override;

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
	};

	typedef std::shared_ptr<OGLScreenRenderTargetView> OGLScreenRenderTargetViewPtr;


	class OGLScreenDepthStencilView : public OGLDepthStencilView
	{
	public:
		OGLScreenDepthStencilView(uint32_t width, uint32_t height, ElementFormat pf);

		void Discard() override;

		void OnAttached(FrameBuffer& fb) override;
		void OnDetached(FrameBuffer& fb) override;
	};

	typedef std::shared_ptr<OGLScreenDepthStencilView> OGLScreenDepthStencilViewPtr;


	class OGLTexture1DRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLTexture1DRenderTargetView(TexturePtr const & texture_1d, ElementFormat pf, int array_index, int array_size, int level);

		void ClearColor(Color const & clr) override;

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;

	private:
		int array_index_;
		int array_size_;
		int level_;
	};

	typedef std::shared_ptr<OGLTexture1DRenderTargetView> OGLTexture1DRenderTargetViewPtr;


	class OGLTexture2DRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLTexture2DRenderTargetView(TexturePtr const & texture_2d, ElementFormat pf, int array_index, int array_size, int level);

		void ClearColor(Color const & clr) override;

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;

	private:
		int array_index_;
		int array_size_;
		int level_;
	};

	typedef std::shared_ptr<OGLTexture2DRenderTargetView> OGLTexture2DRenderTargetViewPtr;


	class OGLTexture3DRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLTexture3DRenderTargetView(TexturePtr const & texture_3d, ElementFormat pf, int array_index, uint32_t slice, int level);
		~OGLTexture3DRenderTargetView();

		void ClearColor(Color const & clr);

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;

		void OnUnbind(FrameBuffer& fb, FrameBuffer::Attachment att);

	private:
		void CopyToSlice(FrameBuffer::Attachment att);

	private:
		uint32_t slice_;
		int level_;
		int copy_to_tex_;
		GLuint gl_tex_2d_;
	};

	typedef std::shared_ptr<OGLTexture3DRenderTargetView> OGLTexture3DRenderTargetViewPtr;


	class OGLTextureCubeRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLTextureCubeRenderTargetView(TexturePtr const & texture_cube, ElementFormat pf, int array_index, Texture::CubeFaces face,
			int level);
		OGLTextureCubeRenderTargetView(TexturePtr const & texture_cube, ElementFormat pf, int array_index, int level);

		void ClearColor(Color const & clr) override;

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;

	private:
		Texture::CubeFaces face_;
		int level_;
	};

	typedef std::shared_ptr<OGLTextureCubeRenderTargetView> OGLTextureCubeRenderTargetViewPtr;


	class OGLGraphicsBufferRenderTargetView : public OGLRenderTargetView
	{
	public:
		OGLGraphicsBufferRenderTargetView(GraphicsBufferPtr const & gb, ElementFormat pf, uint32_t forst_elem, uint32_t num_elems);
		~OGLGraphicsBufferRenderTargetView();

		void ClearColor(Color const & clr) override;

		void Discard() override;

		void OnAttached(FrameBuffer& fb, FrameBuffer::Attachment att) override;
		void OnDetached(FrameBuffer& fb, FrameBuffer::Attachment att) override;

		void OnUnbind(FrameBuffer& fb, FrameBuffer::Attachment att);

	private:
		void CopyToGB(FrameBuffer::Attachment att);
	};

	typedef std::shared_ptr<OGLGraphicsBufferRenderTargetView> OGLGraphicsBufferRenderTargetViewPtr;


	class OGLTextureDepthStencilView : public OGLDepthStencilView
	{
	public:
		OGLTextureDepthStencilView(uint32_t width, uint32_t height, ElementFormat pf, uint32_t sample_count, uint32_t sample_quality);
		OGLTextureDepthStencilView(TexturePtr const & texture, ElementFormat pf, int array_index, int array_size, int level);
		~OGLTextureDepthStencilView();

		void Discard() override;

		void OnAttached(FrameBuffer& fb) override;
		void OnDetached(FrameBuffer& fb) override;

	private:
		GLenum target_type_;
		int array_index_;
		int array_size_;
		int level_;
		uint32_t sample_count_, sample_quality_;
		GLuint gl_rbo_;
	};

	typedef std::shared_ptr<OGLTextureDepthStencilView> OGLTextureDepthStencilViewPtr;

	class OGLTextureCubeFaceDepthStencilView : public OGLDepthStencilView
	{
	public:
		OGLTextureCubeFaceDepthStencilView(TexturePtr const & texture_cube, ElementFormat pf, int array_index, Texture::CubeFaces face,
			int level);

		void Discard() override;

		void OnAttached(FrameBuffer& fb) override;
		void OnDetached(FrameBuffer& fb) override;

	private:
		Texture::CubeFaces face_;
		int level_;
	};

	typedef std::shared_ptr<OGLTextureCubeFaceDepthStencilView> OGLTextureCubeFaceDepthStencilViewPtr;
}

#endif			// _OGLRENDERVIEW_HPP
