#ifndef PRUTENGINE_METAL_RENDERER_H
#define PRUTENGINE_METAL_RENDERER_H

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>
#import <Metal/Metal.h>
#import <functional>
#import "../../data/GLProgram.hpp"
#import <memory>
#import <vector>
#import "../../data/Shader.hpp"



// Protocol abstracting the platform specific view in order to keep the Renderer
//   class independent from platform
@protocol RenderDestinationProvider

@property (nonatomic, readonly, nullable) MTLRenderPassDescriptor *currentRenderPassDescriptor;
@property (nonatomic, readonly, nullable) id<MTLDrawable> currentDrawable;

@property (nonatomic) MTLPixelFormat colorPixelFormat;
@property (nonatomic) MTLPixelFormat depthStencilPixelFormat;
@property (nonatomic) NSUInteger sampleCount;

@end




@interface Renderer : NSObject

-(nonnull instancetype)initWithMetalDevice:(nonnull id<MTLDevice>)device
                 renderDestinationProvider:(nonnull id<RenderDestinationProvider>)renderDestinationProvider;

- (void)drawRectResized:(CGSize)size;

-(id<MTLDevice>) getDevice;

-(id<RenderDestinationProvider>) getRenderDestinationProvider;

-(MTLVertexDescriptor *) getVertexDescriptor;
- (void)update;

@end

namespace Prutengine{
    namespace Data{
        
        
        class MetalShaderData : public PrutEngine::Data::ShaderData{
            private:
            id <MTLFunction> metalFunction;
            public:
            MetalShaderData(id<MTLFunction> metalFunction);
            id <MTLFunction> getMetalFunction() const;
        };
        
        class MetalPipeline : public PrutEngine::Data::GraphicsProgram{
            private:
            id <MTLRenderPipelineState> pipeline;
            MTLVertexDescriptor* mtlVertexDescriptor;
            public:
            MetalPipeline(const std::string& name,const std::vector<std::shared_ptr<PrutEngine::Data::Shader>> &shaders,Renderer* renderer);
            id <MTLRenderPipelineState> getPipeline() const;
        };
    }
}

#endif


