#ifndef PRUTENGINE_METAL_RENDERER_H
#define PRUTENGINE_METAL_RENDERER_H

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>
#import <Metal/Metal.h>
#import <functional>
#import "../../data/GraphicsProgram.hpp"
#import <memory>
#import <vector>
#import "../../data/Shader.hpp"
#import "../../Renderer.hpp"


// Protocol abstracting the platform specific view in order to keep the Renderer
//   class independent from platform
@protocol RenderDestinationProvider

@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;
@property (nonatomic, readonly, nullable) id<MTLDrawable> currentDrawable;

@property (nonatomic) MTLPixelFormat colorPixelFormat;
@property (nonatomic) MTLPixelFormat depthStencilPixelFormat;
@property (nonatomic) NSUInteger sampleCount;

@end


@interface MacMetalRenderer : NSObject

-(nonnull instancetype)initWithMetalDevice:(nonnull id<MTLDevice>)device
                 renderDestinationProvider:(nonnull id<RenderDestinationProvider>)renderDestinationProvider;

- (void)drawRectResized:(CGSize)size;

-(_Nonnull id<MTLDevice> ) getDevice;

-(_Nonnull id<RenderDestinationProvider>) getRenderDestinationProvider;

-(_Nonnull id<MTLLibrary>) getDefaultLibrary;

-(MTLVertexDescriptor*_Nonnull) getVertexDescriptor;
- (void)update;

@end

namespace PrutEngine{
    namespace Data{
        
        
        class MetalShaderData : public PrutEngine::Data::ShaderData{
            private:
            _Nonnull id<MTLFunction>  metalFunction;
            public:
            MetalShaderData(_Nonnull id<MTLFunction> metalFunction);
            MetalShaderData(MacMetalRenderer* _Nonnull  renderer, const std::string& name);
            _Nonnull id<MTLFunction> getMetalFunction() const;
        };
        
        class MetalPipeline : public PrutEngine::Data::GraphicsProgram{
            private:
            _Nonnull id<MTLRenderPipelineState> pipeline;
            public:
            MetalPipeline(const std::string& name, const std::vector<std::shared_ptr<PrutEngine::Data::Shader>> &shaders,MacMetalRenderer* _Nonnull renderer);
            _Nonnull id<MTLRenderPipelineState>  getPipeline() const;
        };
    }
    
    class MetalRenderer : public PrutEngine::Renderer{
        _Nonnull id<MTLBuffer> vertexBuffer;
       _Nonnull id<MTLBuffer> indexBuffer;
    public:
        MetalRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program);
    };
    
    
}



#endif


